//
//  OutputAudioQueue.hpp
//  CmdAudio
//
//  Created by Michael Currington on 7/22/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "OutputBase.h"
#include "MachineState.h"
#include <AudioToolbox/AudioQueue.h>

class AudioQueue;
class AudioQueueBuffer;


class OutputAudioQueue : public OutputBase
{
public:
    OutputAudioQueue(int sampleRate);
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Write(MachineState& machineState, int outputLength) override;
    
protected:
    ~OutputAudioQueue();
    
    static void BufferFillCallback(void *custom_data, AudioQueueRef queue, AudioQueueBufferRef buffer);
    bool FillBuffer( AudioQueueBuffer* buffer );
    
protected:
    BaseCountedPtr<GeneratorBase> m_sourceGenerator;
    BaseCountedPtr<SampleDataBuffer> m_output;
    int m_outputLength;
    int m_sampleRate;
    int m_currentSampleOffset;
    MachineState m_machineState;
};
