#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "display.h"

void knownNodes(Node *nodeA,Descriptor* subsetListB,bool* subsetListBoolA,int* tmp);
void emptyCase(Node *nodeA,Descriptor* subsetListB,int* tmp, bool flagMalicious);
void exchangeRemainingNode(Node *nodeA,Descriptor* subsetListB,bool* subsetListBoolA,int* tmp,bool flagMalicious);
void exchangeNeighbors(Node *nodeA, Node *nodeB, bool* subsetListBoolA, Descriptor* subsetListB,bool flagMalicious);
void subsetListSend(Descriptor * list, int sender, int receiver, bool flagSender,bool flagMalicious, int c);
void viewInitialization(Descriptor* subsetList1, Descriptor* subsetList2,int nodeIndex1, int nodeIndex2, int c );
void viewExchange(Node network[NUM_NODES],Descriptor* subsetList1, Descriptor* subsetList2, bool* subsetListBool1, bool* subsetListBool2, int nodeIndex1, int nodeIndex2, int c);

#endif