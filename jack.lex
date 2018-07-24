%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"
	#include "jack.tab.h"
	char *clone (char *s)
	{
	  char *p = malloc (strlen(s)+1);
	  strcpy (p, s);
	  return p;
	}
%}

%%

" " {continue;}
"\n" {continue;}
"\t" {continue;}

"class" {return CLASS;}
"constructor" {return CONSTRUCTOR;}
"function" {return FUNCTION;}
"method" {return METHOD;}
"field" {return FIELD;}
"static" {return STATIC;}
"var" {return VAR;}
"int" {return INT;}
"char" {return CHAR;}
"boolean" {return BOOLEAN;}
"void" {return VOID;}
"true" {return TRUE;}
"false" {return FALSE;}
"null" {return _NULL;}
"this" {return THIS;}
"let" {return LET;}
"do" {return DO;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"return" {return RETURN;} 

"{" {return '{';}
"}" {return '}';}
"(" {return '(';}
")" {return ')';}
"[" {return '[';}
"]" {return ']';}
"." {return '.';}
"," {return ',';}
";" {return ';';}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"&" {return '&';}
"|" {return '|';}
"<" {return '<';}
">" {return '>';}
"=" {return '=';}
"~" {return '~';}

[0-9]+ {yylval.intNumVal = atoi(yytext); return INTNUM;}
[a-zA-Z][a-zA-Z0-9_]* {yylval.idVal = clone(yytext); return ID;}
. {printf("lex error!!!\n");}

%%

int yywrap() {
	return 1;
}