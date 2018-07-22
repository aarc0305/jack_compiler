%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
  	void yyerror (char *);
%}

%union {
	int programVal;
};

// terminal
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
%type <programVal> program

%%

program:

%%

void yyerror (char *s) {
  fprintf (stderr, "%s\n", s);
  return;
}