//
//  GeneratorAdd.cpp
//  CmdAudio
//
//  Created by Michael Currington on 7/16/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "GeneratorAdd.h"

GeneratorAdd::GeneratorAdd(const std::string & name) : GeneratorBase(name)
{
}

GeneratorAdd::~GeneratorAdd()
{
}

void GeneratorAdd::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "in") == 0)
    {
        assert( dynamic_cast<GeneratorArray*>(value.Obj()) != nullptr );
        generators = value;
    }
    else
        GeneratorBase::AddInput(paramName, value);
}

void GeneratorAdd::Supply(MachineState&  machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
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
                    BaseCountedPtr<SampleDataBuffer> bDataBuffer( new SampleDataBuffer(rDataBuffer->GetLength()) );
                    inputIter->second->Supply(machineState, bDataBuffer, startSample);
        
                    for (int i = 0; i < rDataBuffer->GetLength(); i++)
                    {
                        rDataBuffer->Get(i) += bDataBuffer->Get(i);
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
