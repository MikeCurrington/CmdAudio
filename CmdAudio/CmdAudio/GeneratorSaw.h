#pragma once
#include "GeneratorWaveformBase.h"

class GeneratorSaw : public GeneratorWaveformBase
{
public:
	GeneratorSaw( const std::string & name, int sampleRate );

protected:
	virtual ~GeneratorSaw();
	void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample);

protected:
};
