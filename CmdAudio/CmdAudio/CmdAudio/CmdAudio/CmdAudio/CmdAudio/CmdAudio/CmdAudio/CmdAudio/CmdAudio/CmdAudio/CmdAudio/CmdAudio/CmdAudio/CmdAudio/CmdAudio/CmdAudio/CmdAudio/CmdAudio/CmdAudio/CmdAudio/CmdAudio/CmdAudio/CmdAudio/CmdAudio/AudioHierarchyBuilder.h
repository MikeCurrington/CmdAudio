//
//  AudioHierarchyBuilder.h
//  CmdAudio
//
//  Created by Michael Currington on 8/29/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorComponent.h"

class GeneratorComponent;
namespace antlr4
{
    class ANTLRInputStream;
}


class AudioHierarchyBuilder
{
public:
    AudioHierarchyBuilder() {}
    BaseCountedPtr<GeneratorComponent> Build( antlr4::ANTLRInputStream* input );
};
