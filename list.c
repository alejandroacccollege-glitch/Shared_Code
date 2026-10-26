# include <stdio.h>
# include "list.h"

#include <stdlib.h>

struct strNode{
    Type data;
    struct strNode *prior, *next;
};

typedef struct strNode *Node;

struct strList {
    Node first, last;
    size_t size;
    DestroyFunc destroyFunc;
};

List list_create(DestroyFunc destroyFunction){
    List list = malloc(sizeof(struct strList));
    list -> first = NULL;
    list -> last = NULL;
    list -> size = 0;
    list -> destroyFunc = destroyFunction;

    return list;
}

size_t list_size(List list){
    return list -> size;
}

void list_add(List list, Type type){
    Node newNode = (Node) malloc(sizeof(struct strNode));
    newNode -> data = type;  

    if (list -> first == NULL){
        list -> first = newNode;
    } 

    list -> size++;
}

Type list_get(List list, int position){
    if (position < 0 || position >= list_size(list)) return NULL;
    Node newNode = list -> first;
    for (int i = 0; i < position; i++){
        newNode = newNode -> next;
    }

    return newNode -> data;
}

void list_insert(List list, Type insertedData, int position) {
    // 1.0 Esto representa el caso cuando la lista está vacía
    if (position < 0 || position > list_size(list))
    {
        printf("Invalid position"); // Se revisa si la posición es válida
    }
    else if (list -> size == 0){
        Node newNode = (Node) malloc (sizeof(struct strNode));
        newNode -> data = insertedData;
        list -> first = newNode;
        list -> last = newNode;
        newNode -> prior = NULL;
        newNode -> next = NULL;
        list -> size ++;
    }
    // 2.0 Esto representa cualquier otro caso
        else {
            // 2.1 Crea el nodo con el cual el dato insetado se podrá conectar en donde se inserte
            Node newNode = (Node) malloc (sizeof(struct strNode));
            newNode -> data = insertedData;
            // Este es el caso en el que se quiere ingresar en la primera posición
            if (position == 0) {
                newNode -> prior = NULL; // El anterior del nuevo dato apunta a nulo ya que queda al frente
                newNode -> next = list -> first; // El siguiente del nuevo dato apunta al que antes era el primero para que el nuevo dato sea el primero
                list -> first -> prior = newNode; // Ahora el que era el primero se recorre y ahora su anterior es el nodo del nuevo dato
                //(El que era el primero deja de ser el primero)
                list -> first = newNode; // Ahora el first se actualiza
                list->size++;
            }
            else {
                Node currentNode = list -> first;
                for (int i = 0; i < position; i++){
                    currentNode = currentNode -> next;
                }
                newNode -> prior = currentNode;
                newNode -> next = currentNode -> next;
                currentNode -> next = newNode;

                if (newNode->next != NULL) {
                    newNode->next->prior = newNode;
                } else {
                    list->last = newNode;
                }
                list -> size++;
            }
        }
    }
Type list_remove(List list, int position) {
    if (position < 0 || position >= list_size(list)) {
        return NULL;
    }
    Type newData;
    Node newNode;
    if (list -> size == 1) {
        newData = list -> first -> data;
        free(list -> first);
        list -> first = NULL;
        list -> last = NULL;

    } else if (position == 0) {
        newData = list -> first -> data;
        newNode = list -> first -> next;
        free(list -> first);
        list -> first = newNode;
        newNode -> prior = NULL;
    } else if (position == list -> size - 1) {
        newData = list -> last -> data;
        newNode = list -> last -> prior;
        free(list -> last);
        list -> last = newNode;
        newNode -> next = NULL;
    } else {
        newNode = list -> first;
        for (int i = 0; i < position; i++) {
            newNode = newNode -> next;
        }
        newData = newNode -> data;
        newNode -> prior -> next = newNode -> next;
        newNode -> next -> prior = newNode -> prior;
        free(newNode);
    }
    return newData;
}