#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

List_t table = 0;

// Insert one indentifier in to the symbol table
void Table_Insert(char* id, Type_t type) {

}

void Table_Lookup(char* id) {

}

void Table_Pop_One() {
	if (table == 0) {
		printf("The symbol table is empty\n");
		return;
	}
	List_t oldptr = table;
	table = table -> next;
	free(oldptr);
}

void Check_Subroutine_Decs(List_t subroutineDecs) {
	while (subroutineDecs) {
		subroutineDecs = subroutineDecs -> next;
	}
}

void Check_Var_Name(Var_Name_t varName, Type_t type) {
	char* name = varName -> varName;
	Table_Insert(name, type);
	return;
}

void Check_Comma_Var_Names(List_t commaVarNames, Type_t type) {

}

void Check_Var_Dec(Class_Var_Dec_t classVarDec) {
	Class_Var_Dec_Kind_t kind = classVarDec -> kind;
	if (kind == CLASS_VAR_STATIC) {
		Class_Var_Dec_Static classVarDecStatic = (Class_Var_Dec_Static) classVarDec;
		Type_t type = classVarDecStatic -> type;
		Var_Name_t varName = classVarDecStatic -> varName;
		List_t commaVarNames = classVarDecStatic -> commaVarNames;
		Check_Var_Name(varName, type);
		Check_Comma_Var_Names(commaVarNames, type);
	}
}

void Check_Class_Var_Decs(List_t classVarDecs) {
	while (classVarDecs) {
		Class_Var_Dec_t classVarDec = classVarDecs -> data;
		Check_Var_Dec(classVarDec);
		classVarDecs = classVarDecs -> next;
	}
}

void Check_Class(Class_t class) {
	List_t classVarDecs = class -> classVarDecs;
	List_t subroutineDecs = class -> subroutineDecs;
	Check_Class_Var_Decs(classVarDecs);
	Check_Subroutine_Decs(subroutineDecs);
}