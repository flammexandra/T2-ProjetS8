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
            printf("%d ", network[i].neighbors[j].id);
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


// Affichage d'une liste de Descriptors courte
void printListDescriptorSimple(Descriptor* list, int taille){

    printf("Liste des descripteurs :  \n");
        for (int i = 0; i < taille; i++) {
            printf("%d ", list[i].id);
        }
    printf("\n\n");
}

// Affichage d'une liste de Descriptors
void printListDescriptor(Descriptor* list, int taille){

    printf("Liste des descripteurs :  \n");
        for (int i = 0; i < taille; i++) {
            printf("%d ", list[i].id);
        }

        printf("\n");
        for (int i = 0; i < taille; i++){
            if (list[i].id!=-1)
            {
                printf("descrpt : %d \n", list[i].id);

                printf("Chaine prop: ");
                struct Ownership * tmp =list[i].ownership;
                while(tmp!=NULL){
                    printf( "PubKey_rec : %d ,Sign_trans : %d |||||",tmp->PubKey_rec,tmp->Sign_trans);
                    tmp=tmp->nextOwnership;

                }

                printf("\n swappable (0 pour faux et 1 pour vrai) : %d \n", list[i].swappable);

                printf("\n\n");
            }
        }
        
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

