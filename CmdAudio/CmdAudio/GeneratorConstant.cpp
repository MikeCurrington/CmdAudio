#include "stdafx.h"
#include "GeneratorConstant.h"


GeneratorConstant::GeneratorConstant(const std::string& name, float value) : GeneratorBase(name)
{
	this->fValue = value;
}


GeneratorConstant::~GeneratorConstant()
{
}


void GeneratorConstant::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
	for (int i = 0; i < rDataBuffer->GetLength(); i++)
		rDataBuffer->Get(i) = fValue;
}
