#pragma once

#include "GeneratorBase.h"
#include "BaseCounted.h"

class GeneratorInstance;
class GeneratorArray;

class GeneratorComponent : public GeneratorBase
{
private:
    GeneratorComponent();		// deliberately not implemented
public:
    GeneratorComponent(int sampleRate);
    void Supply(const GeneratorInstance * parent, MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample);
    
protected:
    ~GeneratorComponent();
    virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override {
        GeneratorComponent::Supply(nullptr, machineState, rDataBuffer, startSample);
    }
    
protected:
    int sampleRate;
    BaseCountedPtr<GeneratorArray> parameters;
    BaseCountedPtr<GeneratorBase>  source;
};
