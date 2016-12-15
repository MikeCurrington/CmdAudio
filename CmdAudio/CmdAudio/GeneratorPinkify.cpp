//
//  GeneratorPinkify.cpp
//  CmdAudio
//
//  Created by Michael Currington on 8/14/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#include "GeneratorPinkify.h"
#include "MachineState.h"


GeneratorPinkify::GeneratorPinkify(const std::string& name, int sampleRate) : GeneratorBase(name)
{
}

void GeneratorPinkify::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "value") == 0)
    {
        this->valueGenerator = value;
    }
    else
        GeneratorBase::AddInput(paramName, value);
}

void GeneratorPinkify::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStatePinkify> generatorState = machineState.GetGeneratorState<GeneratorStatePinkify>( GetId() );
    
    if (valueGenerator)
    {
        float b[7];
        b[0] = generatorState->b[0];
        b[1] = generatorState->b[1];
        b[2] = generatorState->b[2];
        b[3] = generatorState->b[3];
        b[4] = generatorState->b[4];
        b[5] = generatorState->b[5];
        b[6] = generatorState->b[6];
        const float outputScale = 0.25f;//mjc - hack to keep in range somewhat!
        
        valueGenerator->Supply(machineState, rDataBuffer, startSample);
        
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
        {
            float white = rDataBuffer->Get(i);
            b[0] = 0.99886f * b[0] + white * 0.0555179f;
            b[1] = 0.99332f * b[1] + white * 0.0750759f;
            b[2] = 0.96900f * b[2] + white * 0.1538520f;
            b[3] = 0.86650f * b[3] + white * 0.3104856f;
            b[4] = 0.55000f * b[4] + white * 0.5329522f;
            b[5] = -0.7616f * b[5] - white * 0.0168980f;
            rDataBuffer->Get(i) = outputScale * (b[0] + b[1] + b[2] + b[3] + b[4] + b[5] + b[6] + white * 0.5362f);
            b[6] = white * 0.115926f;
        }

        generatorState->b[0] = b[0];
        generatorState->b[1] = b[1];
        generatorState->b[2] = b[2];
        generatorState->b[3] = b[3];
        generatorState->b[4] = b[4];
        generatorState->b[5] = b[5];
        generatorState->b[6] = b[6];
    }
}
