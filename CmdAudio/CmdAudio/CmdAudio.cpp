// CmdAudio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SampleDataBuffer.h"
#include "WavWriter.h"
#include "GeneratorLerp.h"
#include "GeneratorConstant.h"
#include "GeneratorDelay.h"
#include "GeneratorMultiply.h"
#include "GeneratorRamp.h"
#include "GeneratorSine.h"
#include "GeneratorSaw.h"
#include "GeneratorValueTransformHardClip.h"
#include "OutputWav.h"
#include "OutputAudioQueue.h"
#include "AudioHierarchy.h"
#include "CmdAudio.h"

#include "yaml-cpp/yaml.h"


//yaml-cpp/yaml.h"


// Helpers
static GeneratorBase * MakeLinearRamp(int sampleRate, float startVal, float endVal, float seconds)
{
	GeneratorBase * rampGen = new GeneratorRamp(sampleRate);
	GeneratorBase * rampTime = new GeneratorConstant(seconds);
	rampGen->AddInput("time", rampTime);
	GeneratorBase * minValueGen = new GeneratorConstant(startVal);
	GeneratorBase * maxValueGen = new GeneratorConstant(endVal);
	GeneratorBase * valueLerp = new GeneratorLerp();
	valueLerp->AddInput("value", rampGen);
	valueLerp->AddInput("min", minValueGen);
	valueLerp->AddInput("max", maxValueGen);

	rampGen->Release();
	rampTime->Release();
	minValueGen->Release();
	maxValueGen->Release();

	return valueLerp;
}

static GeneratorBase * MakeSineOscillator(int sampleRate, float minValue, float maxValue, float frequency )
{
	GeneratorBase * sineGen = new GeneratorSine(sampleRate);
	GeneratorBase * sineFreqGen = new GeneratorConstant(frequency);
	sineGen->AddInput("frequency", sineFreqGen);

	GeneratorBase * rangedValue = new GeneratorLerp();
	GeneratorBase * maxValueGen = new GeneratorConstant(maxValue);
	GeneratorBase * minValueGen = new GeneratorConstant(minValue);
	rangedValue->AddInput("value", sineGen);
	rangedValue->AddInput("min", minValueGen);
	rangedValue->AddInput("max", maxValueGen);

	maxValueGen->Release();
	minValueGen->Release();
	sineGen->Release();
	sineFreqGen->Release();

	return rangedValue;
}



YAML::Node LoadConfig( const char * filename )
{
    YAML::Node config = YAML::LoadFile( filename );
    return config;
}


int _main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage:\n cmdaudio <config.yaml> [-loop]");
        return -1;
    }
    
    bool loop = false;
    if (argc==3 && strcasecmp(argv[2], "-loop")==0)
    {
        loop = true;
    }
    
	const int sampleRate = 22050;
	const float sampleLengthSeconds = 8.0f;
	const int outputLength = (int) (sampleRate * sampleLengthSeconds);	// length of sample to generate

    do {
        auto config = LoadConfig( argv[1] );
        
        AudioHierarchy * hierarchy = new AudioHierarchy( config, sampleRate );
        hierarchy->Write(outputLength);
        delete hierarchy;
        hierarchy = nullptr;
    } while(loop);
    
	GeneratorBase::CheckMemFree();

	return 0;
}




