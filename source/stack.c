//
// Created by mao on 2021/11/21.
//

#include "../header/stack.h"

Stack *initStack(int max_size) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->max_size = max_size;
    stack->size = 0;
    stack->top = 0;
    return stack;
}

void pushStack(Stack *s, void *value) {
    if (s->size > s->max_size) {
        return;
    }
    SNode *sNode = (SNode *) malloc(sizeof(SNode));
    sNode->value = value;
    if (s->size == 0) {
        s->size = 1;
        s->top = sNode;
        return;
    }
    s->size += 1;
    sNode->next = s->top;
    s->top = sNode;
}

void *popStack(Stack *s) {
    if (s->size <=0 || s->top == 0){
        return 0;
    }
    void *res = s->top->value;
    SNode *t = s->top;
    s->top = s->top->next;
    free(t);
    s->size--;
    return res;
}