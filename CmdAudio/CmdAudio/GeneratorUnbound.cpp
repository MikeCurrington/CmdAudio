#include "GeneratorUnbound.h"
#include "MachineState.h"


GeneratorUnbound::GeneratorUnbound( const std::string & name ) : GeneratorBase()
{
    this->name = name;
}


GeneratorUnbound::~GeneratorUnbound()
{
}


void GeneratorUnbound::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
    GeneratorBase::AddInput(pParamName, value);
}

void GeneratorUnbound::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorBase> param = machineState.Find( this->name );
    if (param)
    {
        param->Supply(machineState, rDataBuffer, startSample);
    }
    else
    {
        fprintf(stdout, "unbound variable: %s\n", this->name.c_str() );
        assert(0 && "Unbound variable remaining");
    }
}