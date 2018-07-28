%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"
	int yylex();
  	void yyerror (char *);
  	Class_t class;
%}

%union {
	Class_t classVal;
	List_t classVarDecsVal;
	Class_Var_Dec_t classVarDecVal;
	List_t subroutineDecsVal;
	Subroutine_Dec_t subroutineDecVal;
	Parameter_List_t parameterListVal;
	List_t commaTypeVarNamesVal;
	Comma_Type_Var_Name_t commaTypeVarNameVal;
	Subroutine_Body_t subroutineBodyVal;
	List_t varDecsVal;
	Var_Dec_t varDecVal;
	Type_t typeVal;
	Class_Name_t classNameVal;
	Var_Name_t varNameVal;
	List_t commaVarNamesVal;
	Comma_Var_Name_t commaVarNameVal;
	Expression_List_t expressionListVal;
	Expression_t expressionVal;
	List_t commaExpressionsVal;
	Comma_Expression_t commaExpressionVal;
	Term_t termVal;
	List_t opTermsVal;
	Op_Term_t opTermVal;
	Sub_Routine_Name_t subRoutineNameVal;
	List_t statementsVal;
	Statement_t statementVal;
	Op_t opVal;
	Sub_Routine_Call_t subroutineCallVal;
	Unary_Op_t unaryOpVal;
	Keyword_Constant_t keywordConstantVal;
	int intNumVal;
	char* idVal;
};

// terminal
%token <intNumVal> INTNUM
%token <idVal> ID
%token CLASS
%token CONSTRUCTOR
%token FUNCTION
%token METHOD
%token FIELD
%token STATIC
%token VAR
%token INT
%token CHAR
%token BOOLEAN
%token VOID
%token TRUE
%token FALSE
%token _NULL
%token THIS
%token LET
%token DO
%token IF
%token ELSE
%token WHILE
%token RETURN
%token ADD
%token MINUS
%token TIMES
%token DIV
%token AND
%token OR
%token MORE
%token LESS
%token EQUAL
%token NOT
%token ASSIGN

//nonterminal
%type <classVal> class
%type <classVarDecsVal> classVarDecs
%type <classVarDecVal> classVarDec
%type <subroutineDecsVal> subroutineDecs
%type <subroutineDecVal> subroutineDec
%type <parameterListVal> parameterList
%type <commaTypeVarNamesVal> commaTypeVarNames
%type <commaTypeVarNameVal> commaTypeVarName
%type <subroutineBodyVal> subroutineBody
%type <varDecsVal> varDecs
%type <varDecVal> varDec
%type <typeVal> type
%type <classNameVal> className
%type <varNameVal> varName 
%type <commaVarNamesVal> commaVarNames
%type <commaVarNameVal> commaVarName
%type <subRoutineNameVal> subRoutineName
%type <statementsVal> statements
%type <statementVal> statement
%type <expressionListVal> expressionList
%type <expressionVal> expression
%type <commaExpressionsVal> commaExpressions
%type <commaExpressionVal> commaExpression
%type <termVal> term
%type <opVal> op
%type <subroutineCallVal> subroutineCall
%type <opTermsVal> opTerms
%type <opTermVal> opTerm
%type <unaryOpVal> unaryOp
%type <keywordConstantVal> keywordConstant

// precedence (same as c language)
%left OR
%left AND
%left LESS MORE EQUAL
%left ADD MINUS
%left TIMES DIV
%left NOT

// the program starts from class
%start class

%%

// BNF

class: CLASS className '{' classVarDecs subroutineDecs '}' {class = Class_new($2, $4, $5);}
;

classVarDecs: classVarDec classVarDecs {$$ = List_new($1, $2);}
| {$$ = 0;}
;

classVarDec: STATIC type varName commaVarNames ';' {$$ = Class_Var_Dec_Static_new($2, $3, $4);}
| FIELD type varName commaVarNames ';' {$$ = Class_Var_Dec_Field_new($2, $3, $4);}
;

subroutineDecs: subroutineDec subroutineDecs {$$ = List_new($1, $2);}
| {$$ = 0;}
;

subroutineDec: CONSTRUCTOR VOID subRoutineName '(' parameterList ')' subroutineBody {$$ = Subroutine_Dec_Constructor_Void_new($3, $5, $7);}
| CONSTRUCTOR type subRoutineName '(' parameterList ')' subroutineBody {$$ = Subroutine_Dec_Constructor_Type_new($2, $3, $5, $7);}
;

parameterList: type varName commaTypeVarNames {$$ = Parameter_List_new($1, $2, $3);}
| {$$ = 0;}
;

