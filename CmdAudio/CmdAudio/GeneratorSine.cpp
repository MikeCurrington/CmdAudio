#include "stdafx.h"
#include "math.h"
#include "GeneratorSine.h"

GeneratorSine::GeneratorSine(int sampleRate) : GeneratorWaveformBase(sampleRate)
{
}

GeneratorSine::~GeneratorSine()
{
}

void GeneratorSine::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	const float fSampleRate = (float) this->sampleRate;
	
	// get the frequency (how do we deal with the starting phase of the sine given that the frequency may have been sweeping all over?)
	if (frequencyGenerator != NULL)
	{
		frequencyGenerator->Supply(machineState, rDataBuffer, startSample);
		float fPiDivSampleRate = 2.0f *M_PI / fSampleRate;
		float fSample = fPiDivSampleRate * (float)startSample;
		for (int i = 0; i < rDataBuffer.GetLength(); i++)
		{
			float nextAngle = fSample + rDataBuffer[i] * fPiDivSampleRate;
			rDataBuffer[i] = sinf(fSample);
			fSample = nextAngle;
		}
	}
}
