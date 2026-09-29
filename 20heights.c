#include <stdio.h>
#include <stdlib.h>

typedef unsigned char (*getterFunction)();

unsigned char initialNumberOfHeights(){
    
    printf("Insert how many height you want to add: ");
    unsigned char numberOfHeights = 0;
    scanf("%c", &numberOfHeights);
    getchar();

    unsigned char value = numberOfHeights - '0';  
    return value;
}// Asks for the main quantity of heights that the user want

unsigned char nextNumberOfHeights(){

    printf("Insert how many height more you want to add: ");
    unsigned char newNumberOfHeights = 0;
    scanf("%c", &newNumberOfHeights);
    getchar();
 
    unsigned char value = newNumberOfHeights - '0';   
    return value;
}// Asks for the complementary quantity of heights that the user want


float *processHeights (char *numberOfHeights){
float *userHeights = (float*) calloc(*numberOfHeights, sizeof(float));
    for (int i = 0; i < *numberOfHeights; i++){
        printf("Insert height %d: ", i + 1);
        float insertedHeight = 0;
        scanf("%f", &insertedHeight);
        *(userHeights + i) = insertedHeight;
    }
    return userHeights;
}// Fills the spaces that the user lets in the initial
// and next quantity of heights

float getMaxHeight(float *userHeights, char *totalQuantity) {
    float maxHeight = *userHeights; 
    for (int i = 1; i < *totalQuantity; i++) {
        if (*(userHeights + i) > maxHeight) {
            maxHeight = *(userHeights + i);
        }
    }
    return maxHeight;
}// Goes throught the "array" looking for the max height

float getMinHeight(float *userHeights, char *totalQuantity) {
    float minHeight = *userHeights;
    int startIndex = 0;
    
    for (int i = 0; i < *totalQuantity; i++) {
        if (*(userHeights + i) != 0.0f) {
            minHeight = *(userHeights + i);
            startIndex = i + 1;
            break;
        }
    }// Looks for the min different of "0"

    if (minHeight == 0.0f) {
        return 0.0f;
    }// When all number aren't different of "0"
    // means that all heights was "0"

    for (int i = startIndex; i < *totalQuantity; i++) {
        if (*(userHeights + i) != 0.0f && *(userHeights + i) < minHeight) {
            minHeight = *(userHeights + i);
        }
    }// Compares the rest of the numbers differents of "0"

    return minHeight;
}// Goes throught the "array" looking for the min height

float getAverageHeight(float *userHeights, char *totalQuantity) {
    float accumulatedSum = 0.0;
    for (int i = 0; i < *totalQuantity; i++) {
        accumulatedSum += *(userHeights + i);
    }
    return accumulatedSum / *totalQuantity;
}//Goes throught the "array" accumulating the sum of the heights
// then devide by the the number of heights inserted 

void printFinalHeights(float *(*principalHeights)(char *), getterFunction getInitial, getterFunction getNext){
    char initialQuantity = getInitial();

    float *userHeights = principalHeights(&initialQuantity); // Get the initial number of the heights that the user want

    getchar();

    char extraQuantity = getNext(); // Get the extra number of the heights that the user want

    char totalQuantity = initialQuantity + extraQuantity;

    if (extraQuantity > 0){
        float *temporal = (float*) realloc(userHeights, totalQuantity * sizeof(float));
        if (temporal != NULL){
            userHeights = temporal; // Evaluates if the values inside are different of NULL
            // to determinate if we can use userHeights as our principal container

            for (int i = initialQuantity; i < totalQuantity; i++) {
                printf("Insert height %d: ", i + 1);
                float insertedHeight = 0;
                scanf("%f", &insertedHeight);
                *(userHeights + i) = insertedHeight;
        }
        }// Fills the userHeights with the heights that the user insert
    } 
    
    printf("Heights inserted: \n");
    for (int i = 0; i < totalQuantity; i++) {
        printf("%.2f \n", *(userHeights + i));
    }// Prints the final container with all heights

    float maxHeight = getMaxHeight(userHeights, &totalQuantity);
    float minHeight = getMinHeight(userHeights, &totalQuantity);
    float averageHeight = getAverageHeight(userHeights, &totalQuantity);
    // maxHeight, minHeight and averageHeight evaluates or calculates the things
    // that we need to let

    printf("Max height: %.2f\n", maxHeight);
    printf("Min height: %.2f\n", minHeight);
    printf("Average height: %.2f\n", averageHeight);
    // Prints the functions used before
    free(userHeights);
}

int main (){

    printFinalHeights(processHeights, initialNumberOfHeights, nextNumberOfHeights); 

    return 0;
}