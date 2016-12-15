#pragma once
#include "GeneratorWaveformBase.h"

class GeneratorSine : public GeneratorWaveformBase
{
public:
	GeneratorSine( const std::string& name, int sampleRate );

protected:
	~GeneratorSine();
	void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample);

protected:
};
