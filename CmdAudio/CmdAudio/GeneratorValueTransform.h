#pragma once
#include "GeneratorBase.h"
#include "SampleDataBuffer.h"
#include "TransformFunc.h"
#include "TransformClamp.h"

class GeneratorValueTransform : public GeneratorBase
{
public:
	GeneratorValueTransform(const std::string & name);

protected:
	virtual ~GeneratorValueTransform();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override = 0;

protected:
	BaseCountedPtr<GeneratorBase> sourceBuffer;
};

