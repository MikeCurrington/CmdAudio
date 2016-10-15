
// Generated from CmdAudio.g4 by ANTLR 4.5.3


#include "CmdAudioListener.h"

#include "CmdAudioParser.h"


using namespace antlrcpp;
using namespace antlr4;

CmdAudioParser::CmdAudioParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CmdAudioParser::~CmdAudioParser() {
  delete _interpreter;
}

std::string CmdAudioParser::getGrammarFileName() const {
  return "CmdAudio.g4";
}

const std::vector<std::string>& CmdAudioParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CmdAudioParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ChunkContext ------------------------------------------------------------------

CmdAudioParser::ChunkContext::ChunkContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> CmdAudioParser::ChunkContext::EOF() {
  return getToken(CmdAudioParser::EOF, 0);
}

std::vector<Ref<CmdAudioParser::GeneratordefContext>> CmdAudioParser::ChunkContext::generatordef() {
  return getRuleContexts<CmdAudioParser::GeneratordefContext>();
}

Ref<CmdAudioParser::GeneratordefContext> CmdAudioParser::ChunkContext::generatordef(int i) {
  return getRuleContext<CmdAudioParser::GeneratordefContext>((size_t)i);
}


ssize_t CmdAudioParser::ChunkContext::getRuleIndex() const {
  return CmdAudioParser::RuleChunk;
}

void CmdAudioParser::ChunkContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChunk(this);
}

void CmdAudioParser::ChunkContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChunk(this);
}

Ref<CmdAudioParser::ChunkContext> CmdAudioParser::chunk() {
  Ref<ChunkContext> _localctx = std::make_shared<ChunkContext>(_ctx, getState());
  enterRule(_localctx, 0, CmdAudioParser::RuleChunk);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CmdAudioParser::T__0) {
      setState(42);
      generatordef();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(48);
    match(CmdAudioParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GeneratordefContext ------------------------------------------------------------------

CmdAudioParser::GeneratordefContext::GeneratordefContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> CmdAudioParser::GeneratordefContext::NAME() {
  return getToken(CmdAudioParser::NAME, 0);
}

Ref<CmdAudioParser::BlockContext> CmdAudioParser::GeneratordefContext::block() {
  return getRuleContext<CmdAudioParser::BlockContext>(0);
}

Ref<CmdAudioParser::GenparlistContext> CmdAudioParser::GeneratordefContext::genparlist() {
  return getRuleContext<CmdAudioParser::GenparlistContext>(0);
}


ssize_t CmdAudioParser::GeneratordefContext::getRuleIndex() const {
  return CmdAudioParser::RuleGeneratordef;
}

void CmdAudioParser::GeneratordefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGeneratordef(this);
}

void CmdAudioParser::GeneratordefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGeneratordef(this);
}

Ref<CmdAudioParser::GeneratordefContext> CmdAudioParser::generatordef() {
  Ref<GeneratordefContext> _localctx = std::make_shared<GeneratordefContext>(_ctx, getState());
  enterRule(_localctx, 2, CmdAudioParser::RuleGeneratordef);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    match(CmdAudioParser::T__0);
    setState(51);
    match(CmdAudioParser::NAME);
    setState(52);
    match(CmdAudioParser::T__1);
    setState(54);

    _la = _input->LA(1);
    if (_la == CmdAudioParser::NAME) {
      setState(53);
      genparlist();
    }
    setState(56);
    match(CmdAudioParser::T__2);
    setState(57);
    match(CmdAudioParser::T__3);
    setState(58);
    match(CmdAudioParser::T__4);
    setState(59);
    block();
    setState(60);
    match(CmdAudioParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenparlistContext ------------------------------------------------------------------

CmdAudioParser::GenparlistContext::GenparlistContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::NamelistContext> CmdAudioParser::GenparlistContext::namelist() {
  return getRuleContext<CmdAudioParser::NamelistContext>(0);
}


ssize_t CmdAudioParser::GenparlistContext::getRuleIndex() const {
  return CmdAudioParser::RuleGenparlist;
}

void CmdAudioParser::GenparlistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenparlist(this);
}

void CmdAudioParser::GenparlistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenparlist(this);
}

