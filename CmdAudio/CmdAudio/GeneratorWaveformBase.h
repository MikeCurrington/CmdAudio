#pragma once
#include "GeneratorBase.h"

class GeneratorWaveformBase : public GeneratorBase
{
private:
	GeneratorWaveformBase();		// deliberately not implemented

public:
	GeneratorWaveformBase(int sampleRate);
	
protected:
	~GeneratorWaveformBase();
	virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value) override;
	//	virtual void Supply(DataBuffer & rDataBuffer, int startSample) = 0;

protected:
	int sampleRate;
	BaseCountedPtr<GeneratorBase> frequencyGenerator;
};


class GeneratorStateWaveformBase : public GeneratorStateBase
{
public:
    GeneratorStateWaveformBase( int id) : GeneratorStateBase(id)
    {
    }
};

