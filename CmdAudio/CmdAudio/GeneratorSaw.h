#pragma once
#include "GeneratorWaveformBase.h"

class GeneratorSaw : public GeneratorWaveformBase
{
public:
	GeneratorSaw( int sampleRate );

protected:
	~GeneratorSaw();
	void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample);

protected:
};
