//
//  GeneratorFilterHigh.cpp
//  CmdAudio
//
//  Created by Michael Currington on 8/21/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorFilterHigh.h"
#include "MachineState.h"
#include "stdafx.h"
#include "string.h"


GeneratorFilterHigh::GeneratorFilterHigh(const std::string & name) : GeneratorValueTransform(name)
{
}


GeneratorFilterHigh::~GeneratorFilterHigh()
{
}

void GeneratorFilterHigh::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "frequency") == 0)
    {
        m_frequencyGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "resonance") == 0)
    {
        resonanceGenerator = value;
    }
    else
        GeneratorValueTransform::AddInput(paramName, value);
}

float filthigh(float b_in, float cutFreqNorm, float rez, float& b_buf1, float& b_buf2, float& b_buf3, float& b_buf4 )
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
    return b_in - b_buf4;
}

void GeneratorFilterHigh::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateFilterHigh> generatorState = machineState.GetGeneratorState<GeneratorStateFilterHigh>( GetId() );
    
    if (sourceBuffer && m_frequencyGenerator)
    {
        sourceBuffer->Supply(machineState, rDataBuffer, startSample);
        
        BaseCountedPtr<SampleDataBuffer> freqDataBuffer = new SampleDataBuffer(rDataBuffer->GetLength());
        BaseCountedPtr<SampleDataBuffer> resoDataBuffer = new SampleDataBuffer(rDataBuffer->GetLength());
        m_frequencyGenerator->Supply(machineState, freqDataBuffer, startSample);
        resonanceGenerator->Supply(machineState, resoDataBuffer, startSample);
        
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
        {
            rDataBuffer->Get(i) = filthigh( rDataBuffer->Get(i), freqDataBuffer->Get(i) / machineState.GetSampleRate(), resoDataBuffer->Get(i),
                                       generatorState->buf1, generatorState->buf2, generatorState->buf3, generatorState->buf4 );
        }
    }
}



