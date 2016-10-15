#include "stdafx.h"
#include "math.h"
#include "GeneratorSaw.h"
#include "MachineState.h"

GeneratorSaw::GeneratorSaw( int sampleRate ) : GeneratorWaveformBase(sampleRate)
{
}

GeneratorSaw::~GeneratorSaw()
{
}

void GeneratorSaw::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	// get the frequency (how do we deal with the starting phase of the sine given that the frequency may have been sweeping all over?)
	if (frequencyGenerator)
	{
        auto state = machineState.GetGeneratorState<GeneratorStateWaveformBase>( GetId() );
        const float fSampleRate = (float) this->sampleRate;

        frequencyGenerator->Supply(machineState, rDataBuffer, startSample);
		float fPiDivSampleRate = 1.0f / fSampleRate;
        float fPhase = state->GetPhase();
        float trashf = 0.0f;
		for (int i = 0; i < rDataBuffer.GetLength(); i++)
		{
			if (fPhase > 1.0f)
				fPhase = modff(fPhase, &trashf);
			float nextAngle = fPhase + rDataBuffer[i] * fPiDivSampleRate;
			rDataBuffer[i] = (fPhase) * 2.0f - 1.0f;

			fPhase = nextAngle;
		}
        state->SetPhase(fPhase);
	}
}
