#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "parameters.h"

// percentageMaliciousNodes  renvoie le pourcentage des noeuds malicieux (0 à 10) dans la vue
float percentageMaliciousNodes(Node network[NUM_NODES]){
    float percentage=0;
    int numNodesKnown=0;
    for (int i = NUM_MALICIOUS; i < NUM_NODES; i++){
        for (int j = 0; j < NUM_NEIGHBORS; j++){
            if ((network[i].neighbors[j].id<NUM_MALICIOUS)&&(network[i].neighbors[j].id>-1)){
                percentage+=1;
            }
            if (network[i].neighbors[j].id>-1){
                numNodesKnown++;
            }
            
        }
    }
    percentage =percentage/numNodesKnown*100;
    return percentage;
}

// appendIntToFile écrit un entier à la fin d'un fichier texte 
void appendIntToFile(FILE *file, float tmp) {
    if (file != NULL) {
        fprintf(file, "%f\n", tmp); // Écriture de l'entier à la fin du fichier
    } 
    else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}