#pragma once

#include "GeneratorBase.h"
class GeneratorConstant :
	public GeneratorBase
{
private:
	GeneratorConstant();	// deliberately not implemened
public:
	GeneratorConstant( const std::string& name, float value );
    float GetValue() const { return fValue; }

protected:
	~GeneratorConstant();
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

private:
	float fValue;
};

