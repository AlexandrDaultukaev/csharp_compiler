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
ID: SYMBOL (SYMBOL | DIGIT | '.' SYMBOL)*;
fragment SYMBOL: [A-Za-z];
fragment DIGIT: [0-9];

ASSIGN: '=';
BINARY_OP: PLUS | MINUS | PERS | DIVISION;
DIVISION: '/';
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
NUMBER: '0' | DIGITNOZERO (DIGIT)*;
// NUMBER: DIGITNOZERO (DIGIT)*;

TEXT: [0-9A-Za-z!?@#$%^&*.]+;

UNIT: NUMBER | ID | DQUOTES (TEXT (' ' TEXT)*)? DQUOTES;

fragment DIGITNOZERO: [1-9];

UNARYMATHEXP: '++' | '--';
WS: [ \r\t\n]+ -> skip;
// start: (var_def_expr | func_def_expr)*; var_def_expr: VAR ID ASSIGN NUMBER SEMICOLON;
// func_def_expr: VAR ID RLP RRP (CLB var_def_expr CRB | SEMICOLON);

// func() ; a+b ; a++ ; a=b ; if/while/for ; return ;

program: expressions* EOF;
expressions: (func_def | var_def);
var_def: VAR ID (SEMICOLON | ASSIGN NUMBER SEMICOLON);
func_def: (KEYWORD* VAR | VAR) ID RLP RRP ( SEMICOLON | scope);
scope: CLB statement* CRB;
statement: func_call SEMICOLON;
func_call: ID RLP args RRP;
args: (UNIT (COMMA UNIT)*)?;

// type a = number rvalue: NUMBER+ | ZERO | TEXT |

// int a = 12; string a = "Hello"; int a = c + b + ... + n; int a = c + 4; int a = c + b; int a =
// b++;
