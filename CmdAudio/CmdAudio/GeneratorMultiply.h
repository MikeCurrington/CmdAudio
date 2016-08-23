#pragma once
#include "GeneratorBase.h"
#include "GeneratorArray.h"

class GeneratorMultiply :
	public GeneratorBase
{
public:
	GeneratorMultiply();
	~GeneratorMultiply();

	virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;

protected:
    BaseCountedPtr<GeneratorBase> generators;
};

