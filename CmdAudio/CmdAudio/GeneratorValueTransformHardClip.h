#pragma once
#include "GeneratorValueTransform.h"

class GeneratorValueTransformHardClip :	public GeneratorValueTransform
{
public:
	GeneratorValueTransformHardClip();

protected:
	~GeneratorValueTransformHardClip();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;

protected:
	BaseCountedPtr<GeneratorBase> clip;
};

