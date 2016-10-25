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

    if (strcasecmp(paramName.c_str(), "reset") == 0)
    {
        m_resetGenerator = value;
    }
    else
    {
        m_inputs->AddInput(paramName, value );
    }
}

void GeneratorInstance::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateInstance> generatorState = machineState.GetGeneratorState<GeneratorStateInstance>( GetId(), machineState );
    
    bool running = generatorState->m_running;
    int startOffset = 0;
    int instanceStartSample = generatorState->m_instanceStartSample;
    
    if (m_resetGenerator)
    {
        BaseCountedPtr<SampleDataBuffer> resetDataBuffer = new SampleDataBuffer(rDataBuffer->GetLength());
        m_resetGenerator->Supply(machineState, resetDataBuffer, startSample);

        for(int i=0;i<rDataBuffer->GetLength(); i++)
        {
            if (resetDataBuffer->Get(i) > 0.0f)
            {
                // greater than zero is a trigger
                if (!running)
                {
                    startOffset = i;
                    instanceStartSample = 0;
                    running = true;
                }
            }
            else
            {
                if (running)
                {
                    running = false;
                    int length = i - startOffset;
                    if (length > 0)
                    {
                        BaseCountedPtr<SampleDataBuffer> rSubBuffer = new SampleDataBufferView(rDataBuffer, startOffset, length );
                        generatorState->m_machineState->PushParameters(m_inputs);
                        m_component->Supply(this, *generatorState->m_machineState, rSubBuffer, instanceStartSample);
                        instanceStartSample += length;
                        generatorState->m_machineState->PopParameters();
                    }
                    // we need to reset the generator ready for when retriggered
                    machineState.RemoveGeneratorState( GetId() );
                    generatorState = machineState.GetGeneratorState<GeneratorStateInstance>( GetId(), machineState );
                }
                rDataBuffer->Get(i) = 0.0f;
            }
        }
    }
    if (running)
    {
        // fill in the remaining samples up to the end of the current buffer
        int length = rDataBuffer->GetLength() - startOffset;
        if (length > 0)
        {
            BaseCountedPtr<SampleDataBuffer> rSubBuffer = new SampleDataBufferView(rDataBuffer, startOffset, length );
            generatorState->m_machineState->PushParameters(m_inputs);
            m_component->Supply(this, *generatorState->m_machineState, rSubBuffer, instanceStartSample);
            instanceStartSample += length;
            generatorState->m_machineState->PopParameters();
        }
    }

    generatorState->m_running = running;
    generatorState->m_instanceStartSample = instanceStartSample;
}


GeneratorStateInstance::GeneratorStateInstance(int id, MachineState& parentMachineState) : GeneratorStateBase(id), m_running(true), m_instanceStartSample(0)
{
    m_machineState = new MachineState( parentMachineState );
}

GeneratorStateInstance::~GeneratorStateInstance()
{
    delete m_machineState;
}

