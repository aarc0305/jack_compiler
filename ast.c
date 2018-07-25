#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

Class_t Class_new(char* className, List_t classVarDecs) {

}

// type
Type_t Type_new(Type_Kind_t kind) {
	Type_t type = malloc(sizeof(*type));
	type -> kind = kind;
	return type;
}

// class name
Class_Name_t Class_Name_new(char* className) {
	Class_Name_t name = malloc(sizeof(*name));
	name -> className = className;
	return name;
}

// var name
Var_Name_t Var_Name_new(char* varName) {
	Var_Name_t name = malloc(sizeof(*name));
	name -> varName = varName;
	return name;
}

// commaVarName
Comma_Var_Name_t Comma_Var_Name_new(Var_Name_t varName) {
	Comma_Var_Name_t comma_var_name = malloc(sizeof(*comma_var_name));
	comma_var_name -> varName = varName;
	return comma_var_name;
}

// static class var dec 
Class_Var_Dec_t Class_Var_Dec_Static_new(Type_t type, Var_Name_t varName, List_t commaVarNames) {
	Class_Var_Dec_Static class_var_dec_static = malloc(sizeof(*class_var_dec_static));
	class_var_dec_static -> kind = CLASS_VAR_STATIC;
	class_var_dec_static -> type = type;
	class_var_dec_static -> varName = varName;
	class_var_dec_static -> commaVarNames = commaVarNames;
	return (Class_Var_Dec_t) class_var_dec_static;
}

// field class var dec
Class_Var_Dec_t Class_Var_Dec_Field_new(Type_t type, Var_Name_t varName, List_t commaVarNames) {
	Class_Var_Dec_Field class_var_dec_field = malloc(sizeof(*class_var_dec_field));
	class_var_dec_field -> kind = CLASS_VAR_FIELD;
	class_var_dec_field -> type = type;
	class_var_dec_field -> varName = varName;
	class_var_dec_field -> commaVarNames = commaVarNames;
	return (Class_Var_Dec_t) class_var_dec_field;
}

// sub routine name
Sub_Routine_Name_t Sub_Routine_Name_new(char* subRoutineName) {
	Sub_Routine_Name_t sub_routine_name = malloc(sizeof(*sub_routine_name));
	sub_routine_name -> subRoutineName = subRoutineName;
	return sub_routine_name;
}

// keyword constant
Keyword_Constant_t Keyword_Constant_new(Keyword_Constant_Kind_t kind) {
	Keyword_Constant_t keyword_constant = malloc(sizeof(*keyword_constant));
	keyword_constant -> kind = kind;
	return keyword_constant;
}

// unary op
Unary_Op_t Unary_Op_new(Unary_Op_Kind_t kind) {
	Unary_Op_t unary_op = malloc(sizeof(*unary_op));
	unary_op -> kind = kind;
	return unary_op;
}

// op
Op_t Op_new(Op_Kind_t kind) {
	Op_t op_t = malloc(sizeof(*op_t));
	op_t -> kind = kind;
	return op_t;
}

// op term
Op_Term_t Op_Term_new(Op_t op, Term_t term) {
	Op_Term_t op_term = malloc(sizeof(*op_term));
	op_term -> op = op;
	op_term -> term = term;
	return op_term;
}

// expression
Expression_t Expression_new(Term_t term, List_t opTermList) {
	Expression_t expression = malloc(sizeof(*expression));
	expression -> term = term;
	expression -> opTermList = opTermList;
	return expression;
}

// comma expression
Comma_Expression_t Comma_Expression_new(Expression_t expression) {
	Comma_Expression_t comma_expression = malloc(sizeof(*comma_expression));
	comma_expression -> expression = expression;
	return comma_expression;
}

// expression list
Expression_List_t Expression_List_new(Expression_t expression, List_t commaExpressions) {
	Expression_List_t expression_list = malloc(sizeof(*expression_list));
	expression_list -> expression = expression;
	expression_list -> commaExpressions = commaExpressions;
	return expression_list;
}

// sub routine call for self function
Sub_Routine_Call_t Sub_Routine_Call_Self_Function_new(Sub_Routine_Name_t subRoutineName, Expression_List_t expressionList) {
	Sub_Routine_Call_Self_Function self_function = malloc(sizeof(*self_function));
	self_function -> kind = SUB_ROUTINE_SELF_FUNCTION;
	self_function -> subRoutineName = subRoutineName;
	self_function -> expressionList = expressionList;
	return (Sub_Routine_Call_t) self_function;
}

// sub routine call for object function
Sub_Routine_Call_t Sub_Routine_Call_Object_Function_new(Var_Name_t varName, Sub_Routine_Name_t subRoutineName, Expression_List_t expressionList) {
	Sub_Routine_Call_Object_Function object_function = malloc(sizeof(*object_function));
	object_function -> kind = SUB_ROUTINE_OBJECT_FUNCTION;
	object_function -> varName = varName;
	object_function -> subRoutineName = subRoutineName;
	object_function -> expressionList = expressionList;
	return (Sub_Routine_Call_t) object_function;
}

