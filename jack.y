%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"
	int yylex();
  	void yyerror (char *);
%}

%union {
	Class_t classVal;
	List_t classVarDecsVal;
	Class_Var_Dec_t classVarDecVal;
	Type_t typeVal;
	Class_Name_t classNameVal;
	Var_Name_t varNameVal;
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

//nonterminal
%type <classVal> class
%type <classVarDecsVal> classVarDecs
%type <classVarDecVal> classVarDec
%type <typeVal> type
%type <classNameVal> className
%type <varNameVal> varName 

%%

class: CLASS className '{' classVarDecs '}' 
;

classVarDecs: classVarDec classVarDecs
|
;

classVarDec: STATIC type varName ';'
;

type: INT {$$ = Type_new(TYPE_INT);}
| BOOLEAN {$$ = Type_new(TYPE_BOOLEAN);}
| CHAR {$$ = Type_new(TYPE_CHAR);}
;

className: ID {$$ = Class_Name_new($1);}
;

varName: ID {$$ = Var_Name_new($1);}
;

%%

void yyerror (char *s) {
  fprintf (stderr, "%s\n", s);
  return;
}