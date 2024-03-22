#define NUM_NODES 10
#define NUM_NEIGHBORS 5
#define NUM_CYCLE 1

typedef struct {
    int PubKey_dest;
    int Signature;
    struct Ownership* nextOwnership;
} Ownership;

typedef struct {
    int PubKey; //identifiant
    int timestamp;
} NodeInfo;

typedef struct {
    NodeInfo nodeInfo; 
    Ownership* nextOwnership;
} ChainOfOwnership;


typedef struct {
    int id;
    ChainOfOwnership chaine[NUM_NEIGHBORS];
} Node;




