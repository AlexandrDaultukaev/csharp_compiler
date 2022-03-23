// Generated from /home/alex/Code/Compilers/lab2_cpp/Lexer-Parser-rustlang/src/app/grammar/Csharp.g4 by ANTLR 4.8
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class CsharpParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, KEYWORD=2, VAR=3, INT=4, FLOAT=5, DOUBLE=6, DECIMAL=7, SBYTE=8, 
		BYTE=9, SHORT=10, USHORT=11, UINT=12, LONG=13, ULONG=14, STRING=15, IF=16, 
		ELSE=17, FOR=18, ID=19, ASSIGN=20, OP=21, PLUS=22, MINUS=23, PERS=24, 
		EQ=25, LESS=26, MR=27, SEMICOLON=28, RLP=29, RRP=30, CLB=31, SLP=32, SRP=33, 
		CRB=34, DOT=35, COLON=36, COMMA=37, APOSTROPH=38, DQUOTES=39, ZERO=40, 
		NUMBER=41, TEXT=42, UNARYMATHEXP=43, WS=44;
	public static final int
		RULE_start = 0;
	private static String[] makeRuleNames() {
		return new String[] {
			"start"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'hello'", null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, "'if'", "'else'", "'for'", null, "'='", 
			null, "'+'", "'-'", "'%'", "'=='", "'<'", "'>'", "';'", "'('", "')'", 
			"'{'", "'['", "']'", "'}'", "'.'", "':'", "','", "'''", "'\"'", "'0'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, "KEYWORD", "VAR", "INT", "FLOAT", "DOUBLE", "DECIMAL", "SBYTE", 
			"BYTE", "SHORT", "USHORT", "UINT", "LONG", "ULONG", "STRING", "IF", "ELSE", 
			"FOR", "ID", "ASSIGN", "OP", "PLUS", "MINUS", "PERS", "EQ", "LESS", "MR", 
			"SEMICOLON", "RLP", "RRP", "CLB", "SLP", "SRP", "CRB", "DOT", "COLON", 
			"COMMA", "APOSTROPH", "DQUOTES", "ZERO", "NUMBER", "TEXT", "UNARYMATHEXP", 
			"WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Csharp.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CsharpParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class StartContext extends ParserRuleContext {
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_start);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(2);
			match(T__0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3.\7\4\2\t\2\3\2\3"+
		"\2\3\2\2\2\3\2\2\2\2\5\2\4\3\2\2\2\4\5\7\3\2\2\5\3\3\2\2\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}