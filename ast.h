#ifndef AST_H
#define AST_H
#include "list.h"

typedef enum Class_Var_Dec_Kind_t {
	CLASS_VAR_STATIC,
	CLASS_VAR_FIELD
} Class_Var_Dec_Kind_t;

typedef enum Type_Kind_t {
	TYPE_INT,
	TYPE_BOOLEAN,
	TYPE_CHAR,
	TYPE_CLASS
} Type_Kind_t;

typedef enum Keyword_Constant_Kind_t {
	KEYWORD_TRUE,
	KEYWORD_FALSE,
	KEYWORD_NULL,
	KEYWORD_THIS
} Keyword_Constant_Kind_t;

typedef enum Unary_Op_Kind_t {
	UNARY_OP_DASH,
	UNARY_OP_WAVE
} Unary_Op_Kind_t;

typedef enum Op_Kind_t {
	OP_PLUS,
	OP_MINUS,
	OP_TIMES,
	OP_DIV,
	OP_AND,
	OP_OR,
	OP_LESS,
	OP_MORE,
	OP_EQUAL
} Op_Kind_t;

typedef enum Term_Kind_t {
	TERM_INTEGERCONSTANT,
	TERM_STRINGCONSTANT,
	TERM_KEYWORDCONSTANT,
	TERM_VARNAME,
	TERM_VARNAMEARRAY,
	TERM_SUBROUTINECALL,
	TERM_EXPRESSION,
	TERM_UNARYOPTERM
} Term_Kind_t;

typedef enum Sub_Routine_Call_Kind_t {
	SUB_ROUTINE_SELF_FUNCTION,
	SUB_ROUTINE_OBJECT_FUNCTION,
	SUB_ROUTINE_STATIC_FUNCTION
} Sub_Routine_Call_Kind_t;

typedef enum Statement_Kind_t {
	STATEMENT_LET,
	STATEMENT_IF,
	STATEMENT_IF_ELSE,
	STATEMENT_WHILE,
	STATEMENT_DO,
	STATEMENT_RETURN,
	STATEMENT_RETURN_EXPRESSION
} Statement_Kind_t;

typedef enum Subroutine_Dec_Kind_t {
	SUBROUTINE_DEC_CONSTRUCTOR_VOID,
	SUBROUTINE_DEC_CONSTRUCTOR_TYPE,
	SUBROUTINE_DEC_FUNCTION_VOID,
	SUBROUTINE_DEC_FUNCTION_TYPE,
	SUBROUTINE_DEC_METHOD_VOID,
	SUBROUTINE_DEC_METHOD_TYPE
} Subroutine_Dec_Kind_t;

// className
typedef struct Class_Name_t* Class_Name_t;
struct Class_Name_t {
	char* className;
};
Class_Name_t Class_Name_new(char* className);

// class
typedef struct Class_t* Class_t;
struct Class_t {
	Class_Name_t className;
	List_t classVarDecs;
	List_t subroutineDecs;
};
Class_t Class_new(Class_Name_t className, List_t classVarDecs, List_t subroutineDecs);

// type
typedef struct Type_t* Type_t;
struct Type_t {
	Type_Kind_t kind;
};
Type_t Type_new(Type_Kind_t kind);

// varName
typedef struct Var_Name_t* Var_Name_t;
struct Var_Name_t {
	char* varName;
};
Var_Name_t Var_Name_new(char* varName);

// commaVarName
typedef struct Comma_Var_Name_t* Comma_Var_Name_t;
struct Comma_Var_Name_t {
	Var_Name_t varName;
};
Comma_Var_Name_t Comma_Var_Name_new(Var_Name_t varName);

// class var declaration
typedef struct Class_Var_Dec_t* Class_Var_Dec_t;
struct Class_Var_Dec_t {
	Class_Var_Dec_Kind_t kind;
};

// static class var dec 
typedef struct Class_Var_Dec_Static* Class_Var_Dec_Static;
struct Class_Var_Dec_Static {
	Class_Var_Dec_Kind_t kind;
	Type_t type;
	Var_Name_t varName;
	List_t commaVarNames;
};
Class_Var_Dec_t Class_Var_Dec_Static_new(Type_t type, Var_Name_t varName, List_t commaVarNames);

// field class var dec 
typedef struct Class_Var_Dec_Field* Class_Var_Dec_Field;
struct Class_Var_Dec_Field {
	Class_Var_Dec_Kind_t kind;
	Type_t type;
	Var_Name_t varName;
	List_t commaVarNames;
};
Class_Var_Dec_t Class_Var_Dec_Field_new(Type_t type, Var_Name_t varName, List_t commaVarNames);

// subRoutineName
typedef struct Sub_Routine_Name_t* Sub_Routine_Name_t;
struct Sub_Routine_Name_t {
	char* subRoutineName;
};
Sub_Routine_Name_t Sub_Routine_Name_new(char* subRoutineName);

