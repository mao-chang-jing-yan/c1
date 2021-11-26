//
// Created by mao on 2021/11/21.
//

#include <stdlib.h>

#ifndef C1_STACK_H
#define C1_STACK_H

#endif //C1_STACK_H

typedef struct sNode {
    void *value;
    struct sNode *next;
} SNode;

typedef struct stack {
    int max_size;
    int size;
    struct sNode *top;
} Stack;

Stack *initStack(int max_size);

void pushStack(Stack *s, void *value);

void *popStack(Stack *s);