#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "astPrinter.h"
#include "semantic.h"

extern void yyparse();
extern Class_t class;

int main(int argc, char* argv[]) {
	yyparse();
	Print_Class(class);
	Check_Class(class);
}