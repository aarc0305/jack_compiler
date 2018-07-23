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
	List_t commaVarNamesVal;
	Comma_Var_Name_t commaVarNameVal;
	Sub_Routine_Name_t subRoutineNameVal;
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
%type <commaVarNamesVal> commaVarNames
%type <commaVarNameVal> commaVarName
%type <subRoutineNameVal> subRoutineName

%%

class: CLASS className '{' classVarDecs '}' 
;

classVarDecs: classVarDec classVarDecs
|
;

classVarDec: STATIC type varName commaVarNames ';' {$$ = Class_Var_Dec_Static_new($2, $3, $4);}
| FIELD type varName commaVarNames ';' {$$ = Class_Var_Dec_Field_new($2, $3, $4);}
;

type: INT {$$ = Type_new(TYPE_INT);}
| BOOLEAN {$$ = Type_new(TYPE_BOOLEAN);}
| CHAR {$$ = Type_new(TYPE_CHAR);}
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

%%

void yyerror (char *s) {
  fprintf (stderr, "%s\n", s);
  return;
}