Ref<CmdAudioParser::GenparlistContext> CmdAudioParser::genparlist() {
  Ref<GenparlistContext> _localctx = std::make_shared<GenparlistContext>(_ctx, getState());
  enterRule(_localctx, 4, CmdAudioParser::RuleGenparlist);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    namelist();
    setState(64);

    _la = _input->LA(1);
    if (_la == CmdAudioParser::T__6) {
      setState(63);
      match(CmdAudioParser::T__6);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamelistContext ------------------------------------------------------------------

CmdAudioParser::NamelistContext::NamelistContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<tree::TerminalNode>> CmdAudioParser::NamelistContext::NAME() {
  return getTokens(CmdAudioParser::NAME);
}

Ref<tree::TerminalNode> CmdAudioParser::NamelistContext::NAME(int i) {
  return getToken(CmdAudioParser::NAME, (size_t)i);
}


ssize_t CmdAudioParser::NamelistContext::getRuleIndex() const {
  return CmdAudioParser::RuleNamelist;
}

void CmdAudioParser::NamelistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamelist(this);
}

void CmdAudioParser::NamelistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamelist(this);
}

Ref<CmdAudioParser::NamelistContext> CmdAudioParser::namelist() {
  Ref<NamelistContext> _localctx = std::make_shared<NamelistContext>(_ctx, getState());
  enterRule(_localctx, 6, CmdAudioParser::RuleNamelist);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    int alt;
    enterOuterAlt(_localctx, 1);
    setState(66);
    match(CmdAudioParser::NAME);
    setState(71);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(67);
        match(CmdAudioParser::T__6);
        setState(68);
        match(CmdAudioParser::NAME); 
      }
      setState(73);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

CmdAudioParser::BlockContext::BlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::OutputstatContext> CmdAudioParser::BlockContext::outputstat() {
  return getRuleContext<CmdAudioParser::OutputstatContext>(0);
}

std::vector<Ref<CmdAudioParser::StatContext>> CmdAudioParser::BlockContext::stat() {
  return getRuleContexts<CmdAudioParser::StatContext>();
}

Ref<CmdAudioParser::StatContext> CmdAudioParser::BlockContext::stat(int i) {
  return getRuleContext<CmdAudioParser::StatContext>((size_t)i);
}


ssize_t CmdAudioParser::BlockContext::getRuleIndex() const {
  return CmdAudioParser::RuleBlock;
}

void CmdAudioParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void CmdAudioParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

Ref<CmdAudioParser::BlockContext> CmdAudioParser::block() {
  Ref<BlockContext> _localctx = std::make_shared<BlockContext>(_ctx, getState());
  enterRule(_localctx, 8, CmdAudioParser::RuleBlock);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CmdAudioParser::T__7) {
      setState(74);
      stat();
      setState(79);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(80);
    outputstat();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

CmdAudioParser::StatContext::StatContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> CmdAudioParser::StatContext::NAME() {
  return getToken(CmdAudioParser::NAME, 0);
}

Ref<CmdAudioParser::ExpContext> CmdAudioParser::StatContext::exp() {
  return getRuleContext<CmdAudioParser::ExpContext>(0);
}

Ref<tree::TerminalNode> CmdAudioParser::StatContext::STATEND() {
  return getToken(CmdAudioParser::STATEND, 0);
}


ssize_t CmdAudioParser::StatContext::getRuleIndex() const {
  return CmdAudioParser::RuleStat;
}

void CmdAudioParser::StatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStat(this);
}

void CmdAudioParser::StatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStat(this);
}

