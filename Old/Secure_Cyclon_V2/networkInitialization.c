#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"

// FONCTIONS INITIALISATION DU RÉSEAU
// initializeNeighbors initialise les voisins d'un nœud avec des valeurs aléatoires.
void initializeNeighbors(NodeData *node, int index ,int * timestamp) {
    bool used[NUM_NODES]; // Tableau pour garder une trace des noeuds déjà utilisés
    memset(used,false,NUM_NODES*sizeof(bool)); // Initialisation du tableau à faux
    
    used[index] = true; // Index du noeud à vrai (un noeud ne peux pas s'autoconnaitre)
    
    // Parcours du nombre de voisin possible
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        int rand_num = rand() % NUM_NODES; // noeuds aléatoire

        if (used[rand_num])
            node->chain[i].nodeInfo.PubKey = -1; // Si déja connu, le noeud devient inconnu
        else { // Sinon il devient un nouveau voisin
            node->chain[i].nodeInfo.PubKey = rand_num; 
            node->chain[i].nodeInfo.nonSwappable = false ;
            node->chain[i].nodeInfo.Time = timestamp[rand_num];
            timestamp[rand_num]++;
            node->chain[i].ownership=malloc(sizeof(Ownership));
            node->chain[i].ownership->PubKey_rec = index;
            node->chain[i].ownership->Sign_trans=rand_num;
            node->chain[i].ownership->nextOwnership=NULL;
        }
        used[rand_num] = true; // Marquer le noeud comme utilisé
    }
}

void orderNeighbors(NodeData *node){
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
    }

}

// networkInitialisation initialise chaque noeuds de réseau
void networkInitialisation(NodeData * network, int * timestamp){
    srand(time(NULL));
    //Parcours du réseau
    for (int i = 0; i < NUM_NODES; i++) {
        network[i].id = i;
        initializeNeighbors(&network[i], i,timestamp);
    }

    printNetwork(network);
    printf("\n");
}
