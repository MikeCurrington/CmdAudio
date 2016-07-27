#include "stdafx.h"
#include "string.h"
#include "math.h"
#include "GeneratorDelay.h"

template<class T> T min(const T &a, const T &b) { return a < b ? a : b; }
template<class T> T max(const T &a, const T &b) { return a > b ? a : b; }


GeneratorDelay::GeneratorDelay() : delayGenerator(nullptr), durationGenerator(nullptr), sourceGenerator(nullptr)
{
}


GeneratorDelay::~GeneratorDelay()
{
}

void GeneratorDelay::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(pParamName, "delay") == 0)
	{
		this->delayGenerator = value;
	}
	else if (strcasecmp(pParamName, "duration") == 0)
	{
		this->durationGenerator = value;
	}
	else if (strcasecmp(pParamName, "in") == 0)
	{
		this->sourceGenerator = value;
	}
	else
		GeneratorBase::AddInput(pParamName, value);
}

void GeneratorDelay::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	int outputLength = rDataBuffer.GetLength();
	if (outputLength == 0)
		return;

	if (sourceGenerator != NULL && delayGenerator != NULL && durationGenerator != NULL)
	{
		SampleDataBuffer delayDataBuffer(outputLength);
		SampleDataBuffer durationDataBuffer(outputLength);
		delayGenerator->Supply(machineState, delayDataBuffer, startSample);
		durationGenerator->Supply(machineState, durationDataBuffer, startSample);

		// Fill the databuffer on the assumption that the delayDataBuffer is actually constant (ie the delay isn't changing with time and causing a 'resample') and neither is the duration
		///TODO: We should start flagging the databuffers if they are constant values so we can optimize this case (would be useful in other generators too)
		int startDelay = (int) delayDataBuffer[0];

		SampleDataBuffer * sourceDataBuffer = nullptr;
		int startSampleDelayed = startSample - startDelay;
		if (startSampleDelayed >= 0)
		{
			int sourceLength = outputLength - startSampleDelayed;
			sourceDataBuffer = new SampleDataBuffer(sourceLength);
			sourceGenerator->Supply(machineState, *sourceDataBuffer, startSampleDelayed);

			int i = 0;
			for (int j = 0; i < outputLength && j < sourceDataBuffer->GetLength(); i++, j++)
				rDataBuffer[i] = sourceDataBuffer->Get(j);
			for (; i < outputLength; i++)
				rDataBuffer[i] = 0.0f;
		}
		else
		{
			int sourceLength = outputLength + startSampleDelayed;
			sourceDataBuffer = new SampleDataBuffer(sourceLength);
			sourceGenerator->Supply(machineState, *sourceDataBuffer, 0);

			int i = 0;
            for (; i < -startSampleDelayed; i++)
                rDataBuffer[i] = 0.0f;
            for (; i < outputLength; i++)
				rDataBuffer[i] = sourceDataBuffer->Get(i+startSampleDelayed);
		}

		delete sourceDataBuffer;
		sourceDataBuffer = nullptr;
	}


}