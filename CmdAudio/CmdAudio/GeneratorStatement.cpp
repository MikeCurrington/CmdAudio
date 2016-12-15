//
//  GeneratorStatement.cpp
//  CmdAudio
//
//  Created by Michael Currington on 10/15/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorStatement.h"
#include "MachineState.h"

GeneratorStatement::GeneratorStatement( const std::string& name, const BaseCountedPtr<GeneratorBase>& valueGenerator ) : GeneratorBase(name), m_valueGenerator(valueGenerator)
{
}

void GeneratorStatement::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    const SampleDataBuffer * buffer = machineState.GetGeneratorBuffer( GetId() );
    if (buffer != nullptr)
    {
    }
    else
    {
        BaseCountedPtr<GeneratorStateStatement> generatorState = machineState.GetGeneratorState<GeneratorStateStatement>( GetId() );
        
        BaseCountedPtr<SampleDataBuffer> rStoredBuffer = new SampleDataBuffer( rDataBuffer->GetLength() );
        
        m_valueGenerator->Supply(machineState, rStoredBuffer, startSample);

        machineState.SetGeneratorBuffer( GetId(), rStoredBuffer );
        
        buffer = rStoredBuffer.ConstObj();
    }
    rDataBuffer->Set( *buffer );
}