Ref<CmdAudioParser::StatContext> CmdAudioParser::stat() {
  Ref<StatContext> _localctx = std::make_shared<StatContext>(_ctx, getState());
  enterRule(_localctx, 10, CmdAudioParser::RuleStat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(CmdAudioParser::T__7);
    setState(83);
    match(CmdAudioParser::NAME);
    setState(84);
    match(CmdAudioParser::T__3);
    setState(85);
    exp(0);
    setState(86);
    match(CmdAudioParser::STATEND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OutputstatContext ------------------------------------------------------------------

CmdAudioParser::OutputstatContext::OutputstatContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::ExpContext> CmdAudioParser::OutputstatContext::exp() {
  return getRuleContext<CmdAudioParser::ExpContext>(0);
}

Ref<tree::TerminalNode> CmdAudioParser::OutputstatContext::STATEND() {
  return getToken(CmdAudioParser::STATEND, 0);
}


ssize_t CmdAudioParser::OutputstatContext::getRuleIndex() const {
  return CmdAudioParser::RuleOutputstat;
}

void CmdAudioParser::OutputstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOutputstat(this);
}

void CmdAudioParser::OutputstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOutputstat(this);
}

Ref<CmdAudioParser::OutputstatContext> CmdAudioParser::outputstat() {
  Ref<OutputstatContext> _localctx = std::make_shared<OutputstatContext>(_ctx, getState());
  enterRule(_localctx, 12, CmdAudioParser::RuleOutputstat);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(CmdAudioParser::T__8);
    setState(89);
    exp(0);
    setState(90);
    match(CmdAudioParser::STATEND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExplistContext ------------------------------------------------------------------

CmdAudioParser::ExplistContext::ExplistContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<CmdAudioParser::ExpContext>> CmdAudioParser::ExplistContext::exp() {
  return getRuleContexts<CmdAudioParser::ExpContext>();
}

Ref<CmdAudioParser::ExpContext> CmdAudioParser::ExplistContext::exp(int i) {
  return getRuleContext<CmdAudioParser::ExpContext>((size_t)i);
}


ssize_t CmdAudioParser::ExplistContext::getRuleIndex() const {
  return CmdAudioParser::RuleExplist;
}

void CmdAudioParser::ExplistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplist(this);
}

void CmdAudioParser::ExplistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplist(this);
}

Ref<CmdAudioParser::ExplistContext> CmdAudioParser::explist() {
  Ref<ExplistContext> _localctx = std::make_shared<ExplistContext>(_ctx, getState());
  enterRule(_localctx, 14, CmdAudioParser::RuleExplist);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    exp(0);
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CmdAudioParser::T__6) {
      setState(93);
      match(CmdAudioParser::T__6);
      setState(94);
      exp(0);
      setState(99);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

CmdAudioParser::ExpContext::ExpContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::NumberContext> CmdAudioParser::ExpContext::number() {
  return getRuleContext<CmdAudioParser::NumberContext>(0);
}

Ref<CmdAudioParser::PrefixexpContext> CmdAudioParser::ExpContext::prefixexp() {
  return getRuleContext<CmdAudioParser::PrefixexpContext>(0);
}

Ref<CmdAudioParser::OperatorUnaryContext> CmdAudioParser::ExpContext::operatorUnary() {
  return getRuleContext<CmdAudioParser::OperatorUnaryContext>(0);
}

std::vector<Ref<CmdAudioParser::ExpContext>> CmdAudioParser::ExpContext::exp() {
  return getRuleContexts<CmdAudioParser::ExpContext>();
}

Ref<CmdAudioParser::ExpContext> CmdAudioParser::ExpContext::exp(int i) {
  return getRuleContext<CmdAudioParser::ExpContext>((size_t)i);
}

Ref<CmdAudioParser::OperatorMulDivContext> CmdAudioParser::ExpContext::operatorMulDiv() {
  return getRuleContext<CmdAudioParser::OperatorMulDivContext>(0);
}

Ref<CmdAudioParser::OperatorAddSubContext> CmdAudioParser::ExpContext::operatorAddSub() {
  return getRuleContext<CmdAudioParser::OperatorAddSubContext>(0);
}


ssize_t CmdAudioParser::ExpContext::getRuleIndex() const {
  return CmdAudioParser::RuleExp;
}

void CmdAudioParser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void CmdAudioParser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}


Ref<CmdAudioParser::ExpContext> CmdAudioParser::exp() {
   return exp(0);
}

Ref<CmdAudioParser::ExpContext> CmdAudioParser::exp(int precedence) {
  Ref<ParserRuleContext> parentContext = _ctx;
  int parentState = getState();
  Ref<CmdAudioParser::ExpContext> _localctx = std::make_shared<ExpContext>(_ctx, parentState);
  Ref<CmdAudioParser::ExpContext> previousContext = _localctx;
  int startState = 16;
  enterRecursionRule(_localctx, 16, CmdAudioParser::RuleExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    int alt;
    enterOuterAlt(_localctx, 1);
    setState(106);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CmdAudioParser::INT:
      case CmdAudioParser::FLOAT: {
        setState(101);
        number();
        break;
      }

      case CmdAudioParser::T__1:
      case CmdAudioParser::NAME: {
        setState(102);
        prefixexp();
        break;
      }

      case CmdAudioParser::T__10:
      case CmdAudioParser::T__11:
      case CmdAudioParser::T__12:
      case CmdAudioParser::T__13: {
        setState(103);
        operatorUnary();
        setState(104);
        exp(3);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(118);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(116);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          _localctx = std::make_shared<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(108);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(109);
          operatorMulDiv();
          setState(110);
          exp(3);
          break;
        }

        case 2: {
          _localctx = std::make_shared<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(112);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(113);
          operatorAddSub();
          setState(114);
          exp(2);
          break;
        }

        } 
      }
      setState(120);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

CmdAudioParser::NumberContext::NumberContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> CmdAudioParser::NumberContext::INT() {
  return getToken(CmdAudioParser::INT, 0);
}

Ref<tree::TerminalNode> CmdAudioParser::NumberContext::FLOAT() {
  return getToken(CmdAudioParser::FLOAT, 0);
}


ssize_t CmdAudioParser::NumberContext::getRuleIndex() const {
  return CmdAudioParser::RuleNumber;
}

void CmdAudioParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void CmdAudioParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

Ref<CmdAudioParser::NumberContext> CmdAudioParser::number() {
  Ref<NumberContext> _localctx = std::make_shared<NumberContext>(_ctx, getState());
  enterRule(_localctx, 18, CmdAudioParser::RuleNumber);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    _la = _input->LA(1);
    if (!(_la == CmdAudioParser::INT

    || _la == CmdAudioParser::FLOAT)) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrefixexpContext ------------------------------------------------------------------

CmdAudioParser::PrefixexpContext::PrefixexpContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::FunctionContext> CmdAudioParser::PrefixexpContext::function() {
  return getRuleContext<CmdAudioParser::FunctionContext>(0);
}

Ref<CmdAudioParser::NamedArgListContext> CmdAudioParser::PrefixexpContext::namedArgList() {
  return getRuleContext<CmdAudioParser::NamedArgListContext>(0);
}

Ref<CmdAudioParser::VarOrExpContext> CmdAudioParser::PrefixexpContext::varOrExp() {
  return getRuleContext<CmdAudioParser::VarOrExpContext>(0);
}


ssize_t CmdAudioParser::PrefixexpContext::getRuleIndex() const {
  return CmdAudioParser::RulePrefixexp;
}

void CmdAudioParser::PrefixexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrefixexp(this);
}

void CmdAudioParser::PrefixexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrefixexp(this);
}

