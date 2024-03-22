#ifndef EXCHANGEINITIALIZATION_H
#define EXCHANGEINITIALIZATION_H

#include "display.h"
#include "auxiliary.h"

int chooseSenderNode(int* tableTimestamp);
int chooseReceiverNode(int* subsetList,int numSubset);
int numberOfNeighbors(Node node);
void initSubsetNeighbors(Node *node, int numSubset, bool* subsetListBool, int* subsetList);
void setupNode1(Node network[NUM_NODES],int* tableTimestamp,int* nodeIndex1,int* numNeighbors1, int* numSubset1, int* subsetList1,bool* subsetListBool1);
void setupNode2(Node network[NUM_NODES],int* nodeIndex2,int* numNeighbors2, int* numSubset2, int* subsetList2,bool* subsetListBool2,int* subsetList1, int numSubset1);

#endif