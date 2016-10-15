#include "stdafx.h"
#include "math.h"
#include "GeneratorPulse.h"
#include "MachineState.h"

GeneratorPulse::GeneratorPulse( int sampleRate ) : GeneratorWaveformBase(sampleRate)
{
}

GeneratorPulse::~GeneratorPulse()
{
}

void GeneratorPulse::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateWaveformBase> generatorState = machineState.GetGeneratorState<GeneratorStateWaveformBase>( GetId() );
    
    const float fSampleRate = (float) this->sampleRate;

    if (frequencyGenerator)
    {
        frequencyGenerator->Supply(machineState, rDataBuffer, startSample);

        float fPiDivSampleRate = 1.0f / fSampleRate;
        float fSample = generatorState->GetPhase();
        for (int i = 0; i < rDataBuffer.GetLength(); i++)
        {
            float fOut = (fSample >= 0.0f && fSample < 1.0f) ? 1.0f : 0.0f;
            float nextAngle = fSample + rDataBuffer[i] * fPiDivSampleRate;
            rDataBuffer[i] = fOut;
            fSample = nextAngle;
        }
        generatorState->SetPhase(fSample);
    }
}


