
// Generated from Csharp.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"
#include "CsharpListener.h"


/**
 * This class provides an empty implementation of CsharpListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CsharpBaseListener : public CsharpListener {
public:

  virtual void enterStart(CsharpParser::StartContext * /*ctx*/) override { }
  virtual void exitStart(CsharpParser::StartContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

