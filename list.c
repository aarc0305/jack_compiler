#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List_t List_new(void* data, List_t tail) {
	List_t list = malloc(sizeof(*list));
	list -> data = data;
	list -> next = tail;
}