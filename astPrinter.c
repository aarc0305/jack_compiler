#include <stdio.h>
#include <stdlib.h>
#include "astPrinter.h"

void Print_Type(Type_t type) {
	Type_Kind_t kind = type -> kind;
	if (kind == TYPE_INT) {
		printf("<keyword>");
		printf("int");
		printf("</keyword>\n");
	} else if (kind == TYPE_BOOLEAN) {
		printf("<keyword>");
		printf("boolean");
		printf("</keyword>\n");
	} else if (kind == TYPE_CHAR) {
		printf("<keyword>");
		printf("char");
		printf("</keyword>\n");
	} else if (kind == TYPE_CLASS) {
		Type_Class type_class = (Type_Class) type;
		Class_Name_t className = type_class -> className;
		Print_Class_Name(className);
	}
}

void Print_Var_Name(Var_Name_t varName) {
	printf("<identifier>");
	printf("%s", varName -> varName);
	printf("</identifier>\n");
}

void Print_Comma_Var_Names(List_t commaVarNames) {
	while (commaVarNames) {
		Comma_Var_Name_t comma_var_name = commaVarNames -> data;
		printf("<symbol>,</symbol>\n");
		Print_Var_Name(comma_var_name -> varName);
		commaVarNames = commaVarNames -> next;
	} 
}

void Print_Keyword_Constant(Keyword_Constant_t keywordConstant) {
	Keyword_Constant_Kind_t kind = keywordConstant -> kind;
	if (kind == KEYWORD_TRUE) {
		printf("<constant>true</constant>\n");
	} else if (kind == KEYWORD_FALSE) {
		printf("<constant>false</constant>\n");
	} else if (kind == KEYWORD_NULL) {
		printf("<constant>null</constant>\n");
	} else if (kind == KEYWORD_THIS) {
		printf("<constant>this</constant>\n");
	}
}

void Print_Comma_Expressions(List_t commaExpressions) {
	while (commaExpressions) {
		Comma_Expression_t commaExpression = commaExpressions -> data;
		printf("<symbol>,</symbol>\n");
		Print_Expression(commaExpression -> expression);
		commaExpressions = commaExpressions -> next;
	}
}

void Print_Expression_List(Expression_List_t expressionList) {
	printf("<expressionList>\n");
	if (expressionList == 0) {
		// nop
	} else {
		Expression_t expression = expressionList -> expression;
		List_t commaExpressions = expressionList -> commaExpressions;
		Print_Expression(expression);
		Print_Comma_Expressions(commaExpressions);
	}
	printf("</expressionList>\n");
}

void Print_Subroutine_Call(Sub_Routine_Call_t subroutineCall) {
	Sub_Routine_Call_Kind_t kind = (Sub_Routine_Call_Kind_t) subroutineCall -> kind;
	if (kind == SUB_ROUTINE_SELF_FUNCTION) {
		Sub_Routine_Call_Self_Function subRoutineCallSelfFunction = (Sub_Routine_Call_Self_Function) subroutineCall;
		Sub_Routine_Name_t subRoutineName = subRoutineCallSelfFunction -> subRoutineName;
		Expression_List_t expressionList = subRoutineCallSelfFunction -> expressionList;
		Print_Subroutine_Name(subRoutineName);
		printf("<symbol>(</symbol>\n");
		Print_Expression_List(expressionList);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>;</symbol>\n");
	} else if (kind == SUB_ROUTINE_OBJECT_FUNCTION) {
		Sub_Routine_Call_Object_Function subRoutineCallObjectFunction = (Sub_Routine_Call_Object_Function) subroutineCall;
		Var_Name_t varName = subRoutineCallObjectFunction -> varName;
		Sub_Routine_Name_t subRoutineName = subRoutineCallObjectFunction -> subRoutineName;
		Expression_List_t expressionList = subRoutineCallObjectFunction -> expressionList;
		Print_Var_Name(varName);
		printf("<symbol>.</symbol>\n");
		Print_Subroutine_Name(subRoutineName);
		printf("<symbol>(</symbol>\n");
		Print_Expression_List(expressionList);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>;</symbol>\n");
	}
	// BUG: There is a reduce/reduce conflict in the jack.y
}

void Print_UnaryOp(Unary_Op_t unaryOp) {
	Unary_Op_Kind_t kind = unaryOp -> kind;
	if (kind == UNARY_OP_DASH) {
		printf("<symbol>-</symbol>\n");
	} else if (kind == UNARY_OP_WAVE) {
		printf("<symbol>~</symbol>\n");
	}
}

