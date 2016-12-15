#pragma once
#include "GeneratorValueTransform.h"

class GeneratorValueTransformHardClip :	public GeneratorValueTransform
{
public:
	GeneratorValueTransformHardClip(const std::string& name);

protected:
	~GeneratorValueTransformHardClip();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

protected:
	BaseCountedPtr<GeneratorBase> clip;
};

