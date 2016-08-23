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
#define BUFFER_SIZE 4096
#define NUM_BUFFERS 8


OutputAudioQueue::OutputAudioQueue(int sampleRate)
    : OutputBase()
    , m_sourceGenerator(nullptr)
    , m_output(nullptr)
    , m_currentSampleOffset(0)
    , m_sampleRate(sampleRate)
{
}

OutputAudioQueue::~OutputAudioQueue()
{
    delete m_output;
}


void OutputAudioQueue::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(pParamName, "source") == 0)
    {
        this->m_sourceGenerator = value;
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


void OutputAudioQueue::Write(MachineState& machineState, int outputLength)
{
    if (m_sourceGenerator)
    {
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

        m_outputLength = outputLength;
        m_machineState = machineState;
        
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
    int bufferLength = buffer->mAudioDataByteSize/sizeof(short);

    if (m_output == nullptr || bufferLength != m_output->GetLength() )
    {
        delete m_output;
        m_output = new SampleDataBuffer(bufferLength);
    }
    m_sourceGenerator->Supply(m_machineState, *m_output, m_currentSampleOffset);
    
    short* casted_buffer = static_cast<short*>(buffer->mAudioData);
    
    int remainingLength = m_outputLength - m_currentSampleOffset;

    int copySamples = (remainingLength > bufferLength) ? bufferLength : remainingLength;
    
    int i = 0;
    for( ;i<copySamples;i++ )
    {
        short o = (short)(fmax(fmin(m_output->Get(i), 1.0f), -1.0f) * 32767.0f);
        casted_buffer[i] = o;
    }
    for( ;i<bufferLength;i++ )
    {
        casted_buffer[i] = 0;
    }

    remainingLength -= copySamples;
    m_currentSampleOffset += copySamples;

    return remainingLength > 0;
}

