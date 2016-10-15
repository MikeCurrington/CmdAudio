
// Generated from CmdAudio.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "CmdAudioParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CmdAudioParser.
 */
class CmdAudioListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterChunk(CmdAudioParser::ChunkContext *ctx) = 0;
  virtual void exitChunk(CmdAudioParser::ChunkContext *ctx) = 0;

  virtual void enterGeneratordef(CmdAudioParser::GeneratordefContext *ctx) = 0;
  virtual void exitGeneratordef(CmdAudioParser::GeneratordefContext *ctx) = 0;

  virtual void enterGenparlist(CmdAudioParser::GenparlistContext *ctx) = 0;
  virtual void exitGenparlist(CmdAudioParser::GenparlistContext *ctx) = 0;

  virtual void enterNamelist(CmdAudioParser::NamelistContext *ctx) = 0;
  virtual void exitNamelist(CmdAudioParser::NamelistContext *ctx) = 0;

  virtual void enterBlock(CmdAudioParser::BlockContext *ctx) = 0;
  virtual void exitBlock(CmdAudioParser::BlockContext *ctx) = 0;

  virtual void enterStat(CmdAudioParser::StatContext *ctx) = 0;
  virtual void exitStat(CmdAudioParser::StatContext *ctx) = 0;

  virtual void enterOutputstat(CmdAudioParser::OutputstatContext *ctx) = 0;
  virtual void exitOutputstat(CmdAudioParser::OutputstatContext *ctx) = 0;

  virtual void enterExplist(CmdAudioParser::ExplistContext *ctx) = 0;
  virtual void exitExplist(CmdAudioParser::ExplistContext *ctx) = 0;

  virtual void enterExp(CmdAudioParser::ExpContext *ctx) = 0;
  virtual void exitExp(CmdAudioParser::ExpContext *ctx) = 0;

  virtual void enterNumber(CmdAudioParser::NumberContext *ctx) = 0;
  virtual void exitNumber(CmdAudioParser::NumberContext *ctx) = 0;

  virtual void enterPrefixexp(CmdAudioParser::PrefixexpContext *ctx) = 0;
  virtual void exitPrefixexp(CmdAudioParser::PrefixexpContext *ctx) = 0;

  virtual void enterFunction(CmdAudioParser::FunctionContext *ctx) = 0;
  virtual void exitFunction(CmdAudioParser::FunctionContext *ctx) = 0;

  virtual void enterNamedArgList(CmdAudioParser::NamedArgListContext *ctx) = 0;
  virtual void exitNamedArgList(CmdAudioParser::NamedArgListContext *ctx) = 0;

  virtual void enterNamedArg(CmdAudioParser::NamedArgContext *ctx) = 0;
  virtual void exitNamedArg(CmdAudioParser::NamedArgContext *ctx) = 0;

  virtual void enterVarOrExp(CmdAudioParser::VarOrExpContext *ctx) = 0;
  virtual void exitVarOrExp(CmdAudioParser::VarOrExpContext *ctx) = 0;

  virtual void enterVar(CmdAudioParser::VarContext *ctx) = 0;
  virtual void exitVar(CmdAudioParser::VarContext *ctx) = 0;

  virtual void enterNameAndArgs(CmdAudioParser::NameAndArgsContext *ctx) = 0;
  virtual void exitNameAndArgs(CmdAudioParser::NameAndArgsContext *ctx) = 0;

  virtual void enterArgs(CmdAudioParser::ArgsContext *ctx) = 0;
  virtual void exitArgs(CmdAudioParser::ArgsContext *ctx) = 0;

  virtual void enterOperatorUnary(CmdAudioParser::OperatorUnaryContext *ctx) = 0;
  virtual void exitOperatorUnary(CmdAudioParser::OperatorUnaryContext *ctx) = 0;

  virtual void enterOperatorMulDiv(CmdAudioParser::OperatorMulDivContext *ctx) = 0;
  virtual void exitOperatorMulDiv(CmdAudioParser::OperatorMulDivContext *ctx) = 0;

  virtual void enterOperatorAddSub(CmdAudioParser::OperatorAddSubContext *ctx) = 0;
  virtual void exitOperatorAddSub(CmdAudioParser::OperatorAddSubContext *ctx) = 0;


};

