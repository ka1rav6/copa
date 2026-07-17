#include <stdarg.h>

struct Bitfields {
    unsigned int flag_a : 1;
    unsigned int flag_b : 3;
    unsigned int value : 8;
};

int variadic(int count, ...);

typedef struct node {
    int data;
    struct node* next;
} Node;

struct Container {
    struct {
        int x;
        int y;
    } inner;
    int z;
};
