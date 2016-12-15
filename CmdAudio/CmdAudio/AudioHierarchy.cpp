//
//  AudioHierarchy.cpp
//  CmdAudio
//
//  Created by Michael Currington on 11/12/15.
//  Copyright (c) 2015 Doodleoo Games. All rights reserved.
//
#include "AudioHierarchy.h"
#include "GeneratorArray.h"
#include "GeneratorConstant.h"
#include "GeneratorSine.h"
#include "GeneratorSaw.h"
#include "GeneratorSquare.h"
#include "GeneratorLerp.h"
#include "GeneratorLerp01.h"
#include "GeneratorThreshold.h"
#include "GeneratorDelay.h"
#include "GeneratorComponent.h"
#include "GeneratorInstance.h"
#include "GeneratorMultiply.h"
#include "GeneratorAdd.h"
#include "GeneratorRamp.h"
#include "GeneratorPulse.h"
#include "GeneratorUnbound.h"
#include "GeneratorValueTransformHardClip.h"
#include "GeneratorFilter.h"
#include "GeneratorFilterHigh.h"
#include "GeneratorFilterComb.h"
#include "GeneratorNoise.h"
#include "GeneratorPinkify.h"
#include "GeneratorHold.h"
#include "GeneratorMidiChannel.h"


#include "OutputWav.h"
#include "OutputAudioQueue.h"

#include <boost/unordered_map.hpp>
#include <boost/assign/list_of.hpp>
using boost::assign::map_list_of;


