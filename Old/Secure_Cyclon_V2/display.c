#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "parameters.h"

// FONCTIONS D'AFFICHAGE
// Affichage du réseau
void printNetwork(NodeData network[NUM_NODES]){
    for (int i = 0; i < NUM_NODES; i++) {
        printf("    Node %d neighbors: \n", network[i].id);
        for (int j = 0; j < NUM_NEIGHBORS; j++) {
            printf("        Descriptors %d : \n", j);
            printf("            Node Info :\n");
            printf("                PubKey : %d\n",network[i].chain[j].nodeInfo.PubKey);
            printf("                Time : %d\n",network[i].chain[j].nodeInfo.Time);
            printf("                Non Swapable : %d\n",network[i].chain[j].nodeInfo.nonSwappable);

            if (network[i].chain[j].nodeInfo.PubKey>=0){
                printf("            Ownership :\n");
                printf("                PubKey Rec: %d\n",network[i].chain[j].ownership->PubKey_rec);
                printf("                Signature : %d\n",network[i].chain[j].ownership->Sign_trans);
            }
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

