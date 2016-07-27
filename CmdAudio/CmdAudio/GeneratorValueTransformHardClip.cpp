#include "stdafx.h"
#include "string.h"
#include "math.h"
#include "GeneratorValueTransformHardClip.h"


GeneratorValueTransformHardClip::GeneratorValueTransformHardClip() : GeneratorValueTransform(), clip(nullptr)
{
}

GeneratorValueTransformHardClip::~GeneratorValueTransformHardClip()
{
}

void GeneratorValueTransformHardClip::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(pParamName, "clip") == 0)
	{
		this->clip = value;
	}
	else
		GeneratorValueTransform::AddInput(pParamName, value);
}

void GeneratorValueTransformHardClip::Supply(MachineState & machineState, SampleDataBuffer & rDataBuffer, int startSample)
{
	if (sourceBuffer)
	{
		sourceBuffer->Supply(machineState, rDataBuffer, startSample);

		if (clip)
		{
			SampleDataBuffer clipDataBuffer(rDataBuffer.GetLength());
			clip->Supply(machineState, clipDataBuffer, startSample);

			for (int i = 0; i < rDataBuffer.GetLength(); i++)
			{
                float f = rDataBuffer[i];
                float clipf = clipDataBuffer[i];
                if (f > clipf)
                	f = clipf;
                else if (f < -clipf)
                	f = -clipf;
				rDataBuffer[i] = f;
			}
		}
	}
}
