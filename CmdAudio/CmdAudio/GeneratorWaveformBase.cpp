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

void GeneratorWaveformBase::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(paramName.c_str(), "Frequency") == 0)
	{
		this->frequencyGenerator = value;
	}
	else
		GeneratorBase::AddInput(paramName, value);
}
