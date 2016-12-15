#include "GeneratorArray.h"


GeneratorArray::GeneratorArray(const std::string& name) : GeneratorBase(name)
{
}


GeneratorArray::~GeneratorArray()
{
}


void GeneratorArray::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    generators.insert( std::make_pair(paramName, value) );
    
    //GeneratorBase::AddInput(pParamName, value);
}

void GeneratorArray::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    assert(0 && "Unbound variable remaining");
}

BaseCountedPtr<GeneratorBase> GeneratorArray::Find( const std::string generatorName ) const
{
    auto r = generators.find(generatorName);
    if (r == generators.end())
        return nullptr;
    else
        return r->second;
}