AudioHierarchy::GeneratorTypeToConstructor::GeneratorTypeToConstructor() {
    map.insert( tGeneratorToConstructor::value_type(std::string("Sine"), [](const std::string& name, int sampleRate) { return new GeneratorSine(name, sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Saw"), [](const std::string& name, int sampleRate) { return new GeneratorSaw(name, sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Square"), [](const std::string& name, int sampleRate) { return new GeneratorSquare(name, sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Lerp"), [](const std::string& name, int sampleRate) { return new GeneratorLerp(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Lerp01"), [](const std::string& name, int sampleRate) { return new GeneratorLerp01(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Threshold"), [](const std::string& name, int sampleRate) { return new GeneratorThreshold(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Delay"), [](const std::string& name, int sampleRate) { return new GeneratorDelay(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Multiply"), [](const std::string& name, int sampleRate) { return new GeneratorMultiply(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Add"), [](const std::string& name, int sampleRate) { return new GeneratorAdd(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Pulse"), [](const std::string& name, int sampleRate) { return new GeneratorPulse(name, sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Ramp"), [](const std::string& name, int sampleRate) { return new GeneratorRamp(name, sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Hardclip"), [](const std::string& name, int sampleRate) { return new GeneratorValueTransformHardClip(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("FilterLadder"), [](const std::string& name, int sampleRate) { return new GeneratorFilter(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("FilterHigh"), [](const std::string& name, int sampleRate) { return new GeneratorFilterHigh(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("FilterComb"), [](const std::string& name, int sampleRate) { return new GeneratorFilterComb(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Hold"), [](const std::string& name, int sampleRate) { return new GeneratorHold(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Noise"), [](const std::string& name, int sampleRate) { return new GeneratorNoise(name);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Pinkify"), [](const std::string& name, int sampleRate) { return new GeneratorPinkify(name, sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("MidiChannel"), [](const std::string& name, int sampleRate) { return new GeneratorMidiChannel(name, sampleRate);}) );

    map.insert( tGeneratorToConstructor::value_type(std::string("Component"), [](const std::string& name, int sampleRate) { return new GeneratorComponent(name, sampleRate);}) );
}

AudioHierarchy::OutputTypeToFunction::OutputTypeToFunction() {
    map.insert( tOutputToFunction::value_type(std::string("wav"), [](int sampleRate) { return new OutputWav(sampleRate); }) );
    map.insert( tOutputToFunction::value_type(std::string("audio"), [](int sampleRate) { return new OutputAudioQueue(sampleRate); }) );
}

AudioHierarchy::AudioHierarchy( const YAML::Node config, int sampleRate )
{
    auto generatorNodes = config["Generators"];
    if (generatorNodes)
    {
        for( auto it=generatorNodes.begin(); it!=generatorNodes.end(); ++it )
        {
            if (it->IsMap())
            {
                auto h = ParseHierarchy( *it, sampleRate );
                generators.insert( h );
            }
        }
    }
    
    auto outputNodes = config["Outputs"];
    if (outputNodes)
    {
        for( auto it=outputNodes.begin(); it!=outputNodes.end(); ++it )
        {
            if (it->IsMap())
            {
                const std::string & id = (*it)["Id"].as<std::string>();
                const std::string & source = (*it)["Source"].as<std::string>();
                const std::string & type = (*it)["Type"].as<std::string>();
                
                auto outputConstructIt = outputTypeToFunction.map.find(type);
                if (outputConstructIt != outputTypeToFunction.map.end())
                {
                    OutputBase * o = outputConstructIt->second(sampleRate);
                
                    const std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>>::const_iterator foundSourceGenerator = generators.find(source);
                    if (foundSourceGenerator != generators.end())
                    {
                        o->AddInput( "source", foundSourceGenerator->second );
                        outputs.insert( std::make_pair(id,o) );
                    }
                    else
                    {
                        assert(0);
                    }
                }
                else
                {
                    assert(0);
                }
            }
        }
    }
}

AudioHierarchy::AudioHierarchy( BaseCountedPtr<GeneratorBase> generator, int sampleRate )
{
    const std::string & type = "audio";//"audio";//"wav";//
    auto outputConstructIt = outputTypeToFunction.map.find(type);
    if (outputConstructIt != outputTypeToFunction.map.end())
    {
        OutputBase * o = outputConstructIt->second(sampleRate);
        o->AddInput( "source", generator );
        outputs.insert( std::make_pair("out", o));
    }
    else
    {
        assert(0);
    }
}

std::pair<std::string, BaseCountedPtr<GeneratorBase>> AudioHierarchy::ParseHierarchy( const YAML::Node & baseNode, int sampleRate )
{
    const std::string & id = baseNode["Id"].as<std::string>();
    const std::string & type = baseNode["Type"].as<std::string>();
    fprintf(stdout, "id: %s\n", id.c_str() );
    
    GeneratorBase * g = nullptr;
    //                GeneratorTypeToConstructor.map.at
    auto generatorConstructIt = generatorTypeToConstructor.map.find(type);
    if (generatorConstructIt != generatorTypeToConstructor.map.end())
    {
        g = generatorConstructIt->second(id, sampleRate);
    }
    else
    {
        auto generator = generators.find(type);
        if (generator != generators.end())
        {
            BaseCountedPtr<GeneratorBase> parent = generator->second;
            g = new GeneratorInstance( id, parent.StaticCast<GeneratorComponent>() );
        }
    }
    
    for( YAML::const_iterator nodeIt = baseNode.begin(); nodeIt!=baseNode.end(); ++nodeIt )
    {
        const std::string & nodeId = nodeIt->first.as<std::string>();
        if (nodeId == "Id" || nodeId == "Type")
            continue;
        BaseCountedPtr<GeneratorBase> freqGenerator = ParseNode( nodeIt->second, sampleRate );
        g->AddInput( nodeId.c_str(), freqGenerator );
    }
    return std::make_pair(id,g);
}

BaseCountedPtr<GeneratorBase> AudioHierarchy::ParseNode( const YAML::Node & yamlNode, int sampleRate )
{
    BaseCountedPtr<GeneratorBase> freqGenerator;
    if (yamlNode.IsSequence())
    {
        freqGenerator = new GeneratorArray("array");
        for( auto it=yamlNode.begin(); it!=yamlNode.end(); ++it )
        {
            auto strVal = (*it).as<std::string>();
            try {
                float fVal = (*it).as<float>();
                fprintf(stdout, "  freq: %f\n", fVal );
                freqGenerator->AddInput( strVal.c_str(), new GeneratorConstant( strVal, fVal ) );
            }
            catch( YAML::TypedBadConversion<float> e )
            {
                fprintf(stdout, "array: %s\n", strVal.c_str());
                
                const std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>>::const_iterator foundGenerator = generators.find(strVal);
                if (foundGenerator != generators.end())
                {
                    freqGenerator->AddInput( strVal.c_str(), foundGenerator->second );
                }
                else
                {
                    freqGenerator->AddInput( strVal.c_str(), new GeneratorUnbound( strVal ) );
                }
            }
        }
    }
    else if (yamlNode.IsMap())
    {
        auto h = ParseHierarchy(yamlNode, sampleRate);
        freqGenerator = h.second;
    }
    else
    {
        try {
            float fVal = yamlNode.as<float>();
            fprintf(stdout, "  freq: %f\n", fVal );
            freqGenerator = new GeneratorConstant( "const", fVal );
        }
        catch( YAML::TypedBadConversion<float> e )
        {
            const std::string & strVal = yamlNode.as<std::string>();
            const std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>>::const_iterator foundGenerator = generators.find(strVal);
            if (foundGenerator != generators.end())
            {
                freqGenerator = foundGenerator->second;
            }
            else
            {
                freqGenerator = new GeneratorUnbound( strVal );
            }
        }
    }
    return freqGenerator;
}


void AudioHierarchy::Write( MachineState& machineState, int outputLength )
{
    for( auto it=outputs.begin(); it!=outputs.end(); ++it )
    {
        it->second->Write(machineState, outputLength);
    }
}

AudioHierarchy::~AudioHierarchy()
{
    for( auto it=outputs.begin(); it!=outputs.end(); ++it )
    {
        auto p = it->second;
        it->second = nullptr;
        delete p;
    }
}
