
// Generated from Csharp.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"
#include "CsharpParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CsharpParser.
 */
class  CsharpListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStart(CsharpParser::StartContext *ctx) = 0;
  virtual void exitStart(CsharpParser::StartContext *ctx) = 0;


};

