#include <stdio.h>
#include <stdlib.h>

extern void yyparse();

int main(int argc, char* argv[]) {
	yyparse();
}