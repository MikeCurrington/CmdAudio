#include "stdafx.h"
#include "string.h"
#include "GeneratorRamp.h"
#include "MachineState.h"


void GeneratorRamp::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateRamp> generatorState = machineState.GetGeneratorState<GeneratorStateRamp>( GetId() );
    
	const float fSampleRate = (float) this->sampleRate;

	if (timeGenerator)
	{
		timeGenerator->Supply(machineState, rDataBuffer, startSample);

        float fInvSampleRate = 1.0f / fSampleRate;
        float value = generatorState->m_phase;
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
		{
			float nextValue = value + fInvSampleRate / rDataBuffer->Get(i);
			if (value > 1.0f)
				value = 1.0f;
			else if (value < 0.0f)
				value = 0.0f;
			rDataBuffer->Get(i) = value;

			value = nextValue;
		}
        generatorState->m_phase = value;
	}
}


GeneratorStateRamp::GeneratorStateRamp(int id) : GeneratorStateBase(id), m_phase(0.0f)
{
}