// keyword constant
typedef struct Keyword_Constant_t* Keyword_Constant_t;
struct Keyword_Constant_t {
	Keyword_Constant_Kind_t kind;
};
Keyword_Constant_t Keyword_Constant_new(Keyword_Constant_Kind_t kind);

// unary op
typedef struct Unary_Op_t* Unary_Op_t;
struct Unary_Op_t {
	Unary_Op_Kind_t kind;
};
Unary_Op_t Unary_Op_new(Unary_Op_Kind_t kind);

// op
typedef struct Op_t* Op_t;
struct Op_t {
	Op_Kind_t kind;
};
Op_t Op_new(Op_Kind_t kind);

// term
typedef struct Term_t* Term_t;
struct Term_t {
	Term_Kind_t kind;
};

// op term
typedef struct Op_Term_t* Op_Term_t;
struct Op_Term_t {
	Op_t op;
	Term_t term;
};
Op_Term_t Op_Term_new(Op_t op, Term_t term);

// expression
typedef struct Expression_t* Expression_t;
struct Expression_t {
	Term_t term;
	List_t opTermList;
};
Expression_t Expression_new(Term_t term, List_t opTermList);

// comma expression
typedef struct Comma_Expression_t* Comma_Expression_t;
struct Comma_Expression_t {
	Expression_t expression;
};
Comma_Expression_t Comma_Expression_new(Expression_t expression);

// expression list
typedef struct Expression_List_t* Expression_List_t;
struct Expression_List_t {
	Expression_t expression;
	List_t commaExpressions;
};
Expression_List_t Expression_List_new(Expression_t expression, List_t commaExpressions);

// sub routine call
typedef struct Sub_Routine_Call_t* Sub_Routine_Call_t;
struct Sub_Routine_Call_t {
	Sub_Routine_Call_Kind_t kind;
};

// sub routine call for self function
typedef struct Sub_Routine_Call_Self_Function* Sub_Routine_Call_Self_Function;
struct Sub_Routine_Call_Self_Function {
	Sub_Routine_Call_Kind_t kind;
	Sub_Routine_Name_t subRoutineName;
	Expression_List_t expressionList;
};
Sub_Routine_Call_t Sub_Routine_Call_Self_Function_new(Sub_Routine_Name_t subRoutineName, Expression_List_t expressionList);

// sub routine call for object function
typedef struct Sub_Routine_Call_Object_Function* Sub_Routine_Call_Object_Function;
struct Sub_Routine_Call_Object_Function {
	Sub_Routine_Call_Kind_t kind;
	Var_Name_t varName;
	Sub_Routine_Name_t subRoutineName;
	Expression_List_t expressionList;
};
Sub_Routine_Call_t Sub_Routine_Call_Object_Function_new(Var_Name_t varName, Sub_Routine_Name_t subRoutineName, Expression_List_t expressionList);

// sub routine call for static function
typedef struct Sub_Routine_Call_Static_Function* Sub_Routine_Call_Static_Function;
struct Sub_Routine_Call_Static_Function {
	Sub_Routine_Call_Kind_t kind;
	Class_Name_t className;
	Sub_Routine_Name_t subRoutineName;
	Expression_List_t expressionList;
};
Sub_Routine_Call_t Sub_Routine_Call_Static_Function_new(Class_Name_t className, Sub_Routine_Name_t subRoutineName, Expression_List_t expressionList);

// term integer constant
typedef struct Term_Integer_Constant* Term_Integer_Constant;
struct Term_Integer_Constant {
	Term_Kind_t kind;
	int constant;
};
Term_t Term_Integer_Constant_new(int constant);

// term keyword constant
typedef struct Term_Keyword_Constnant* Term_Keyword_Constnant;
struct Term_Keyword_Constnant {
	Term_Kind_t kind;
	Keyword_Constant_t constant;
};
Term_t Term_Keyword_Constnant_new(Keyword_Constant_t constant);

// term var name
typedef struct Term_Var_Name* Term_Var_Name;
struct Term_Var_Name {
	Term_Kind_t kind;
	Var_Name_t varName;
};
Term_t Term_Var_Name_new(Var_Name_t varName);

// term subroutine call
typedef struct Term_Sub_Routine_Call* Term_Sub_Routine_Call;
struct Term_Sub_Routine_Call {
	Term_Kind_t kind;
	Sub_Routine_Call_t subRoutineCall;
};
Term_t Term_Sub_Routine_Call_new(Sub_Routine_Call_t subRoutineCall);

// term expression
typedef struct Term_Expression* Term_Expression;
struct Term_Expression {
	Term_Kind_t kind;
	Expression_t expression;
};
Term_t Term_Expression_new(Expression_t expression);

