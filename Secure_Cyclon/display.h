#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "parameters.h"

void printNetwork(NodeData network[NUM_NODES]);
void printList(int* list, int taille);
void printListBool( int taille, bool* listBool);
void printListWithBool(int* list, int taille, bool* listBool);

#endif
