#pragma once
//
//  AudioHierarchy.h
//  CmdAudio
//
//  Created by Michael Currington on 11/12/15.
//  Copyright (c) 2015 Doodleoo Games. All rights reserved.
//
#include "GeneratorBase.h"
#include "BaseCounted.h"
#include "OutputBase.h"

#include <unordered_map>
#include "yaml-cpp/yaml.h"

class AudioHierarchySchema
{
public:
    AudioHierarchySchema( const YAML::Node config );
    ~AudioHierarchySchema();
};



class AudioHierarchy
{
public:
    AudioHierarchy( const YAML::Node config, int sampleRate );
    AudioHierarchy( BaseCountedPtr<GeneratorBase> generator, int sampleRate );
    //    AudioHierarchy( )
    ~AudioHierarchy();
    
    void Write( MachineState& machineState, int outputLength );
    
protected:
    std::pair<std::string, BaseCountedPtr<GeneratorBase>> ParseHierarchy( const YAML::Node & node, int sampleRate );
    BaseCountedPtr<GeneratorBase> ParseNode( const YAML::Node & freqNode, int sampleRate );

    std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>> generators;
    std::unordered_map<std::string, OutputBase*> outputs;

private:
    
    typedef std::function<GeneratorBase*(const std::string& name, int sampleRate)> tGeneratorConstructor;
    typedef std::map<std::string,tGeneratorConstructor> tGeneratorToConstructor;
    struct GeneratorTypeToConstructor {
        operator const tGeneratorToConstructor() const {
            return map;
        }
        GeneratorTypeToConstructor();
        tGeneratorToConstructor map;
    } generatorTypeToConstructor;

    typedef std::function<OutputBase*(int)> tOutputFunction;
    typedef std::map<std::string,tOutputFunction> tOutputToFunction;
    struct OutputTypeToFunction {
        operator const tOutputToFunction() const {
            return map;
        }
        OutputTypeToFunction();
        tOutputToFunction map;
    } outputTypeToFunction;
};
