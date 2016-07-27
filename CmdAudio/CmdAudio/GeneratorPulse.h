#pragma once
#include "GeneratorWaveformBase.h"

class GeneratorPulse : public GeneratorWaveformBase
{
public:
    GeneratorPulse( int sampleRate );
    
protected:
    ~GeneratorPulse();
    void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample);
    
protected:
};
