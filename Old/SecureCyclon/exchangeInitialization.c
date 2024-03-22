#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"
#include "auxiliary.h"

//FONCTIONS POUR INITIALISER L'ÉCHANGE
//chooseSenderNode renvoi l'indice du noeud qui initie l'échange
int chooseSenderNode(int* tableTimestamp){
    return minList(tableTimestamp, NUM_NODES);
}

//chooseReceiverNode renvoi l'indice du noeud receveur
int chooseReceiverNode(int* subsetList,int numSubset){
    int ind = rand() % numSubset;
    int nodeIndex = subsetList[ind];
    printf("            Node 2 : %d \n",nodeIndex);
    return nodeIndex;
}

//numberOfNeighbors détermine le nombre de voisin d'un noeud 
int numberOfNeighbors(Node node) {
    int tmp = 0;
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        tmp+=(node.chaine[i].nodeInfo.PubKey!=-1);
    }
    printf("            Neighbors length %d \n",tmp);
    return tmp; 
}

//findOldNeighbors renvoie l'indice du noeud le plus vieux dans la liste non encore vue
int findOldNeighbors(Node *node,bool* subsetListBool){
    int idMin=-1;
    for (int i = 0; i < NUM_NEIGHBORS; i++){
        if ((node->chaine[i].nodeInfo.PubKey>-1)&&(!subsetListBool[i])){
            if (idMin==-1)
                idMin=i;
            else if (node->chaine[i].nodeInfo.timestamp<node->chaine[idMin].nodeInfo.timestamp)
                idMin=i;
        } 
    }
    subsetListBool[idMin]=true;
    return idMin;
}

// initSubsetNeigbors initialise une sous liste de voisin subsetList du noeud node ainsi que l'emplacement de ces voisins selectionnés dans subsetListBool. 
void initSubsetNeighbors(Node *node, int numSubset, bool* subsetListBool, int* subsetList) {
    
    for (int i = 0; i < numSubset; i++) {
        int idOld=findOldNeighbors(node,subsetListBool);
    }

    printf("            List of neighbors : ");
    printNodeNeighbors(*node);
    printf("            List of subset neighbors BOOL: ");
    printListBool(NUM_NEIGHBORS,subsetListBool);
    printf("            List of subset neighbors : ");
    printList(subsetList, numSubset);
}

// setupNode1 initialise les paramètres du noeud qui initie l'échange
void setupNode1(Node network[NUM_NODES],int* tableTimestamp,int* nodeIndex1,int* numNeighbors1, int* numSubset1, ChainOfOwnership* subsetList1,bool* subsetListBool1){
    srand(time(NULL));
    //Choix du noeud émetteur
    *nodeIndex1 = chooseSenderNode(tableTimestamp);

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
void setupNode2(Node network[NUM_NODES],int* nodeIndex2,int* numNeighbors2, int* numSubset2, int* subsetList2,bool* subsetListBool2,int* subsetList1, int numSubset1){ 
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
