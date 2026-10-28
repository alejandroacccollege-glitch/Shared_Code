#include <stdio.h>
#include <stdlib.h>

struct strNode
{
    int value;
    struct strNode *next;
};

typedef struct strNode *Node;

void insert(Node first, int newValue)
{
    Node current = first;
    Node newNodeData = (Node)malloc(sizeof(struct strNode));
    newNodeData->value = newValue;
    newNodeData->next = NULL;

    while (current->next != NULL && (current->next->value) < (newNodeData->value))
    {
        current = current->next;
    }
    newNodeData->next = current->next;
    current->next = newNodeData;
}

void printList(Node first) {
    Node current = first;
    
    printf("Lista ordenada: ");
    while (current != NULL) {
        // Si tu campo de datos es un apuntador (int *data), recuerda desreferenciarlo:
        printf("%d -> ", (current -> value));
        
        // (O si en tu estructura final usas 'value', sería: printf("%d -> ", current -> value);)
        
        current = current -> next;
    }
    printf("NULL\n");
}// Only to print the final list, isn't in the exercise

int main()
{
    Node first = (Node)malloc(sizeof(struct strNode));
    first->value = 5; // first quedará fijo como el primero de la lista
    first->next = NULL;
    insert(first, 8);
    insert(first, 7);
    insert(first, 6);
    
    insert(first, 10);
    insert(first, 9);

    printList(first);
    return 0;
}