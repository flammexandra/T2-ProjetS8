#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define NUM_NODES 10
#define NUM_NEIGHBORS 5
#define NUM_CYCLE 1

typedef struct {
    int id;
    int neighbors[NUM_NEIGHBORS];
} Node;

// -1 dans le tableau neighbors signifie que le noeud a pas d'information dans sa vue.

// FONCTIONS D'AFFICHAGE
// Affichage du réseau
void printNetwork(Node network[NUM_NODES]){
    for (int i = 0; i < NUM_NODES; i++) {
        printf("    Node %d neighbors: ", network[i].id);
        for (int j = 0; j < NUM_NEIGHBORS; j++) {
            printf("%d ", network[i].neighbors[j]);
        }
        printf("\n");
    }
}

// Affichage d'une liste
void printList(int* list, int taille){
        for (int i = 0; i < taille; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");

}

// Affichage d'une liste de booléen
void printListBool( int taille, bool* listBool){
        for (int i = 0; i < taille; i++) {
            if (listBool[i])
                printf("true ");
            else
                printf("false ");
        }
        printf("\n");

}

// Affichage d'une liste à l'aide d'une liste de booléens
void printListWithBool(int* list, int taille, bool* listBool){
        for (int i = 0; i < taille; i++) {
            if (listBool[i])
                printf("%d ", list[i]);
        }
        printf("\n");

}


// FONCTIONS INITIALISATION DU RÉSEAU
// initializeNeighbors initialise les voisins d'un nœud avec des valeurs aléatoires.
void initializeNeighbors(Node *node, int index) {
    bool used[NUM_NODES]; // Tableau pour garder une trace des nombres déjà utilisés

    memset(used,false,NUM_NODES*sizeof(bool)); // Initialisation du tableau à faux
    used[index] = true; // Index du noeud à vrai (un noeud ne peux pas s'autoconnaitre)
    
    // Parcours du nombre de voisin possible
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        int rand_num = rand() % NUM_NODES; // noeuds aléatoire

        if (used[rand_num])
            node->neighbors[i] = -1; // Si déja connu, le noeud devient inconnu
        else
            node->neighbors[i] = rand_num; // Sinon il devient un nouveau voisin
        used[rand_num] = true; // Marquer le noeud comme utilisé
    }
}

// networkInitialisation initialise chaque noeuds de réseau
void networkInitialisation(Node network[NUM_NODES]){
    //Parcours du réseau
    for (int i = 0; i < NUM_NODES; i++) {
        network[i].id = i;
        initializeNeighbors(&network[i], i);
    }
    printNetwork(network);
    printf("\n");
}


//FONCTIONS POUR INITIALISER L'ÉCHANGE
//chooseSenderNode renvoi l'indice du noeud qui initie l'échange
int chooseSenderNode(){
    srand(time(NULL));
    int tmp=rand() % NUM_NODES;
    printf("            Node 1 : %d \n",tmp);
    return tmp;
}

//chooseReceiverNode renvoi l'indice du noeud receveur
int chooseReceiverNode(int* subsetList,int numSubset){
    int ind = rand() % numSubset;
    int nodeIndex = subsetList[ind];
    printf("            Node 2 : %d \n",nodeIndex);
    return nodeIndex;
}

//numberOfNeighbors détermine le nombre de voisin d'un noeud 
int numberOfNeighbors(Node *node) {
    int tmp = 0;
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        tmp+=(node->neighbors[i]!=-1);
    }
    printf("            Neighbors length %d \n",tmp);
    return tmp; 
}

// isNotInList renvoie 
//      -1 si l'entier a n'est pas dans la liste list, 
//      l'indice de l'entier a sinon
int isAInList(int* list, int len, int a){
    for (int i = 0; i < len; i++){
        if (list[i]==a)
            return i;       
    }
    return -1;
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

    printf("            List of neighbors : ");
    printList(node->neighbors, NUM_NEIGHBORS);
    printf("            List of subset neighbors BOOL: ");
    printListBool(NUM_NEIGHBORS,subsetListBool);
    printf("            List of subset neighbors : ");
    printList(subsetList, numSubset);
}

// subsetListSend determine la liste à envoyer au noeud receiver
void subsetListSend(int * list, int len, int sender, int receiver){
    for (int i = 0; i < len; i++){
        if (list[i]==receiver) // si l'indice du receveur est dans la liste
            list[i]=sender; // on le remplace par le sender
    }
}


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


//FONCTIONS AUXILIAIRES
int min(int a, int b) {
    return (a < b) ? a : b;
}


int main() {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    Node network[NUM_NODES];

    // Initialisation du réseau
    printf("Initialisation : \n");
    networkInitialisation(network);
    
    printf("Traitement : \n");
    for (int c = 0; c < NUM_CYCLE; c++){
        printf("    Cycle number %d \n",c);
        printf("\n        Détermination de l'échange : \n");

        // Choix du noeud initiateur:
        int nodeIndex1 = chooseSenderNode();
        // Nombre de voisins du noeuds :
        int numNeighbors1 = numberOfNeighbors(&network[nodeIndex1]);
        
        // Nombre de sous noeuds sellectionnés :
        int numSubset1 = rand() % numNeighbors1 + 1;
        printf("            Number of subset of neighbors %d \n",numSubset1);

        bool subsetListBool1[NUM_NEIGHBORS];
        memset(subsetListBool1,false,NUM_NEIGHBORS*sizeof(bool));
        int subsetList1[numSubset1];
        memset(subsetList1,0,numSubset1*sizeof(int));

        // Détermination de la sous liste à envoyer :
        initSubsetNeighbors(&network[nodeIndex1], numSubset1,subsetListBool1,subsetList1);
        
        printf("\n");
        // Choix du noeuds receveur :
        int nodeIndex2=chooseReceiverNode(subsetList1,numSubset1);

        // Nombre de voisins du noeuds :
        int numNeighbors2 = numberOfNeighbors(&network[nodeIndex2]);

        // Nombre de sous noeuds sellectionnés :
        int numSubset2 =min(numNeighbors2,numSubset1);
        printf("            Number of subset of neighbors %d \n",numSubset2);

        bool subsetListBool2[NUM_NEIGHBORS];
        memset(subsetListBool2,false,NUM_NEIGHBORS*sizeof(bool));
        int subsetList2[numSubset2];
        memset(subsetList2,0,numSubset2*sizeof(int));

        // Détermination de la sous liste à envoyer :
        initSubsetNeighbors(&network[nodeIndex2], numSubset2,subsetListBool2,subsetList2);


        // Échange des vues:
        printf("\n        Échange des vues : \n");

        subsetListSend(subsetList2,numSubset2,nodeIndex2,nodeIndex1);
        printf("            List of subset neighbors send to 1: ");
        printList(subsetList2,numSubset2);
        
        subsetListSend(subsetList1,numSubset1,nodeIndex1,nodeIndex2);
        printf("            List of subset neighbors send to 2: ");
        printList(subsetList1,numSubset1);

        printf("\n");
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
    
    return 0;
}
