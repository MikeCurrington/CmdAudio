#include "stdafx.h"
#include "math.h"
#include "GeneratorSine.h"
#include "MachineState.h"

GeneratorSine::GeneratorSine(int sampleRate) : GeneratorWaveformBase(sampleRate)
{
}

GeneratorSine::~GeneratorSine()
{
}

void GeneratorSine::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    auto state = machineState.GetGeneratorState<GeneratorStateWaveformBase>( GetId() );
    
    const float fSampleRate = (float) this->sampleRate;
	
	if (frequencyGenerator)
	{
		frequencyGenerator->Supply(machineState, rDataBuffer, startSample);
		float fPiDivSampleRate = 2.0f *M_PI / fSampleRate;
        float fPhase = state->GetPhase();
		for (int i = 0; i < rDataBuffer.GetLength(); i++)
		{
			float nextPhase = fPhase + rDataBuffer[i] * fPiDivSampleRate;
			rDataBuffer[i] = sinf(fPhase);
			fPhase = nextPhase;
		}
        state->SetPhase(fPhase);
	}
}
