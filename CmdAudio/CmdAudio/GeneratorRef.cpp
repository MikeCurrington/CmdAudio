//
//  GeneratorRef.cpp
//  CmdAudio
//
//  Created by Michael Currington on 10/16/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorRef.h"


GeneratorRef::GeneratorRef( const std::string& name, BaseCountedPtr<GeneratorStatement>& valueGenerator ) : GeneratorBase(name), m_statementGenerator(valueGenerator)
{
}

void GeneratorRef::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    //    m_statementGenerator->Supply( machineState, rDataBuffer, startSample);
    //rDataBuffer->Set( m_statementGenerator->GetCurrentBuffer(machineState) );
    assert(0);
}