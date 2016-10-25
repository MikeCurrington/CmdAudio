//
//  GeneratorRef.h
//  CmdAudio
//
//
//  Reference to a statement
//
//  Created by Michael Currington on 10/16/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorStatement.h"

class GeneratorRef : public GeneratorBase
{
private:
    GeneratorRef();		// deliberately not implemented
    
public:
    GeneratorRef( BaseCountedPtr<GeneratorStatement>& valueGenerator );
    
protected:
    virtual void Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample) override;
    
protected:
    BaseCountedPtr<GeneratorStatement> m_statementGenerator;
};
