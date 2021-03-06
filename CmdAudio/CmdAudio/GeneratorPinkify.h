//
//  GeneratorPinkify.hpp
//  CmdAudio
//
//  Created by Michael Currington on 8/14/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once
#include "GeneratorBase.h"

class GeneratorPinkify : public GeneratorBase
{
private:
    GeneratorPinkify();		// deliberately not implemented
    
public:
    GeneratorPinkify(const std::string& name, int sampleRate);
    
protected:
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorBase> valueGenerator;
};


class GeneratorStatePinkify : public GeneratorStateBase
{
public:
    GeneratorStatePinkify( int id)
    : GeneratorStateBase(id)
    {
    }
private:
    friend class GeneratorPinkify;
    float b[7] = {0,0,0,0,0,0,0};
};

