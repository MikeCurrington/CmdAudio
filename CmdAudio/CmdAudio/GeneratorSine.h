#pragma once
#include "GeneratorWaveformBase.h"

class GeneratorSine : public GeneratorWaveformBase
{
public:
	GeneratorSine( int sampleRate );

protected:
	~GeneratorSine();
	void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample);

protected:
};