// term unary op term
typedef struct Term_Unary_Op_Term* Term_Unary_Op_Term;
struct Term_Unary_Op_Term {
	Term_Kind_t kind;
	Unary_Op_t unaryOp;
	Term_t term;
};
Term_t Term_Unary_Op_Term_new(Unary_Op_t unaryOp, Term_t term);

// statement
typedef struct Statement_t* Statement_t;
struct Statement_t {
	Statement_Kind_t kind;
};

// statement let
// TODO: array part has not been implemented yet.
typedef struct Statement_Let* Statement_Let;
struct Statement_Let {
	Statement_Kind_t kind;
	Var_Name_t varName;
	Expression_t expression;
};
Statement_t Statement_Let_new(Var_Name_t varName, Expression_t expression);

// statement if
typedef struct Statement_If* Statement_If;
struct Statement_If {
	Statement_Kind_t kind;
	Expression_t expression;
	List_t statements;
};
Statement_t Statement_If_new(Expression_t expression, List_t statements);

// statement if else
typedef struct Statement_If_Else* Statement_If_Else;
struct Statement_If_Else {
	Statement_Kind_t kind;
	Expression_t expression;
	List_t ifStatements;
	List_t elseStatements;
};
Statement_t Statement_If_Else_new(Expression_t expression, List_t ifStatements, List_t elseStatements);

// statement while
typedef struct Statement_While* Statement_While;
struct Statement_While {
	Statement_Kind_t kind;
	Expression_t expression;
	List_t statements;
};
Statement_t Statement_While_new(Expression_t expression, List_t statements);

// statement do
typedef struct Statement_Do* Statement_Do;
struct Statement_Do {
	Statement_Kind_t kind;
	Sub_Routine_Call_t sub_routine_call;
};
Statement_t Statement_Do_new(Sub_Routine_Call_t sub_routine_call);

// statement return
typedef struct Statement_Return* Statement_Return;
struct Statement_Return {
	Statement_Kind_t kind; 
};
Statement_t Statement_Return_new();

// statement return expression
typedef struct Statement_Return_Expression* Statement_Return_Expression;
struct Statement_Return_Expression {
	Statement_Kind_t kind; 
	Expression_t expression;
};
Statement_t Statement_Return_Expression_new();

// var dec
typedef struct Var_Dec_t* Var_Dec_t;
struct Var_Dec_t {
	Type_t type;
	Var_Name_t varName;
	List_t commaVarNames;
};
Var_Dec_t Var_Dec_new(Type_t type, Var_Name_t varName, List_t commaVarNames);

// subroutine body
typedef struct Subroutine_Body_t* Subroutine_Body_t;
struct Subroutine_Body_t {
	List_t varDecs;
	List_t statements;
};
Subroutine_Body_t Subroutine_Body_new(List_t varDecs, List_t statements);

// comma type varName
typedef struct Comma_Type_Var_Name_t* Comma_Type_Var_Name_t;
struct Comma_Type_Var_Name_t {
	Type_t type;
	Var_Name_t varName;
};
Comma_Type_Var_Name_t Comma_Type_Var_Name_new(Type_t type, Var_Name_t varName);

// parameter list
typedef struct Parameter_List_t* Parameter_List_t;
struct Parameter_List_t {
	Type_t type;
	Var_Name_t varName;
	List_t commaVarNames;
};
Parameter_List_t Parameter_List_new(Type_t type, Var_Name_t varName, List_t commaVarNames);

//subroutine dec
typedef struct Subroutine_Dec_t* Subroutine_Dec_t;
struct Subroutine_Dec_t {
	Subroutine_Dec_Kind_t kind;
};

// subroutine dec constructor void
typedef struct Subroutine_Dec_Constructor_Void* Subroutine_Dec_Constructor_Void;
struct Subroutine_Dec_Constructor_Void {
	Subroutine_Dec_Kind_t kind;
	Sub_Routine_Name_t subroutineName;
	Parameter_List_t parameter_list;
	Subroutine_Body_t subroutineBody;
};
Subroutine_Dec_t Subroutine_Dec_Constructor_Void_new(Sub_Routine_Name_t subroutineName, Parameter_List_t parameter_list, Subroutine_Body_t subroutineBody);

// subroutine dec constructor type
typedef struct Subroutine_Dec_Constructor_Type* Subroutine_Dec_Constructor_Type;
struct Subroutine_Dec_Constructor_Type {
	Subroutine_Dec_Kind_t kind;
	Type_t type;
	Sub_Routine_Name_t subroutineName;
	Parameter_List_t parameter_list;
	Subroutine_Body_t subroutineBody;
};
Subroutine_Dec_t Subroutine_Dec_Constructor_Type_new(Type_t type, Sub_Routine_Name_t subroutineName, Parameter_List_t parameter_list, Subroutine_Body_t subroutineBody);

#endif