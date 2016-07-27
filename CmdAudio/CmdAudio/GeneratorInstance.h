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
    GeneratorInstance(GeneratorComponent * component);
    
protected:
    virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorComponent> component;
    BaseCountedPtr<GeneratorArray> inputs;
};
