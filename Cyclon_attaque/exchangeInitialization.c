#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "auxiliary.h"

//FONCTIONS POUR INITIALISER L'ÉCHANGE

//chooseReceiverNode renvoi l'indice du noeud receveur
int chooseReceiverNode(Descriptor* neighborsList,int* idRec){
    for (int i = 1; i < NUM_NEIGHBORS; i++){
        if (neighborsList[i].id==-1)
            continue;
        if (neighborsList[*idRec].id==-1){
            *idRec=i;
            continue;
        }
        if (neighborsList[i].time<neighborsList[*idRec].time){
            *idRec=i;
        }
    }
    int nodeIndex = neighborsList[*idRec].id;
    return nodeIndex;
}

//numberOfNeighbors détermine le nombre de voisin d'un noeud 
int numberOfNeighbors(Node node) {
    int tmp = 0;
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        tmp+=(node.neighbors[i].id!=-1);
    }
    return tmp; 
}

// initSubsetNeigbors initialise une sous liste de voisin subsetList du noeud node ainsi que l'emplacement de ces voisins selectionnés dans subsetListBool. 
void initSubsetNeighbors(Node *node, bool* subsetListBool, Descriptor* subsetList, int numSubset,int idnodeIndex2) {
    bool used[NUM_NEIGHBORS]; // Tableau pour garder une trace des noeuds déjà vus
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        // Initialisation de tous les éléments à false 
        used[i] = (node->neighbors[i].id==-1); //(si une place i est libre, used[i]=true pour ne pas envoyer une information vide)
    }

    int tmp=0;

    if (idnodeIndex2!=-1){
        used[idnodeIndex2] = true; // Marquer le noeud comme utilisé
        subsetListBool[idnodeIndex2]=true;
        subsetList[0].id=node->neighbors[idnodeIndex2].id;
        subsetList[0].time=node->neighbors[idnodeIndex2].time;
        tmp=1;
    }
    
    
    for (int i = tmp; i < numSubset; i++) {
        int rand_node;
        do {
            rand_node = rand() % NUM_NEIGHBORS;
        } while (used[rand_node]); // Tant que le noeud est déjà utilisé, en générer un nouveau
        used[rand_node] = true; // Marquer le noeud comme utilisé
        subsetListBool[rand_node]=true;
        subsetList[i].id=node->neighbors[rand_node].id;
        subsetList[i].time=node->neighbors[rand_node].time;
        //node->neighbors[rand_node].id=-1;
        //node->neighbors[rand_node].time=-1;
    }
}

// setupNode1 initialise les paramètres du noeud qui initie l'échange
void setupNode1(Node network[NUM_NODES],int nodeIndex1, Descriptor* subsetList1,bool* subsetListBool1,int idnodeIndex2){

    int numNeighbors = numberOfNeighbors(network[nodeIndex1]);

    int numSubset = min(numNeighbors,NUM_SUBSET);

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[nodeIndex1], subsetListBool1, subsetList1, numSubset, idnodeIndex2);

}

// setupNode2 initialise les paramètres du noeud qui reçoit l'échange
void setupNode2(Node network[NUM_NODES],int nodeIndex2, Descriptor* subsetList2,bool* subsetListBool2,Descriptor* subsetList1){ 

    int numNeighbors = numberOfNeighbors(network[nodeIndex2]);

    int numSubset = min(numNeighbors,NUM_SUBSET);

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[nodeIndex2],subsetListBool2,subsetList2,numSubset,-1);

}
