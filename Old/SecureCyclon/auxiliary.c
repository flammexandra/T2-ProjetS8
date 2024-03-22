#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//FONCTIONS AUXILIAIRES
// isAInList renvoie 
//      -1 si l'entier a n'est pas dans la liste list, 
//      l'indice de l'entier a sinon
int isAInList(int* list, int len, int a){
    for (int i = 0; i < len; i++){
        if (list[i]==a)
            return i;       
    }
    return -1;
}

// min renvoie l'entier minimum entre a et b
int min(int a, int b) {
    return (a < b) ? a : b;
}

// minList renvoie lindice du minimum d'une liste
int minList(int* list, int len) {
    int minId=0;
    for (int i = 1; i < len; i++){
        if (list[minId]>list[i]){
            minId=i;
        }
    }
    return minId;
}

