#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "parameters.h"

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

// isAInListDescriptor renvoie 
//      -1 si l'entier a n'est pas dans la liste list des descripteurs, 
//      l'indice de l'entier a sinon
int isAInListDescriptor(Descriptor* list, int len, int a){
    for (int i = 0; i < len; i++){
        if (list[i].id==a)
            return i;       
    }
    return -1;
}

// min renvoie l'entier minimum entre a et b
int min(int a, int b) {
    return (a < b) ? a : b;
}

// initFilename initialise le nom du fichier qui enregistrera les résultats
void initFilename(char filename[200]){
    char entier[20];
    memset(filename,'\0',200*sizeof(char));
    memset(entier,'\0',20*sizeof(char));
    strcat(filename, "result");
    snprintf(entier,sizeof(entier),"%d",NUM_NODES);
    strcat(filename, "_");
    strcat(filename, entier);
    strcat(filename, "_");
    memset(entier,'\0',20*sizeof(char));
    snprintf(entier,sizeof(entier),"%d",NUM_SUBSET);
    strcat(filename, entier);
    strcat(filename, ".txt");
}

