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
        //tmp+=((node.neighbors[i].id!=-1)&&(node.neighbors[i].swappable));
        tmp+=(node.neighbors[i].id!=-1);
    }
    return tmp; 
}

// initSubsetNeigbors initialise une sous liste de voisin subsetList du noeud node ainsi que l'emplacement de ces voisins selectionnés dans subsetListBool. 
void initSubsetNeighbors(Node *node, bool* subsetListBool, Descriptor* subsetList, int numSubset,int idnodeIndex2,int rec, int send,int c) {
    bool used[NUM_NEIGHBORS]; // Tableau pour garder une trace des noeuds déjà vus

    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        // Initialisation de tous les éléments à false 
        used[i] = ((node->neighbors[i].id==-1)||!(node->neighbors[i].swappable)); //(si une place i est libre, used[i]=true pour ne pas envoyer une information vide)
    }

    int tmp=0;

    // On cherche le noeud receveur si il s'agit le l'envoi
    if (idnodeIndex2!=-1){
        used[idnodeIndex2] = true; // Marquer le noeud comme utilisé
        subsetListBool[idnodeIndex2]=true;
        subsetList[NUM_SUBSET].id=node->neighbors[idnodeIndex2].id;
        subsetList[NUM_SUBSET].time=node->neighbors[idnodeIndex2].time;
        subsetList[NUM_SUBSET].swappable=node->neighbors[idnodeIndex2].swappable;
        subsetList[NUM_SUBSET].ownership=node->neighbors[idnodeIndex2].ownership;
        //node->neighbors[idnodeIndex2].swappable=false;


        subsetList[0].id=send; // on le remplace par le sender
        subsetList[0].time=c;
        subsetList[0].swappable=true;
        subsetList[0].ownership=malloc(sizeof(struct Ownership));
        subsetList[0].ownership->PubKey_rec=rec;
        subsetList[0].ownership->Sign_trans=send;
        subsetList[0].ownership->nextOwnership=NULL;

        tmp=1;
    }


    // Envoie des autres descripteurs 
    for (int i = tmp; i < numSubset; i++) {
        int rand_node;
        do {
            rand_node = rand() % NUM_NEIGHBORS;
        } while (used[rand_node]); // Tant que le noeud est déjà utilisé, en générer un nouveau
        used[rand_node] = true; // Marquer le noeud comme utilisé
        subsetListBool[rand_node]=true;
        subsetList[i].id=node->neighbors[rand_node].id;
        subsetList[i].time=node->neighbors[rand_node].time;
        subsetList[i].swappable=node->neighbors[rand_node].swappable;
        subsetList[i].ownership=node->neighbors[rand_node].ownership;

        
        // Ajout de sa propriété :
        struct Ownership * lastOwnership=node->neighbors[rand_node].ownership;
        while (lastOwnership->nextOwnership!=NULL){
            lastOwnership=lastOwnership->nextOwnership;
        }
        struct Ownership * nodeOwnership= malloc(sizeof(struct Ownership));
        nodeOwnership->Sign_trans=lastOwnership->PubKey_rec;
        nodeOwnership->PubKey_rec=rec;
        nodeOwnership->nextOwnership=NULL;
        lastOwnership->nextOwnership=nodeOwnership;
        //node->neighbors[rand_node].swappable=false;
    }

}

// setupNode1 initialise les paramètres du noeud qui initie l'échange
void setupNode1(Node network[NUM_NODES],int nodeIndex1, int nodeIndex2, Descriptor* subsetList1,bool* subsetListBool1,int idnodeIndex2,int c){

    int numNeighbors = numberOfNeighbors(network[nodeIndex1]);

    int numSubset = min(numNeighbors,NUM_SUBSET);

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[nodeIndex1], subsetListBool1, subsetList1, numSubset,idnodeIndex2,nodeIndex2,nodeIndex1, c);

}

// setupNode2 initialise les paramètres du noeud qui reçoit l'échange
void setupNode2(Node network[NUM_NODES],int nodeIndex1, int nodeIndex2, Descriptor* subsetList2,bool* subsetListBool2,Descriptor* subsetList1){ 


    int numNeighbors = numberOfNeighbors(network[nodeIndex2]);

    int numSubset = min(numNeighbors,NUM_SUBSET);

    

    // Détermination de la sous liste à envoyer :
    initSubsetNeighbors(&network[nodeIndex2],subsetListBool2,subsetList2,numSubset,-1,nodeIndex1,-1,-1);

}
