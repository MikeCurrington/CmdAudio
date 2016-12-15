//
//  GeneratorInstance.h
//  CmdAudio
//
//  Created by Michael Currington on 11/24/15.
//  Copyright (c) 2015 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorBase.h"
#include "GeneratorArray.h"
#include "GeneratorComponent.h"

class GeneratorInstance : public GeneratorBase
{
private:
    GeneratorInstance();		// deliberately not implemented
public:
    GeneratorInstance(const std::string & name, BaseCountedPtr<GeneratorComponent> component);
    
protected:
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorComponent> m_component;
    BaseCountedPtr<GeneratorArray> m_inputs;
    BaseCountedPtr<GeneratorBase> m_resetGenerator;
    BaseCountedPtr<GeneratorBase> m_runGenerator;
};

class GeneratorStateInstance : public GeneratorStateBase
{
public:
    GeneratorStateInstance(int id, MachineState& parentMachineState);
    ~GeneratorStateInstance();
protected:
    friend class GeneratorInstance;
    
    bool m_running;     // set when the instance is running (false when 'paused')
    bool m_hasReset;    // set when the instance has been reset and the 'reset' input is still high (cleared when input goes low, ready for next reset)
    int m_instanceStartSample;
    
    MachineState* m_machineState;
};
