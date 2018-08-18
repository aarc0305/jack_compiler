#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "semantic.h"

List_t table = 0;

St_Element_t St_Element_new(char* id, Type_t type) {
	St_Element_t stElement = malloc(sizeof(*stElement));
	stElement -> id = id;
	stElement -> type = type;
	return stElement;
}

// Insert one indentifier in to the symbol table
void Table_Insert(char* newId, Type_t type) {
	List_t tableReplica = table;
	while (tableReplica) {
		char* oldId = ((St_Element_t) (tableReplica -> data)) -> id;
		if (strcmp(oldId, newId) == 0) {
			printf("The identifier is already esisted!\n");
			return;
		}
		tableReplica = tableReplica -> next;
	}
	St_Element_t stElement = St_Element_new(newId, type);
	table = List_new(stElement, table);
}

Type_t Table_Lookup(char* id) {
	List_t tableReplica = table;
	while (tableReplica) {
		St_Element_t stElement = (St_Element_t) (tableReplica -> data);
		char* st_id = stElement -> id;
		if (strcmp(id, st_id) == 0) {
			return (Type_t) (stElement -> type);
		}
		tableReplica = tableReplica -> next;
	}
	printf("The indentifier is not found in symbol table.\n");
	return 0;
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

void Check_Var_Dec(Class_Var_Dec_t classVarDec) {
	Class_Var_Dec_Kind_t kind = classVarDec -> kind;
	if (kind == CLASS_VAR_STATIC) {
		Class_Var_Dec_Static classVarDecStatic = (Class_Var_Dec_Static) classVarDec;
		Type_t type = classVarDecStatic -> type;
		Var_Name_t varName = classVarDecStatic -> varName;
		List_t commaVarNames = classVarDecStatic -> commaVarNames;
		Table_Insert(varName -> varName, type);
		while (commaVarNames) {
			Comma_Var_Name_t commaVarName = commaVarNames -> data;
			Var_Name_t varName = commaVarName -> varName;
			Table_Insert(varName -> varName, type);
			commaVarNames = commaVarNames -> next;
		}
	} else if (kind == CLASS_VAR_FIELD) {
		Class_Var_Dec_Field classVarDecField = (Class_Var_Dec_Field) classVarDec;
		Type_t type = classVarDecField -> type;
		Var_Name_t varName = classVarDecField -> varName;
		List_t commaVarNames = classVarDecField -> commaVarNames;
		Table_Insert(varName -> varName, type);
		while (commaVarNames) {
			Comma_Var_Name_t commaVarName = commaVarNames -> data;
			Var_Name_t varName = commaVarName -> varName;
			Table_Insert(varName -> varName, type);
			commaVarNames = commaVarNames -> next;
		}
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