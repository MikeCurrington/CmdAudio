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


GeneratorInstance::GeneratorInstance( BaseCountedPtr<GeneratorComponent> component) : GeneratorBase(), m_component(component)
{
    m_inputs = new GeneratorArray();
}

void GeneratorInstance::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    fprintf(stderr, "input instance: %s\n", paramName.c_str());
    
    m_inputs->AddInput(paramName, value );
}

void GeneratorInstance::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateInstance> generatorState = machineState.GetGeneratorState<GeneratorStateInstance>( GetId(), machineState );

    //    fprintf(stderr, "supply instance\n");

    generatorState->m_machineState->PushParameters(m_inputs);
    
    m_component->Supply(this, *generatorState->m_machineState, rDataBuffer, startSample);
    
    generatorState->m_machineState->PopParameters();
}


GeneratorStateInstance::GeneratorStateInstance(int id, MachineState& parentMachineState) : GeneratorStateBase(id)
{
    m_machineState = new MachineState( parentMachineState );
}

GeneratorStateInstance::~GeneratorStateInstance()
{
    delete m_machineState;
}

