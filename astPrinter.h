#ifndef ASTPRINTER_H
#define ASTPRINTER_H
#include "ast.h"

void Print_Subroutine_Decs(List_t subroutineDecs);
void Print_Class_Var_Dec(Class_Var_Dec_t class_var_dec);
void Print_Class_Var_Decs(List_t classVarDecs);
void Print_Class_Name(Class_Name_t className);
void Print_Class(Class_t class);

#endif