#pragma once

#include "GeneratorBase.h"
class GeneratorLerp : public GeneratorBase
{
public:
	GeneratorLerp(const std::string& name);

protected:
	~GeneratorLerp();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

protected:
	BaseCountedPtr<GeneratorBase> valueGenerator;
	BaseCountedPtr<GeneratorBase> minGenerator;
	BaseCountedPtr<GeneratorBase> maxGenerator;
};

