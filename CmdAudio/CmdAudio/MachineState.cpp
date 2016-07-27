//MachineState
#include "MachineState.h"

MachineState::MachineState()
{
}

void MachineState::PushParameters(BaseCountedPtr<GeneratorArray> & parameters)
{
    this->parameterStack.push_back(parameters);
}

void MachineState::PopParameters()
{
    this->parameterStack.pop_back();
}

BaseCountedPtr<GeneratorBase> MachineState::Find( const std::string & name )
{
    for( auto it = this->parameterStack.rbegin(); it != this->parameterStack.rend(); ++it )
    {
        auto parameter = (*it)->Find( name );
        if (parameter)
        {
            return parameter;
        }
    }
    return BaseCountedPtr<GeneratorBase>();
}