Ref<CmdAudioParser::PrefixexpContext> CmdAudioParser::prefixexp() {
  Ref<PrefixexpContext> _localctx = std::make_shared<PrefixexpContext>(_ctx, getState());
  enterRule(_localctx, 20, CmdAudioParser::RulePrefixexp);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(123);
      function();
      setState(124);
      match(CmdAudioParser::T__1);
      setState(126);

      _la = _input->LA(1);
      if (_la == CmdAudioParser::NAME) {
        setState(125);
        namedArgList();
      }
      setState(128);
      match(CmdAudioParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(130);
      varOrExp();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

CmdAudioParser::FunctionContext::FunctionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> CmdAudioParser::FunctionContext::NAME() {
  return getToken(CmdAudioParser::NAME, 0);
}


ssize_t CmdAudioParser::FunctionContext::getRuleIndex() const {
  return CmdAudioParser::RuleFunction;
}

void CmdAudioParser::FunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction(this);
}

void CmdAudioParser::FunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction(this);
}

Ref<CmdAudioParser::FunctionContext> CmdAudioParser::function() {
  Ref<FunctionContext> _localctx = std::make_shared<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 22, CmdAudioParser::RuleFunction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(CmdAudioParser::NAME);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedArgListContext ------------------------------------------------------------------

CmdAudioParser::NamedArgListContext::NamedArgListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<CmdAudioParser::NamedArgContext>> CmdAudioParser::NamedArgListContext::namedArg() {
  return getRuleContexts<CmdAudioParser::NamedArgContext>();
}

Ref<CmdAudioParser::NamedArgContext> CmdAudioParser::NamedArgListContext::namedArg(int i) {
  return getRuleContext<CmdAudioParser::NamedArgContext>((size_t)i);
}


ssize_t CmdAudioParser::NamedArgListContext::getRuleIndex() const {
  return CmdAudioParser::RuleNamedArgList;
}

void CmdAudioParser::NamedArgListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedArgList(this);
}

void CmdAudioParser::NamedArgListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedArgList(this);
}

Ref<CmdAudioParser::NamedArgListContext> CmdAudioParser::namedArgList() {
  Ref<NamedArgListContext> _localctx = std::make_shared<NamedArgListContext>(_ctx, getState());
  enterRule(_localctx, 24, CmdAudioParser::RuleNamedArgList);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
    namedArg();
    setState(140);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CmdAudioParser::T__6) {
      setState(136);
      match(CmdAudioParser::T__6);
      setState(137);
      namedArg();
      setState(142);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedArgContext ------------------------------------------------------------------

CmdAudioParser::NamedArgContext::NamedArgContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::VarContext> CmdAudioParser::NamedArgContext::var() {
  return getRuleContext<CmdAudioParser::VarContext>(0);
}

Ref<CmdAudioParser::ExpContext> CmdAudioParser::NamedArgContext::exp() {
  return getRuleContext<CmdAudioParser::ExpContext>(0);
}


ssize_t CmdAudioParser::NamedArgContext::getRuleIndex() const {
  return CmdAudioParser::RuleNamedArg;
}

void CmdAudioParser::NamedArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedArg(this);
}

void CmdAudioParser::NamedArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedArg(this);
}

