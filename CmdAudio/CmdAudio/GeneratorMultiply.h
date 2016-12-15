#pragma once
#include "GeneratorBase.h"
#include "GeneratorArray.h"

class GeneratorMultiply :
	public GeneratorBase
{
public:
	GeneratorMultiply(const std::string & name);
	virtual ~GeneratorMultiply();

	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

protected:
    BaseCountedPtr<GeneratorBase> generators;
};