void Print_Term(Term_t term) {
	printf("<term>\n");
	Term_Kind_t kind = term -> kind;
	if (kind == TERM_INTEGERCONSTANT) {
		Term_Integer_Constant termIntegerConstant = (Term_Integer_Constant) term;
		int constant = termIntegerConstant -> constant;
		printf("<constant>%d</constant>\n", constant);
	} else if (kind == TERM_KEYWORDCONSTANT) {
		Term_Keyword_Constnant termKeywordConstant = (Term_Keyword_Constnant) term;
		Keyword_Constant_t keywordConstant = termKeywordConstant -> constant;
		Print_Keyword_Constant(keywordConstant);
	} else if (kind == TERM_VARNAME) {
		Term_Var_Name termVarName = (Term_Var_Name) term;
		Var_Name_t varName = termVarName -> varName;
		Print_Var_Name(varName);
	} else if (kind == TERM_SUBROUTINECALL) {
		Term_Sub_Routine_Call termSubroutineCall = (Term_Sub_Routine_Call) term;
		Sub_Routine_Call_t subRoutineCall = termSubroutineCall -> subRoutineCall;
		Print_Subroutine_Call(subRoutineCall);
	} else if (kind == TERM_EXPRESSION) {
		Term_Expression termExpression = (Term_Expression) term;
		Expression_t expression = termExpression -> expression;
		printf("<symbol>(</symbol>\n");
		Print_Expression(expression);
		printf("<symbol>)</symbol>\n");
	} else if (kind == TERM_UNARYOPTERM) {
		Term_Unary_Op_Term termUnaryOpTerm = (Term_Unary_Op_Term) term;
		Unary_Op_t unaryOp = termUnaryOpTerm -> unaryOp;
		Term_t term = termUnaryOpTerm -> term;
		Print_UnaryOp(unaryOp);
		Print_Term(term);
	}
	printf("</term>\n");
}

void Print_Op(Op_t op) {
	Op_Kind_t kind = op -> kind;
	if (kind == OP_PLUS) {
		printf("<symbol>+</symbol>\n");
	} else if (kind == OP_MINUS) {
		printf("<symbol>-</symbol>\n");
	} else if (kind == OP_TIMES) {
		printf("<symbol>*</symbol>\n");
	} else if (kind == OP_DIV) {
		printf("<symbol>/</symbol>\n");
	} else if (kind == OP_AND) {
		printf("<symbol>&</symbol>\n");
	} else if (kind == OP_OR) {
		printf("<symbol>|</symbol>\n");
	} else if (kind == OP_LESS) {
		printf("<symbol><</symbol>\n");
	} else if (kind == OP_MORE) {
		printf("<symbol>></symbol>\n");
	} else if (kind == OP_EQUAL) {
		printf("<symbol>==</symbol>\n");
	}
}

void Print_Op_Term(Op_Term_t opTerm) {
	Op_t op = opTerm -> op;
	Term_t term = opTerm -> term;
	Print_Op(op);
	Print_Term(term);
}

void Print_Op_Terms(List_t opTerms) {
	while (opTerms) {
		Op_Term_t opTerm = opTerms -> data;
		Print_Op_Term(opTerm);
		opTerms = opTerms -> next;
	}
}

void Print_Expression(Expression_t expression) {
	printf("<expression>\n");
	Term_t term = expression -> term;
	List_t opTerms = expression -> opTerms;
	Print_Term(term);
	Print_Op_Terms(opTerms);
	printf("</expression>\n");
}

