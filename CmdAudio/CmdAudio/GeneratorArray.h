#pragma once

#include "GeneratorBase.h"
#include <unordered_map>
#include <string>

//
// Generator for arrays of variables (used to define macro inputs)
//

class GeneratorArray : public GeneratorBase
{
private:
public:
    GeneratorArray( );
    
    BaseCountedPtr<GeneratorBase> Find( const std::string generatorName );
    
    std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>>::iterator begin()
    {
        return generators.begin();
    };
    std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>>::iterator end()
    {
        return generators.end();
    };
    
protected:
    ~GeneratorArray();
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;
    friend class GeneratorInstance;

private:
    std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>> generators;
};

