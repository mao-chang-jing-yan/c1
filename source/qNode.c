//
// Created by mao on 2021/11/20.
//

#include "../header/qNode.h"
#include <stdio.h>

Que *initQueue(int max_size) {
    Que *q = (Que *) malloc(sizeof(Que));
    if (q == NULL) {
        return NULL;
    }
    q->max_size = max_size;
    q->size = 0;
    q->front = q->back = NULL;
    return q;
}

void pushBack(Que *q, void *value) {
    QNode *sq = (QNode *) malloc(sizeof(QNode));
    if (sq == NULL || q->size >= q->max_size) {
        if (sq != NULL) { free(sq); }
        return;
    }
    sq->value = value;
    if (q->front == q->back && q->back == NULL) {
        q->front = q->back = sq;
        q->size += 1;
        return;
    }
    sq->front = q->back;
    q->back->back = sq;
    q->back = sq;
    q->size += 1;
}

void pushFront(Que *q, void *value) {
    QNode *sq = (QNode *) malloc(sizeof(QNode));
    if (sq == NULL || q->size >= q->max_size) {
        if (sq != NULL) { free(sq); }
        return;
    }
    sq->value = value;
    if (q->front == q->back && q->front == NULL) {
        q->front = q->back = sq;
        q->size += 1;
        return;
    }
    sq->back = q->front;
    q->front->front = sq;
    q->front = sq;
    q->size += 1;
}

void *popBack(Que *q) {
    if ((q->front == q->back && q->back == NULL) || q->size <= 0) {
        return NULL;
    }
    if (q->front == q->back) {
        void *res = q->back->value;
        free(q->back);
        q->front = q->back = NULL;
        q->size -= 1;
        return res;
    }
    void *res = q->back->value;
    q->back = q->back->front;
    free(q->back->back);
    q->size -= 1;
    return res;
}

void *popFront(Que *q) {
    if ((q->front == q->back && q->back == NULL) || q->size <= 0) {
        return NULL;
    }
    if (q->front == q->back) {
        void *res = q->back->value;
        free(q->back);
        q->front = q->back = NULL;
        q->size -= 1;
        return res;
    }
    void *res = q->front->value;
    q->front = q->front->back;
    free(q->front->front);
    q->size -= 1;
    return res;
}

void clear_q(Que *q) {
    while (q->size > 0) {
        popBack(q);
    }
}

void test_q() {
    int num = 209;
    int *l = malloc(sizeof(int) * num);
    int *li = l;
    Que *q = initQueue(num);
    void *d;


    for (int i = 0; i < num; ++i) {
        l[i] = i;
        pushBack(q, li);
        li++;
    }
    for (int i = 0; i < num; ++i) {
        d = popFront(q);
        printf("%d\n", *(int *) d);
        d = popBack(q);
        printf("%d\n", *(int *) d);
    }


    clear_q(q);
    free(q);
    free(l);
}
