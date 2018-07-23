#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

Class_t Class_new(char* className) {

}

Type_t Type_new(Type_Kind_t kind) {
	Type_t type = malloc(sizeof(*type));
	type -> kind = kind;
	return type;
}

Class_Name_t Class_Name_new(char* className) {
	Class_Name_t name = malloc(sizeof(*name));
	name -> className = className;
	return name;
}

Var_Name_t Var_Name_new(char* varName) {
	Var_Name_t name = malloc(sizeof(*name));
	name -> varName = varName;
	return name;
}