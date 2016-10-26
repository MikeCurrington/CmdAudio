#pragma once
#include "GeneratorWaveformBase.h"

class GeneratorRamp : public GeneratorWaveformBase
{
private:
	GeneratorRamp();		// deliberately not implemented
public:
    GeneratorRamp( int sampleRate );
    
protected:
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;

protected:
};


class GeneratorStateRamp : public GeneratorStateBase
{
public:
    GeneratorStateRamp(int id);
protected:
    friend class GeneratorRamp;
    float m_phase;
};
