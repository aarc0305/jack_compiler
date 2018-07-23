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

// commaVarName
Comma_Var_Name_t Comma_Var_Name_new(Var_Name_t varName) {
	Comma_Var_Name_t comma_var_name = malloc(sizeof(*comma_var_name));
	comma_var_name -> varName = varName;
	return comma_var_name;
}

// static class var dec 
Class_Var_Dec_t Class_Var_Dec_Static_new(Type_t type, Var_Name_t varName, List_t commaVarNames) {
	Class_Var_Dec_Static class_var_dec_static = malloc(sizeof(*class_var_dec_static));
	class_var_dec_static -> type = CLASS_VAR_STATIC;
	class_var_dec_static -> varName = varName;
	class_var_dec_static -> commaVarNames = commaVarNames;
	return (Class_Var_Dec_t) class_var_dec_static;
}

// field class var dec
Class_Var_Dec_t Class_Var_Dec_Field_new(Type_t type, Var_Name_t varName, List_t commaVarNames) {
	Class_Var_Dec_Field class_var_dec_field = malloc(sizeof(*class_var_dec_field));
	class_var_dec_field -> type = CLASS_VAR_FIELD;
	class_var_dec_field -> varName = varName;
	class_var_dec_field -> commaVarNames = commaVarNames;
	return (Class_Var_Dec_t) class_var_dec_field;
}

// subRoutineName
Sub_Routine_Name_t Sub_Routine_Name_new(char* subRoutineName) {
	Sub_Routine_Name_t sub_routine_name = malloc(sizeof(*sub_routine_name));
	sub_routine_name -> subRoutineName = subRoutineName;
	return sub_routine_name;
}
