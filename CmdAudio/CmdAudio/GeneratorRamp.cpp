#include "stdafx.h"
#include "string.h"
#include "GeneratorRamp.h"
#include "MachineState.h"


GeneratorRamp::GeneratorRamp(int sampleRate) : sampleRate(sampleRate), timeGenerator(NULL)
{
}

GeneratorRamp::~GeneratorRamp()
{
}

void GeneratorRamp::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(pParamName, "Time") == 0)
	{
		this->timeGenerator = value;
	}
	else
		GeneratorBase::AddInput(pParamName, value);
}


void GeneratorRamp::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateRamp> generatorState = machineState.GetGeneratorState<GeneratorStateRamp>( GetId() );
    
	const float fSampleRate = (float) this->sampleRate;

	if (timeGenerator)
	{
		timeGenerator->Supply(machineState, rDataBuffer, startSample);

        float fInvSampleRate = 1.0f / fSampleRate;
        float value = generatorState->m_phase;
        for (int i = 0; i < rDataBuffer.GetLength(); i++)
		{
			float nextValue = value + fInvSampleRate / rDataBuffer[i];
			if (value > 1.0f)
				value = 1.0f;
			else if (value < 0.0f)
				value = 0.0f;
			rDataBuffer[i] = value*2.0f - 1.0f;

			value = nextValue;
		}
        generatorState->m_phase = value;
	}
}


GeneratorStateRamp::GeneratorStateRamp(int id) : GeneratorStateBase(id), m_phase(0.0f)
{
}
