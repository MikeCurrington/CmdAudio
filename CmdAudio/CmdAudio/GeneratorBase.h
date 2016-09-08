#pragma once
#include "BaseCounted.h"
#include "SampleDataBuffer.h"
#include <utility>
#include <unordered_map>
#include <string>

// Forward decl
class MachineState;

///
/// Base class for all the sample Generators
/// The job of the generator is to fill (supply) a buffer with samples/value - the contents of which is determined by the inputs to the generator.
///
class GeneratorBase : public BaseCounted<GeneratorBase>
{
public:
	GeneratorBase();

	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value);
	virtual void Supply(MachineState& machineState, SampleDataBuffer & rDataBuffer, int startSample) = 0;
    
protected:
    int                 GetId()     { return id; }

private:
    int                 id;
};


///
/// Base class for the data local to an instance of a sample generator
///
class GeneratorStateBase : public BaseCounted<GeneratorStateBase>
{
public:
    GeneratorStateBase(int id);
    
protected:
    int                 GetId()     { return id; }
    
private:
    friend class MachineState;

    BaseCountedPtr<GeneratorStateBase> next;
    int                 id;
};
