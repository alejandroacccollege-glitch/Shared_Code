# include <stdio.h>
# include "list.h"

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

void list_set(List list, Type insertedData, int position){
    if (list -> size == 0){
        Node newNode = (Node) malloc (sizeof(struct strNode)); 
        newNode -> data = insertedData;
        list -> first = newNode;
        list -> last = newNode;
        newNode -> prior = NULL;
        newNode -> next = NULL;
        list -> size ++;
    } else {
        if (position < 0 || position > list_size(list)) 
        {
        printf("Invalid position"); 
        } else {
            Node newNode = (Node) malloc (sizeof(struct strNode));
            newNode -> data = insertedData;
            
            if (position == 0) {
            newNode ->prior = NULL;
            newNode->next = list->first;
            list->first->prior = newNode;
            list->first = newNode;
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
}


