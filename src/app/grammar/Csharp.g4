grammar Csharp;

KEYWORD:
	'abstract'
	| 'as'
	| 'bool'
	| 'base'
	| 'break'
	| 'case'
	| 'catch'
	| 'char'
	| 'checked'
	| 'class'
	| 'const'
	| 'continue'
	| 'default'
	| 'delegate'
	| 'do'
	| 'enum'
	| 'event'
	| 'explicit'
	| 'extern'
	| 'false'
	| 'finally'
	| 'fixed'
	| 'foreach'
	| 'goto'
	| 'implicit'
	| 'in'
	| 'interface'
	| 'internal'
	| 'is'
	| 'lock'
	| 'namespace'
	| 'new'
	| 'null'
	| 'object'
	| 'operator'
	| 'out'
	| 'override'
	| 'params'
	| 'private'
	| 'protected'
	| 'public'
	| 'readonly'
	| 'ref'
	| 'return'
	| 'sealed'
	| 'sizeof'
	| 'stackalloc'
	| 'static'
	| 'struct'
	| 'switch'
	| 'this'
	| 'throw'
	| 'true'
	| 'try'
	| 'typeof'
	| 'unchecked'
	| 'unsafe'
	| 'using'
	| 'virtual'
	| 'void'
	| 'volatile'
	| 'while';

VAR:
	INT
	| FLOAT
	| DOUBLE
	| DECIMAL
	| SBYTE
	| BYTE
	| SHORT
	| USHORT
	| UINT
	| LONG
	| ULONG
	| STRING;

INT: 'int' | 'System.Int32';
FLOAT: 'float' | 'System.Single';
DOUBLE: 'double' | 'System.Double';
DECIMAL: 'decimal' | 'System.Decimal';
SBYTE: 'sbyte' | 'System.SByte';
BYTE: 'byte' | 'System.Byte';
SHORT: 'short' | 'System.Int16';
USHORT: 'ushort' | 'System.UInt16';
UINT: 'uint' | 'System.UInt32';
LONG: 'long' | 'System.Int64';
ULONG: 'ulong' | 'System.UInt64';
STRING: 'string' | 'System.String';
IF: 'if';
ELSE: 'else';
FOR: 'for';
ID: SYMBOL (SYMBOL | DIGIT)*;
fragment SYMBOL: [A-Za-z];
fragment DIGIT: [0-9];

ASSIGN: '=';
OP: PLUS | ASSIGN | MINUS | EQ | LESS | MR | PERS;
PLUS: '+';
MINUS: '-';
PERS: '%';
EQ: '==';
LESS: '<';
MR: '>';

SEMICOLON: ';';
RLP: '(';
RRP: ')';
CLB: '{';
SLP: '[';
SRP: ']';
CRB: '}';
DOT: '.';
COLON: ':';
COMMA: ',';
APOSTROPH: '\'';
DQUOTES: '"';
ZERO: '0';
NUMBER: DIGITNOZERO (DIGIT)*;
TEXT: [0-9A-Za-z];

fragment DIGITNOZERO: [1-9];

UNARYMATHEXP: '++' | '--';

WS: [ \r\t\n]+ -> skip;

start: 'hello';

//
// kw_expr: KEYWORD+ ID? (DOT ID)* in_parent? SEMICOLON?; array: VAR SLP (ID | NUMBER)? SRP ID
// SEMICOLON?; var: VAR ID (ASSIGN (NUMBER | func | ID | ZERO))? SEMICOLON?; ch_var: ( (ID
// UNARYMATHEXP) | (UNARYMATHEXP ID) | (ID ASSIGN (ID | NUMBER | ZERO) OP? (ID | NUMBER)) )
// SEMICOLON?; in_parent: RLP (array | var | func | ID | NUMBER | ZERO | TEXT)* RRP SEMICOLON?;
// func: ID (DOT ID)* in_parent; if_expr: IF RLP ID OP (ID | NUMBER) (OP (ID | NUMBER | ZERO))? RRP;
// for_expr: FOR RLP var SEMICOLON? ID OP (ID | NUMBER | ZERO) SEMICOLON? ch_var RRP; // FOR RLP VAR
// ID ASSIGN ID SEMICOLON ID OP ZERO SEMICOLON ID UNARYMATHEXP RRP; clb: CLB; crb: CRB;
