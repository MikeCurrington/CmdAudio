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

void GeneratorValueTransformHardClip::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(paramName.c_str(), "clip") == 0)
	{
		this->clip = value;
	}
	else
		GeneratorValueTransform::AddInput(paramName, value);
}

void GeneratorValueTransformHardClip::Supply(MachineState& machineState, BaseCountedPtr<SampleDataBuffer>& rDataBuffer, int startSample)
{
	if (sourceBuffer)
	{
		sourceBuffer->Supply(machineState, rDataBuffer, startSample);

		if (clip)
		{
			BaseCountedPtr<SampleDataBuffer> clipDataBuffer( new SampleDataBuffer(rDataBuffer->GetLength()) );
			clip->Supply(machineState, clipDataBuffer, startSample);

			for (int i = 0; i < rDataBuffer->GetLength(); i++)
			{
                float f = rDataBuffer->Get(i);
                float clipf = clipDataBuffer->Get(i);
                if (f > clipf)
                	f = clipf;
                else if (f < -clipf)
                	f = -clipf;
				rDataBuffer->Get(i) = f;
			}
		}
	}
}
