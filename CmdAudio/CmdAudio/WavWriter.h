#pragma once
#include "SampleDataBuffer.h"

class WavWriter
{
public:
	WavWriter(int sampleRate);
	~WavWriter();

	void Write(const char * const filename, const SampleDataBuffer & output);

protected:
	const int sampleRate;
};

