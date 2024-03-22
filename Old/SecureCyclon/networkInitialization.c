#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"

// FONCTIONS INITIALISATION DU RÉSEAU
// initializeNeighbors initialise les voisins d'un nœud avec des valeurs aléatoires.
void initializeNeighbors(Node *node, int index, int* tableTimestamp) {
    bool used[NUM_NODES]; // Tableau pour garder une trace des nombres déjà utilisés

    memset(used,false,NUM_NODES*sizeof(bool)); // Initialisation du tableau à faux
    used[index] = true; // Index du noeud à vrai (un noeud ne peux pas s'autoconnaitre)

    
    // Parcours du nombre de voisin possible
    for (int i = 0; i < NUM_NEIGHBORS; i++) {
        int rand_num = rand() % NUM_NODES; // noeuds aléatoire

        if (used[rand_num]){
            node->chaine[i].nodeInfo.PubKey = -1; // Si déja connu, le noeud devient inconnu
            node->chaine[i].nodeInfo.timestamp = -1;
        }  
        else{
            node->chaine[i].nodeInfo.PubKey = rand_num; // Sinon il devient un nouveau voisin
            node->chaine[i].nodeInfo.timestamp =tableTimestamp[i];// Initialisation de l'horodatage
            tableTimestamp[i]++;
        }
        node->chaine[i].nextOwnership=NULL;
        used[rand_num] = true; // Marquer le noeud comme utilisé
    }
}

// networkInitialisation initialise chaque noeuds de réseau
void networkInitialisation(Node network[NUM_NODES],int* tableTimestamp){
    //Parcours du réseau
    for (int i = 0; i < NUM_NODES; i++) {
        network[i].id = i;
        initializeNeighbors(&network[i], i, tableTimestamp);
    }
    printNetwork(network);
    printf("\n");
}
