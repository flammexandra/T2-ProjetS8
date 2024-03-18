#define NUM_NODES 10
#define NUM_NEIGHBORS 5
#define NUM_CYCLE 1
#define FILENAME "result.txt"

typedef struct {
    int id;
    int neighbors[NUM_NEIGHBORS];
} Node;