Ref<CmdAudioParser::NamedArgContext> CmdAudioParser::namedArg() {
  Ref<NamedArgContext> _localctx = std::make_shared<NamedArgContext>(_ctx, getState());
  enterRule(_localctx, 26, CmdAudioParser::RuleNamedArg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    var();
    setState(144);
    match(CmdAudioParser::T__9);
    setState(145);
    exp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarOrExpContext ------------------------------------------------------------------

CmdAudioParser::VarOrExpContext::VarOrExpContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::VarContext> CmdAudioParser::VarOrExpContext::var() {
  return getRuleContext<CmdAudioParser::VarContext>(0);
}

Ref<CmdAudioParser::ExpContext> CmdAudioParser::VarOrExpContext::exp() {
  return getRuleContext<CmdAudioParser::ExpContext>(0);
}


ssize_t CmdAudioParser::VarOrExpContext::getRuleIndex() const {
  return CmdAudioParser::RuleVarOrExp;
}

void CmdAudioParser::VarOrExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarOrExp(this);
}

void CmdAudioParser::VarOrExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarOrExp(this);
}

Ref<CmdAudioParser::VarOrExpContext> CmdAudioParser::varOrExp() {
  Ref<VarOrExpContext> _localctx = std::make_shared<VarOrExpContext>(_ctx, getState());
  enterRule(_localctx, 28, CmdAudioParser::RuleVarOrExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(152);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CmdAudioParser::NAME: {
        enterOuterAlt(_localctx, 1);
        setState(147);
        var();
        break;
      }

      case CmdAudioParser::T__1: {
        enterOuterAlt(_localctx, 2);
        setState(148);
        match(CmdAudioParser::T__1);
        setState(149);
        exp(0);
        setState(150);
        match(CmdAudioParser::T__2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarContext ------------------------------------------------------------------

CmdAudioParser::VarContext::VarContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> CmdAudioParser::VarContext::NAME() {
  return getToken(CmdAudioParser::NAME, 0);
}


ssize_t CmdAudioParser::VarContext::getRuleIndex() const {
  return CmdAudioParser::RuleVar;
}

void CmdAudioParser::VarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar(this);
}

void CmdAudioParser::VarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar(this);
}

Ref<CmdAudioParser::VarContext> CmdAudioParser::var() {
  Ref<VarContext> _localctx = std::make_shared<VarContext>(_ctx, getState());
  enterRule(_localctx, 30, CmdAudioParser::RuleVar);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    match(CmdAudioParser::NAME);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameAndArgsContext ------------------------------------------------------------------

CmdAudioParser::NameAndArgsContext::NameAndArgsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::ArgsContext> CmdAudioParser::NameAndArgsContext::args() {
  return getRuleContext<CmdAudioParser::ArgsContext>(0);
}

Ref<tree::TerminalNode> CmdAudioParser::NameAndArgsContext::NAME() {
  return getToken(CmdAudioParser::NAME, 0);
}


ssize_t CmdAudioParser::NameAndArgsContext::getRuleIndex() const {
  return CmdAudioParser::RuleNameAndArgs;
}

void CmdAudioParser::NameAndArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNameAndArgs(this);
}

void CmdAudioParser::NameAndArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNameAndArgs(this);
}

Ref<CmdAudioParser::NameAndArgsContext> CmdAudioParser::nameAndArgs() {
  Ref<NameAndArgsContext> _localctx = std::make_shared<NameAndArgsContext>(_ctx, getState());
  enterRule(_localctx, 32, CmdAudioParser::RuleNameAndArgs);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);

    _la = _input->LA(1);
    if (_la == CmdAudioParser::T__9) {
      setState(156);
      match(CmdAudioParser::T__9);
      setState(157);
      match(CmdAudioParser::NAME);
    }
    setState(160);
    args();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

CmdAudioParser::ArgsContext::ArgsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<CmdAudioParser::ExplistContext> CmdAudioParser::ArgsContext::explist() {
  return getRuleContext<CmdAudioParser::ExplistContext>(0);
}


ssize_t CmdAudioParser::ArgsContext::getRuleIndex() const {
  return CmdAudioParser::RuleArgs;
}

void CmdAudioParser::ArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgs(this);
}

void CmdAudioParser::ArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgs(this);
}

Ref<CmdAudioParser::ArgsContext> CmdAudioParser::args() {
  Ref<ArgsContext> _localctx = std::make_shared<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 34, CmdAudioParser::RuleArgs);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    match(CmdAudioParser::T__1);
    setState(164);

    _la = _input->LA(1);
    if ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << CmdAudioParser::T__1)
      | (1ULL << CmdAudioParser::T__10)
      | (1ULL << CmdAudioParser::T__11)
      | (1ULL << CmdAudioParser::T__12)
      | (1ULL << CmdAudioParser::T__13)
      | (1ULL << CmdAudioParser::NAME)
      | (1ULL << CmdAudioParser::INT)
      | (1ULL << CmdAudioParser::FLOAT))) != 0)) {
      setState(163);
      explist();
    }
    setState(166);
    match(CmdAudioParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperatorUnaryContext ------------------------------------------------------------------

CmdAudioParser::OperatorUnaryContext::OperatorUnaryContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}


