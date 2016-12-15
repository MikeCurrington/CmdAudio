//
//  GeneratorMidiChannel.h
//  CmdAudio
//
//  Created by Michael Currington on 8/21/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorBase.h"
#include "GeneratorInstance.h"
#include <vector>

class GeneratorMidiChannel : public GeneratorBase
{
public:
    GeneratorMidiChannel(const std::string& name, int sampleRate);
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorBase> channelGenerator;
    BaseCountedPtr<GeneratorBase> componentGenerator;
};


class GeneratorStateMidiChannel : public GeneratorStateBase
{
public:
    GeneratorStateMidiChannel(int id);
protected:
    friend class GeneratorMidiChannel;
    std::vector< BaseCountedPtr<GeneratorInstance> > m_runningNotes;
};
