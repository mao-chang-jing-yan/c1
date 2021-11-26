#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header/func.h"
#include "header/graph.h"
#include "header/qNode.h"
#include "header/stack.h"
#include "header/yiqun.h"
#include "header/window.h"

void test_q();

void test_graph();

void test_stack();

void test_sort();

void test_1();

int main(int argc, char *argv[]) {
    while (argc-- > 1)
        printf("%s\n", *++argv);
//    test_q();
//    test_graph();
//    test_stack();
//    test_sort();
//    printf("%d %s", argc, *argv);

//    test_1();
//    int a = test_sort_();
//    printf("%d", a);

//    printf("%o \n", 0b1);
//    printf("%d \n", 0b10);
//    printf("%d \n", 0b101);
//    printf("%d \n", 0b1010);
//    printf("%d \n", 0b10101);
//    printf("%d \n", 0b101010);
//    printf("%d \n", 0b10101010);

//    main_yi();


    return 0;
}

void test_1() {
    int **p = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; ++i) {
        int *pi = (int *) malloc(sizeof(int) * 10);
        for (int j = 0; j < 10; ++j) {
            pi[j] = j * i + j - i;
        }
        p[i] = pi;
    }


    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d ", p[i][j]);
        }
//        free(*(p + i));
        printf("\n");
    }

    Que *q = initQueue(101);
    int a[10];
    for (int k = 0; k < 10; ++k) {
        a[k] = -1;
    }
    for (int i = 0; i < 100; ++i) {
        int min = p[0][a[0] + 1];
        int min_index = 0;
        for (int j = 0; j < 10; ++j) {
            if (p[j][a[j]] < min) {
                min_index = j;
                min = p[j][a[j]];
            }
        }
    }


    free(p);
}

void test_sort() {
    int a[] = {1, 2, 3, 3, 2, 1, -1};
    int length = sizeof(a) / sizeof(int);

//    insert_sort(a, length);
//    bubble_sort(a, length);
    quick_sort(a, length);

    for (int i = 0; i < 6; ++i) {
        printf("%d ", a[i]);
    }

}

void test_stack() {
    Stack *s = initStack(100);
    int a = 100;
    void *b = &a;
    pushStack(s, b);
    pushStack(s, b);
    popStack(s);
    popStack(s);
    popStack(s);
    free(s);
}


void test_graph() {
    int a[][3] = {
            {0, 1, 5},
            {1, 6, 60},
            {1, 5, 30},
            {1, 2, 20},
            {2, 3, 10},
            {3, 2, -15},
            {2, 4, 75},
            {4, 9, 100},
            {5, 4, 25},
            {5, 6, 5},
            {5, 8, 50},
            {6, 7, -50},
            {7, 8, -10},
    };


    bellman_ford((int *) a, sizeof(a) / sizeof(0) / 3, 0, 3);
    floyd((int *) a, sizeof(a) / sizeof(0) / 3, 0, 3);
    SpFa((int *) a, sizeof(a) / sizeof(0) / 3, 0, 3);
}

void test_q() {
    Que *q = initQueue(100);
    void *d = (void *) 789;
    for (int i = 0; i < 100; ++i) {
        int c = 789;
        void *f = &c;
        pushBack(q, f);
    }
    pushBack(q, d);
    d = popBack(q);
    printf("%d\n", *(int *) d);
    d = popBack(q);
    printf("%d\n", *(int *) d);

    clear(q);
    free(q);
}
