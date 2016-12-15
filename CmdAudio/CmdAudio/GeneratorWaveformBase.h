#pragma once
#include "GeneratorBase.h"

class GeneratorWaveformBase : public GeneratorBase
{
private:
	GeneratorWaveformBase();		// deliberately not implemented

public:
	GeneratorWaveformBase(const std::string & name, int sampleRate);
	
protected:
	virtual ~GeneratorWaveformBase();
	virtual void AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value) override;
	//	virtual void Supply(DataBuffer & rDataBuffer, int startSample) = 0;

protected:
	int sampleRate;
    BaseCountedPtr<GeneratorBase> m_frequencyGenerator;
};


class GeneratorStateWaveformBase : public GeneratorStateBase
{
public:
    GeneratorStateWaveformBase( int id) : GeneratorStateBase(id), m_phase(0.0f)
    {
    }
    float GetPhase() const      { return m_phase; }
    void  SetPhase(float phase) {m_phase = phase; }
private:
    float m_phase;
};

