#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "exchange.h"
#include "exchangeInitialization.h"
#include "networkInitialization.h"

// -1 dans le tableau neighbors signifie que le noeud a pas d'information dans sa vue.

int main() {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    Node network[NUM_NODES];

    // Initialisation du réseau
    printf("Initialisation : \n");
    networkInitialisation(network);
    
    printf("Traitement : \n");
    for (int c = 0; c < NUM_CYCLE; c++){
        printf("    Cycle number %d \n",c);
        printf("\n        Détermination de l'échange : \n");

        // Noeud 1 :
        // Initialisation des paramètres
        int nodeIndex1; int numNeighbors1; int numSubset1;
        bool* subsetListBool1=(bool*)malloc(NUM_NEIGHBORS * sizeof(bool));
        memset(subsetListBool1,false,NUM_NEIGHBORS*sizeof(bool));
        int* subsetList1=(int*)malloc(numSubset1 * sizeof(int));
        memset(subsetList1,0,numSubset1*sizeof(int));
        setupNode1(network,&nodeIndex1,&numNeighbors1, &numSubset1, subsetList1,subsetListBool1);

        //Noeud 2:
        // Initialisation des paramètres
        int nodeIndex2; int numNeighbors2;int numSubset2 ;
        bool* subsetListBool2=(bool*)malloc(NUM_NEIGHBORS * sizeof(bool));
        memset(subsetListBool2,false,NUM_NEIGHBORS*sizeof(bool));
        int* subsetList2=(int*)malloc(numSubset2 * sizeof(int));
        memset(subsetList2,0,numSubset2*sizeof(int));
        setupNode2(network,&nodeIndex2,&numNeighbors2, &numSubset2, subsetList2,subsetListBool2,subsetList1,numSubset1);

        // Échange des vues:
        viewExchange(network, subsetList1, subsetList2, subsetListBool1, subsetListBool2, numSubset1, numSubset2, nodeIndex1, nodeIndex2);

    }
    
    return 0;
}
