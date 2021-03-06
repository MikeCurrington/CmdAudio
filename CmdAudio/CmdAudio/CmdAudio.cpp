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
#include <ios>

#include "yaml-cpp/yaml.h"


BaseCountedPtr<GeneratorBase> LoadProgram( const char * filename, int sampleRate )
{
    antlr4::ANTLRInputStream input;
    
    std::filebuf fb;
    if (fb.open (filename, std::ios::in))
    {
        std::istream is(&fb);
        input.load( is );
    }

    AudioHierarchyBuilder builder;
    BaseCountedPtr<GeneratorComponent> component = builder.Build( &input );
                                   
    return new GeneratorInstance( filename, component );
                                   
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
         state beep = Sine( frequency=1000 )
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
	const float sampleLengthSeconds = 18.0f;
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




