//
//  GeneratorComponent.cpp
//  CmdAudio
//
//  Created by Michael Currington on 11/17/15.
//  Copyright (c) 2015 Doodleoo Games. All rights reserved.
//
#include "GeneratorComponent.h"
#include "GeneratorArray.h"
#include "MachineState.h"


GeneratorComponent::GeneratorComponent(int sampleRate) : GeneratorBase(), parameters(nullptr), source(nullptr)
{
    this->sampleRate = sampleRate;
}

GeneratorComponent::~GeneratorComponent()
{
}

void GeneratorComponent::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "inputs") == 0)
    {
        GeneratorArray * pArray = dynamic_cast<GeneratorArray*>(value.Obj());
        if (pArray != nullptr)
        {
            this->parameters = pArray;
        }
    }
    else if (strcasecmp(paramName.c_str(), "source") == 0)
    {
        this->source = value;
    }
    else
    {
        GeneratorBase::AddInput(paramName, value);
    }
}

void GeneratorComponent::Supply(const GeneratorInstance * parent, MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    source->Supply(machineState, rDataBuffer, startSample);
}


