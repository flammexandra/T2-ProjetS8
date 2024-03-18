#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "auxiliary.h"

//FONCTIONS POUR INITIALISER L'ÉCHANGE
//chooseSenderNode renvoi l'indice du noeud qui initie l'échange
int chooseSenderNode(){
    srand(time(NULL));
    int tmp=rand() % NUM_NODES;
    return tmp;
}

//chooseReceiverNode renvoi l'indice du noeud receveur
int chooseReceiverNode(int* subsetList,int numSubset){
    int ind = rand() % numSubset;
    int nodeIndex = subsetList[ind];
    return nodeIndex;
}

//numberOfNeighbors détermine le nombre de voisin d'un noeud 
int numberOfNeighbors(Node node) {
    int tmp = 0;
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        tmp+=(node.neighbors[i]!=-1);
    }
    return tmp; 
}

// initSubsetNeigbors initialise une sous liste de voisin subsetList du noeud node ainsi que l'emplacement de ces voisins selectionnés dans subsetListBool. 
void initSubsetNeighbors(Node *node, int numSubset, bool* subsetListBool, int* subsetList) {
    bool used[NUM_NEIGHBORS]; // Tableau pour garder une trace des noeuds déjà vus
    
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        // Initialisation de tous les éléments à false 
        used[i] = (node->neighbors[i]==-1); //(si une place i est libre, used[i]=true pour ne pas envoyer une information vide)
    }
    
    for (int i = 0; i < numSubset; i++) {
        int rand_node;
        do {
            rand_node = rand() % NUM_NEIGHBORS;
        } while (used[rand_node]); // Tant que le noeud est déjà utilisé, en générer un nouveau
        used[rand_node] = true; // Marquer le noeud comme utilisé
        subsetListBool[rand_node]=true;
        subsetList[i]=node->neighbors[rand_node];
    }
}

// setupNode1 initialise les paramètres du noeud qui initie l'échange
void setupNode1(Node network[NUM_NODES],int* nodeIndex1,int* numNeighbors1, int* numSubset1, int* subsetList1,bool* subsetListBool1){
    srand(time(NULL));
    // Nombre de voisins du noeuds :
    *numNeighbors1 = numberOfNeighbors(network[*nodeIndex1]);
        
    // Nombre de sous noeuds sellectionnés :
    *numSubset1 = rand() % *numNeighbors1 + 1;

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[*nodeIndex1], *numSubset1 ,subsetListBool1,subsetList1);

}

// setupNode2 initialise les paramètres du noeud qui reçoit l'échange
void setupNode2(Node network[NUM_NODES],int* nodeIndex2,int* numNeighbors2, int* numSubset2, int* subsetList2,bool* subsetListBool2,int* subsetList1, int numSubset1){ 
    // Choix du noeuds receveur :
    *nodeIndex2=chooseReceiverNode(subsetList1,numSubset1);

    // Nombre de voisins du noeuds :
    *numNeighbors2 = numberOfNeighbors(network[*nodeIndex2]);

    // Nombre de sous noeuds sellectionnés :
    *numSubset2 =min(*numNeighbors2,numSubset1);

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[*nodeIndex2], *numSubset2,subsetListBool2,subsetList2);

}
