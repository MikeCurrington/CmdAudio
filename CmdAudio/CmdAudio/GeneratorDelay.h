#pragma once
#include "GeneratorBase.h"

class GeneratorDelay : public GeneratorBase
{
public:
	GeneratorDelay();

	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

protected:
	~GeneratorDelay();

protected:
	BaseCountedPtr<GeneratorBase> delayGenerator;
	BaseCountedPtr<GeneratorBase> durationGenerator;
	BaseCountedPtr<GeneratorBase> sourceGenerator;
};