commaTypeVarNames: commaTypeVarName commaTypeVarNames {$$ = List_new($1, $2);}
| {$$ = 0;}
;

commaTypeVarName: ',' type varName {$$ = Comma_Type_Var_Name_new($2, $3);}
;

subroutineBody: '{' varDecs statements '}' {$$ = Subroutine_Body_new($2, $3);}
;

varDecs: varDec varDecs {$$ = List_new($1, $2);}
| {$$ = 0;}
;

varDec: VAR type varName commaVarNames ';' {$$ = Var_Dec_new($2, $3, $4);}
;

type: INT {$$ = Type_new(TYPE_INT);}
| BOOLEAN {$$ = Type_new(TYPE_BOOLEAN);}
| CHAR {$$ = Type_new(TYPE_CHAR);}
| className {Type_new(TYPE_CLASS);}
;

className: ID {$$ = Class_Name_new($1);}
;

commaVarNames: commaVarName commaVarNames {$$ = List_new($1, $2);}
| {$$ = 0;}
;

commaVarName: ',' varName {$$ = Comma_Var_Name_new($2);}
;

varName: ID {$$ = Var_Name_new($1);}
;

subRoutineName: ID {$$ = Sub_Routine_Name_new($1);}
;

statements: statement statements {$$ = List_new($1, $2);}
| {$$ = 0;}
;

statement: LET varName ASSIGN expression ';' {$$ = Statement_Let_new($2, $4);}
| IF '(' expression ')' '{' statements '}' {$$ = Statement_If_new($3, $6);}
| IF '(' expression ')' '{' statements '}' ELSE '{' statements '}' {$$ = Statement_If_Else_new($3, $6, $10);}
| WHILE '(' expression ')' '{' statements '}' {$$ = Statement_While_new($3, $6);}
| DO subroutineCall ';' {$$ = Statement_Do_new($2);}
| RETURN ';' {$$ = Statement_Return_new();}
| RETURN expression ';' {$$ = Statement_Return_Expression_new($2);}
;

expressionList: expression commaExpressions {$$ = Expression_List_new($1, $2);}
| {$$ = 0;}
;

commaExpressions: commaExpression commaExpressions {$$ = List_new($1, $2);}
| {$$ = 0;}
;

commaExpression: ',' expression {$$ = Comma_Expression_new($2);}
;

expression: term opTerms {$$ = Expression_new($1, $2);}
;

opTerms: opTerm opTerms {$$ = List_new($1, $2);}
| {$$ = 0;}
;

opTerm: op term {$$ = Op_Term_new($1, $2);}
;

term: INTNUM {$$ = Term_Integer_Constant_new($1);}
| keywordConstant {$$ = Term_Keyword_Constnant_new($1);}
| varName {$$ = Term_Var_Name_new($1);}
| subroutineCall {$$ = Term_Sub_Routine_Call_new($1);}
| '(' expression ')' {$$ = Term_Expression_new($2);}
| unaryOp term {$$ = Term_Unary_Op_Term_new($1, $2);}
;

subroutineCall: subRoutineName '(' expressionList ')' {$$ = Sub_Routine_Call_Self_Function_new($1, $3);}
// BUG: There are reduce/reduce conflict here because these two rules are the same
| varName '.' subRoutineName '(' expressionList ')' {$$ = Sub_Routine_Call_Object_Function_new($1, $3, $5);}
| className '.' subRoutineName '(' expressionList ')' {$$ = Sub_Routine_Call_Static_Function_new($1, $3, $5);}
;

op: ADD {$$ = Op_new(OP_PLUS);}
| MINUS {$$ = Op_new(OP_MINUS);}
| TIMES {$$ = Op_new(OP_TIMES);}
| DIV {$$ = Op_new(OP_DIV);}
| AND {$$ = Op_new(OP_AND);}
| OR {$$ = Op_new(OP_OR);}
| LESS {$$ = Op_new(OP_LESS);}
| MORE {$$ = Op_new(OP_MORE);}
| EQUAL {$$ = Op_new(OP_EQUAL);}
;

unaryOp: MINUS {$$ = Unary_Op_new(UNARY_OP_DASH);}
| NOT {$$ = Unary_Op_new(UNARY_OP_WAVE);}
;

keywordConstant: TRUE {$$ = Keyword_Constant_new(KEYWORD_TRUE);}
| FALSE {$$ = Keyword_Constant_new(KEYWORD_FALSE);}
| _NULL {$$ = Keyword_Constant_new(KEYWORD_NULL);}
| THIS {$$ = Keyword_Constant_new(KEYWORD_THIS);}

%%

void yyerror (char *s) {
  fprintf (stderr, "%s\n", s);
  return;
}