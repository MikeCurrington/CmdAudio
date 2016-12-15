#include "GeneratorUnbound.h"
#include "MachineState.h"


GeneratorUnbound::GeneratorUnbound( const std::string & name ) : GeneratorBase(name)
{
    this->name = name;
}


GeneratorUnbound::~GeneratorUnbound()
{
}


void GeneratorUnbound::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    GeneratorBase::AddInput(paramName, value);
}

void GeneratorUnbound::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    // get the named generator, and the machine it runs inside (will be in a parent machine if it is a parameter to a Generator block (may even be in a grandparent))
    std::pair<BaseCountedPtr<GeneratorBase>, MachineState&> paramAndState = machineState.Find( this->name );
    if (paramAndState.first)
    {
        paramAndState.first->Supply(paramAndState.second, rDataBuffer, startSample);
    }
    else
    {
        fprintf(stdout, "unbound variable: %s\n", this->name.c_str() );
        assert(0 && "Unbound variable remaining");
    }
}
