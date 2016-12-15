#pragma once

#include "GeneratorBase.h"
class GeneratorLerp01 : public GeneratorBase
{
public:
    GeneratorLerp01(const std::string & name);
    
protected:
    virtual ~GeneratorLerp01();
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorBase> valueGenerator;
    BaseCountedPtr<GeneratorBase> minGenerator;
    BaseCountedPtr<GeneratorBase> maxGenerator;
};

