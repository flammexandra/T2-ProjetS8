#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "auxiliary.h"
#include "exchangeInitialization.h"

//FONCTIONS POUR L'ÉCHANGE

void freeOwnership(struct Ownership* head) {
    struct Ownership* current = head;
    struct Ownership* next;

    // Parcours de la liste et libération de la mémoire de chaque nœud
    while (current != NULL) {
        next = current->nextOwnership;
        free(current);
        current = next;
    }
}


// emptyCase remplie les cases vides du noeuds A avec les noeuds que B lui envoie
void emptyCase(Node *nodeA,Descriptor* subsetListB,int* tmp,bool flagMalicious){
    for (int i = 0; i < NUM_NEIGHBORS; i++){
        if (*tmp==0)
            return;
        if (nodeA->neighbors[i].id==-1){

                //struct Ownership* head = nodeA->neighbors[i].ownership;
                nodeA->neighbors[i].id=subsetListB[*tmp-1].id;
                nodeA->neighbors[i].time=subsetListB[*tmp-1].time;
                nodeA->neighbors[i].swappable=subsetListB[*tmp-1].swappable;

                nodeA->neighbors[i].ownership=subsetListB[*tmp-1].ownership;
                //freeOwnership(head);

            (*tmp)--;
        }
    }
}

// exchangeRemainingNode remplie les cases modifiables du noeuds A avec les noeuds que B lui envoie
void exchangeRemainingNode(Node *nodeA,Descriptor* subsetListB,bool* subsetListBoolA,int* tmp,bool flagMalicious){
    for (int i = 0; i < NUM_NEIGHBORS; i++){
        if (*tmp==0){
            break;
        }
        if (subsetListBoolA[i]){

                //struct Ownership* head = nodeA->neighbors[i].ownership;
                nodeA->neighbors[i].id=subsetListB[*tmp-1].id;
                nodeA->neighbors[i].time=subsetListB[*tmp-1].time;
                nodeA->neighbors[i].swappable=subsetListB[*tmp-1].swappable;
                nodeA->neighbors[i].ownership=subsetListB[*tmp-1].ownership;
                //freeOwnership(head);

            (*tmp)--;
        }  
    }
}

// exchangeNeighbors met à jour la liste des voisins du noeud A en fonction de la liste que B lui a envoyé
void exchangeNeighbors(Node *nodeA, Node *nodeB, bool* subsetListBoolA, Descriptor* subsetListB,bool flagMalicious){

    int tmp = NUM_SUBSET;

    // Compléter les cases vides 
    emptyCase(nodeA,subsetListB,&tmp,flagMalicious);

    // si tous les noeuds on été placé, on arrète
    if (tmp==0)
        return;
    
    // Échange des noeuds restants
    exchangeRemainingNode(nodeA,subsetListB,subsetListBoolA,&tmp,flagMalicious);
}

// subsetListMalicious crée un liste malicieuse
void subsetListMalicious(Descriptor * list, int c, int rec){
    srand(time(NULL));

    //Création de descripteur malicieux
    for (int i = 0; i < NUM_SUBSET; i++){
        int send = rand() % NUM_MALICIOUS;
        list[i].id=send;
        list[i].time=c;
        list[i].swappable=true;
        list[i].ownership=malloc(sizeof(struct Ownership));
        list[i].ownership->PubKey_rec=rec;
        list[i].ownership->Sign_trans=send;
        list[i].ownership->nextOwnership=NULL;
    }
    
    
}


void viewExchange(Node network[NUM_NODES], Descriptor* subsetList1, Descriptor* subsetList2, bool* subsetListBool1, bool* subsetListBool2, int nodeIndex1, int nodeIndex2, int c){
    //CHECKER LE DERNIER NODE !
        //////// À faire !

    bool flagMalicious = false;
        
    if (nodeIndex1<NUM_MALICIOUS){
        subsetListMalicious(subsetList1, c, nodeIndex2);
        flagMalicious=true;
    }
    

    exchangeNeighbors(&network[nodeIndex2],&network[nodeIndex1],subsetListBool2,subsetList1,flagMalicious);



    flagMalicious = false;

    if (nodeIndex2<NUM_MALICIOUS){
        subsetListMalicious(subsetList1, c, nodeIndex1);
        flagMalicious=true;
    }

    exchangeNeighbors(&network[nodeIndex1],&network[nodeIndex2],subsetListBool1,subsetList2,flagMalicious);
    
    /*
    printf("\nListe de voisin du noeud 1 : \n");
    printListDescriptor(network[nodeIndex1].neighbors, NUM_NEIGHBORS);
    printf("\nListe de voisin du noeud 2 : \n");
    printListDescriptor(network[nodeIndex2].neighbors, NUM_NEIGHBORS);
    */
}
