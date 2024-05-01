#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "auxiliary.h"
#include "exchangeInitialization.h"

//FONCTIONS POUR L'ÉCHANGE
// knownNodes determine si le noeuds A connait déjà les noeuds que B lui envoie
void knownNodes(Node *nodeA,Descriptor* subsetListB,bool* subsetListBoolA,int* tmp){
    int i=0;
    int flag=subsetListB[i].id;

    
    while ((flag>-1)&&(i<NUM_SUBSET)){
        int index=isAInListDescriptor(nodeA->neighbors,NUM_NEIGHBORS,subsetListB[i].id);

        if (index!=-1)// Si c'est le cas
            subsetListBoolA[index]=false; // il n'est plus à modifier
        else{ //sinon 
            subsetListB[*tmp].id=subsetListB[i].id; // on le laisse dans la liste des noeuds à insérer
            subsetListB[*tmp].time=subsetListB[i].time;
            (*tmp)++; 
        }  
        i++;
        flag=subsetListB[i].id;
    }
}

// emptyCase remplie les cases vides du noeuds A avec les noeuds que B lui envoie
void emptyCase(Node *nodeA,Descriptor* subsetListB,int* tmp,bool flagMalicious){
    for (int i = 0; i < NUM_NEIGHBORS; i++){
        if (*tmp==0)
            return;
        if (nodeA->neighbors[i].id==-1){
            if (((subsetListB[*tmp-1].id>=NUM_MALICIOUS)&&flagMalicious)||!flagMalicious){
                nodeA->neighbors[i].id=subsetListB[*tmp-1].id;
                nodeA->neighbors[i].time=subsetListB[*tmp-1].time;
            }
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
        if (subsetListBoolA[i]==true){
            if (((subsetListB[*tmp-1].id>=NUM_MALICIOUS)&&flagMalicious)||!flagMalicious){
                nodeA->neighbors[i].id=subsetListB[*tmp-1].id;
                nodeA->neighbors[i].time=subsetListB[*tmp-1].time;
            }
            (*tmp)--;
        }  
    }
}

// exchangeNeighbors met à jour la liste des voisins du noeud A en fonction de la liste que B lui a envoyé
void exchangeNeighbors(Node *nodeA, Node *nodeB, bool* subsetListBoolA, Descriptor* subsetListB,bool flagMalicious){
    //int tmp=0;

    // Verification de noeuds déjà présents
    //knownNodes(nodeA,subsetListB,subsetListBoolA,&tmp);

    // si tous les noeuds était déjà présents, on arrète
    //if (tmp==0)
        //return;

    

    int tmp = NUM_SUBSET;

    // Compléter les cases vides 
    emptyCase(nodeA,subsetListB,&tmp,flagMalicious);

    // si tous les noeuds on été placé, on arrète
    if (tmp==0)
        return;
    
    // Échange des noeuds restants
    exchangeRemainingNode(nodeA,subsetListB,subsetListBoolA,&tmp,flagMalicious);
}

// subsetListSend determine la liste à envoyer au noeud receiver
void subsetListSend(Descriptor * list, int sender, int receiver, bool flagSender,bool flagMalicious, int c){
    // Noeud malveillant
    if ((sender<NUM_MALICIOUS)&&flagMalicious) {
        for (int i = 0; i < NUM_SUBSET; i++){
            list[i].id=i;
            list[i].time=c;
        }
        return;  
    }
    

    if (flagSender){
        for (int i = 0; i < NUM_SUBSET; i++){
            if (list[i].id==receiver){// si l'indice du receveur est dans la liste
                list[i].id=sender; // on le remplace par le sender
                list[i].time=c;
            } 
        }
    }

}

void viewInitialization(Descriptor* subsetList1, Descriptor* subsetList2,int nodeIndex1, int nodeIndex2, int c ){
    subsetListSend(subsetList1,nodeIndex1,nodeIndex2, true,(c > 50),c);
    subsetListSend(subsetList2,nodeIndex2,nodeIndex1, false,(c > 50),c);
}

void viewExchange(Node network[NUM_NODES], Descriptor* subsetList1, Descriptor* subsetList2, bool* subsetListBool1, bool* subsetListBool2, int nodeIndex1, int nodeIndex2, int c){
    viewInitialization(subsetList1, subsetList2, nodeIndex1, nodeIndex2,c );

    bool flagMalicious=true;
    if (nodeIndex1>NUM_MALICIOUS)
        flagMalicious=false;
    

    exchangeNeighbors(&network[nodeIndex1],&network[nodeIndex2],subsetListBool1,subsetList2,flagMalicious);

    flagMalicious=true;
    if (nodeIndex2>NUM_MALICIOUS)
        flagMalicious=false;
    
    exchangeNeighbors(&network[nodeIndex2],&network[nodeIndex1],subsetListBool2,subsetList1,flagMalicious);
    
   

    
    /*
    printf("\nListe de voisin du noeud 1 : \n");
    printListDescriptor(network[nodeIndex1].neighbors, NUM_NEIGHBORS);
    printf("\nListe de voisin du noeud 2 : \n");
    printListDescriptor(network[nodeIndex2].neighbors, NUM_NEIGHBORS);
    */
}
