#pragma once
//
//  GeneratorState.h
//  CmdAudio
//
//  Created by Michael Currington on 11/23/15.
//  Copyright (c) 2015 Doodleoo Games. All rights reserved.
//
#include "GeneratorBase.h"
#include <array>

class GeneratorState
{
public:
    GeneratorState();
    
protected:
    int             GetId()     { return id; }
    
private:
    int             id;
    
};

