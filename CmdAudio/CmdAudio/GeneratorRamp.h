#pragma once
#include "GeneratorBase.h"

class GeneratorRamp : public GeneratorBase
{
private:
	GeneratorRamp();		// deliberately not implemented
public:
	GeneratorRamp(int sampleRate);

protected:
	~GeneratorRamp();
	virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;

protected:
	int sampleRate;
	BaseCountedPtr<GeneratorBase> timeGenerator;
};
