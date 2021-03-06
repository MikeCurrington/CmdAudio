//
//  GeneratorMidiChannel.cpp
//  CmdAudio
//
//  Midi to audio
//
//  Created by Michael Currington on 8/21/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorMidiChannel.h"
#include "MachineState.h"


GeneratorMidiChannel::GeneratorMidiChannel(const std::string& name, int sampleRate) : GeneratorBase(name)
{
}

void GeneratorMidiChannel::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "Channel") == 0)
    {
        channelGenerator = value;
    }
    else if (strcasecmp(paramName.c_str(), "Component") == 0)
    {
        componentGenerator = value;
    }
    else
        GeneratorBase::AddInput(paramName, value);
}

void GeneratorMidiChannel::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    BaseCountedPtr<GeneratorStateMidiChannel> generatorState = machineState.GetGeneratorState<GeneratorStateMidiChannel>( GetId() );
    
    if (channelGenerator && componentGenerator)
    {
        if (startSample==0)
        {
            //        generatorState->m_runningNotes.push_back( new GeneratorInstance( componentGenerator ) );
        }
        
        
        
    }
}


GeneratorStateMidiChannel::GeneratorStateMidiChannel(int id)
: GeneratorStateBase(id)
{
    
    
    
    
}
