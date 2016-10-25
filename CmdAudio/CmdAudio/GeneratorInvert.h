//
//  GeneratorInvert.h
//  CmdAudio
//
//  output = 1.0 / value (input)
//
//  Created by Michael Currington on 10/24/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#pragma once

#include "GeneratorValueTransform.h"

class GeneratorInvert : public GeneratorValueTransform
{
public:
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
};
