# ifndef LIST_H_
# define LIST_H_

#include "common.h"

typedef struct strList *List;

List list_create(DestroyFunc);
size_t list_size(List);
void list_add(List list, Type type);
Type list_get(List, int);
void list_insert(List, Type, int);
Type list_remove(List, int);
List list_destroy(List);

# endif