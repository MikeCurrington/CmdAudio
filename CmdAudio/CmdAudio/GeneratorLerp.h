#pragma once

#include "GeneratorBase.h"
class GeneratorLerp : public GeneratorBase
{
public:
	GeneratorLerp();

protected:
	~GeneratorLerp();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;

protected:
	BaseCountedPtr<GeneratorBase> valueGenerator;
	BaseCountedPtr<GeneratorBase> minGenerator;
	BaseCountedPtr<GeneratorBase> maxGenerator;
};

