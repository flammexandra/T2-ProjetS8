#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "display.h"

void knownNodes(Node *nodeA,int* subsetListB,bool* subsetListBoolA,int numSubsetB,int* tmp);
void emptyCase(Node *nodeA,int* subsetListB,int* tmp);
void exchangeRemainingNode(Node *nodeA,int* subsetListB,bool* subsetListBoolA,int* tmp);
void exchangeNeighbors(Node *nodeA, Node *nodeB, bool* subsetListBoolA, int* subsetListB, int numSubsetA,int numSubsetB);
void subsetListSend(int * list, int len, int sender, int receiver);
void viewInitialization(int* subsetList1, int* subsetList2, int numSubset1, int numSubset2, int nodeIndex1, int nodeIndex2 );
void viewExchange(Node network[NUM_NODES],int* subsetList1, int* subsetList2, bool* subsetListBool1, bool* subsetListBool2, int numSubset1, int numSubset2, int nodeIndex1, int nodeIndex2);

#endif