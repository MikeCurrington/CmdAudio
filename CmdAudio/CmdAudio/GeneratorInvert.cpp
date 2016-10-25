//
//  GeneratorInvert.cpp
//  CmdAudio
//
//  Created by Michael Currington on 10/24/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorInvert.h"

void GeneratorInvert::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
    if (sourceBuffer)
    {
        sourceBuffer->Supply(machineState, rDataBuffer, startSample);
        
        for (int i = 0; i < rDataBuffer->GetLength(); i++)
        {
            float& val = rDataBuffer->Get(i);
            val = 1.0f / val;
        }
    }
}