//
//  GeneratorSquare.cpp
//  CmdAudio
//
//  Created by Michael Currington on 10/31/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "stdafx.h"
#include "math.h"
#include "GeneratorSquare.h"
#include "MachineState.h"

GeneratorSquare::GeneratorSquare( const std::string& name, int sampleRate ) : GeneratorWaveformBase(name, sampleRate)
{
}

GeneratorSquare::~GeneratorSquare()
{
}

void GeneratorSquare::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    if (m_frequencyGenerator)
    {
        auto state = machineState.GetGeneratorState<GeneratorStateWaveformBase>( GetId() );
        const float fSampleRate = (float) this->sampleRate;
        
        m_frequencyGenerator->Supply(machineState, rDataBuffer, startSample);
        float fPiDivSampleRate = 1.0f / fSampleRate;
        float fPhase = state->GetPhase();
        float trashf = 0.0f;
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
        {
            if (fPhase > 1.0f)
                fPhase = modff(fPhase, &trashf);
            float nextAngle = fPhase + rDataBuffer->Get(i) * fPiDivSampleRate;
            rDataBuffer->Get(i) = (fPhase >= 0.5f) ? -1.0 : 1.0f;
            
            fPhase = nextAngle;
        }
        state->SetPhase(fPhase);
    }
}
