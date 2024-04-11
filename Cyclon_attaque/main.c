#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "exchange.h"
#include "exchangeInitialization.h"
#include "networkInitialization.h"
#include "outcome.h"

// -1 dans le tableau neighbors signifie que le noeud a pas d'information dans sa vue.

int main() {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    Node *network=malloc(NUM_NODES*sizeof(Node));

    int *timestamp=malloc(NUM_NODES*sizeof(int));
    memset(timestamp,-1,NUM_NODES*sizeof(int));

    char filename[200];
    initFilename(filename);

    // Ouverture du fichier pour l'écriture
    FILE *file = fopen(filename, "w"); 

    // Initialisation du réseau
    networkInitialisation(network,timestamp);
    //printNetwork(network);

    free(timestamp);
    
    //printf("Traitement : \n");
    for (int c = 0; c < NUM_CYCLE; c++){
        for (int nodeIndex1 = 0; nodeIndex1 < NUM_NODES; nodeIndex1++){

            // Noeud 1 :
            // Initialisation des paramètres
            int numNeighbors1; 
            bool* subsetListBool1=(bool*)malloc(NUM_NEIGHBORS * sizeof(bool));
            memset(subsetListBool1,false,NUM_NEIGHBORS*sizeof(bool));
            Descriptor* subsetList1=malloc(NUM_SUBSET * sizeof(Descriptor));

            for (int i = 0; i < NUM_SUBSET; i++){
                subsetList1[i].id=-1;
                subsetList1[i].time=-1;
            }
            
            //memset(subsetList1,-1,NUM_SUBSET*sizeof(int));
            setupNode1(network,nodeIndex1, subsetList1,subsetListBool1);
            //printf("\nListe de descripteur n°1 : \n");
            //printListDescriptor(subsetList1, NUM_SUBSET);


            //Noeud 2:
            // Initialisation des paramètres
            int nodeIndex2; int numNeighbors2;
            bool* subsetListBool2=(bool*)malloc(NUM_NEIGHBORS * sizeof(bool));
            memset(subsetListBool2,false,NUM_NEIGHBORS*sizeof(bool));
            Descriptor* subsetList2=malloc(NUM_SUBSET * sizeof(Descriptor));
            for (int i = 0; i < NUM_SUBSET; i++){
                subsetList2[i].id=-1;
                subsetList2[i].time=-1;
            }
            //memset(subsetList2,-1,NUM_SUBSET*sizeof(int));
            setupNode2(network,&nodeIndex2, subsetList2,subsetListBool2,subsetList1);

            //printf("\nListe de descripteur n°2 : \n");
            //printListDescriptor(subsetList2, NUM_SUBSET);

            // Échange des vues:
            viewExchange(network,subsetList1, subsetList2, subsetListBool1, subsetListBool2,nodeIndex1, nodeIndex2, c);
            
            
            //Libération de la mémoire 
            free(subsetList1);
            free(subsetList2);
            free(subsetListBool1);
            free(subsetListBool2);
        
        }
        // On note les résultats dans un fichier
        float tmp= percentageMaliciousNodes(network);
        appendIntToFile(file,tmp);
    }

    printf("\n");
    //printNetwork(network);

    free(network);

     
    return 0;
}
