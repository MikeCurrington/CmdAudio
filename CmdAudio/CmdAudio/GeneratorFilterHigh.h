//
//  GeneratorFilterHigh.h
//  CmdAudio
//
//  Created by Michael Currington on 8/21/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorValueTransform.h"

class GeneratorFilterHigh : public GeneratorValueTransform
{
public:
    GeneratorFilterHigh(const std::string & name);
    virtual ~GeneratorFilterHigh();
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorBase> m_frequencyGenerator;
    BaseCountedPtr<GeneratorBase> resonanceGenerator;
};


class GeneratorStateFilterHigh : public GeneratorStateBase
{
public:
    GeneratorStateFilterHigh(int id)
    : GeneratorStateBase(id)
    , buf1(0.0f)
    , buf2(0.0f)
    , buf3(0.0f)
    , buf4(0.0f)
    {
    }
    float buf1, buf2, buf3, buf4;
};
