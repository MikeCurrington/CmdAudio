//
//  GeneratorHold.h
//  CmdAudio
//
//  Created by Michael Currington on 10/6/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorValueTransform.h"

class GeneratorHold : public GeneratorValueTransform
{
public:
    GeneratorHold();
    ~GeneratorHold();
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorBase> holdGenerator;
};


class GeneratorStateHold : public GeneratorStateBase
{
public:
    GeneratorStateHold(int id)
    : GeneratorStateBase(id)
    , m_value(0.0f)
    , m_holding(false)
    {
    }
    void  Set( bool hold, float value )     { m_holding = hold; m_value = value; }
    float GetValue() const                  { return m_value;   }
    bool  GetHolding() const                { return m_holding; }
protected:
    float m_value;
    bool  m_holding;
};
