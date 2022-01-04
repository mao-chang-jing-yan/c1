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

void insert_q(Que *q, int index, void *value) {
    if (q->size >= q->max_size){
        return;
    }
    if (q->size <= index) {
        pushBack(q, value);
        return;
    }
    if (index <= 0) {
        pushFront(q, value);
        return;
    }
    QNode *p = q->front;
    for (int i = 0; i < index; ++i) {
        p = p->back;
    }

    QNode *fr = p->front;
    QNode *ba = p;
    QNode *mi = (QNode *) malloc(sizeof(QNode));
    fr->back = mi;
    ba->front = mi;
    mi->front = fr;
    mi->back = ba;
    mi->value = value;
    q->size++;
}


void test_q() {
    int num = 7129;
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
        if (d == NULL) {
            break;
        }
        printf("%d\n", *(int *) d);
    }


    clear_q(q);
    free(q);
    free(l);



//    Que *q1 = initQueue(3);
//    int a = 12;
//    int b = 13;
//    int c = 14;
//    int d = 15;
//    pushBack(q1, &a);
//    pushBack(q1, &c);
//    pushBack(q1, &d);
//    insert_q(q1, 1, &b);
//
//
//    int si = q1->size;
//    while (q1->size>0){
//        printf("%d, ", *(int *) popFront(q1));
//    }
//    printf("\n%d", si);
//
//    clear_q(q1);
//    free(q1);
}
