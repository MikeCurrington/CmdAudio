//
//  GeneratorStatement.h
//  CmdAudio
//
//  Base generator for statements - contains a generator (tree) and also the current output buffer for the
//  statement so that we only generate the output once (for multiple references).
//
//  Created by Michael Currington on 10/15/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorBase.h"
#include "SampleDataBuffer.h"

class GeneratorStatement : public GeneratorBase
{
private:
    GeneratorStatement();		// deliberately not implemented
    friend class GeneratorRef;
    
public:
    GeneratorStatement( const std::string& name, const BaseCountedPtr<GeneratorBase>& valueGenerator );
    
protected:
    //virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorBase> m_valueGenerator;
};


class GeneratorStateStatement : public GeneratorStateBase
{
public:
    GeneratorStateStatement( int id)
    : GeneratorStateBase(id)
    {
    }
private:
    friend class GeneratorStatement;
};

