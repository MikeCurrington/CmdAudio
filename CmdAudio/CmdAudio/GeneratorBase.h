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
	GeneratorBase(const std::string& name);
    const std::string& GetName() const            { return m_name; }

	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value);
	virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) = 0;
    
protected:
    int                 GetId() const       { return m_id; }

private:
    const std::string   m_name;
    int                 m_id;
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
