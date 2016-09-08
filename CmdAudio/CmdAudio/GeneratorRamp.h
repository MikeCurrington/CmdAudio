#pragma once
#include "GeneratorBase.h"

class GeneratorRamp : public GeneratorBase
{
private:
	GeneratorRamp();		// deliberately not implemented
public:
	GeneratorRamp(int sampleRate);

protected:
	~GeneratorRamp();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;

protected:
	int sampleRate;
	BaseCountedPtr<GeneratorBase> timeGenerator;
};


class GeneratorStateRamp : public GeneratorStateBase
{
public:
    GeneratorStateRamp(int id);
protected:
    friend class GeneratorRamp;
    float m_phase;
};
