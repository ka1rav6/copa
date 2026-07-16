#include <stdio.h>
#include "myheader.h"

#define MAX_SIZE 1024
#define SQUARE(x) ((x) * (x))

typedef struct {
    int x;
    int y;
} Point;

typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

typedef void (*callback_t)(int, const char*);

extern int global_var;

int add(int a, int b);
static void internal_func(void);
int* get_pointer(const char* name);

struct Forward;

int main(int argc, char* argv[]) {
    Point p = {10, 20};
    int arr[5] = {1, 2, 3, 4, 5};
    double pi = 3.14159;
    char c = 'A';
    const char* msg = "hello world";

    if (p.x > 0 && p.y > 0) {
        printf("positive: %s\n", msg);
    }

    for (int i = 0; i < 10; i++) {
        arr[i % 5] += i;
    }

    return 0;
}

// add two numbers
int add(int a, int b) {
    return a + b;
}

static void internal_func(void) {
    /* this is a block comment */
    int x = 42; // inline comment
}
