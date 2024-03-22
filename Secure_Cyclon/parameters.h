#define NUM_NODES 10
#define NUM_NEIGHBORS 5
#define NUM_CYCLE 1
#define FILENAME "result.txt"

typedef struct {
    int PubKey_rec; // clé publique du noeud qui recoit le descripetur
    int Sign_trans; // signature du noeud qui émet le descripteur
    struct Ownership* nextOwnership;
} Ownership;

typedef struct {
    int PubKey;
    int Time;
    bool nonSwappable;
} NodeInfo;

typedef struct {
    NodeInfo nodeInfo;
    Ownership* ownership;
} ChainOfOwnership;

typedef struct {
    int id;
    ChainOfOwnership chain[NUM_NEIGHBORS];
} NodeData;










typedef struct {
    int id;
    int neighbors[NUM_NEIGHBORS];
} Node;