#include "stdafx.h"
#include "math.h"
#include "GeneratorSaw.h"

GeneratorSaw::GeneratorSaw( int sampleRate ) : GeneratorWaveformBase(sampleRate)
{
}

GeneratorSaw::~GeneratorSaw()
{
}

void GeneratorSaw::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	const float fSampleRate = (float) this->sampleRate;

	// get the frequency (how do we deal with the starting phase of the sine given that the frequency may have been sweeping all over?)
	if (frequencyGenerator)
	{
		frequencyGenerator->Supply(machineState, rDataBuffer, startSample);
		float fPiDivSampleRate = 1.0f / fSampleRate;
		float fSample = fPiDivSampleRate * (float)startSample;
		float trashf = 0.0f;
		for (int i = 0; i < rDataBuffer.GetLength(); i++)
		{
			if (fSample > 1.0f)
				fSample = modff(fSample, &trashf);
			float nextAngle = fSample + rDataBuffer[i] * fPiDivSampleRate;
			rDataBuffer[i] = (fSample) * 2.0f - 1.0f;

			fSample = nextAngle;
		}
	}
}
