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
    GeneratorComponent(const std::string& name, int sampleRate);
    void Supply(const GeneratorInstance * parent, MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample);
    
protected:
    ~GeneratorComponent();
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override {
        GeneratorComponent::Supply(nullptr, machineState, rDataBuffer, startSample);
    }
    
protected:
    int sampleRate;
    BaseCountedPtr<GeneratorArray> parameters;
    BaseCountedPtr<GeneratorBase>  source;
};
