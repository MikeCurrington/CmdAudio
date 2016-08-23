#include "stdafx.h"
#include "string.h"
#include "GeneratorWaveformBase.h"

GeneratorWaveformBase::GeneratorWaveformBase(int sampleRate) :
	sampleRate(sampleRate)
{
}

GeneratorWaveformBase::~GeneratorWaveformBase()
{
}

void GeneratorWaveformBase::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(pParamName, "Frequency") == 0)
	{
		this->frequencyGenerator = value;
	}
	else
		GeneratorBase::AddInput(pParamName, value);
}

