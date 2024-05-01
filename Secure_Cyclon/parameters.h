#define NUM_NODES 100
#define NUM_NEIGHBORS 10
#define NUM_CYCLE 1000
#define NUM_SUBSET 5
#define NUM_MALICIOUS 10


struct Ownership{
    int PubKey_rec; // clé publique du noeud qui recoit le descripetur
    int Sign_trans; // signature du noeud qui émet le descripteur
    struct Ownership * nextOwnership;
} ;

typedef struct{
    int id;
    int time;
    bool swappable;
    struct Ownership * ownership;
} Descriptor;

typedef struct {
    int id;
    Descriptor neighbors[NUM_NEIGHBORS];
} Node;