ssize_t CmdAudioParser::OperatorUnaryContext::getRuleIndex() const {
  return CmdAudioParser::RuleOperatorUnary;
}

void CmdAudioParser::OperatorUnaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperatorUnary(this);
}

void CmdAudioParser::OperatorUnaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperatorUnary(this);
}

Ref<CmdAudioParser::OperatorUnaryContext> CmdAudioParser::operatorUnary() {
  Ref<OperatorUnaryContext> _localctx = std::make_shared<OperatorUnaryContext>(_ctx, getState());
  enterRule(_localctx, 36, CmdAudioParser::RuleOperatorUnary);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    _la = _input->LA(1);
    if (!((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << CmdAudioParser::T__10)
      | (1ULL << CmdAudioParser::T__11)
      | (1ULL << CmdAudioParser::T__12)
      | (1ULL << CmdAudioParser::T__13))) != 0))) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperatorMulDivContext ------------------------------------------------------------------

CmdAudioParser::OperatorMulDivContext::OperatorMulDivContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}


ssize_t CmdAudioParser::OperatorMulDivContext::getRuleIndex() const {
  return CmdAudioParser::RuleOperatorMulDiv;
}

void CmdAudioParser::OperatorMulDivContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperatorMulDiv(this);
}

void CmdAudioParser::OperatorMulDivContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperatorMulDiv(this);
}

Ref<CmdAudioParser::OperatorMulDivContext> CmdAudioParser::operatorMulDiv() {
  Ref<OperatorMulDivContext> _localctx = std::make_shared<OperatorMulDivContext>(_ctx, getState());
  enterRule(_localctx, 38, CmdAudioParser::RuleOperatorMulDiv);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    _la = _input->LA(1);
    if (!(_la == CmdAudioParser::T__14

    || _la == CmdAudioParser::T__15)) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperatorAddSubContext ------------------------------------------------------------------

CmdAudioParser::OperatorAddSubContext::OperatorAddSubContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}


ssize_t CmdAudioParser::OperatorAddSubContext::getRuleIndex() const {
  return CmdAudioParser::RuleOperatorAddSub;
}

void CmdAudioParser::OperatorAddSubContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperatorAddSub(this);
}

void CmdAudioParser::OperatorAddSubContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CmdAudioListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperatorAddSub(this);
}

