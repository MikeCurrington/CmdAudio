//
//  GeneratorHold.cpp
//  CmdAudio
//
//  Created by Michael Currington on 10/6/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorHold.h"
#include "MachineState.h"
//#include "stdafx.h"
//#include "string.h"


GeneratorHold::GeneratorHold(const std::string& name) : GeneratorValueTransform(name)
{
}

GeneratorHold::~GeneratorHold()
{
}

void GeneratorHold::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "hold") == 0)
    {
        holdGenerator = value;
    }
    else
        GeneratorValueTransform::AddInput(paramName, value);
}

void GeneratorHold::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateHold> generatorState = machineState.GetGeneratorState<GeneratorStateHold>( GetId() );
    
    if (sourceBuffer && holdGenerator)
    {
        ///TODO: restructure to take advantage of not needing to Supply the inputs for all the time are holding
        sourceBuffer->Supply(machineState, rDataBuffer, startSample);
        
        bool holding = generatorState->GetHolding();
        float fHoldValue = generatorState->GetValue();
        
        BaseCountedPtr<SampleDataBuffer> resetDataBuffer( new SampleDataBuffer(rDataBuffer->GetLength()) );
        holdGenerator->Supply(machineState, resetDataBuffer, startSample);
        
        int i;
        for (i = 0; i < rDataBuffer->GetLength(); i++)
        {
            if (resetDataBuffer->Get(i) > 0.0f)
            {
                // leave output as it is (reset state)
                holding = false;
            }
            else
            {
                if (!holding)
                {
                    holding = true;
                    if (i > 0)
                    {
                        fHoldValue = rDataBuffer->Get(i-1);
                    }
                }
                // holding - copy hold value to output
                rDataBuffer->Get(i) = fHoldValue;
            }
        }
        if (!holding && i > 0)
        {
            // if we are not holding then store off the last output value incase we want to hold on the first sample of the next buffer
            generatorState->Set( holding, rDataBuffer->Get(i-1) );
        }
        else
        {
            generatorState->Set( holding, fHoldValue );
        }
    }
}



