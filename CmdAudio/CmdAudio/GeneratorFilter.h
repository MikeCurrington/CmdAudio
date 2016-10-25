//
//  GeneratorFilter.h
//  CmdAudio
//
//  Created by Michael Currington on 7/30/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorValueTransform.h"

class GeneratorFilter : public GeneratorValueTransform
{
public:
    GeneratorFilter();
    ~GeneratorFilter();
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorBase> m_frequencyGenerator;
    BaseCountedPtr<GeneratorBase> resonanceGenerator;
};


class GeneratorStateFilter : public GeneratorStateBase
{
public:
    GeneratorStateFilter(int id)
    : GeneratorStateBase(id)
    , buf1(0.0f)
    , buf2(0.0f)
    , buf3(0.0f)
    , buf4(0.0f)
    {
    }
    float buf1, buf2, buf3, buf4;
};
