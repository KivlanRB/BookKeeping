#ifndef STACK_H_
#define STACK_H_
#include <time.h>

typedef struct stack{
    char history[150];
    time_t epoch_time;
    struct stack *next;
}Stack;

void push_stack(Stack ** head, char *history);

void pop_stack(Stack ** head, int amount);

void print_stack(Stack * node);

void save_stack(Stack * head, char *filename);

Stack *init_stack(char *history);

#endif