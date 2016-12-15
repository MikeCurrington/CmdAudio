#include "stdafx.h"
#include "string.h"
#include "math.h"
#include "GeneratorDelay.h"

template<class T> T min(const T &a, const T &b) { return a < b ? a : b; }
template<class T> T max(const T &a, const T &b) { return a > b ? a : b; }

#define MAX_BUFFERSIZE (1024000)

GeneratorDelay::GeneratorDelay(const std::string& name) : GeneratorBase(name), delayGenerator(nullptr), durationGenerator(nullptr), sourceGenerator(nullptr)
{
}


GeneratorDelay::~GeneratorDelay()
{
}

void GeneratorDelay::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(paramName.c_str(), "delay") == 0)
	{
		this->delayGenerator = value;
	}
	else if (strcasecmp(paramName.c_str(), "duration") == 0)
	{
		this->durationGenerator = value;
	}
	else if (strcasecmp(paramName.c_str(), "in") == 0)
	{
		this->sourceGenerator = value;
	}
	else
		GeneratorBase::AddInput(paramName, value);
}

#if 1
void GeneratorDelay::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
	int outputLength = rDataBuffer->GetLength();
	if (outputLength == 0)
		return;

	if (sourceGenerator && delayGenerator && durationGenerator)
	{
		BaseCountedPtr<SampleDataBuffer> delayDataBuffer( new SampleDataBuffer(outputLength) );
		BaseCountedPtr<SampleDataBuffer> durationDataBuffer( new SampleDataBuffer(outputLength) );
		delayGenerator->Supply(machineState, delayDataBuffer, startSample);
		durationGenerator->Supply(machineState, durationDataBuffer, startSample);

        int minSample = 0, maxSample = -1;
        if (outputLength>0)
        {
            maxSample = -1;
            minSample = MAX_BUFFERSIZE;
        }
        for (int i=0; i < outputLength; i++)
        {
            int sample = -delayDataBuffer->Get(i) + startSample + i;
            maxSample = max(sample, maxSample);
            minSample = max(min(sample, minSample),0);
        }
        
        int sourceLength = maxSample - minSample + 1;   // max sample is inclusive
        //if (sourceLength < 0)
        //    sourceLength = -sourceLength;
        if (sourceLength > MAX_BUFFERSIZE)
            return;
        if (maxSample < 0)
        {
            rDataBuffer->Clear();
            return;
        }
            
        
        // Now we know how much data we need we can request it!
        BaseCountedPtr<SampleDataBuffer> sourceDataBuffer( new SampleDataBuffer(sourceLength) );
        sourceGenerator->Supply(machineState, sourceDataBuffer, minSample);
        
        for(int i=0;i<outputLength;i++)
        {
            int delay = -delayDataBuffer->Get(i) + startSample - minSample + i;
            if (delay < 0)
            {
                rDataBuffer->Get(i) = 0.0f;
            }
            else
            {
                rDataBuffer->Get(i) = sourceDataBuffer->Get(delay);
            }
        }
	}
}

#else

void GeneratorDelay::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    int outputLength = rDataBuffer->GetLength();
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
                rDataBuffer->Get(i) = sourceDataBuffer->Get(j);
            for (; i < outputLength; i++)
                rDataBuffer->Get(i) = 0.0f;
        }
        else
        {
            int sourceLength = outputLength + startSampleDelayed;
            sourceDataBuffer = new SampleDataBuffer(sourceLength);
            sourceGenerator->Supply(machineState, *sourceDataBuffer, 0);
            
            int i = 0;
            for (; i < -startSampleDelayed; i++)
                rDataBuffer->Get(i) = 0.0f;
            for (; i < outputLength; i++)
                rDataBuffer->Get(i) = sourceDataBuffer->Get(i+startSampleDelayed);
        }
        
        delete sourceDataBuffer;
        sourceDataBuffer = nullptr;
    }
    
    
}
#endif

