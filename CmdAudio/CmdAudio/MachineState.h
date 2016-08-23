#pragma once

#include <vector>
#include <map>
#include "BaseCounted.h"
#include "GeneratorArray.h"

///
/// MachineState
/// Class storing the current state of the 'machine'
///
class MachineState
{
public:
    MachineState(MachineState* pParent = nullptr);
    
    void PushParameters( BaseCountedPtr<GeneratorArray> & parameters );
    void PopParameters();
    BaseCountedPtr<GeneratorBase> Find( const std::string & name );
    
    float GetSampleRate() const { return sampleRate; }

    template <class T>
    BaseCountedPtr<T> GetGeneratorState( int generatorId )
    {
        BaseCountedPtr<GeneratorStateBase> state = GetGeneratorState_(generatorId);
        if (!state)
        {
            state = new T( GenerateStateId() );
            states.insert( std::pair<int,BaseCountedPtr<GeneratorStateBase>>(generatorId, state) );
            fprintf(stdout, "not found gen %d\n", generatorId);
        }
        else
        {
            fprintf(stdout, "found gen %d\n", generatorId);
        }
        return state.StaticCast<T>();
    }
    template <class T, typename U>
    BaseCountedPtr<T> GetGeneratorState( int generatorId, U data )
    {
        BaseCountedPtr<GeneratorStateBase> state = GetGeneratorState_(generatorId);
        if (!state)
        {
            state = new T( GenerateStateId(), data );
            states.insert( std::pair<int,BaseCountedPtr<GeneratorStateBase>>(generatorId, state) );
            fprintf(stdout, "not found gen %d\n", generatorId);
        }
        else
        {
            fprintf(stdout, "found gen %d\n", generatorId);
        }
        return state.StaticCast<T>();
    }
    
    
private:
    BaseCountedPtr<GeneratorStateBase> GetGeneratorState_( int id ) const
    {
        auto stateIt = states.find(id);
        if (stateIt != states.end())
        {
            return stateIt->second;
        }
        return nullptr;
    }
    int GenerateStateId();
    
    std::vector< BaseCountedPtr<GeneratorArray> > parameterStack;
    MachineState*       parent;
    float               sampleRate;
    int                 nextStateId;
    
    typedef std::map<int,BaseCountedPtr<GeneratorStateBase>> tStateMap;
    tStateMap   states;
};
