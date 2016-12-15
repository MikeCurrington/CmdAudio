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


GeneratorInstance::GeneratorInstance( const std::string& name, BaseCountedPtr<GeneratorComponent> component) : GeneratorBase(name), m_component(component)
{
    m_inputs = new GeneratorArray(name);
}

void GeneratorInstance::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    fprintf(stderr, "input instance: %s\n", paramName.c_str());

    if (strcasecmp(paramName.c_str(), "reset") == 0)
    {
        m_resetGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "run") == 0)
    {
        m_runGenerator = value;
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
    bool hasReset = generatorState->m_hasReset;
    int startOffset = 0;
    int instanceStartSample = generatorState->m_instanceStartSample;
    
    if (m_runGenerator || m_resetGenerator)
    {
        BaseCountedPtr<SampleDataBuffer> runningDataBuffer;
        if (m_runGenerator)
        {
            runningDataBuffer = new SampleDataBuffer(rDataBuffer->GetLength());
            m_runGenerator->Supply(machineState, runningDataBuffer, startSample);
        }
        BaseCountedPtr<SampleDataBuffer> resetDataBuffer;
        if (m_resetGenerator)
        {
            resetDataBuffer = new SampleDataBuffer(rDataBuffer->GetLength());
            m_resetGenerator->Supply(machineState, resetDataBuffer, startSample);
        }
        
        for(int i=0;i<rDataBuffer->GetLength(); i++)
        {
            if (resetDataBuffer && resetDataBuffer->Get(i) > 0.0f)
            {
                // greater than zero is a reset
                if (!hasReset)
                {
                    fprintf(stderr, "reset %s\n", GetName().c_str() );
                    hasReset = true;
                    
                    if (running)
                    {
                        // do the samples up to this point
                        int length = i - startOffset;
                        if (length > 0)
                        {
                            BaseCountedPtr<SampleDataBuffer> rSubBuffer = new SampleDataBufferView(rDataBuffer, startOffset, length );
                            generatorState->m_machineState->PushParameters( m_inputs, machineState );
                            m_component->Supply(this, *generatorState->m_machineState, rSubBuffer, instanceStartSample);
                            instanceStartSample += length;
                            generatorState->m_machineState->PopParameters();
                        }
                    }
                    // Always reset the generator
                    generatorState->m_machineState->Reset();
                    instanceStartSample = 0;
                    startOffset = i;
                }
            }
            else
            {
                hasReset = false;
            }
            
            if (!runningDataBuffer || runningDataBuffer->Get(i) > 0.0f)
            {
                // greater than zero allows the buffer to run
                if (!running)
                {
                    fprintf(stderr, "unpause %s\n", GetName().c_str() );
                    startOffset = i;
                    running = true;
                }
            }
            else
            {
                if (running)
                {
                    fprintf(stderr, "pause %s\n", GetName().c_str() );
                    running = false;
                    int length = i - startOffset;
                    if (length > 0)
                    {
                        BaseCountedPtr<SampleDataBuffer> rSubBuffer = new SampleDataBufferView(rDataBuffer, startOffset, length );
                        generatorState->m_machineState->PushParameters( m_inputs, machineState );
                        m_component->Supply(this, *generatorState->m_machineState, rSubBuffer, instanceStartSample);
                        instanceStartSample += length;
                        generatorState->m_machineState->PopParameters();
                    }
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
            generatorState->m_machineState->PushParameters(m_inputs, machineState);
            m_component->Supply(this, *generatorState->m_machineState, rSubBuffer, instanceStartSample);
            instanceStartSample += length;
            generatorState->m_machineState->PopParameters();
        }
    }

    generatorState->m_running = running;
    generatorState->m_hasReset = hasReset;
    generatorState->m_instanceStartSample = instanceStartSample;
}


GeneratorStateInstance::GeneratorStateInstance(int id, MachineState& parentMachineState) : GeneratorStateBase(id), m_running(true), m_hasReset(false), m_instanceStartSample(0)
{
    m_machineState = new MachineState( parentMachineState );
}

GeneratorStateInstance::~GeneratorStateInstance()
{
    delete m_machineState;
}

