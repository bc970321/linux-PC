/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月13日 星期四 13时47分52秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init(int n) {
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

int expand(Vector *v) {
    int *p = (int *)realloc(v->data, sizeof(int) * 2 * v->size);
    if (p == NULL) return 0;
    v->data = p;
    v->size *= 2;
    return 1;
}

int insert(Vector *v, int ind, int val) {
    if (ind < 0 || ind > v->length) return 0;
    if (v->length == v->size) {
        if (!expand(v)) {
            return 0;
        }
    }
    for (int i = v->length - 1; i >= ind; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = val;
    v->length++;
    return 1;
}

int main() {
    #define MAX_OP 20
    int op, ind, val;
    Vector *v = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        ind = rand() % (v->length + 3) - 1;
        val = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d to vector at %d = %d\n", val, ind, insert(v, ind, val));
            } break;
            case 3: {
                printf("erase element at %d = %d\n", ind, erase(v, ind));
            } break;
            default: fprintf(stderr, "wrong op %d\n", op);
            break;
        }
    }
    clear(v);
    return 0;
}
