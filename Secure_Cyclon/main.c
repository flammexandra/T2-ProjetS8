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

    printNetwork(network);

    free(timestamp);
    
    //printf("Traitement : \n");
    for (int c = 0; c < NUM_CYCLE; c++){
        for (int nodeIndex1 = 0; nodeIndex1 < NUM_NODES; nodeIndex1++){
            int idnodeIndex2=0;
            int nodeIndex2=chooseReceiverNode(network[nodeIndex1].neighbors,&idnodeIndex2);
            //printf("Node2 : %d\n",nodeIndex2);

            // Noeud 1 :
            // Initialisation des paramètres
            int numNeighbors1; 
            bool* subsetListBool1=(bool*)malloc(NUM_NEIGHBORS * sizeof(bool));
            memset(subsetListBool1,false,NUM_NEIGHBORS*sizeof(bool));
            Descriptor* subsetList1=malloc((NUM_SUBSET+1) * sizeof(Descriptor));

            for (int i = 0; i < NUM_SUBSET+1; i++){
                subsetList1[i].id=-1;
                subsetList1[i].time=-1;
                subsetList1[i].swappable=true;
                subsetList1[i].ownership=NULL;
            }
            
            //memset(subsetList1,-1,NUM_SUBSET*sizeof(int));
            
            setupNode1(network,nodeIndex1,nodeIndex2, subsetList1,subsetListBool1,idnodeIndex2,c);

            //printf("Liste des booléens:\n");
            //printListBool(NUM_NEIGHBORS,subsetListBool1);
            //printf("\n");

            //printf("Liste des voisins détaillée:\n");
            //printListDescriptor(subsetList1,NUM_SUBSET+1);
            //printf("\n");

            


            //Noeud 2:
            // Initialisation des paramètres
            int numNeighbors2;
            bool* subsetListBool2=(bool*)malloc(NUM_NEIGHBORS * sizeof(bool));
            memset(subsetListBool2,false,NUM_NEIGHBORS*sizeof(bool));
            Descriptor* subsetList2=malloc(NUM_SUBSET * sizeof(Descriptor));
            for (int i = 0; i < NUM_SUBSET; i++){
                subsetList2[i].id=-1;
                subsetList2[i].time=-1;
                subsetList2[i].swappable=true;
                subsetList2[i].ownership=NULL;
            }
            //memset(subsetList2,-1,NUM_SUBSET*sizeof(int));


            setupNode2(network,nodeIndex1,nodeIndex2, subsetList2,subsetListBool2,subsetList1);

            //printf("Liste des booléens:\n");
            //printListBool(NUM_NEIGHBORS,subsetListBool2);
            //printf("\n");

            //printf("Liste des voisins détaillée:\n");
            //printListDescriptor(subsetList2,NUM_SUBSET);
            //printf("\n");

            



            // Échange des vues:
            viewExchange(network,subsetList1, subsetList2, subsetListBool1, subsetListBool2,nodeIndex1, nodeIndex2, c);


            //printf("Liste des voisins détaillée noeuds 1:\n");
            //printListDescriptor(network[nodeIndex1].neighbors,NUM_NEIGHBORS);
            //printf("\n");


            //printf("Liste des voisins détaillée noeuds 2:\n");
            //printListDescriptor(network[nodeIndex2].neighbors,NUM_NEIGHBORS);
            //printf("\n");

            //printNetwork(network);
            
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

    printNetwork(network);

    free(network);

     
    return 0;
}
