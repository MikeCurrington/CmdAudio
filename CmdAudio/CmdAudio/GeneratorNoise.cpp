//
//  GeneratorNoise.cpp
//  CmdAudio
//
//  Created by Michael Currington on 8/14/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorNoise.h"
#include "MachineState.h"


GeneratorNoise::GeneratorNoise(int sampleRate) : GeneratorBase()
{
}

void GeneratorNoise::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    GeneratorBase::AddInput(paramName, value);
}

void GeneratorNoise::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateNoise> generatorState = machineState.GetGeneratorState<GeneratorStateNoise>( GetId() );
    
    int seed = generatorState->m_seed;
    for (int i = 0; i < rDataBuffer.GetLength(); i++)
    {
        seed *= 16807;
        rDataBuffer[i] = seed * 4.6566129e-010f;
    }
    generatorState->m_seed = seed;

}
