#pragma once
#include "GeneratorBase.h"

class OutputBase
{
private:
    OutputBase & operator=(const OutputBase &rhs);	// deliberately not implemented so we dont accidentally assign
    OutputBase(const OutputBase&);					// deliberately not implemented copy constructor
    
public:
    OutputBase();
    virtual ~OutputBase() = 0;
    
    virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) = 0;
    virtual void Write(int outputLength) = 0;
    
protected:
    
protected:
};
