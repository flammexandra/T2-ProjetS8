#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "parameters.h"

// FONCTIONS D'AFFICHAGE
// Affichage du réseau
void printNetwork(Node network[NUM_NODES]){
    for (int i = 0; i < NUM_NODES; i++) {
        printf("    Node %d neighbors: ", network[i].id);
        for (int j = 0; j < NUM_NEIGHBORS; j++) {
            printf("%d ", network[i].chaine[j].nodeInfo.PubKey);
        }
        printf("\n");
        printf("    And Timestamp : ");
        for (int j = 0; j < NUM_NEIGHBORS; j++) {
            printf("%d ", network[i].chaine[j].nodeInfo.timestamp);
        }
        printf("\n");
    }
}

void printNodeNeighbors(Node node){
    printf("    Node %d neighbors: ", node.id);
        for (int j = 0; j < NUM_NEIGHBORS; j++) {
            printf("%d ", node.chaine[j].nodeInfo.PubKey);
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

