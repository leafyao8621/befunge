#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

typedef struct Node {
    int val;
    struct Node* previous;
} Node;

struct Stack {
    Node* tail;
};

Stack* malloc_Stack(void) {
    Stack* opt = malloc(sizeof(Stack));
    if (!opt) {
        puts("malloc stack error");
        return NULL;
    }
    opt->tail = NULL;
    return opt;
}

int push(Stack* s, int v) {
    if (!s) {
        puts("Stack push nullptr");
        return 1;
    }
    Node* added = malloc(sizeof(Node));
    added->val = v;
    added->previous = s->tail;
    s->tail = added;
    return 0;
}

int pop(Stack* s, int* opt) {
    if (!s || !opt) {
        puts("Stack pop nullptr");
        return 1;
    }
    if (!(s->tail)) {
        *opt = 0;
        return 2;
    }
    *opt = s->tail->val;
    Node* temp = s->tail->previous;
    free(s->tail);
    s->tail = temp;
    return 0;
}

int copy_val(Stack* s) {
    if (!s) {
        puts("copy val nullptr");
        return 1;
    }
    if (!s->tail) {
        push(s, 0);
        return 2;
    }
    push(s, s->tail->val);
    return 0;
}

int swap_val(Stack* s) {
    if (!s) {
        puts("copy val nullptr");
        return 1;
    }
    if (!s->tail || !s->tail->previous) {
        push(s, 0);
        return 2;
    }
    int temp = s->tail->val;
    s->tail->val = s->tail->previous->val;
    s->tail->previous->val = temp;
    return 0;
}

int print_Stack(Stack* s) { 
    if (!s) {
        puts("print stack nullptr");
        return 1;
    }
    if (!s->tail) return 0;
    printf("%d", s->tail->val);
    for (Node* temp = s->tail->previous;
         temp; printf(",%d", temp->val), temp = temp->previous);
    puts("");
    return 0;
}
