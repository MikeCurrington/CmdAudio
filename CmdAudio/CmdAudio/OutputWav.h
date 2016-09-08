#pragma once
#include "OutputBase.h"
#include "WavWriter.h"

class OutputWav : public OutputBase
{
public:
    OutputWav(int sampleRate);
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Write(MachineState& machineState, int outputLength) override;
    
protected:
    ~OutputWav();
    
protected:
    BaseCountedPtr<GeneratorBase> sourceGenerator;
    WavWriter * wavWriter;
};
