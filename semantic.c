#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "semantic.h"

List_t table = 0;
List_t functionTable = 0;

St_Element_t St_Element_new(char* id, Type_t type) {
	St_Element_t stElement = malloc(sizeof(*stElement));
	stElement -> id = id;
	stElement -> type = type;
	return stElement;
}

/* 
    Insert one indentifier in to the symbol table.
    Return 0 when successful; Otherwise, return -1.
*/
int Table_Insert(char* newId, Type_t type) {
	List_t tableReplica = table;
	while (tableReplica) {
		char* oldId = ((St_Element_t) (tableReplica -> data)) -> id;
		if (strcmp(oldId, newId) == 0) {
			printf("The identifier is already esisted!\n");
			return -1;
		}
		tableReplica = tableReplica -> next;
	}
	St_Element_t stElement = St_Element_new(newId, type);
	table = List_new(stElement, table);
	return 0;
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

// Return 0 when successful; Otherwise, return -1.
int Function_Table_Insert(char* newFunctionName) {
	// See if the functionName is already existed.
	List_t functionTableReplica = functionTable;
	while (functionTableReplica) {
		char* oldFunctionName = functionTableReplica -> data;
		if (strcmp(oldFunctionName, newFunctionName) == 0) {
			printf("The function name is already used!\n");
			return -1;
		}
		functionTableReplica = functionTableReplica -> next;
	}
	// If the function name is not existed in the function table, insert it.
	functionTable = List_new(newFunctionName, functionTable);
	return 0;
}

void Function_Table_Pop_One () {
	if (functionTable == 0) {
		printf("The function table is empty\n");
	}
	List_t oldptr = functionTable;
	functionTable = functionTable -> next;
	free(oldptr);
}

void Check_Subroutine_Name(Sub_Routine_Name_t subroutineName, int* funcNum) {
	char* name = subroutineName -> subRoutineName;
	if (Function_Table_Insert(name) == 0) {
		(*funcNum)++;
	}
}

void Check_Subroutine_Dec(Subroutine_Dec_t subroutineDec, int* varNum, int* funcNum) {
	Subroutine_Dec_Kind_t kind = subroutineDec -> kind;
	if (kind == SUBROUTINE_DEC_CONSTRUCTOR_VOID) {
		Subroutine_Dec_Constructor_Void subroutuneDecConstructorVoid = (Subroutine_Dec_Constructor_Void) subroutineDec;
		Sub_Routine_Name_t subroutineName = subroutuneDecConstructorVoid -> subroutineName;
		Parameter_List_t parameterList = subroutuneDecConstructorVoid -> parameter_list;
		Subroutine_Body_t subroutineBody = subroutuneDecConstructorVoid -> subroutineBody;
		Check_Subroutine_Name(subroutineName, funcNum);
		// TODO: parameterList and subroutineBody
	}
}

void Check_Subroutine_Decs(List_t subroutineDecs, int* varNum, int* funcNum) {
	while (subroutineDecs) {
		Subroutine_Dec_t subroutineDec = subroutineDecs -> data;
		Check_Subroutine_Dec(subroutineDec, varNum, funcNum);
		subroutineDecs = subroutineDecs -> next;
	}
}

void Check_Var_Dec(Class_Var_Dec_t classVarDec, int* varNum) {
	Class_Var_Dec_Kind_t kind = classVarDec -> kind;
	if (kind == CLASS_VAR_STATIC) {
		Class_Var_Dec_Static classVarDecStatic = (Class_Var_Dec_Static) classVarDec;
		Type_t type = classVarDecStatic -> type;
		Var_Name_t varName = classVarDecStatic -> varName;
		List_t commaVarNames = classVarDecStatic -> commaVarNames;
		if (Table_Insert(varName -> varName, type) == 0) {
			(*varNum)++;
		}
		while (commaVarNames) {
			Comma_Var_Name_t commaVarName = commaVarNames -> data;
			Var_Name_t varName = commaVarName -> varName;
			if (Table_Insert(varName -> varName, type) == 0) {
				(*varNum)++;
			}
			commaVarNames = commaVarNames -> next;
		}
	} else if (kind == CLASS_VAR_FIELD) {
		Class_Var_Dec_Field classVarDecField = (Class_Var_Dec_Field) classVarDec;
		Type_t type = classVarDecField -> type;
		Var_Name_t varName = classVarDecField -> varName;
		List_t commaVarNames = classVarDecField -> commaVarNames;
		if (Table_Insert(varName -> varName, type) == 0) {
			(*varNum)++;
		}
		while (commaVarNames) {
			Comma_Var_Name_t commaVarName = commaVarNames -> data;
			Var_Name_t varName = commaVarName -> varName;
			if (Table_Insert(varName -> varName, type) == 0) {
				(*varNum)++;
			}
			commaVarNames = commaVarNames -> next;
		}
	}
}

void Check_Class_Var_Decs(List_t classVarDecs, int* varNum) {
	while (classVarDecs) {
		Class_Var_Dec_t classVarDec = classVarDecs -> data;
		Check_Var_Dec(classVarDec, varNum);
		classVarDecs = classVarDecs -> next;
	}
}

void Check_Class(Class_t class) {
	// varNum records the number of variable in the scope of this class.
	int* varNum = malloc(sizeof(*varNum));
	(*varNum) = 0;

	// funcNum records the number of functions in the scope of this class.
	int* funcNum = malloc(sizeof(*funcNum));
	(*funcNum) = 0;

	List_t classVarDecs = class -> classVarDecs;
	List_t subroutineDecs = class -> subroutineDecs;
	Check_Class_Var_Decs(classVarDecs, varNum);
	Check_Subroutine_Decs(subroutineDecs, varNum, funcNum);

	// Pop the variables from the symbol table used in the scope of this class
	for (int i = 0; i < (*varNum); i++) {
		Table_Pop_One();
	}
	free(varNum);

	// Pop the name of functions from the function table used in the scope of this class.
	for (int i = 0; i < (*funcNum); i++) {
		Function_Table_Pop_One();
	}
	free(funcNum);
}