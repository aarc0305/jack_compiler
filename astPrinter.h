#ifndef ASTPRINTER_H
#define ASTPRINTER_H
#include "ast.h"

void Print_Type(Type_t type);
void Print_Var_Name(Var_Name_t varName);
void Print_Comma_Var_Names(List_t commaVarNames);
void Print_Keyword_Constant(Keyword_Constant_t keywordConstant);
void Print_Comma_Expressions(List_t commaExpressions);
void Print_Expression_List(Expression_List_t expressionList);
void Print_Subroutine_Call(Sub_Routine_Call_t subroutineCall);
void Print_Term(Term_t term);
void Print_Expression(Expression_t expression);
void Print_Statement(Statement_t statement);
void Print_Statements(List_t statements);
void Print_Var_Dec(Var_Dec_t varDec);
void Print_Var_Decs(List_t varDecs);
void Print_Subroutine_Body(Subroutine_Body_t subroutineBody);
void Print_Parameter_List(Parameter_List_t parameter_list);
void Print_Subroutine_Name(Sub_Routine_Name_t routine_name);
void Print_Subroutine_Dec(Subroutine_Dec_t subroutineDec);
void Print_Subroutine_Decs(List_t subroutineDecs);
void Print_Class_Var_Dec(Class_Var_Dec_t class_var_dec);
void Print_Class_Var_Decs(List_t classVarDecs);
void Print_Class_Name(Class_Name_t className);
void Print_Class(Class_t class);

#endif