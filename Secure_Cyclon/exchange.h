#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "display.h"

void emptyCase(Node *nodeA,Descriptor* subsetListB,int* tmp,bool flagMalicious);
void exchangeRemainingNode(Node *nodeA,Descriptor* subsetListB,bool* subsetListBoolA,int* tmp,bool flagMalicious);
void exchangeNeighbors(Node *nodeA, Node *nodeB, bool* subsetListBoolA, Descriptor* subsetListB,bool flagMalicious);
void subsetListMalicious(Descriptor * list, int c, int rec);
void viewExchange(Node network[NUM_NODES],Descriptor* subsetList1, Descriptor* subsetList2, bool* subsetListBool1, bool* subsetListBool2, int nodeIndex1, int nodeIndex2, int c);

#endif