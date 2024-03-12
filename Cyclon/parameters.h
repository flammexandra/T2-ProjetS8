#define NUM_NODES 10000
#define NUM_NEIGHBORS 5
#define NUM_CYCLE 1000

typedef struct {
    int id;
    int neighbors[NUM_NEIGHBORS];
} Node;