//
//  GeneratorFilterComb.h
//  CmdAudio
//
//  Created by Michael Currington on 7/30/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//
#pragma once

#include "GeneratorValueTransform.h"

class GeneratorFilterComb : public GeneratorValueTransform
{
public:
    GeneratorFilterComb();
    ~GeneratorFilterComb();
    
    virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
    virtual void Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample) override;
protected:
    BaseCountedPtr<GeneratorBase> delayGenerator;
    BaseCountedPtr<GeneratorBase> feedbackGainGenerator;
};


class GeneratorStateFilterComb : public GeneratorStateBase
{
public:
    GeneratorStateFilterComb(int id);
    ~GeneratorStateFilterComb()
    {
        delete m_delayBuffer;
    }
    void  Write( float v );
    float Read( float offset );
private:
    friend class GeneratorFilterComb;
    SampleDataBuffer* m_delayBuffer;
    int m_writeOffset;
    
    const int cMaxBufferSamples = 22050;
};
