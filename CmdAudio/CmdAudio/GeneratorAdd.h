//
//  GeneratorAdd.hpp
//  CmdAudio
//
//  Created by Michael Currington on 7/16/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorBase.h"
#include "GeneratorArray.h"

class GeneratorAdd : public GeneratorBase
{
public:
    GeneratorAdd(const std::string & name);
    virtual ~GeneratorAdd();
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    
protected:
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

    BaseCountedPtr<GeneratorBase> generators;
};
