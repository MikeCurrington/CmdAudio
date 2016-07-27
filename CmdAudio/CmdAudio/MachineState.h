#pragma once

#include <vector>
#include "BaseCounted.h"
#include "GeneratorArray.h"

///
/// MachineState
/// Class storing the current state of the 'machine'
///
class MachineState
{
public:
    MachineState();
    
    void PushParameters( BaseCountedPtr<GeneratorArray> & parameters );
    void PopParameters();
    BaseCountedPtr<GeneratorBase> Find( const std::string & name );

private:
    std::vector< BaseCountedPtr<GeneratorArray> > parameterStack;
};
