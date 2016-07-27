#include "GeneratorArray.h"


GeneratorArray::GeneratorArray() : GeneratorBase()
{
}


GeneratorArray::~GeneratorArray()
{
}


void GeneratorArray::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
    generators.insert( std::make_pair(pParamName, value) );
    
    //GeneratorBase::AddInput(pParamName, value);
}

void GeneratorArray::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    assert(0 && "Unbound variable remaining");
}

BaseCountedPtr<GeneratorBase> GeneratorArray::Find( const std::string generatorName )
{
    auto r = generators.find(generatorName);
    if (r == generators.end())
        return nullptr;
    else
        return r->second;
}
