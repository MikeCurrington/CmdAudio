//
//  GeneratorFilterComb.cpp
//  CmdAudio
//
//  Feedforward comb filter.
//
//  Created by Michael Currington on 8/16/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorFilterComb.h"
#include "MachineState.h"


GeneratorFilterComb::GeneratorFilterComb() : GeneratorValueTransform()
{
}

GeneratorFilterComb::~GeneratorFilterComb()
{
}

void GeneratorFilterComb::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "delay") == 0)
    {
        delayGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "feedback") == 0)
    {
        feedbackGainGenerator = value;
    }
    else
        GeneratorValueTransform::AddInput(paramName, value);
}

void GeneratorFilterComb::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateFilterComb> generatorState = machineState.GetGeneratorState<GeneratorStateFilterComb>( GetId() );
    
    if (delayGenerator && feedbackGainGenerator)
    {
        sourceBuffer->Supply(machineState, rDataBuffer, startSample);
        
        SampleDataBuffer delayDataBuffer(rDataBuffer.GetLength());
        SampleDataBuffer feedbackDataBuffer(rDataBuffer.GetLength());

        delayGenerator->Supply(machineState, delayDataBuffer, startSample);
        feedbackGainGenerator->Supply(machineState, feedbackDataBuffer, startSample);
        
        for (int i = 0; i < rDataBuffer.GetLength(); i++)
        {
            float in = rDataBuffer[i];
            generatorState->Write( in );
            float feedback = feedbackDataBuffer[i];
            rDataBuffer[i] = feedback *  generatorState->Read( delayDataBuffer[i] ) + (1.0f - feedback) * in;
        }
    }
}


GeneratorStateFilterComb::GeneratorStateFilterComb(int id)
: GeneratorStateBase(id)
, m_writeOffset(0)
{
    m_delayBuffer = new SampleDataBuffer(cMaxBufferSamples);
}

void GeneratorStateFilterComb::Write( float v )
{
    m_delayBuffer->Get(m_writeOffset++) = v;
    if (m_writeOffset >= cMaxBufferSamples)
    {
        m_writeOffset = 0;
    }
}

float GeneratorStateFilterComb::Read( float offset )
{
    if (offset >= cMaxBufferSamples)
    {
        offset = cMaxBufferSamples-1;
    }
    int iOffset = m_writeOffset - offset;
    if (iOffset < 0)
    {
        iOffset += cMaxBufferSamples;
    }
    return m_delayBuffer->Get(iOffset);
}



