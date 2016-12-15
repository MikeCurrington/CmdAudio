#pragma once
//
//  GeneratorSquare.hpp
//  CmdAudio
//
//  Created by Michael Currington on 10/31/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#include "GeneratorWaveformBase.h"

class GeneratorSquare : public GeneratorWaveformBase
{
public:
    GeneratorSquare( const std::string& name, int sampleRate );
    
protected:
    ~GeneratorSquare();
    void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample);
    
protected:
};
