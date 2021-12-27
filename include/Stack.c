#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

void print_stack(Stack * head){
    Stack *current = head;
    while(current != NULL){
        printf("%s\n", current->history);
        current = current->next;
    }
}

void push_stack(Stack ** head, char *history){
    Stack *new_head = init_stack(history);
    new_head->next = *head;
    *head = new_head;
}

void pop_stack(Stack ** head, int amount){
    while(*head != NULL && amount > 0){
        (*head) = (*head)->next;
        amount--;
    }
}

Stack *init_stack(char *history){
    Stack *head = (Stack *) malloc(sizeof(Stack));

    strcpy(head->history, history);
    head->next = NULL;

    return head;
}