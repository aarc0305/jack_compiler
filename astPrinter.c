#include <stdio.h>
#include <stdlib.h>
#include "astPrinter.h"

// print the type
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

// print varName
void Print_Var_Name(Var_Name_t varName) {
	printf("<identifier>");
	printf("%s", varName -> varName);
	printf("</identifier>\n");
}

// print comma var names
void Print_Comma_Var_Names(List_t commaVarNames) {
	while (commaVarNames) {
		Comma_Var_Name_t comma_var_name = commaVarNames -> data;
		printf("<symbol>,</symbol>\n");
		Print_Var_Name(comma_var_name -> varName);
		commaVarNames = commaVarNames -> next;
	} 
}

// print the keyword constant
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

// print the comma expressions
void Print_Comma_Expressions(List_t commaExpressions) {

}

// print the expression list
void Print_Expression_List(Expression_List_t expressionList) {
	printf("<expressionList>\n");
	if (expressionList == 0) {
		//nop
	} else {
		Expression_t expression = expressionList -> expression;
		List_t commaExpressions = expressionList -> commaExpressions;
		Print_Expression(expression);
		Print_Comma_Expressions(commaExpressions);
	}
	printf("</expressionList>\n");
}

// print the subroutine call
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
	}
	// TODO:
}

// print the term
void Print_Term(Term_t term) {
	// TODO:
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
	}
}

// print the expression
void Print_Expression(Expression_t expression) {
	// TODO:
	Term_t term = expression -> term;
	List_t opTerms = expression -> opTerms;
	Print_Term(term);
}

// print the statement
void Print_Statement(Statement_t statement) {
	Statement_Kind_t kind = statement -> kind;
	if (kind == STATEMENT_LET) {
		Statement_Let statementLet = (Statement_Let) statement;
		Var_Name_t varName = statementLet -> varName;
		Expression_t expression = statementLet -> expression;
		printf("<keyword>let</keyword>\n");
		Print_Var_Name(varName);
		printf("<symbol>=</symbol>\n");
		Print_Expression(expression);
		printf("<symbol>;</symbol>\n");
	} else if (kind == STATEMENT_IF) {
		// TODO:
	}
}

// print the statements
void Print_Statements(List_t statements) {
	while (statements) {
		Statement_t statement = statements -> data;
		Print_Statement(statement);
		statements = statements -> next;
	}
}

// print the var dec
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

// print the var decs
void Print_Var_Decs(List_t varDecs) {
	while (varDecs) {
		Var_Dec_t varDec = (varDecs -> data);
		Print_Var_Dec(varDec);
		varDecs = varDecs -> next;
	} 
}

// print the subroutine body
void Print_Subroutine_Body(Subroutine_Body_t subroutineBody) {
	List_t varDecs = subroutineBody -> varDecs;
	List_t statements = subroutineBody -> statements;
	Print_Var_Decs(varDecs);
	Print_Statements(statements);

}

// print the parameter list
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

// print the sub routine name
void Print_Subroutine_Name(Sub_Routine_Name_t routine_name) {
	char* name = routine_name -> subRoutineName;
	printf("<identifier>");
	printf("%s", name);
	printf("</identifier>\n");
}

// print the subroutine dec
void Print_Subroutine_Dec(Subroutine_Dec_t subroutineDec) {
	Subroutine_Dec_Kind_t kind = subroutineDec -> kind;
	if (kind == SUBROUTINE_DEC_CONSTRUCTOR_VOID) {
		printf("<subroutineDec>\n");
		printf("<keyword>constructor</keyword>\n");
		printf("<keyword>void</keyword>\n");
		// TODO:
		Subroutine_Dec_Constructor_Void subroutine_dec_constructor_void = (Subroutine_Dec_Constructor_Void) subroutineDec;
		Sub_Routine_Name_t routine_name = subroutine_dec_constructor_void -> subroutineName;
		Parameter_List_t parameter_list = subroutine_dec_constructor_void -> parameter_list;
		Subroutine_Body_t subroutine_body = subroutine_dec_constructor_void -> subroutineBody;
		Print_Subroutine_Name(routine_name);
		printf("<symbol>(</symbol>\n");
		Print_Parameter_List(parameter_list);
		printf("<symbol>)</symbol>\n");
		printf("<symbol>{</symbol>\n");
		Print_Subroutine_Body(subroutine_body);
		printf("<symbol>}</symbol>\n");
		printf("</subroutineDec>\n");

	}
}

// print the subroutune decs
void Print_Subroutine_Decs(List_t subroutineDecs) {
	while (subroutineDecs) {
		Subroutine_Dec_t subroutine_dec = subroutineDecs -> data;
		Print_Subroutine_Dec(subroutine_dec);
		subroutineDecs = subroutineDecs -> next;
	}
}

// print the class var dec
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

// print the class var decs
void Print_Class_Var_Decs(List_t classVarDecs) {
	while(classVarDecs) {
		Class_Var_Dec_t class_var_dec = classVarDecs -> data;
		Print_Class_Var_Dec(class_var_dec);
		classVarDecs = classVarDecs -> next;
	}
}

// print the class name
void Print_Class_Name(Class_Name_t className) {
	char* name = className -> className;
	printf("<identifier>");
	printf("%s", name);
	printf("</identifier>\n");
}

// print the class
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

