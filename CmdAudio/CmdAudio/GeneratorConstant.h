#pragma once

#include "GeneratorBase.h"
class GeneratorConstant :
	public GeneratorBase
{
private:
	GeneratorConstant();	// deliberately not implemened
public:
	GeneratorConstant( float value );

protected:
	~GeneratorConstant();
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;

private:
	float fValue;
};

