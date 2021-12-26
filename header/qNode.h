//
// Created by mao on 2021/11/20.
//

#include <stddef.h>
#include <stdlib.h>

#ifndef C1_QUE_H
#define C1_QUE_H

#endif //C1_QUE_H

typedef struct qNode {
    void *value;
    struct qNode *front;
    struct qNode *back;
} QNode;

typedef struct que{
    int max_size;
    int size;
    struct qNode *front;
    struct qNode *back;
} Que;


Que *initQueue(int max_size);
void pushBack(Que * q, void * value);
void pushFront(Que * q, void * value);
void *popBack(Que * q);
void *popFront(Que * q);
void clear(Que * q);

void test_q();
