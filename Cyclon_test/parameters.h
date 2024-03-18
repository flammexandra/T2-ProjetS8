#define NUM_NODES 100
#define NUM_NEIGHBORS 5
#define NUM_CYCLE 100000
#define FILENAME "result.txt"

typedef struct {
    int id;
    int neighbors[NUM_NEIGHBORS];
} Node;