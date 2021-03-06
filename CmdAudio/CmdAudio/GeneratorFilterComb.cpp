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


GeneratorFilterComb::GeneratorFilterComb(const std::string & name) : GeneratorValueTransform(name)
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

void GeneratorFilterComb::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateFilterComb> generatorState = machineState.GetGeneratorState<GeneratorStateFilterComb>( GetId() );
    
    if (delayGenerator && feedbackGainGenerator)
    {
        sourceBuffer->Supply(machineState, rDataBuffer, startSample);
        
        BaseCountedPtr<SampleDataBuffer> delayDataBuffer( new SampleDataBuffer(rDataBuffer->GetLength()) );
        BaseCountedPtr<SampleDataBuffer> feedbackDataBuffer( new SampleDataBuffer(rDataBuffer->GetLength()) );

        delayGenerator->Supply(machineState, delayDataBuffer, startSample);
        feedbackGainGenerator->Supply(machineState, feedbackDataBuffer, startSample);
        
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
        {
            float in = rDataBuffer->Get(i);
            generatorState->Write( in );
            float feedback = feedbackDataBuffer->Get(i);
            rDataBuffer->Get(i) = feedback *  generatorState->Read( delayDataBuffer->Get(i) ) + (1.0f - feedback) * in;
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



