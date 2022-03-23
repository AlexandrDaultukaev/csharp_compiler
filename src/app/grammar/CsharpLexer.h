
// Generated from Csharp.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"




class  CsharpLexer : public antlr4::Lexer {
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

  explicit CsharpLexer(antlr4::CharStream *input);
  ~CsharpLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

