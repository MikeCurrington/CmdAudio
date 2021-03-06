#pragma once
#include "GeneratorBase.h"

class GeneratorNoise : public GeneratorBase
{
private:
    GeneratorNoise();		// deliberately not implemented
    
public:
    GeneratorNoise(const std::string & name);
    
protected:
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
};


class GeneratorStateNoise : public GeneratorStateBase
{
public:
    GeneratorStateNoise( int id)
        : GeneratorStateBase(id)
        , m_seed(1)
    {
    }
private:
    friend class GeneratorNoise;
    int m_seed;
};

