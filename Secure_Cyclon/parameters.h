#define NUM_NODES 10000
#define NUM_NEIGHBORS 50
#define NUM_CYCLE 500
#define NUM_SUBSET 10
#define NUM_MALICIOUS 50


typedef struct{
    int id;
    int time;
} Descriptor;

typedef struct {
    int id;
    Descriptor neighbors[NUM_NEIGHBORS];
} Node;