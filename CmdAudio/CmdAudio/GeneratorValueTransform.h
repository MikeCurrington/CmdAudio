#pragma once
#include "GeneratorBase.h"
#include "SampleDataBuffer.h"
#include "TransformFunc.h"
#include "TransformClamp.h"

class GeneratorValueTransform : public GeneratorBase
{
public:
	GeneratorValueTransform();

protected:
	~GeneratorValueTransform();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override = 0;

protected:
	BaseCountedPtr<GeneratorBase> sourceBuffer;
};

