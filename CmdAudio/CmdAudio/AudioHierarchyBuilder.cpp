//
//  AudioHierarchyBuilder.cpp
//  CmdAudio
//
//  Created by Michael Currington on 8/29/16.
//  Copyright © 2016 Doodleoo Games. All rights reserved.
//

#include "AudioHierarchyBuilder.h"
#include "AudioHierarchy.h"

#include "GeneratorComponent.h"
#include "GeneratorConstant.h"

#include <map>

#include "antlr4-runtime.h"
#include "../GeneratedAntlr/CmdAudioLexer.h"
#include "../GeneratedAntlr/CmdAudioParser.h"
#include "../GeneratedAntlr/CmdAudioBaseListener.h"

#include "GeneratorBase.h"
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
#include "GeneratorUnbound.h"


/*
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
*/

static const int sampleRate = 22050;    ///TODO: remove this



class CmdAudioListenerImpl : public CmdAudioBaseListener
{
    typedef std::function<GeneratorBase*(int)> tGeneratorConstructor;
    typedef std::map<std::string,tGeneratorConstructor> tGeneratorToConstructor;
    struct GeneratorTypeToConstructor {
        operator const tGeneratorToConstructor() const {
            return map;
        }
        GeneratorTypeToConstructor();
        tGeneratorToConstructor map;
    } generatorTypeToConstructor;
    
public:
    virtual void enterGeneratordef(CmdAudioParser::GeneratordefContext * ctx) override
    {
        // Do something when entering the key rule.
        std::cout << "Generator ";
        auto name = ctx->NAME();
        std::cout << name->toString();
        auto parameterList = ctx->genparlist();
        
        std::cout << " paramcount=" << parameterList->children.size();
        
        auto component = new GeneratorComponent(sampleRate);
        m_components.insert( std::pair<std::string,BaseCountedPtr<GeneratorComponent>>( name->toString(), component ) );
        if (name->toString()=="Main")
        {
            m_mainComponent = component;
        }
        m_currentComponent = component;
        
        for(auto i : parameterList->children)
        {
        }
        std::cout << "\n";
    }
        
    virtual void exitGeneratordef(CmdAudioParser::GeneratordefContext * ctx) override
    {
        m_currentComponent = nullptr;
        std::cout << "exit gen\n";
    }
        
    virtual void enterStat(CmdAudioParser::StatContext * ctx) override
    {
        auto name = ctx->NAME();
        std::cout << "stat " << name->getText();
        
        Ref<CmdAudioParser::ExpContext> expression = ctx->exp();
        
        BaseCountedPtr<GeneratorBase> statementGenerator = ProcessExpression( expression );
        m_statementLocals.insert( std::pair<std::string,BaseCountedPtr<GeneratorBase>>( name->getText(), statementGenerator ) );
    }
        
    
    BaseCountedPtr<GeneratorBase>  ProcessExpression( Ref<CmdAudioParser::ExpContext> expression )
    {
        BaseCountedPtr<GeneratorBase> generator;
        
        if ( expression->number() )
        {
            Ref<CmdAudioParser::NumberContext> number = expression->number();
            generator = new GeneratorConstant( atof(number->getText().c_str()) );
        }
        else if ( expression->prefixexp() )
        {
            auto prefixExp = expression->prefixexp();
            if ( prefixExp->var() )
            {
                std::cout << "= var:" << prefixExp->var()->NAME()->getText() << "\n";
            }
            else if ( prefixExp->function() )
            {
                auto func = prefixExp->function();
                std::string funcName = func->NAME()->getText();
                std::cout << "= function:" << funcName << "\n";

                // See if the function is a known generator
                auto generatorConstructIt = generatorTypeToConstructor.map.find(funcName);
                if (generatorConstructIt != generatorTypeToConstructor.map.end())
                {
                    generator = generatorConstructIt->second(sampleRate);
                }
                else
                {
                    for( auto componentStackIter = m_componentStack.rbegin(); componentStackIter != m_componentStack.rend(); ++componentStackIter )
                    {
                        auto foundComponentIt = componentStackIter->find(funcName);
                        if (foundComponentIt != componentStackIter->end())
                        {
                            BaseCountedPtr<GeneratorBase> foundComponent = foundComponentIt->second;
                            generator  = new GeneratorInstance( foundComponent.StaticCast<GeneratorComponent>() );
                        }
                    }
                }
                
                
                // Grab the parameters
                auto argumentList = prefixExp->namedArgList();
                if (argumentList)
                {
                    auto namedArgs = argumentList->namedArg();
                    
                    for( const auto & arg : namedArgs )
                    {
                        auto argName = arg->var()->NAME()->getText();
                        auto argValue = arg->exp();
                        BaseCountedPtr<GeneratorBase> expGenerator = ProcessExpression( argValue );
                        
                        generator->AddInput(argName, expGenerator);
                    }
                }
            }
        }
        else
        {
            std::cout << "unknown right side of stat\n";
            assert(0);
        }
        return generator;
    }
        
    virtual void exitStat(CmdAudioParser::StatContext * ctx) override
    {
        std::cout << "exit stat\n";
    }
        
    virtual void enterOutputstat(CmdAudioParser::OutputstatContext * ctx) override
    {
        std::cout << ctx->getText();
        auto outputExp = ctx->exp();
        auto outputPrefixExp = outputExp->prefixexp();
        auto outputPrefixExpVar = outputPrefixExp->var();
        auto varName = outputPrefixExpVar->NAME()->getText();
        auto foundStatementIt = m_statementLocals.find(varName);
        if (foundStatementIt != m_statementLocals.end())
        {
            m_currentComponent.StaticCast<GeneratorBase>()->AddInput( "source", foundStatementIt->second );
        }
        else
        {
            assert(0);
        }
    }

    
    BaseCountedPtr<GeneratorComponent> GetMainComponent() const      { return m_mainComponent; }

private:
    BaseCountedPtr<GeneratorComponent> m_currentComponent;
    //BaseCountedPtr<GeneratorBase> m_statementGenerator;
    std::unordered_map<std::string, BaseCountedPtr<GeneratorBase>> m_statementLocals;
        
protected:
    BaseCountedPtr<GeneratorComponent> m_mainComponent;
    std::map<std::string, BaseCountedPtr<GeneratorComponent>> m_components;
        

    std::vector< std::map< std::string, BaseCountedPtr<GeneratorBase> > > m_componentStack;
    std::vector< std::map< std::string, BaseCountedPtr<GeneratorUnbound> > > m_unboundStack;
        //        std::map<
};


CmdAudioListenerImpl::GeneratorTypeToConstructor::GeneratorTypeToConstructor() {
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
}
        

        
BaseCountedPtr<GeneratorComponent> AudioHierarchyBuilder::Build( antlr4::ANTLRInputStream* input )
{
    CmdAudioLexer lexer(input);
    antlr4::CommonTokenStream tokens(&lexer);
    CmdAudioParser parser(&tokens);
    Ref<tree::ParseTree> tree = parser.chunk();

    Ref<CmdAudioListenerImpl> listener(new CmdAudioListenerImpl());
    Ref<tree::ParseTreeWalker> walker(new tree::ParseTreeWalker());
    walker->walk(listener.get(), tree.get());
    //std::cout << tree->toStringTree(&parser) << std::endl;
    
    return listener->GetMainComponent();
    
}


