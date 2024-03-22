#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "auxiliary.h"

//FONCTIONS POUR INITIALISER L'ÉCHANGE

//chooseSenderNode renvoi l'indice du noeud emetteur
int chooseSenderNode(int* timestamp){
    int id = idMinList(timestamp,NUM_NODES);
    return id;
}


//chooseReceiverNode renvoi l'indice du noeud receveur
int chooseReceiverNode(NodeData node,int numSubset){
    int id=-1;
    for (int i = 1; i < NUM_NEIGHBORS; i++){
        if (node.chain[i]->nodeInfo.PubKey > -1){
            if ((node.chain->nodeInfo.Time))
            {
                /* code */
            }
            
        }
        
    }
    
    int nodeIndex = subsetList[ind];
    printf("            Node 2 : %d \n",nodeIndex);
    return nodeIndex;
}

//numberOfNeighbors détermine le nombre de voisin d'un noeud 
int numberOfNeighbors(NodeData node) {
    int tmp = 0;
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        tmp+=(node.chain[i].nodeInfo.PubKey!=-1);
    }
    printf("            Neighbors length %d \n",tmp);
    return tmp; 
}

// initSubsetNeigbors initialise une sous liste de voisin subsetList du noeud node ainsi que l'emplacement de ces voisins selectionnés dans subsetListBool. 
void initSubsetNeighbors(NodeData *node, int numSubset, bool* subsetListBool, ChainOfOwnership* subsetList) {
    bool used[NUM_NEIGHBORS]; // Tableau pour garder une trace des noeuds déjà vus
    
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        // Initialisation de tous les éléments à false 
        used[i] = (node->chain[i].nodeInfo.PubKey==-1); //(si une place i est libre, used[i]=true pour ne pas envoyer une information vide)
    }
    
    for (int i = 0; i < numSubset; i++) {
        int rand_node;
        do {
            rand_node = rand() % NUM_NEIGHBORS;
        } while (used[rand_node]); // Tant que le noeud est déjà utilisé, en générer un nouveau
        used[rand_node] = true; // Marquer le noeud comme utilisé
        subsetListBool[rand_node]=true;
        subsetList[i]=node->chain[i];
    }

    //printf("            List of neighbors : ");
    //printList(node->neighbors, NUM_NEIGHBORS);
    printf("            List of subset neighbors BOOL: ");
    printListBool(NUM_NEIGHBORS,subsetListBool);
    printf("            List of subset neighbors : ");
    //printList(subsetList, numSubset);
}

// setupNode1 initialise les paramètres du noeud qui initie l'échange
void setupNode1(NodeData network[NUM_NODES],int* nodeIndex1,int* timestamp,int* numNeighbors1, int* numSubset1, ChainOfOwnership* subsetList1,bool* subsetListBool1){
    srand(time(NULL));
    //Choix du noeud émetteur
    *nodeIndex1=chooseSenderNode(timestamp);
    printf("            Node 1 : %d \n",*nodeIndex1);

    // Nombre de voisins du noeuds :
    *numNeighbors1 = numberOfNeighbors(network[*nodeIndex1]);
        
    // Nombre de sous noeuds sellectionnés :
    *numSubset1 = rand() % *numNeighbors1 + 1;
    printf("            Number of subset of neighbors %d \n",*numSubset1);

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[*nodeIndex1], *numSubset1 ,subsetListBool1,subsetList1);
    printf("\n");
}

// setupNode2 initialise les paramètres du noeud qui reçoit l'échange
void setupNode2(NodeData network[NUM_NODES],int* nodeIndex2,int* numNeighbors2, int* numSubset2, ChainOfOwnership* subsetList2,bool* subsetListBool2,ChainOfOwnership* subsetList1, int numSubset1){ 
    // Choix du noeuds receveur :
    *nodeIndex2=chooseReceiverNode(subsetList1,numSubset1);

    // Nombre de voisins du noeuds :
    *numNeighbors2 = numberOfNeighbors(network[*nodeIndex2]);

    // Nombre de sous noeuds sellectionnés :
    *numSubset2 =min(*numNeighbors2,numSubset1);
    printf("            Number of subset of neighbors %d \n",*numSubset2);

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[*nodeIndex2], *numSubset2,subsetListBool2,subsetList2);

    printf("\n");
}
