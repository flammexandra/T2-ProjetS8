#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "auxiliary.h"

//FONCTIONS POUR L'ÉCHANGE
// knownNodes determine si le noeuds A connait déjà les noeuds que B lui envoie
void knownNodes(Node *nodeA,int* subsetListB,bool* subsetListBoolA,int numSubsetB,int* tmp){
    for (int i = 0; i < numSubsetB; i++){
        int index=isAInList(nodeA->neighbors,NUM_NEIGHBORS,subsetListB[i]);
        if (index!=-1) // Si c'est le cas
            subsetListBoolA[index]=false; // il n'est plus à modifier
        else{ //sinon 
            subsetListB[*tmp]=subsetListB[i]; // on le laisse dans la liste des noeuds à insérer
            (*tmp)++; 
        }  
    }
}

// emptyCase remplie les cases vides du noeuds A avec les noeuds que B lui envoie
void emptyCase(Node *nodeA,int* subsetListB,int* tmp){
    for (int i = 0; i < NUM_NEIGHBORS; i++){
        if (nodeA->neighbors[i]==-1){
            nodeA->neighbors[i]=subsetListB[*tmp-1]; // On remplie
            (*tmp)--;
        }
        if (*tmp==0)
            return;
    }
}

// exchangeRemainingNode remplie les cases modifiables du noeuds A avec les noeuds que B lui envoie
void exchangeRemainingNode(Node *nodeA,int* subsetListB,bool* subsetListBoolA,int* tmp){
    for (int i = 0; i < NUM_NEIGHBORS; i++){
        if (subsetListBoolA[i]==true){
            nodeA->neighbors[i]=subsetListB[*tmp-1];
            (*tmp)--;
        }
        if (*tmp==0)
            return;  
    }
}

// exchangeNeighbors met à jour la liste des voisins du noeud A en fonction de la liste que B lui a envoyé
void exchangeNeighbors(Node *nodeA, Node *nodeB, bool* subsetListBoolA, int* subsetListB, int numSubsetA,int numSubsetB){
    int tmp=0;

    // Verification de noeuds déjà présents
    knownNodes(nodeA,subsetListB,subsetListBoolA,numSubsetB,&tmp);

    // si tous les noeuds était déjà présents, on arrète
    if (tmp==0)
        return;

    // Compléter les cases vides 
    emptyCase(nodeA,subsetListB,&tmp);

    // si tous les noeuds on été placé, on arrète
    if (tmp==0)
        return;
    
    // Échange des noeuds restants
    exchangeRemainingNode(nodeA,subsetListB,subsetListBoolA,&tmp);
}

// subsetListSend determine la liste à envoyer au noeud receiver
void subsetListSend(int * list, int len, int sender, int receiver){
    for (int i = 0; i < len; i++){
        if (list[i]==receiver) // si l'indice du receveur est dans la liste
            list[i]=sender; // on le remplace par le sender
    }
}

void viewInitialization(int* subsetList1, int* subsetList2, int numSubset1, int numSubset2, int nodeIndex1, int nodeIndex2 ){
    subsetListSend(subsetList2,numSubset2,nodeIndex2,nodeIndex1);
    printf("            List of subset neighbors send to 1: ");
    printList(subsetList2,numSubset2);
    
    printf("            List of subset neighbors send to 2: ");
    printList(subsetList1,numSubset1);
    printf("\n");
}

void viewExchange(Node network[NUM_NODES],int* subsetList1, int* subsetList2, bool* subsetListBool1, bool* subsetListBool2, int numSubset1, int numSubset2, int nodeIndex1, int nodeIndex2){
    printf("        Échange des vues : \n");
    
    viewInitialization(subsetList1, subsetList2, numSubset1, numSubset2, nodeIndex1, nodeIndex2 );

    printf("            Node 1 : \n");
    exchangeNeighbors(&network[nodeIndex1],&network[nodeIndex2],subsetListBool1,subsetList2,numSubset1,numSubset2);
    printf("            List of neighbors : ");
    printList(network[nodeIndex1].neighbors, NUM_NEIGHBORS);
       
    printf("\n");
    printf("            Node 2 : \n");
    exchangeNeighbors(&network[nodeIndex2],&network[nodeIndex1],subsetListBool2,subsetList1,numSubset2,numSubset1);
    printf("            List of neighbors : ");
    printList(network[nodeIndex2].neighbors, NUM_NEIGHBORS);

}
