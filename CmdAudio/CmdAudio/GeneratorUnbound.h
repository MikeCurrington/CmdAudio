#pragma once

#include "GeneratorBase.h"
#include <string>

//
// Generator for Unbound variables
// Used as a stub until variable definitions are reached
//

class GeneratorUnbound : public GeneratorBase
{
private:
    GeneratorUnbound();	// deliberately not implemened
public:
    GeneratorUnbound( const std::string & value );
    
protected:
    ~GeneratorUnbound();
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
private:
    std::string name;
};

