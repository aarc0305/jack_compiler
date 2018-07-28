#include <stdio.h>
#include <stdlib.h>
#include "astPrinter.h"

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
	Print_Class_Name(class -> className);
	Print_Class_Var_Decs(class -> classVarDecs);
}

