#define NUM_NODES 1000
#define NUM_NEIGHBORS 20
#define NUM_CYCLE 500
#define NUM_SUBSET 10
#define NUM_MALICIOUS 20


typedef struct{
    int id;
    int time;
} Descriptor;

typedef struct {
    int id;
    Descriptor neighbors[NUM_NEIGHBORS];
} Node;