Ref<CmdAudioParser::OperatorAddSubContext> CmdAudioParser::operatorAddSub() {
  Ref<OperatorAddSubContext> _localctx = std::make_shared<OperatorAddSubContext>(_ctx, getState());
  enterRule(_localctx, 40, CmdAudioParser::RuleOperatorAddSub);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    _la = _input->LA(1);
    if (!(_la == CmdAudioParser::T__12

    || _la == CmdAudioParser::T__16)) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CmdAudioParser::sempred(Ref<RuleContext> const& context, int ruleIndex, int predicateIndex) {
  switch (ruleIndex) {
    case 8: return expSempred(std::dynamic_pointer_cast<ExpContext>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CmdAudioParser::expSempred(Ref<ExpContext> const& _localctx, int predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CmdAudioParser::_decisionToDFA;
atn::PredictionContextCache CmdAudioParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CmdAudioParser::_atn;
std::vector<uint16_t> CmdAudioParser::_serializedATN;

std::vector<std::string> CmdAudioParser::_ruleNames = {
  "chunk", "generatordef", "genparlist", "namelist", "block", "stat", "outputstat", 
  "explist", "exp", "number", "prefixexp", "function", "namedArgList", "namedArg", 
  "varOrExp", "var", "nameAndArgs", "args", "operatorUnary", "operatorMulDiv", 
  "operatorAddSub"
};

std::vector<std::string> CmdAudioParser::_literalNames = {
  "", "'generator'", "'('", "')'", "'='", "'{'", "'}'", "','", "'state'", 
  "'output'", "':'", "'not'", "'#'", "'-'", "'~'", "'*'", "'/'", "'+'", 
  "", "", "", "';'"
};

std::vector<std::string> CmdAudioParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "NAME", "INT", "FLOAT", "STATEND", "LINE_COMMENT", "WS"
};

dfa::Vocabulary CmdAudioParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CmdAudioParser::_tokenNames;

CmdAudioParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x430, 0xd6d1, 0x8206, 0xad2d, 0x4417, 0xaef1, 0x8d80, 0xaadd, 
    0x3, 0x19, 0xb1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x3, 0x2, 0x7, 0x2, 0x2e, 0xa, 0x2, 0xc, 
    0x2, 0xe, 0x2, 0x31, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x39, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x43, 
    0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x48, 0xa, 0x5, 0xc, 
    0x5, 0xe, 0x5, 0x4b, 0xb, 0x5, 0x3, 0x6, 0x7, 0x6, 0x4e, 0xa, 0x6, 0xc, 
    0x6, 0xe, 0x6, 0x51, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x62, 0xa, 0x9, 0xc, 
    0x9, 0xe, 0x9, 0x65, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x6d, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x77, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x7a, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x81, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x5, 0xc, 0x86, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x7, 0xe, 0x8d, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x90, 0xb, 
    0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x9b, 0xa, 0x10, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xa1, 0xa, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xa7, 0xa, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x2, 0x3, 0x12, 0x17, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 
    0x28, 0x2a, 0x2, 0x6, 0x3, 0x2, 0x15, 0x16, 0x3, 0x2, 0xd, 0x10, 0x3, 
    0x2, 0x11, 0x12, 0x4, 0x2, 0xf, 0xf, 0x13, 0x13, 0xab, 0x2, 0x2f, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0x34, 0x3, 0x2, 0x2, 0x2, 0x6, 0x40, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x44, 0x3, 0x2, 0x2, 0x2, 0xa, 0x4f, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0x54, 0x3, 0x2, 0x2, 0x2, 0xe, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x10, 0x5e, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x14, 0x7b, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0x85, 0x3, 0x2, 0x2, 0x2, 0x18, 0x87, 0x3, 0x2, 
    0x2, 0x2, 0x1a, 0x89, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x91, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x20, 0x9c, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x24, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x26, 
    0xaa, 0x3, 0x2, 0x2, 0x2, 0x28, 0xac, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xae, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x2e, 0x5, 0x4, 0x3, 0x2, 0x2d, 0x2c, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x31, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2d, 0x3, 0x2, 
    0x2, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x2, 0x2, 0x30, 0x32, 0x3, 0x2, 0x2, 
    0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x7, 0x2, 0x2, 0x3, 
    0x33, 0x3, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x7, 0x3, 0x2, 0x2, 0x35, 
    0x36, 0x7, 0x14, 0x2, 0x2, 0x36, 0x38, 0x7, 0x4, 0x2, 0x2, 0x37, 0x39, 
    0x5, 0x6, 0x4, 0x2, 0x38, 0x37, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 
    0x2, 0x2, 0x2, 0x39, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0x5, 
    0x2, 0x2, 0x3b, 0x3c, 0x7, 0x6, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x7, 0x2, 
    0x2, 0x3d, 0x3e, 0x5, 0xa, 0x6, 0x2, 0x3e, 0x3f, 0x7, 0x8, 0x2, 0x2, 
    0x3f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x40, 0x42, 0x5, 0x8, 0x5, 0x2, 0x41, 
    0x43, 0x7, 0x9, 0x2, 0x2, 0x42, 0x41, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 
    0x3, 0x2, 0x2, 0x2, 0x43, 0x7, 0x3, 0x2, 0x2, 0x2, 0x44, 0x49, 0x7, 
    0x14, 0x2, 0x2, 0x45, 0x46, 0x7, 0x9, 0x2, 0x2, 0x46, 0x48, 0x7, 0x14, 
    0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4b, 0x3, 0x2, 0x2, 
    0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x9, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4c, 
    0x4e, 0x5, 0xc, 0x7, 0x2, 0x4d, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x51, 
    0x3, 0x2, 0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x3, 
    0x2, 0x2, 0x2, 0x50, 0x52, 0x3, 0x2, 0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0x53, 0x5, 0xe, 0x8, 0x2, 0x53, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x54, 0x55, 0x7, 0xa, 0x2, 0x2, 0x55, 0x56, 0x7, 0x14, 0x2, 0x2, 
    0x56, 0x57, 0x7, 0x6, 0x2, 0x2, 0x57, 0x58, 0x5, 0x12, 0xa, 0x2, 0x58, 
    0x59, 0x7, 0x17, 0x2, 0x2, 0x59, 0xd, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 
    0x7, 0xb, 0x2, 0x2, 0x5b, 0x5c, 0x5, 0x12, 0xa, 0x2, 0x5c, 0x5d, 0x7, 
    0x17, 0x2, 0x2, 0x5d, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x63, 0x5, 0x12, 
    0xa, 0x2, 0x5f, 0x60, 0x7, 0x9, 0x2, 0x2, 0x60, 0x62, 0x5, 0x12, 0xa, 
    0x2, 0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x62, 0x65, 0x3, 0x2, 0x2, 0x2, 
    0x63, 0x61, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 
    0x11, 0x3, 0x2, 0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 
    0x8, 0xa, 0x1, 0x2, 0x67, 0x6d, 0x5, 0x14, 0xb, 0x2, 0x68, 0x6d, 0x5, 
    0x16, 0xc, 0x2, 0x69, 0x6a, 0x5, 0x26, 0x14, 0x2, 0x6a, 0x6b, 0x5, 0x12, 
    0xa, 0x5, 0x6b, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x66, 0x3, 0x2, 0x2, 
    0x2, 0x6c, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x69, 0x3, 0x2, 0x2, 0x2, 
    0x6d, 0x78, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0xc, 0x4, 0x2, 0x2, 0x6f, 
    0x70, 0x5, 0x28, 0x15, 0x2, 0x70, 0x71, 0x5, 0x12, 0xa, 0x5, 0x71, 0x77, 
    0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0xc, 0x3, 0x2, 0x2, 0x73, 0x74, 0x5, 
    0x2a, 0x16, 0x2, 0x74, 0x75, 0x5, 0x12, 0xa, 0x4, 0x75, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x76, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x76, 0x72, 0x3, 0x2, 0x2, 
    0x2, 0x77, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x78, 0x76, 0x3, 0x2, 0x2, 0x2, 
    0x78, 0x79, 0x3, 0x2, 0x2, 0x2, 0x79, 0x13, 0x3, 0x2, 0x2, 0x2, 0x7a, 
    0x78, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x9, 0x2, 0x2, 0x2, 0x7c, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x5, 0x18, 0xd, 0x2, 0x7e, 0x80, 0x7, 
    0x4, 0x2, 0x2, 0x7f, 0x81, 0x5, 0x1a, 0xe, 0x2, 0x80, 0x7f, 0x3, 0x2, 
    0x2, 0x2, 0x80, 0x81, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 
    0x2, 0x82, 0x83, 0x7, 0x5, 0x2, 0x2, 0x83, 0x86, 0x3, 0x2, 0x2, 0x2, 
    0x84, 0x86, 0x5, 0x1e, 0x10, 0x2, 0x85, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x85, 
    0x84, 0x3, 0x2, 0x2, 0x2, 0x86, 0x17, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 
    0x7, 0x14, 0x2, 0x2, 0x88, 0x19, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8e, 0x5, 
    0x1c, 0xf, 0x2, 0x8a, 0x8b, 0x7, 0x9, 0x2, 0x2, 0x8b, 0x8d, 0x5, 0x1c, 
    0xf, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x90, 0x3, 0x2, 0x2, 
    0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 0x2, 
    0x8f, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x91, 
    0x92, 0x5, 0x20, 0x11, 0x2, 0x92, 0x93, 0x7, 0xc, 0x2, 0x2, 0x93, 0x94, 
    0x5, 0x12, 0xa, 0x2, 0x94, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x95, 0x9b, 0x5, 
    0x20, 0x11, 0x2, 0x96, 0x97, 0x7, 0x4, 0x2, 0x2, 0x97, 0x98, 0x5, 0x12, 
    0xa, 0x2, 0x98, 0x99, 0x7, 0x5, 0x2, 0x2, 0x99, 0x9b, 0x3, 0x2, 0x2, 
    0x2, 0x9a, 0x95, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x96, 0x3, 0x2, 0x2, 0x2, 
    0x9b, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x14, 0x2, 0x2, 0x9d, 
    0x21, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0xc, 0x2, 0x2, 0x9f, 0xa1, 
    0x7, 0x14, 0x2, 0x2, 0xa0, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x3, 
    0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x5, 0x24, 
    0x13, 0x2, 0xa3, 0x23, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa6, 0x7, 0x4, 0x2, 
    0x2, 0xa5, 0xa7, 0x5, 0x10, 0x9, 0x2, 0xa6, 0xa5, 0x3, 0x2, 0x2, 0x2, 
    0xa6, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xa8, 
    0xa9, 0x7, 0x5, 0x2, 0x2, 0xa9, 0x25, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 
    0x9, 0x3, 0x2, 0x2, 0xab, 0x27, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x9, 
    0x4, 0x2, 0x2, 0xad, 0x29, 0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x9, 0x5, 
    0x2, 0x2, 0xaf, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x11, 0x2f, 0x38, 0x42, 0x49, 
    0x4f, 0x63, 0x6c, 0x76, 0x78, 0x80, 0x85, 0x8e, 0x9a, 0xa0, 0xa6, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  for (int i = 0; i < _atn.getNumberOfDecisions(); i++) { 
    _decisionToDFA.push_back(dfa::DFA(_atn.getDecisionState(i), i));
  }
}

CmdAudioParser::Initializer CmdAudioParser::_init;
