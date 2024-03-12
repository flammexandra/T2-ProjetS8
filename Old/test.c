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

// Fonction pour initialiser les voisins d'un nœud avec des valeurs aléatoires
void initializeNeighbors(Node *node, int index) {
    bool used[NUM_NODES]; // Tableau pour garder une trace des nombres déjà utilisés
    for (int i = 0; i < NUM_NODES; i++) {
        used[i] = false; // Initialisation de tous les éléments à false (non utilisés)
    }
    used[index] = true;
    
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        int rand_num = rand() % NUM_NODES;

        if (used[rand_num])
            node->neighbors[i] = -1;
        else
            node->neighbors[i] = rand_num;
        used[rand_num] = true; // Marquer le nombre comme utilisé
    }
}


//Fonction pour déterminer le nombre de voisin connu d'une liste 
int numberOfNeighbors(Node *node) {
    int tmp = 0;
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        tmp+=(node->neighbors[i]!=-1);
    }
    return tmp;
}

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

void printList(int* list, int taille){
        for (int i = 0; i < taille; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");

}

void subsetNeigbors(Node *node, int numSubset) {
    bool used[NUM_NEIGHBORS]; // Tableau pour garder une trace des nombres déjà utilisés
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        used[i] = (node->neighbors[i]==-1); // Initialisation de tous les éléments à false (non utilisés)
    }
    
    for (int i = 0; i < numSubset; i++) {
        int rand_num;
        do {
            rand_num = rand() % NUM_NEIGHBORS;
        } while (used[rand_num]); // Tant que le nombre aléatoire est déjà utilisé, en générer un nouveau
        used[rand_num] = true; // Marquer le nombre comme utilisé
    }

    int index=0;

    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        if (used[i]&&(node->neighbors[i]!=-1)){
            int tmp=node->neighbors[index];
            node->neighbors[index] = node->neighbors[i];
            node->neighbors[i] = tmp;
            index++;
        }    
    }
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool isNotInList(int* list, int len, int a){
    for (int i = 0; i < len; i++){
        if (list[i]==a)
            return false;       
    }
    return true;
}

void exchangeNeigbors(Node *nodeA, int* subsetListB, int numSubsetA,int numSubsetB){
    int tmp=0;
    for (int i = 0; i < numSubsetB; i++){
       if (isNotInList(nodeA->neighbors,NUM_NEIGHBORS,subsetListB[i])){
            subsetListB[tmp]=subsetListB[i];
            tmp++;
       }   
    }
    printf("            List of subset neighbors send to A: ");
    printList(subsetListB, tmp);
    printf("tmp : %d\n",tmp);

    if (tmp==0)
        return;

    for (int i = 0; i < NUM_NEIGHBORS; i++){
        if (nodeA->neighbors[i]==-1){
            nodeA->neighbors[i]=subsetListB[tmp-1];
            tmp--;
        }
        if (tmp==0)
            return;
    }

    for (int i = 0; i < tmp; i++){
        nodeA->neighbors[i]=subsetListB[i];
    }
}

void subsetList(int * list, int * copy, int len, int sender, int receiver){
    for (int i = 0; i < len; i++){
        if (list[i]==receiver)
            copy[i]=sender;
        else
            copy[i]=list[i];

    }
}



int main() {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    Node network[NUM_NODES];

    // Initialisation des nœuds
    printf("Initialisation : \n");
    for (int i = 0; i < NUM_NODES; i++) {
        network[i].id = i;
        initializeNeighbors(&network[i], i);
    }

    printNetwork(network);
    

    printf("\nTraitement : \n");
    for (int c = 0; c < NUM_CYCLE; c++){
        printf("    Cycle number %d \n",c);
        printf("\n        Détermination de l'échange : \n");

        // Choix du noeud initiateur:
        int nodeIndex1 = rand() % NUM_NODES;
        printf("            Node 1 : %d \n",nodeIndex1);

        // Nombre de voisins du noeuds :
        int numNeighbors1 = numberOfNeighbors(&network[nodeIndex1]);
        printf("            Neighbors length %d \n",numNeighbors1);

        // Nombre de sous noeuds sellectionnés :
        int numSubset1 = rand() % numNeighbors1 + 1;
        printf("            Number of subset of neighbors %d \n",numSubset1);

        // Détermination de la sous liste à envoyer :
        subsetNeigbors(&network[nodeIndex1], numSubset1);
        printf("            List of subset neighbors : ");
        printList(network[nodeIndex1].neighbors, numSubset1);
        printf("            List of neighbors : ");
        printList(network[nodeIndex1].neighbors, NUM_NEIGHBORS);

        // Choix du noeuds receveurs :
        int tmp;
        int nodeIndex2=nodeIndex1;
        do {
            tmp = rand() % numSubset1;
            nodeIndex2 = network[nodeIndex1].neighbors[tmp];
        } while (nodeIndex2==nodeIndex1); 

        printf("\n");
        printf("            Node 2 : %d \n",nodeIndex2);

        // Nombre de voisins du noeuds :
        int numNeighbors2 = numberOfNeighbors(&network[nodeIndex2]);
        printf("            Neighbors length %d \n",numNeighbors2);

        // Nombre de sous noeuds sellectionnés :
        int numSubset2 =min(numNeighbors2,numSubset1);
        printf("            Number of subset of neighbors %d \n",numSubset2);

        // Détermination de la sous liste à envoyer :
        subsetNeigbors(&network[nodeIndex2], numSubset2);
        printf("            List of subset neighbors : ");
        printList(network[nodeIndex2].neighbors, numSubset2);
        printf("            List of neighbors : ");
        printList(network[nodeIndex2].neighbors, NUM_NEIGHBORS);

        // Échange des vues:
        printf("\n        Échange des vues : \n");
        int subsetList2[numSubset2];
        subsetList(network[nodeIndex2].neighbors,subsetList2,numSubset2,nodeIndex2,nodeIndex1);
        printf("            List of subset neighbors send to 1: ");
        printList(subsetList2, numSubset2);
        
        int subsetList1[numSubset1];
        subsetList(network[nodeIndex1].neighbors,subsetList1,numSubset1,nodeIndex1,nodeIndex2);
        printf("            List of subset neighbors send to 2: ");
        printList(subsetList1, numSubset1);

        printf("\n");
        printf("            Node 1 : \n");
        exchangeNeigbors(&network[nodeIndex1], subsetList2, numSubset1,numSubset2);
        printf("            List of neighbors : ");
        printList(network[nodeIndex1].neighbors, NUM_NEIGHBORS);
       
        
        printf("\n");
        printf("            Node 2 : \n");
        exchangeNeigbors(&network[nodeIndex2], subsetList1, numSubset2,numSubset1);
        printf("            List of neighbors : ");
        printList(network[nodeIndex2].neighbors, NUM_NEIGHBORS);







    }
    
    return 0;
}
