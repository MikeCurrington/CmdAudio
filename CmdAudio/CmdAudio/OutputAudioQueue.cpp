//
//  OutputAudioQueue.cpp
//  CmdAudio
//
//  Created by Michael Currington on 7/22/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "OutputAudioQueue.h"
#include "MachineState.h"
#include <cmath>

#include <AudioToolbox/AudioQueue.h>
#include <CoreAudio/CoreAudioTypes.h>
#include <CoreFoundation/CFRunLoop.h>

#define SAMPLE_RATE 22050
#define BUFFER_SIZE 128000
#define NUM_BUFFERS 2


OutputAudioQueue::OutputAudioQueue(int sampleRate)
    : OutputBase()
    , sourceGenerator(nullptr)
    , output(nullptr)
    , currentSampleOffset(0)
{
}

OutputAudioQueue::~OutputAudioQueue()
{
    delete output;
}


void OutputAudioQueue::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(pParamName, "source") == 0)
    {
        this->sourceGenerator = value;
    }
}


void OutputAudioQueue::BufferFillCallback(void *custom_data, AudioQueueRef queue, AudioQueueBufferRef buffer)
{
    OutputAudioQueue* qthis = (OutputAudioQueue*)custom_data;
    
    bool samplesRemaining = qthis->FillBuffer( buffer );

    AudioQueueEnqueueBuffer(queue, buffer, 0, NULL);
    
    if (!samplesRemaining)
    {
        AudioQueueStop(queue, false);
        AudioQueueDispose(queue, false);
        CFRunLoopStop(CFRunLoopGetCurrent());
    }
}


void OutputAudioQueue::Write(int outputLength)
{
    if (sourceGenerator)
    {
        output = new SampleDataBuffer(outputLength);
        MachineState machineState;
        sourceGenerator->Supply(machineState, *output, 0);
        
        AudioStreamBasicDescription format;
        format.mSampleRate       = SAMPLE_RATE;
        format.mFormatID         = kAudioFormatLinearPCM;
        format.mFormatFlags      = kLinearPCMFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
        format.mBitsPerChannel   = 8 * sizeof(short);
        format.mChannelsPerFrame = 1;
        format.mBytesPerFrame    = sizeof(short) * 1;
        format.mFramesPerPacket  = 1;
        format.mBytesPerPacket   = format.mBytesPerFrame * format.mFramesPerPacket;
        format.mReserved         = 0;
        
        AudioQueueRef queue;
        AudioQueueNewOutput(&format, BufferFillCallback, this, CFRunLoopGetCurrent(), kCFRunLoopCommonModes, 0, &queue);
        AudioQueueBufferRef buffer[NUM_BUFFERS];
        
        for(int i=0;i<NUM_BUFFERS;i++)
        {
            AudioQueueAllocateBuffer(queue, BUFFER_SIZE, &buffer[i]);
            buffer[i]->mAudioDataByteSize = BUFFER_SIZE;
            
            BufferFillCallback(this, queue, buffer[i]);
        }
        
        AudioQueueStart(queue, NULL);
        CFRunLoopRun();

        for(int i=0;i<NUM_BUFFERS;i++)
        {
            AudioQueueFreeBuffer(queue, buffer[i]);
        }
        AudioQueueDispose(queue, false);
        //        output.GetLength()
    }
}

bool OutputAudioQueue::FillBuffer( AudioQueueBufferRef buffer )
{
    short* casted_buffer = static_cast<short*>(buffer->mAudioData);
    
    int outputLength = output->GetLength();
    int remainingLength = outputLength - currentSampleOffset;
    int bufferLength = buffer->mAudioDataByteSize/sizeof(short);

    int copySamples = (remainingLength > bufferLength) ? bufferLength : remainingLength;
    
    int i = 0;
    for( ;i<copySamples;i++ )
    {
        short o = (short)(fmax(fmin(output->Get(i+currentSampleOffset), 1.0f), -1.0f) * 32767.0f);
        casted_buffer[i] = o;
    }
    for( ;i<bufferLength;i++ )
    {
        casted_buffer[i] = 0;
    }

    remainingLength -= copySamples;
    currentSampleOffset += copySamples;

    return remainingLength > 0;
}

