
// Generated from CmdAudio.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "CmdAudioListener.h"


/**
 * This class provides an empty implementation of CmdAudioListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class CmdAudioBaseListener : public CmdAudioListener {
public:

  virtual void enterChunk(CmdAudioParser::ChunkContext * /*ctx*/) override { }
  virtual void exitChunk(CmdAudioParser::ChunkContext * /*ctx*/) override { }

  virtual void enterGeneratordef(CmdAudioParser::GeneratordefContext * /*ctx*/) override { }
  virtual void exitGeneratordef(CmdAudioParser::GeneratordefContext * /*ctx*/) override { }

  virtual void enterGenparlist(CmdAudioParser::GenparlistContext * /*ctx*/) override { }
  virtual void exitGenparlist(CmdAudioParser::GenparlistContext * /*ctx*/) override { }

  virtual void enterNamelist(CmdAudioParser::NamelistContext * /*ctx*/) override { }
  virtual void exitNamelist(CmdAudioParser::NamelistContext * /*ctx*/) override { }

  virtual void enterBlock(CmdAudioParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(CmdAudioParser::BlockContext * /*ctx*/) override { }

  virtual void enterStat(CmdAudioParser::StatContext * /*ctx*/) override { }
  virtual void exitStat(CmdAudioParser::StatContext * /*ctx*/) override { }

  virtual void enterOutputstat(CmdAudioParser::OutputstatContext * /*ctx*/) override { }
  virtual void exitOutputstat(CmdAudioParser::OutputstatContext * /*ctx*/) override { }

  virtual void enterExplist(CmdAudioParser::ExplistContext * /*ctx*/) override { }
  virtual void exitExplist(CmdAudioParser::ExplistContext * /*ctx*/) override { }

  virtual void enterExp(CmdAudioParser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(CmdAudioParser::ExpContext * /*ctx*/) override { }

  virtual void enterNumber(CmdAudioParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(CmdAudioParser::NumberContext * /*ctx*/) override { }

  virtual void enterPrefixexp(CmdAudioParser::PrefixexpContext * /*ctx*/) override { }
  virtual void exitPrefixexp(CmdAudioParser::PrefixexpContext * /*ctx*/) override { }

  virtual void enterFunction(CmdAudioParser::FunctionContext * /*ctx*/) override { }
  virtual void exitFunction(CmdAudioParser::FunctionContext * /*ctx*/) override { }

  virtual void enterNamedArgList(CmdAudioParser::NamedArgListContext * /*ctx*/) override { }
  virtual void exitNamedArgList(CmdAudioParser::NamedArgListContext * /*ctx*/) override { }

  virtual void enterNamedArg(CmdAudioParser::NamedArgContext * /*ctx*/) override { }
  virtual void exitNamedArg(CmdAudioParser::NamedArgContext * /*ctx*/) override { }

  virtual void enterVarOrExp(CmdAudioParser::VarOrExpContext * /*ctx*/) override { }
  virtual void exitVarOrExp(CmdAudioParser::VarOrExpContext * /*ctx*/) override { }

  virtual void enterVar(CmdAudioParser::VarContext * /*ctx*/) override { }
  virtual void exitVar(CmdAudioParser::VarContext * /*ctx*/) override { }

  virtual void enterNameAndArgs(CmdAudioParser::NameAndArgsContext * /*ctx*/) override { }
  virtual void exitNameAndArgs(CmdAudioParser::NameAndArgsContext * /*ctx*/) override { }

  virtual void enterArgs(CmdAudioParser::ArgsContext * /*ctx*/) override { }
  virtual void exitArgs(CmdAudioParser::ArgsContext * /*ctx*/) override { }

  virtual void enterOperatorUnary(CmdAudioParser::OperatorUnaryContext * /*ctx*/) override { }
  virtual void exitOperatorUnary(CmdAudioParser::OperatorUnaryContext * /*ctx*/) override { }

  virtual void enterOperatorMulDiv(CmdAudioParser::OperatorMulDivContext * /*ctx*/) override { }
  virtual void exitOperatorMulDiv(CmdAudioParser::OperatorMulDivContext * /*ctx*/) override { }

  virtual void enterOperatorAddSub(CmdAudioParser::OperatorAddSubContext * /*ctx*/) override { }
  virtual void exitOperatorAddSub(CmdAudioParser::OperatorAddSubContext * /*ctx*/) override { }


  virtual void enterEveryRule(ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(tree::ErrorNode * /*node*/) override { }

};

