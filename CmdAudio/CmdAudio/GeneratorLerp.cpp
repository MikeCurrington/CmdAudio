#include "stdafx.h"
#include "GeneratorLerp.h"
#include "string.h"

GeneratorLerp::GeneratorLerp() : valueGenerator(nullptr), minGenerator(nullptr), maxGenerator(nullptr)
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

void GeneratorLerp::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	// get the values to lerp between
	if (valueGenerator && minGenerator && maxGenerator)
	{
		valueGenerator->Supply(machineState, rDataBuffer, startSample);

		SampleDataBuffer minDataBuffer(rDataBuffer.GetLength());
		minGenerator->Supply(machineState, minDataBuffer, startSample);
		SampleDataBuffer maxDataBuffer( rDataBuffer.GetLength() );
		maxGenerator->Supply(machineState, maxDataBuffer, startSample);

		for (int i = 0; i < rDataBuffer.GetLength(); i++)
		{
			float fMin = minDataBuffer[i];
			float fRange = maxDataBuffer[i] - fMin;
			rDataBuffer[i] = (0.5f*(rDataBuffer[i]+1.0f))*fRange + fMin;
		}
	}
}

