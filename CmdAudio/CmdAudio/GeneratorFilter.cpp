//
//  GeneratorFilter.cpp
//  CmdAudio
// Karlsen Fast Ladder filter : http://www.musicdsp.org/archive.php?classid=3
//
//  Created by Michael Currington on 7/30/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorFilter.h"
#include "MachineState.h"
#include "stdafx.h"
#include "string.h"


GeneratorFilter::GeneratorFilter() : GeneratorValueTransform()
{
}


GeneratorFilter::~GeneratorFilter()
{
}

void GeneratorFilter::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "frequency") == 0)
    {
        frequencyGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "resonance") == 0)
    {
        resonanceGenerator = value;
    }
    else
        GeneratorValueTransform::AddInput(paramName, value);
}

float filt(float b_in, float cutFreqNorm, float rez, float& b_buf1, float& b_buf2, float& b_buf3, float& b_buf4 )
{
    float b_cut = (2.0f*M_PI*cutFreqNorm);
    
    float b_rscl = b_buf4;
    if (b_rscl > 1.0f)
    {
        b_rscl = 1.0f;
    }
    b_in = (-b_rscl * rez) + b_in;
    b_buf1 = ((-b_buf1 + b_in) * b_cut) + b_buf1;
    b_buf2 = ((-b_buf2 + b_buf1) * b_cut) + b_buf2;
    b_buf3 = ((-b_buf3 + b_buf2) * b_cut) + b_buf3;
    b_buf4 = ((-b_buf4 + b_buf3) * b_cut) + b_buf4;
    return b_buf4;
}

void GeneratorFilter::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateFilter> generatorState = machineState.GetGeneratorState<GeneratorStateFilter>( GetId() );
    
    if (sourceBuffer && frequencyGenerator)
    {
        sourceBuffer->Supply(machineState, rDataBuffer, startSample);
        
        SampleDataBuffer freqDataBuffer(rDataBuffer.GetLength());
        SampleDataBuffer resoDataBuffer(rDataBuffer.GetLength());
        frequencyGenerator->Supply(machineState, freqDataBuffer, startSample);
        resonanceGenerator->Supply(machineState, resoDataBuffer, startSample);
        
        for (int i = 0; i < rDataBuffer.GetLength(); i++)
        {
            rDataBuffer[i] = filt( rDataBuffer[i], freqDataBuffer[i] / machineState.GetSampleRate(), resoDataBuffer[i],
                                   generatorState->buf1, generatorState->buf2, generatorState->buf3, generatorState->buf4 );
        }
    }
}



