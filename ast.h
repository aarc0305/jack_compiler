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

// class
typedef struct Class_t* Class_t;
struct Class_t {
	char* className;
	// TODO: 1. class var declaration 2. subroutine declaration
};
Class_t Class_new(char* className);

// class var declaration
typedef struct Class_Var_Dec_t* Class_Var_Dec_t;
struct Class_Var_Dec_t {
	Class_Var_Dec_Kind_t kind;
};

// static class var dec 
typedef struct Class_Var_Dec_Static* Class_Var_Dec_Static;
struct Class_Var_Dec_Static {
	Class_Var_Dec_Kind_t kind;
};
Class_Var_Dec_t Class_Var_Dec_Static_new();

// field class var dec 
typedef struct Class_Var_Dec_Field* Class_Var_Dec_Field;
struct Class_Var_Dec_Field {
	Class_Var_Dec_Kind_t kind;
};
Class_Var_Dec_t Class_Var_Dec_Field_new();

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

#endif