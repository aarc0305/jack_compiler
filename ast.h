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
	TYPE_CHAR
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

// class
typedef struct Class_t* Class_t;
struct Class_t {
	char* className;
	List_t classVarDecs;
	// TODO: 1. class var declaration 2. subroutine declaration
};
Class_t Class_new(char* className, List_t classVarDecs);

// type
typedef struct Type_t* Type_t;
struct Type_t {
	Type_Kind_t kind;
};
Type_t Type_new(Type_Kind_t kind);

// className
typedef struct Class_Name_t* Class_Name_t;
struct Class_Name_t {
	char* className;
};
Class_Name_t Class_Name_new(char* className);

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




#endif