#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "ast.h"

// This is the structure stored in the symbol table
typedef struct St_Element_t* St_Element_t;
struct St_Element_t {
	char* id;
	Type_t type;
};
St_Element_t St_Element_new(char* id, Type_t type);

void Check_Var_Name(Var_Name_t varName, Type_t type);
void Check_Comma_Var_Names(List_t commaVarNames, Type_t type);
void Check_Var_Dec(Class_Var_Dec_t classVarDec);
void Check_Subroutine_Decs(List_t subroutineDecs);
void Check_Class_Var_Decs(List_t classVarDecs);
void Check_Class(Class_t class);

#endif