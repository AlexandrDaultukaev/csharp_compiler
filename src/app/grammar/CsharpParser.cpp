
// Generated from Csharp.g4 by ANTLR 4.9


#include "CsharpListener.h"

#include "CsharpParser.h"


using namespace antlrcpp;
using namespace antlr4;

CsharpParser::CsharpParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CsharpParser::~CsharpParser() {
  delete _interpreter;
}

std::string CsharpParser::getGrammarFileName() const {
  return "Csharp.g4";
}

const std::vector<std::string>& CsharpParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CsharpParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StartContext ------------------------------------------------------------------

CsharpParser::StartContext::StartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CsharpParser::StartContext::getRuleIndex() const {
  return CsharpParser::RuleStart;
}

void CsharpParser::StartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CsharpListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStart(this);
}

void CsharpParser::StartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CsharpListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStart(this);
}

CsharpParser::StartContext* CsharpParser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 0, CsharpParser::RuleStart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2);
    match(CsharpParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> CsharpParser::_decisionToDFA;
atn::PredictionContextCache CsharpParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CsharpParser::_atn;
std::vector<uint16_t> CsharpParser::_serializedATN;

std::vector<std::string> CsharpParser::_ruleNames = {
  "start"
};

std::vector<std::string> CsharpParser::_literalNames = {
  "", "'hello'", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "'if'", "'else'", "'for'", "", "'='", "", "'+'", "'-'", "'%'", "'=='", 
  "'<'", "'>'", "';'", "'('", "')'", "'{'", "'['", "']'", "'}'", "'.'", 
  "':'", "','", "'''", "'\"'", "'0'"
};

std::vector<std::string> CsharpParser::_symbolicNames = {
  "", "", "KEYWORD", "VAR", "INT", "FLOAT", "DOUBLE", "DECIMAL", "SBYTE", 
  "BYTE", "SHORT", "USHORT", "UINT", "LONG", "ULONG", "STRING", "IF", "ELSE", 
  "FOR", "ID", "ASSIGN", "OP", "PLUS", "MINUS", "PERS", "EQ", "LESS", "MR", 
  "SEMICOLON", "RLP", "RRP", "CLB", "SLP", "SRP", "CRB", "DOT", "COLON", 
  "COMMA", "APOSTROPH", "DQUOTES", "ZERO", "NUMBER", "TEXT", "UNARYMATHEXP", 
  "WS"
};

dfa::Vocabulary CsharpParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CsharpParser::_tokenNames;

CsharpParser::Initializer::Initializer() {
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
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x2e, 0x7, 0x4, 0x2, 0x9, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x2, 
    0x2, 0x3, 0x2, 0x2, 0x2, 0x2, 0x5, 0x2, 0x4, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x5, 0x7, 0x3, 0x2, 0x2, 0x5, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CsharpParser::Initializer CsharpParser::_init;
