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
#include "GeneratorLerp.h"
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
#include "GeneratorMidiChannel.h"


#include "OutputWav.h"
#include "OutputAudioQueue.h"

#include <boost/unordered_map.hpp>
#include <boost/assign/list_of.hpp>
using boost::assign::map_list_of;


enum eConfigNodeType {
    Sine,
    Saw,
    Lerp,
    Function
};


AudioHierarchySchema::AudioHierarchySchema( const YAML::Node config )
{
    auto definitionNodes = config["Definitions"];
    if (definitionNodes)
    {
        for( auto it=definitionNodes.begin(); it!=definitionNodes.end(); ++it )
        {
            if (it->IsMap())
            {
                const std::string & name = (*it)["Id"].as<std::string>();
                const std::string & type = (*it)["Type"].as<std::string>();
                
            }
        }
    }
    
}


AudioHierarchy::GeneratorTypeToConstructor::GeneratorTypeToConstructor() {
    map.insert( tGeneratorToConstructor::value_type(std::string("Sine"), [](int sampleRate) { return new GeneratorSine(sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Saw"), [](int sampleRate) { return new GeneratorSaw(sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Lerp"), [](int sampleRate) { return new GeneratorLerp();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Delay"), [](int sampleRate) { return new GeneratorDelay();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Multiply"), [](int sampleRate) { return new GeneratorMultiply();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Add"), [](int sampleRate) { return new GeneratorAdd();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Pulse"), [](int sampleRate) { return new GeneratorPulse(sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Ramp"), [](int sampleRate) { return new GeneratorRamp(sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Hardclip"), [](int sampleRate) { return new GeneratorValueTransformHardClip();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("FilterLadder"), [](int sampleRate) { return new GeneratorFilter();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("FilterHigh"), [](int sampleRate) { return new GeneratorFilterHigh();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("FilterComb"), [](int sampleRate) { return new GeneratorFilterComb();}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Noise"), [](int sampleRate) { return new GeneratorNoise(sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("Pinkify"), [](int sampleRate) { return new GeneratorPinkify(sampleRate);}) );
    map.insert( tGeneratorToConstructor::value_type(std::string("MidiChannel"), [](int sampleRate) { return new GeneratorMidiChannel(sampleRate);}) );
    

    map.insert( tGeneratorToConstructor::value_type(std::string("Component"), [](int sampleRate) { return new GeneratorComponent(sampleRate);}) );
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
    const std::string & type = "audio";
    auto outputConstructIt = outputTypeToFunction.map.find(type);
    if (outputConstructIt != outputTypeToFunction.map.end())
    {
        OutputBase * o = outputConstructIt->second(sampleRate);
        o->AddInput( "source", generator );
        outputs.insert( std::make_pair("out", o));
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
        g = generatorConstructIt->second(sampleRate);
    }
    else
    {
        auto generator = generators.find(type);
        if (generator != generators.end())
        {
            BaseCountedPtr<GeneratorBase> parent = generator->second;
            g = new GeneratorInstance( parent.StaticCast<GeneratorComponent>() );
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
        freqGenerator = new GeneratorArray();
        for( auto it=yamlNode.begin(); it!=yamlNode.end(); ++it )
        {
            auto strVal = (*it).as<std::string>();
            try {
                float fVal = (*it).as<float>();
                fprintf(stdout, "  freq: %f\n", fVal );
                freqGenerator->AddInput( strVal.c_str(), new GeneratorConstant( fVal ) );
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
            freqGenerator = new GeneratorConstant( fVal );
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
