#include "stdafx.h"
#include "string.h"
#include "GeneratorMultiply.h"


GeneratorMultiply::GeneratorMultiply() : aGenerator(NULL), bGenerator(NULL)
{
}


GeneratorMultiply::~GeneratorMultiply()
{
}

void GeneratorMultiply::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(pParamName, "in1") == 0)
	{
        aGenerator = value;
    }
	else if (strcasecmp(pParamName, "in2") == 0)
	{
		bGenerator = value;
	}
	else
		GeneratorBase::AddInput(pParamName, value);
}

void GeneratorMultiply::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	if (aGenerator && bGenerator)
	{
		aGenerator->Supply(machineState, rDataBuffer, startSample);

		SampleDataBuffer bDataBuffer(rDataBuffer.GetLength());
		bGenerator->Supply(machineState, bDataBuffer, startSample);

		for (int i = 0; i < rDataBuffer.GetLength(); i++)
		{
			rDataBuffer[i] = rDataBuffer[i] * bDataBuffer[i];
		}
	}
}

