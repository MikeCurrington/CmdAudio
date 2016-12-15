//MachineState
#include "MachineState.h"

MachineState::MachineState(MachineState* pParent)
    : m_sampleRate(22050.0f)
    , m_parent(pParent)
    , m_nextStateId(0)
{
}

void MachineState::Reset()
{
    m_parameterStack.clear();
    m_states.clear();
    m_statementBuffers.clear();
    m_nextStateId = 0;
    
    
}

void MachineState::PushParameters(BaseCountedPtr<GeneratorArray>& parameters, MachineState& machine)
{
    m_parameterStack.push_back( tMachineParameterGroup(parameters, machine) );
}

void MachineState::PopParameters()
{
    m_parameterStack.pop_back();
}

MachineState::tMachineParameter MachineState::Find( const std::string & name ) const
{
    for( auto it = m_parameterStack.rbegin(); it != m_parameterStack.rend(); ++it )
    {
        auto parameter = it->first->Find( name );
        if (parameter)
        {
            return tMachineParameter(parameter, it->second);
        }
    }
    if (m_parent != nullptr)
    {
        auto found = m_parent->Find(name);
        if (found.first)
        {
            return found;
        }
    }
    return tMachineParameter( BaseCountedPtr<GeneratorBase>(), const_cast<MachineState&>(*this) );
}

int MachineState::GenerateStateId()
{
    return ++m_nextStateId;
}

const SampleDataBuffer * MachineState::GetGeneratorBuffer( int generatorId ) const
{
    auto it = m_statementBuffers.find(generatorId);
    if (it != m_statementBuffers.end())
    {
        return it->second.ConstObj();
    }
    return nullptr;
}

void MachineState::SetGeneratorBuffer( int generatorId, BaseCountedPtr<SampleDataBuffer> buffer )
{
    auto it = m_statementBuffers.find(generatorId);
    if (it != m_statementBuffers.end())
    {
        it->second = buffer;
    }
    else
    {
        m_statementBuffers.insert( {generatorId, buffer} );
    }
}

void MachineState::ClearStatementBuffers()
{
    m_statementBuffers.clear();
}





