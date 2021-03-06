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
#include "GeneratorHold.h"
#include "GeneratorNoise.h"
#include "GeneratorPinkify.h"
#include "GeneratorMidiChannel.h"
#include "GeneratorUnbound.h"
#include "GeneratorStatement.h"
#include "GeneratorRef.h"


static const int sampleRate = 22050;    ///TODO: remove this



class CmdAudioListenerImpl : public CmdAudioBaseListener
{
    typedef std::function<GeneratorBase*(const std::string& name, int sampleRate)> tGeneratorConstructor;
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
        const auto& parameterList = ctx->genparlist();
        
        auto component = new GeneratorComponent(name->toString(), sampleRate);
        m_components.insert( std::pair<std::string,BaseCountedPtr<GeneratorComponent>>( name->toString(), component ) );
        if (name->toString()=="Main")
        {
            m_mainComponent = component;
        }
        m_currentComponent = component;

        std::map< std::string, BaseCountedPtr<GeneratorBase> > generatorComponentStack;
        generatorComponentStack.insert( std::pair<std::string,BaseCountedPtr<GeneratorBase>>( name->toString(), m_currentComponent.StaticCast<GeneratorBase>() ) );
        m_componentStack.push_back( generatorComponentStack );
        
        if (parameterList)
        {
            BaseCountedPtr<GeneratorBase> parameterArray = new GeneratorArray("params");
            int paramCount = 0;
            const auto& namelist = parameterList->namelist();
            for(const auto& parameterNameToken : namelist->NAME())
            {
                const auto& parameterName = parameterNameToken->getSymbol()->getText();
                parameterArray->AddInput( parameterName, nullptr);
                paramCount++;
            }
            m_currentComponent.StaticCast<GeneratorBase>()->AddInput("inputs", parameterArray);
            std::cout << " paramcount=" << paramCount;
        }
        else
        {
            std::cout << " paramcount=0";
        }
        std::cout << "\n";
    }
        
    virtual void exitGeneratordef(CmdAudioParser::GeneratordefContext * ctx) override
    {
        //new   m_currentComponent );
        m_currentComponent = nullptr;
        m_statementLocalsUsage.clear();
        m_statementLocals.clear();
        std::cout << "exit gen\n";
    }
        
    virtual void enterStat(CmdAudioParser::StatContext * ctx) override
    {
        auto name = ctx->NAME();
        std::cout << "stat " << name->getText();
        
        Ref<CmdAudioParser::ExpContext> expression = ctx->exp();
        
        BaseCountedPtr<GeneratorStatement> statementGenerator = new GeneratorStatement( name->getText(), ProcessExpression( expression ) );
        m_statementLocals.insert( std::pair<std::string,BaseCountedPtr<GeneratorStatement>>( name->getText(), statementGenerator ) );
        m_statementLocalsUsage.insert( std::pair<std::string, int>( name->getText(), 0 ) );
    }
    
    
    BaseCountedPtr<GeneratorBase>  ProcessExpression( Ref<CmdAudioParser::ExpContext> expression )
    {
        BaseCountedPtr<GeneratorBase> generator;
        
        if ( expression->number() )
        {
            Ref<CmdAudioParser::NumberContext> number = expression->number();
            generator = new GeneratorConstant( number->getText(), atof(number->getText().c_str()) );
        }
        else if ( expression->prefixexp() )
        {
            const auto& prefixExp = expression->prefixexp();
            if ( prefixExp->varOrExp() )
            {
                auto varOrExp = prefixExp->varOrExp();
                if (varOrExp->var())
                {
                    const std::string & varName = varOrExp->var()->NAME()->getText();
                    std::cout << "= var:" << varName << "\n";
                    const auto& foundVarIter = m_statementLocals.find(varName);
                    if ( foundVarIter != m_statementLocals.end() )
                    {
                        generator = foundVarIter->second.StaticCast<GeneratorBase>();
                        m_statementLocalsUsage.find(varName)->second++;
                    }
                    else
                    {
                        generator = new GeneratorUnbound( varName );
                    }
                }
                else if (varOrExp->exp())
                {
                    generator = ProcessExpression( varOrExp->exp() );
                }
                else
                {
                    std::cout << " not a var or exp\n";
                    assert(0);
                }
            }
            else if ( prefixExp->function() )
            {
                const auto& func = prefixExp->function();
                const std::string& funcName = func->NAME()->getText();
                std::cout << "= function:" << funcName << "\n";

                // See if the function is a known generator
                const auto& generatorConstructIt = generatorTypeToConstructor.map.find(funcName);
                if (generatorConstructIt != generatorTypeToConstructor.map.end())
                {
                    generator = generatorConstructIt->second(funcName, sampleRate);
                }
                else
                {
                    for( auto componentStackIter = m_componentStack.rbegin(); componentStackIter != m_componentStack.rend(); ++componentStackIter )
                    {
                        auto foundComponentIt = componentStackIter->find(funcName);
                        if (foundComponentIt != componentStackIter->end())
                        {
                            BaseCountedPtr<GeneratorBase> foundComponent = foundComponentIt->second;
                            generator  = new GeneratorInstance( funcName, foundComponent.StaticCast<GeneratorComponent>() );
                        }
                    }
                }
                if (!generator)
                {
                    std::cout << "cannot find " << funcName;
                    assert(0);
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
        else if (expression->operatorUnary())
        {
            const auto& unary = expression->operatorUnary();
            if ( unary->getText() == "-" )
            {
                const auto& unaryExp = expression->exp();
                assert(unaryExp.size() == 1);
                generator = ProcessExpression( *unaryExp.begin() );
                GeneratorConstant* constantGen = dynamic_cast<GeneratorConstant*>( generator.Obj() );
                if (constantGen != nullptr)
                {
                    generator = new GeneratorConstant( constantGen->GetName(), -constantGen->GetValue() );
                }
                else
                    assert(0);  // cant do unary on a non const (yet), implement with a multiply by -1
            }
            else{
                assert(0);
            }
        }
        else if (expression->operatorMulDiv())
        {
            auto muldiv = expression->operatorMulDiv();
            if ( muldiv->getText() == "*" )
                std::cout << " mult\n";
            else
                std::cout << " div\n";
            BaseCountedPtr<GeneratorBase> multArrayGenerator = new GeneratorArray("muldiv");
            int paramCount = 0;
            
            for( const auto& exp : expression->exp() )
            {
                BaseCountedPtr<GeneratorBase> multParamGenerator = ProcessExpression( exp );
                multArrayGenerator->AddInput( std::to_string(paramCount), multParamGenerator);
                paramCount++;
            }
            
            BaseCountedPtr<GeneratorMultiply> multGenerator = new GeneratorMultiply("*");
            multGenerator->AddInput("in", multArrayGenerator.StaticCast<GeneratorBase>());
            
            generator = multGenerator.StaticCast<GeneratorBase>();
        }
        else if (expression->operatorAddSub())
        {
            auto addsub = expression->operatorAddSub();
            if ( addsub->getText() == "+" )
                std::cout << " add\n";
            else
                std::cout << " sub\n";
            BaseCountedPtr<GeneratorBase> addArrayGenerator = new GeneratorArray("addsub");
            int paramCount = 0;
            
            for( const auto& exp : expression->exp() )
            {
                BaseCountedPtr<GeneratorBase> addParamGenerator = ProcessExpression( exp );
                addArrayGenerator->AddInput( std::to_string(paramCount), addParamGenerator);
                paramCount++;
            }
            
            BaseCountedPtr<GeneratorAdd> addGenerator = new GeneratorAdd("+");
            addGenerator->AddInput("in", addArrayGenerator.StaticCast<GeneratorBase>());
            
            generator = addGenerator.StaticCast<GeneratorBase>();
        }
        else
        {
            std::cout << " unknown right side of stat\n";
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
        auto outputPrefixExpVarOrExp = outputPrefixExp->varOrExp();
        if (outputPrefixExpVarOrExp->var())
        {
            const auto& varName = outputPrefixExpVarOrExp->var()->NAME()->getText();
            auto foundStatementIt = m_statementLocals.find(varName);
            if (foundStatementIt != m_statementLocals.end())
            {
                m_currentComponent.StaticCast<GeneratorBase>()->AddInput( "source", foundStatementIt->second.StaticCast<GeneratorBase>() );
                m_statementLocalsUsage.find(varName)->second++;
            }
            else
            {
                std::cout << "output cannot find variable " << varName;
                assert(0);
            }
        }
        else
        {
            m_currentComponent.StaticCast<GeneratorBase>()->AddInput( "source", ProcessExpression( outputPrefixExpVarOrExp->exp() ) );
        }
    }

    
    BaseCountedPtr<GeneratorComponent> GetMainComponent() const      { return m_mainComponent; }

private:
    BaseCountedPtr<GeneratorComponent> m_currentComponent;
    //BaseCountedPtr<GeneratorBase> m_statementGenerator;
    std::unordered_map<std::string, BaseCountedPtr<GeneratorStatement>> m_statementLocals;
    std::unordered_map<std::string, int> m_statementLocalsUsage;
        
protected:
    BaseCountedPtr<GeneratorComponent> m_mainComponent;
    std::map<std::string, BaseCountedPtr<GeneratorComponent>> m_components;
        

    std::vector< std::map< std::string, BaseCountedPtr<GeneratorBase> > > m_componentStack;
    std::vector< std::map< std::string, BaseCountedPtr<GeneratorUnbound> > > m_unboundStack;
        //        std::map<
};


CmdAudioListenerImpl::GeneratorTypeToConstructor::GeneratorTypeToConstructor() {
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


