//
//  GeneratorInstance.cpp
//  CmdAudio
//
//  Created by Michael Currington on 11/24/15.
//  Copyright (c) 2015 Doodleoo Games. All rights reserved.
//

#include "stdafx.h"
#include "GeneratorInstance.h"
#include "GeneratorComponent.h"
#include "MachineState.h"


GeneratorInstance::GeneratorInstance(GeneratorComponent * component) : GeneratorBase(), component(component)
{
    inputs = new GeneratorArray();
}

void GeneratorInstance::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
    fprintf(stderr, "input instance: %s\n", pParamName);
    
    inputs->AddInput(pParamName, value );
}

void GeneratorInstance::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    fprintf(stderr, "supply instance\n");

    machineState.PushParameters(inputs);
    
    component->Supply(this, machineState, rDataBuffer, startSample);
    
    machineState.PopParameters();
}

