#ifndef EXCHANGEINITIALIZATION_H
#define EXCHANGEINITIALIZATION_H

#include "display.h"
#include "auxiliary.h"

int chooseReceiverNode(Descriptor* neighborsList,int* idRec);
int numberOfNeighbors(Node node);
void initSubsetNeighbors(Node *node, bool* subsetListBool, Descriptor* subsetList, int numSubset,int idnodeIndex2);
void setupNode1(Node network[NUM_NODES],int nodeIndex1, Descriptor* subsetList1,bool* subsetListBool1,int idnodeIndex2);
void setupNode2(Node network[NUM_NODES],int nodeIndex2, Descriptor* subsetList2,bool* subsetListBool2,Descriptor* subsetList1);
#endif