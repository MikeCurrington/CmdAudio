// CmdAudio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SampleDataBuffer.h"
#include "WavWriter.h"
#include "GeneratorInstance.h"
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
#include "MachineState.h"
#include "AudioHierarchy.h"
#include "CmdAudio.h"
#include "AudioHierarchyBuilder.h"

#include "antlr4-runtime.h"
//using namespace antlrcpptest;
//using namespace antlr4;

#include "yaml-cpp/yaml.h"



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



BaseCountedPtr<GeneratorBase> LoadProgram( const char * filename, int sampleRate )
{
    antlr4::ANTLRInputStream input("generator Main(time) = {\n      \
                                   state  beep = Sine( time: time );\n         \
                                   output beep;\n                \
                                   }");
    AudioHierarchyBuilder builder;
    BaseCountedPtr<GeneratorComponent> component = builder.Build( &input );
                                   
    return new GeneratorInstance( component );
                                   
    /*
     
     // Syntax
     beep = Sine( freq=1000 )
     env  = Lerp( Ramp( time=1 ), 1, 0 )
     out  = env * beep
     
     generator AttackRelease( time, attack, releaseTrigger, release ) =
     {
        state attackLerp = Lerp( Ramp( time=time, length=attack ), 0, 1 )
        state decayLerp = Lerp( Ramp( time=releaseTrigger*time, length=decay ), 1, 0 )
        output attackLerp * decayLerp
     }
     
     generator Main( time ) =
     {
         state beep = Sine( time=1000 )
         output beep
     }
     
     */
    
    
    
    
    /*
    auto tree = parser.program();
    
    CmdAudioVisitor visit = new CmdAudioVisitor();
    
    auto eval = new EvalVisitor();
    eval.Visit(tree);
    
    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }
     */
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

    MachineState machineState;
    do {
        AudioHierarchy * hierarchy = new AudioHierarchy( LoadProgram( argv[1], sampleRate ), sampleRate );
        //AudioHierarchy * hierarchy = new AudioHierarchy( config, sampleRate );
        
        //auto config = LoadConfig( argv[1] );
        //AudioHierarchy * hierarchy = new AudioHierarchy( config, sampleRate );
        
        hierarchy->Write(machineState, outputLength);
        delete hierarchy;
        hierarchy = nullptr;
    } while(loop);
    
	GeneratorBase::CheckMemFree();

	return 0;
}




