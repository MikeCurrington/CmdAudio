#include "stdafx.h"
#include "GeneratorThreshold.h"
#include "string.h"

GeneratorThreshold::GeneratorThreshold(const std::string & name) : GeneratorBase(name)
{
}

GeneratorThreshold::~GeneratorThreshold()
{
}

void GeneratorThreshold::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(paramName.c_str(), "value") == 0)
	{
		this->valueGenerator = value;
	}
	else if (strcasecmp(paramName.c_str(), "min") == 0)
	{
		this->minGenerator = value;
	}
    else if (strcasecmp(paramName.c_str(), "max") == 0)
    {
        this->maxGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "onOutput") == 0)
    {
        this->onOutputGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "offOutput") == 0)
    {
        this->offOutputGenerator = value;
    }
    else
		GeneratorBase::AddInput(paramName, value);
}

void GeneratorThreshold::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
	// get the values to lerp between
	if (valueGenerator && minGenerator && maxGenerator)
	{
		valueGenerator->Supply(machineState, rDataBuffer, startSample);

		BaseCountedPtr<SampleDataBuffer> minDataBuffer( new SampleDataBuffer(rDataBuffer->GetLength()) );
		minGenerator->Supply(machineState, minDataBuffer, startSample);
        BaseCountedPtr<SampleDataBuffer> maxDataBuffer( new SampleDataBuffer( rDataBuffer->GetLength()) );
        maxGenerator->Supply(machineState, maxDataBuffer, startSample);
        BaseCountedPtr<SampleDataBuffer> onDataBuffer( new SampleDataBuffer( rDataBuffer->GetLength()) );
        onOutputGenerator->Supply(machineState, onDataBuffer, startSample);
        BaseCountedPtr<SampleDataBuffer> offDataBuffer( new SampleDataBuffer( rDataBuffer->GetLength()) );
        offOutputGenerator->Supply(machineState, offDataBuffer, startSample);
        
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
		{
            float & value = rDataBuffer->Get(i);
            if (value >= minDataBuffer->Get(i) && value <= maxDataBuffer->Get(i))
            {
                value = onDataBuffer->Get(i);
            }
            else
            {
                value = offDataBuffer->Get(i);
            }
		}
	}
}

