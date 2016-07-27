//
//  GeneratorAdd.cpp
//  CmdAudio
//
//  Created by Michael Currington on 7/16/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorAdd.h"

GeneratorAdd::GeneratorAdd() : GeneratorBase()
{
}

GeneratorAdd::~GeneratorAdd()
{
}

void GeneratorAdd::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(pParamName, "in") == 0)
    {
        assert( dynamic_cast<GeneratorArray*>(value.Obj()) != nullptr );
        generators = value;
    }
    else
        GeneratorBase::AddInput(pParamName, value);
}

void GeneratorAdd::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
    if (generators)
    {
        GeneratorArray* generatorArray = dynamic_cast<GeneratorArray*>(generators.Obj());
        if ( generatorArray != nullptr )
        {
            auto inputIter = generatorArray->begin();
            if (inputIter != generatorArray->end())
            {
                inputIter->second->Supply(machineState, rDataBuffer, startSample);
                inputIter++;
                
                for(; inputIter != generatorArray->end(); inputIter++)
                {
                    SampleDataBuffer bDataBuffer(rDataBuffer.GetLength());
                    inputIter->second->Supply(machineState, bDataBuffer, startSample);
        
                    for (int i = 0; i < rDataBuffer.GetLength(); i++)
                    {
                        rDataBuffer[i] = rDataBuffer[i] + bDataBuffer[i];
                    }
                }
            }
        }
        else
        {
            assert(0);
        }
    }
}
