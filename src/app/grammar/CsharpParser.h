
// Generated from Csharp.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"




class  CsharpParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, KEYWORD = 2, VAR = 3, INT = 4, FLOAT = 5, DOUBLE = 6, DECIMAL = 7, 
    SBYTE = 8, BYTE = 9, SHORT = 10, USHORT = 11, UINT = 12, LONG = 13, 
    ULONG = 14, STRING = 15, IF = 16, ELSE = 17, FOR = 18, ID = 19, ASSIGN = 20, 
    OP = 21, PLUS = 22, MINUS = 23, PERS = 24, EQ = 25, LESS = 26, MR = 27, 
    SEMICOLON = 28, RLP = 29, RRP = 30, CLB = 31, SLP = 32, SRP = 33, CRB = 34, 
    DOT = 35, COLON = 36, COMMA = 37, APOSTROPH = 38, DQUOTES = 39, ZERO = 40, 
    NUMBER = 41, TEXT = 42, UNARYMATHEXP = 43, WS = 44
  };

  enum {
    RuleStart = 0
  };

  explicit CsharpParser(antlr4::TokenStream *input);
  ~CsharpParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class StartContext; 

  class  StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartContext* start();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

