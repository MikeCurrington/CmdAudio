//MachineState
#include "MachineState.h"

MachineState::MachineState(MachineState* pParent)
    : sampleRate(22050.0f)
    , parent(pParent)
    , nextStateId(0)
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
    if (parent != nullptr)
    {
        BaseCountedPtr<GeneratorBase> found = parent->Find(name);
        if (found)
        {
            return found;
        }
    }
    return BaseCountedPtr<GeneratorBase>();
}

int MachineState::GenerateStateId()
{
    return ++nextStateId;
}

const SampleDataBuffer * MachineState::GetGeneratorBuffer( int generatorId ) const
{
    auto it = statementBuffers.find(generatorId);
    if (it != statementBuffers.end())
    {
        return it->second.ConstObj();
    }
    return nullptr;
}

void MachineState::SetGeneratorBuffer( int generatorId, BaseCountedPtr<SampleDataBuffer> buffer )
{
    auto it = statementBuffers.find(generatorId);
    if (it != statementBuffers.end())
    {
        it->second = buffer;
    }
    else
    {
        statementBuffers.insert( {generatorId, buffer} );
    }
}

void MachineState::ClearStatementBuffers()
{
    statementBuffers.clear();
}