// sub routine call for static function
Sub_Routine_Call_t Sub_Routine_Call_Static_Function_new(Class_Name_t className, Sub_Routine_Name_t subRoutineName, Expression_List_t expressionList) {
	Sub_Routine_Call_Static_Function static_function = malloc(sizeof(*static_function));
	static_function -> kind = SUB_ROUTINE_STATIC_FUNCTION;
	static_function -> className = className;
	static_function -> subRoutineName = subRoutineName;
	static_function -> expressionList = expressionList;
	return (Sub_Routine_Call_t) static_function;
}

// TODO: term
// term integer constant
Term_t Term_Integer_Constant_new(int constant) {
	Term_Integer_Constant integer_constant = malloc(sizeof(*integer_constant));
	integer_constant -> kind = TERM_INTEGERCONSTANT;
	integer_constant -> constant = constant;
	return (Term_t) integer_constant;
}

// term keyword constant
Term_t Term_Keyword_Constnant_new(Keyword_Constant_t constant) {
	Term_Keyword_Constnant keyword_constant = malloc(sizeof(*keyword_constant));
	keyword_constant -> kind = TERM_KEYWORDCONSTANT;
	keyword_constant -> constant = constant;
	return (Term_t) keyword_constant;
}

// term var name
Term_t Term_Var_Name_new(Var_Name_t varName) {
	Term_Var_Name var_name = malloc(sizeof(*var_name));
	var_name -> kind = TERM_VARNAME;
	var_name -> varName = varName;
	return (Term_t) varName;
}

// term subroutine call
Term_t Term_Sub_Routine_Call_new(Sub_Routine_Call_t subRoutineCall) {
	Term_Sub_Routine_Call sub_routine_call = malloc(sizeof(*sub_routine_call));
	sub_routine_call -> kind = TERM_SUBROUTINECALL;
	sub_routine_call -> subRoutineCall = subRoutineCall;
	return (Term_t) sub_routine_call;
}

// term expression
Term_t Term_Expression_new(Expression_t expression) {
	Term_Expression term_expression = malloc(sizeof(*term_expression));
	term_expression -> kind = TERM_EXPRESSION;
	term_expression -> expression = expression;
	return (Term_t) term_expression;
}

// term unary op term
Term_t Term_Unary_Op_Term_new(Unary_Op_t unaryOp, Term_t term) {
	Term_Unary_Op_Term unary_op_term = malloc(sizeof(*unary_op_term));
	unary_op_term -> kind = TERM_UNARYOPTERM;
	unary_op_term -> unaryOp = unaryOp;
	unary_op_term -> term = term;
	return (Term_t) unary_op_term;
}

// statement let
// TODO: array part has not been implemented yet.
Statement_t Statement_Let_new(Var_Name_t varName, Expression_t expression) {
	Statement_Let statement_let = malloc(sizeof(*statement_let));
	statement_let -> kind = STATEMENT_LET;
}

// statement if
Statement_t Statement_If_new(Expression_t expression, List_t statements) {
	Statement_If statement_if = malloc(sizeof(*statement_if));
	statement_if -> kind = STATEMENT_IF;
	statement_if -> expression = expression;
	statement_if -> statements = statements;
	return (Statement_t) statement_if;
}

// statement if else
Statement_t Statement_If_Else_new(Expression_t expression, List_t ifStatements, List_t elseStatements) {
	Statement_If_Else statement_if_else = malloc(sizeof(*statement_if_else));
	statement_if_else -> kind = STATEMENT_IF_ELSE;
	statement_if_else -> expression = expression;
	statement_if_else -> ifStatements = ifStatements;
	statement_if_else -> elseStatements = elseStatements;
	return (Statement_t) statement_if_else;
}

// statement while
Statement_t Statement_While_new(Expression_t expression, List_t statements) {
	Statement_While statement_while = malloc(sizeof(*statement_while));
	statement_while -> kind = STATEMENT_WHILE;
	statement_while -> expression = expression;
	statement_while -> statements = statements;
	return (Statement_t) statement_while;
}

// statement do
Statement_t Statement_Do_new(Sub_Routine_Call_t sub_routine_call) {
	Statement_Do statement_do = malloc(sizeof(*statement_do));
	statement_do -> kind = STATEMENT_DO;
	statement_do -> sub_routine_call = sub_routine_call;
	return (Statement_t) statement_do;
}

// statement return
Statement_t Statement_Return_new() {
	Statement_Return statement_return = malloc(sizeof(*statement_return));
	statement_return -> kind = STATEMENT_RETURN;
	return (Statement_t) statement_return;
}

// statement return expression
Statement_t Statement_Return_Expression_new(Expression_t expression) {
	Statement_Return_Expression statement_return_expression = malloc(sizeof(*statement_return_expression));
	statement_return_expression -> kind = STATEMENT_RETURN_EXPRESSION;
	statement_return_expression -> expression = expression;
	return (Statement_t) statement_return_expression;
}
