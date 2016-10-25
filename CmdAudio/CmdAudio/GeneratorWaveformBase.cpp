#include "stdafx.h"
#include "string.h"
#include "GeneratorWaveformBase.h"
#include "GeneratorInvert.h"

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
        this->m_frequencyGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "Time") == 0)
    {
        BaseCountedPtr<GeneratorBase> invTime = new GeneratorInvert();
        invTime->AddInput("in", value);
        this->m_frequencyGenerator = invTime;
    }
    else
    {
        GeneratorBase::AddInput(paramName, value);
    }
}
