#pragma once

#include "GeneratorBase.h"
class GeneratorThreshold : public GeneratorBase
{
public:
	GeneratorThreshold();

protected:
	~GeneratorThreshold();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

protected:
	BaseCountedPtr<GeneratorBase> valueGenerator;
	BaseCountedPtr<GeneratorBase> minGenerator;
	BaseCountedPtr<GeneratorBase> maxGenerator;
    BaseCountedPtr<GeneratorBase> onOutputGenerator;
    BaseCountedPtr<GeneratorBase> offOutputGenerator;
};

