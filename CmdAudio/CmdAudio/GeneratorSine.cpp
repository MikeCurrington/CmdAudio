#include "stdafx.h"
#include "math.h"
#include "GeneratorSine.h"
#include "MachineState.h"

GeneratorSine::GeneratorSine(const std::string& name, int sampleRate) : GeneratorWaveformBase(name, sampleRate)
{
}

GeneratorSine::~GeneratorSine()
{
}

void GeneratorSine::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    auto state = machineState.GetGeneratorState<GeneratorStateWaveformBase>( GetId() );
    
    const float fSampleRate = (float) this->sampleRate;
	
	if (m_frequencyGenerator)
	{
		m_frequencyGenerator->Supply(machineState, rDataBuffer, startSample);
		float fPiDivSampleRate = 2.0f *M_PI / fSampleRate;
        float fPhase = state->GetPhase();
		for (int i = 0; i < rDataBuffer->GetLength(); i++)
		{
			float nextPhase = fPhase + rDataBuffer->Get(i) * fPiDivSampleRate;
			rDataBuffer->Get(i) = sinf(fPhase);
			fPhase = nextPhase;
		}
        state->SetPhase(fPhase);
	}
}
