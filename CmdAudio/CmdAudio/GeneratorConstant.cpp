#include "stdafx.h"
#include "GeneratorConstant.h"


GeneratorConstant::GeneratorConstant(float value) : GeneratorBase()
{
	this->fValue = value;
}


GeneratorConstant::~GeneratorConstant()
{
}


void GeneratorConstant::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	GeneratorBase::AddInput(pParamName, value);
}

void GeneratorConstant::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	for (int i = 0; i < rDataBuffer.GetLength(); i++)
		rDataBuffer[i] = fValue;
}
