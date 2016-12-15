#include "stdafx.h"
#include "math.h"
#include "GeneratorPulse.h"
#include "MachineState.h"

GeneratorPulse::GeneratorPulse( const std::string& name, int sampleRate ) : GeneratorWaveformBase(name, sampleRate)
{
}

GeneratorPulse::~GeneratorPulse()
{
}

void GeneratorPulse::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateWaveformBase> generatorState = machineState.GetGeneratorState<GeneratorStateWaveformBase>( GetId() );
    
    const float fSampleRate = (float) this->sampleRate;

    if (m_frequencyGenerator)
    {
        m_frequencyGenerator->Supply(machineState, rDataBuffer, startSample);

        float fPiDivSampleRate = 1.0f / fSampleRate;
        float fSample = generatorState->GetPhase();
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
        {
            float fOut = (fSample >= 0.0f && fSample < 1.0f) ? 1.0f : 0.0f;
            float nextAngle = fSample + rDataBuffer->Get(i) * fPiDivSampleRate;
            rDataBuffer->Get(i) = fOut;
            fSample = nextAngle;
        }
        generatorState->SetPhase(fSample);
    }
}


