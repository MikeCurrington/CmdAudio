#include "stdafx.h"
#include "GeneratorLerp.h"
#include "string.h"

GeneratorLerp::GeneratorLerp(const std::string& name) : GeneratorBase(name), valueGenerator(nullptr), minGenerator(nullptr), maxGenerator(nullptr)
{
}

GeneratorLerp::~GeneratorLerp()
{
}

void GeneratorLerp::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
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
	else
		GeneratorBase::AddInput(paramName, value);
}

void GeneratorLerp::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
	// get the values to lerp between
	if (valueGenerator && minGenerator && maxGenerator)
	{
		valueGenerator->Supply(machineState, rDataBuffer, startSample);

		BaseCountedPtr<SampleDataBuffer> minDataBuffer( new SampleDataBuffer(rDataBuffer->GetLength()) );
		minGenerator->Supply(machineState, minDataBuffer, startSample);
		BaseCountedPtr<SampleDataBuffer> maxDataBuffer( new SampleDataBuffer( rDataBuffer->GetLength()) );
		maxGenerator->Supply(machineState, maxDataBuffer, startSample);

		for (int i = 0; i < rDataBuffer->GetLength(); i++)
		{
			float fMin = minDataBuffer->Get(i);
			float fRange = maxDataBuffer->Get(i) - fMin;
			rDataBuffer->Get(i) = (0.5f*(rDataBuffer->Get(i)+1.0f))*fRange + fMin;
		}
	}
}

