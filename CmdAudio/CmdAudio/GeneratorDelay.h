#pragma once
#include "GeneratorBase.h"

class GeneratorDelay : public GeneratorBase
{
public:
	GeneratorDelay();

	virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;

protected:
	~GeneratorDelay();

protected:
	BaseCountedPtr<GeneratorBase> delayGenerator;
	BaseCountedPtr<GeneratorBase> durationGenerator;
	BaseCountedPtr<GeneratorBase> sourceGenerator;
};

