#define NUM_NODES 100
#define NUM_NEIGHBORS 10
#define NUM_CYCLE 1000
#define NUM_SUBSET 5
#define NUM_MALICIOUS 10


typedef struct{
    int id;
    int time;
} Descriptor;

typedef struct {
    int id;
    Descriptor neighbors[NUM_NEIGHBORS];
} Node;