void Print_Statement(Statement_t statement) {
	Statement_Kind_t kind = statement -> kind;
	if (kind == STATEMENT_LET) {
		printf("<letStatement>\n");
		Statement_Let statementLet = (Statement_Let) statement;
		Var_Name_t varName = statementLet -> varName;
		Expression_t expression = statementLet -> expression;
		printf("<keyword>let</keyword>\n");
		Print_Var_Name(varName);
		printf("<symbol>=</symbol>\n");
		Print_Expression(expression);
		printf("<symbol>;</symbol>\n");
		printf("</letStatement>\n");
	} else if (kind == STATEMENT_IF) {
		printf("<ifStatement>\n");
		printf("<keyword>if</keyword>\n");
		Statement_If statementIf = (Statement_If) statement;
		Expression_t expression = statementIf -> expression;
		List_t statements = statementIf -> statements;
		printf("<symbol>(</symbol>\n");
		Print_Expression(expression);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>{</symbol>\n");
		Print_Statements(statements);
		printf("<symbol>}</symbol>\n");
		printf("</ifStatement>\n");
	} else if (kind == STATEMENT_IF_ELSE) {
		printf("<ifStatement>\n");
		printf("<keyword>if</keyword>\n");
		Statement_If_Else statementIfElse = (Statement_If_Else) statement;
		Expression_t expression = statementIfElse -> expression;
		List_t ifStatements = statementIfElse -> ifStatements;
		List_t elseStatements = statementIfElse -> elseStatements;
		printf("<symbol>(</symbol>\n");
		Print_Expression(expression);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>{</symbol>\n");
		Print_Statements(ifStatements);
		printf("<symbol>}</symbol>\n");
		printf("<keyword>else</keyword>\n");
		printf("<symbol>{</symbol>\n");
		Print_Statements(elseStatements);
		printf("<symbol>}</symbol>\n");
		printf("</ifStatement>\n");
	} else if (kind == STATEMENT_WHILE) {
		printf("<whileStatement>\n");
		printf("<kwyword>while</keyword>\n");
		Statement_While statementWhile = (Statement_While) statement;
		Expression_t expression = statementWhile -> expression;
		List_t statements = statementWhile -> statements;
		printf("<symbol>(</symbol>\n");
		Print_Expression(expression);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>{</symbol>\n");
		Print_Statements(statements);
		printf("<symbol>}</symbol>\n");
		printf("</whileStatement>\n");
	} else if (kind == STATEMENT_DO) {
		printf("<doStatement>\n");
		printf("<keyword>do</keyword>\n");
		Statement_Do statementDo = (Statement_Do) statement;
		Sub_Routine_Call_t subRoutineCall =  statementDo -> sub_routine_call;
		Print_Subroutine_Call(subRoutineCall);
		printf("</doStatement>\n");
	} else if (kind == STATEMENT_RETURN) {
		printf("<returnStatement>\n");
		printf("<keyword>return</keyword>\n");
		printf("</returnStatement>\n");
	} else if (kind == STATEMENT_RETURN_EXPRESSION) {
		printf("<returnStatement>\n");
		printf("<keyword>return</keyword>\n");
		Statement_Return_Expression statementReturnExpression = (Statement_Return_Expression) statement;
		Print_Expression(statementReturnExpression -> expression);
		printf("</returnStatement>\n");
	}
}

void Print_Statements(List_t statements) {
	while (statements) {
		Statement_t statement = statements -> data;
		Print_Statement(statement);
		statements = statements -> next;
	}
}

void Print_Var_Dec(Var_Dec_t varDec) {
	Type_t type = varDec -> type;
	Var_Name_t varName = varDec -> varName;
	List_t commaVarNames = varDec -> commaVarNames;
	printf("<keyword>var</keyword>\n");
	Print_Type(type);
	Print_Var_Name(varName);
	Print_Comma_Var_Names(commaVarNames);
	printf("<symbol>;</symbol>\n");
}

void Print_Var_Decs(List_t varDecs) {
	while (varDecs) {
		Var_Dec_t varDec = (varDecs -> data);
		Print_Var_Dec(varDec);
		varDecs = varDecs -> next;
	} 
}

void Print_Subroutine_Body(Subroutine_Body_t subroutineBody) {
	printf("<subroutineBody>\n");
	List_t varDecs = subroutineBody -> varDecs;
	List_t statements = subroutineBody -> statements;
	Print_Var_Decs(varDecs);
	Print_Statements(statements);
	printf("</subroutineBody>\n");
}

void Print_Parameter_List(Parameter_List_t parameter_list) {
	printf("<parameterList>\n");
	if (parameter_list == 0) {
		// nop
	} else {
		Type_t type = parameter_list -> type;
		Var_Name_t varName = parameter_list -> varName;
		List_t commaVarNames = parameter_list -> commaVarNames;
		Print_Type(type);
		Print_Var_Name(varName);
		Print_Comma_Var_Names(commaVarNames);
	}
	printf("</parameterList>\n");
}

void Print_Subroutine_Name(Sub_Routine_Name_t routine_name) {
	char* name = routine_name -> subRoutineName;
	printf("<identifier>");
	printf("%s", name);
	printf("</identifier>\n");
}

void Print_Subroutine_Dec(Subroutine_Dec_t subroutineDec) {
	Subroutine_Dec_Kind_t kind = subroutineDec -> kind;
	if (kind == SUBROUTINE_DEC_CONSTRUCTOR_VOID) {
		printf("<subroutineDec>\n");
		printf("<keyword>constructor</keyword>\n");
		printf("<keyword>void</keyword>\n");
		Subroutine_Dec_Constructor_Void subroutineDecConstructorVoid = (Subroutine_Dec_Constructor_Void) subroutineDec;
		Sub_Routine_Name_t subroutineName = subroutineDecConstructorVoid -> subroutineName;
		Parameter_List_t parameterList = subroutineDecConstructorVoid -> parameter_list;
		Subroutine_Body_t subroutineBody = subroutineDecConstructorVoid -> subroutineBody;
		Print_Subroutine_Name(subroutineName);
		printf("<symbol>(</symbol>\n");
		Print_Parameter_List(parameterList);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>{</symbol>\n");
		Print_Subroutine_Body(subroutineBody);
		printf("<symbol>}</symbol>\n");
		printf("</subroutineDec>\n");
	} else if (kind == SUBROUTINE_DEC_CONSTRUCTOR_TYPE) {
		printf("<subroutineDec>\n");
		printf("<keyword>constructor</keyword>\n");
		Subroutine_Dec_Constructor_Type subroutineDecConstructorType = (Subroutine_Dec_Constructor_Type) subroutineDec;
		Type_t type = subroutineDecConstructorType -> type;
		Sub_Routine_Name_t subroutineName = subroutineDecConstructorType -> subroutineName;
		Parameter_List_t parameterList = subroutineDecConstructorType -> parameter_list;
		Subroutine_Body_t subroutineBody = subroutineDecConstructorType -> subroutineBody;
		Print_Type(type);
		Print_Subroutine_Name(subroutineName);
		printf("<symbol>(</symbol>\n");
		Print_Parameter_List(parameterList);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>{</symbol>\n");
		Print_Subroutine_Body(subroutineBody);
		printf("<symbol>}</symbol>\n");
	} else if (kind == SUBROUTINE_DEC_FUNCTION_VOID) {
		printf("<subroutineDec>\n");
		printf("<keyword>function</keyword>\n");
		printf("<keyword>void</keyword>\n");
	}
	 // TODO
	
}

// print the subroutune decs
void Print_Subroutine_Decs(List_t subroutineDecs) {
	while (subroutineDecs) {
		Subroutine_Dec_t subroutine_dec = subroutineDecs -> data;
		Print_Subroutine_Dec(subroutine_dec);
		subroutineDecs = subroutineDecs -> next;
	}
}

void Print_Class_Var_Dec(Class_Var_Dec_t class_var_dec) {
	Class_Var_Dec_Kind_t kind = class_var_dec -> kind;
	if (kind == CLASS_VAR_STATIC) {
		Class_Var_Dec_Static var_dec_static = (Class_Var_Dec_Static) class_var_dec;
		Type_t type = var_dec_static -> type;
		Var_Name_t varName = var_dec_static -> varName;
		List_t commaVarNames = var_dec_static -> commaVarNames;
		printf("<classVarDec>\n");
		printf("<keyword>static</keyword>\n");
		Print_Type(type);
		Print_Var_Name(varName);
		Print_Comma_Var_Names(commaVarNames);
		printf("<symbol>;</symbol>\n");
		printf("</classVarDec>\n");
	} else if (kind == CLASS_VAR_FIELD) {
		Class_Var_Dec_Field var_dec_field = (Class_Var_Dec_Field) class_var_dec;
		Type_t type = var_dec_field -> type;
		Var_Name_t varName = var_dec_field -> varName;
		List_t commaVarNames = var_dec_field -> commaVarNames;
		printf("<classVarDec>\n");
		printf("<keyword>field</keyword>\n");
		Print_Type(type);
		Print_Var_Name(varName);
		Print_Comma_Var_Names(commaVarNames);
		printf("<symbol>;</symbol>\n");
		printf("</classVarDec>\n");
	}
}

void Print_Class_Var_Decs(List_t classVarDecs) {
	while(classVarDecs) {
		Class_Var_Dec_t class_var_dec = classVarDecs -> data;
		Print_Class_Var_Dec(class_var_dec);
		classVarDecs = classVarDecs -> next;
	}
}

void Print_Class_Name(Class_Name_t className) {
	char* name = className -> className;
	printf("<identifier>");
	printf("%s", name);
	printf("</identifier>\n");
}

void Print_Class(Class_t class) {
	printf("<class>\n");
	printf("<keyword>class</keyword>\n");
	Print_Class_Name(class -> className);
	printf("<symbol>{</symbol>\n");
	Print_Class_Var_Decs(class -> classVarDecs);
	Print_Subroutine_Decs(class -> subroutineDecs);
	printf("<symbol>}</symbol>\n");
	printf("</class>\n");
}

