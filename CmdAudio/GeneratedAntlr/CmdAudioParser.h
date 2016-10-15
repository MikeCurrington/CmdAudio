
// Generated from CmdAudio.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"


using namespace antlr4;



class CmdAudioParser : public Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, NAME = 18, INT = 19, FLOAT = 20, 
    STATEND = 21, LINE_COMMENT = 22, WS = 23
  };

  enum {
    RuleChunk = 0, RuleGeneratordef = 1, RuleGenparlist = 2, RuleNamelist = 3, 
    RuleBlock = 4, RuleStat = 5, RuleOutputstat = 6, RuleExplist = 7, RuleExp = 8, 
    RuleNumber = 9, RulePrefixexp = 10, RuleFunction = 11, RuleNamedArgList = 12, 
    RuleNamedArg = 13, RuleVarOrExp = 14, RuleVar = 15, RuleNameAndArgs = 16, 
    RuleArgs = 17, RuleOperatorUnary = 18, RuleOperatorMulDiv = 19, RuleOperatorAddSub = 20
  };

  CmdAudioParser(TokenStream *input);
  ~CmdAudioParser();

  virtual std::string getGrammarFileName() const override;
  virtual const atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual dfa::Vocabulary& getVocabulary() const override;


  class ChunkContext;
  class GeneratordefContext;
  class GenparlistContext;
  class NamelistContext;
  class BlockContext;
  class StatContext;
  class OutputstatContext;
  class ExplistContext;
  class ExpContext;
  class NumberContext;
  class PrefixexpContext;
  class FunctionContext;
  class NamedArgListContext;
  class NamedArgContext;
  class VarOrExpContext;
  class VarContext;
  class NameAndArgsContext;
  class ArgsContext;
  class OperatorUnaryContext;
  class OperatorMulDivContext;
  class OperatorAddSubContext; 

  class ChunkContext : public ParserRuleContext {
  public:
    ChunkContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> EOF();
    std::vector<Ref<GeneratordefContext>> generatordef();
    Ref<GeneratordefContext> generatordef(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<ChunkContext> chunk();

  class GeneratordefContext : public ParserRuleContext {
  public:
    GeneratordefContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> NAME();
    Ref<BlockContext> block();
    Ref<GenparlistContext> genparlist();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<GeneratordefContext> generatordef();

  class GenparlistContext : public ParserRuleContext {
  public:
    GenparlistContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<NamelistContext> namelist();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<GenparlistContext> genparlist();

  class NamelistContext : public ParserRuleContext {
  public:
    NamelistContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<tree::TerminalNode>> NAME();
    Ref<tree::TerminalNode> NAME(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<NamelistContext> namelist();

  class BlockContext : public ParserRuleContext {
  public:
    BlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<OutputstatContext> outputstat();
    std::vector<Ref<StatContext>> stat();
    Ref<StatContext> stat(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<BlockContext> block();

  class StatContext : public ParserRuleContext {
  public:
    StatContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> NAME();
    Ref<ExpContext> exp();
    Ref<tree::TerminalNode> STATEND();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<StatContext> stat();

  class OutputstatContext : public ParserRuleContext {
  public:
    OutputstatContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<ExpContext> exp();
    Ref<tree::TerminalNode> STATEND();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<OutputstatContext> outputstat();

  class ExplistContext : public ParserRuleContext {
  public:
    ExplistContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<ExpContext>> exp();
    Ref<ExpContext> exp(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<ExplistContext> explist();

  class ExpContext : public ParserRuleContext {
  public:
    ExpContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<NumberContext> number();
    Ref<PrefixexpContext> prefixexp();
    Ref<OperatorUnaryContext> operatorUnary();
    std::vector<Ref<ExpContext>> exp();
    Ref<ExpContext> exp(int i);
    Ref<OperatorMulDivContext> operatorMulDiv();
    Ref<OperatorAddSubContext> operatorAddSub();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<ExpContext> exp();
  Ref<ExpContext> exp(int precedence);
  class NumberContext : public ParserRuleContext {
  public:
    NumberContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> INT();
    Ref<tree::TerminalNode> FLOAT();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<NumberContext> number();

  class PrefixexpContext : public ParserRuleContext {
  public:
    PrefixexpContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<FunctionContext> function();
    Ref<NamedArgListContext> namedArgList();
    Ref<VarOrExpContext> varOrExp();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<PrefixexpContext> prefixexp();

  class FunctionContext : public ParserRuleContext {
  public:
    FunctionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> NAME();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<FunctionContext> function();

  class NamedArgListContext : public ParserRuleContext {
  public:
    NamedArgListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<NamedArgContext>> namedArg();
    Ref<NamedArgContext> namedArg(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<NamedArgListContext> namedArgList();

  class NamedArgContext : public ParserRuleContext {
  public:
    NamedArgContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<VarContext> var();
    Ref<ExpContext> exp();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<NamedArgContext> namedArg();

  class VarOrExpContext : public ParserRuleContext {
  public:
    VarOrExpContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<VarContext> var();
    Ref<ExpContext> exp();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<VarOrExpContext> varOrExp();

  class VarContext : public ParserRuleContext {
  public:
    VarContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> NAME();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<VarContext> var();

  class NameAndArgsContext : public ParserRuleContext {
  public:
    NameAndArgsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<ArgsContext> args();
    Ref<tree::TerminalNode> NAME();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<NameAndArgsContext> nameAndArgs();

  class ArgsContext : public ParserRuleContext {
  public:
    ArgsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<ExplistContext> explist();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<ArgsContext> args();

  class OperatorUnaryContext : public ParserRuleContext {
  public:
    OperatorUnaryContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<OperatorUnaryContext> operatorUnary();

  class OperatorMulDivContext : public ParserRuleContext {
  public:
    OperatorMulDivContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<OperatorMulDivContext> operatorMulDiv();

  class OperatorAddSubContext : public ParserRuleContext {
  public:
    OperatorAddSubContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;
   
  };

  Ref<OperatorAddSubContext> operatorAddSub();


  virtual bool sempred(Ref<RuleContext> const& _localctx, int ruleIndex, int predicateIndex) override;
  bool expSempred(Ref<ExpContext> const& _localctx, int predicateIndex);

private:
  static std::vector<dfa::DFA> _decisionToDFA;
  static atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static dfa::Vocabulary _vocabulary;
  static atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

