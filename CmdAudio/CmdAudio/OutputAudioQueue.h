//
//  OutputAudioQueue.hpp
//  CmdAudio
//
//  Created by Michael Currington on 7/22/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "OutputBase.h"
#include <AudioToolbox/AudioQueue.h>

class AudioQueue;
class AudioQueueBuffer;


class OutputAudioQueue : public OutputBase
{
public:
    OutputAudioQueue(int sampleRate);
    
    virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Write(int outputLength) override;
    
protected:
    ~OutputAudioQueue();
    
    static void BufferFillCallback(void *custom_data, AudioQueueRef queue, AudioQueueBufferRef buffer);
    bool FillBuffer( AudioQueueBuffer* buffer );
    
protected:
    BaseCountedPtr<GeneratorBase> sourceGenerator;
    SampleDataBuffer* output;
    int currentSampleOffset;
};
