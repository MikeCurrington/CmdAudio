#pragma once
#include "GeneratorWaveformBase.h"

class GeneratorPulse : public GeneratorWaveformBase
{
public:
    GeneratorPulse( int sampleRate );
    
protected:
    ~GeneratorPulse();
    void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample);
    
protected:
};


class GeneratorStatePulse : public GeneratorStateBase
{
public:
    GeneratorStatePulse(int id) : GeneratorStateBase(id), m_phase(0.0f)
    {}
private:
    friend class GeneratorPulse;
    float m_phase;
};

