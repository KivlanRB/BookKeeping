#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

void save_stack(Stack * head, char *filename){
    FILE *fp;
    fp = fopen(filename, "wb");
    if (fp == NULL){
        fprintf(stderr, "Error opening file!");
        return;
    }

    Stack *current = head;

    while (current != NULL){
        fwrite(current, sizeof(Stack), 1, fp);
        current = current->next;
    }

    fclose(fp);
}

void print_stack(Stack * head){
    Stack *current = head;
    while(current != NULL){
        printf("%s%s\n\n", ctime(&(current->epoch_time)),current->history);
        current = current->next;
    }
}

void push_stack(Stack ** head, char *history){
    Stack *new_head = init_stack(history);
    new_head->next = *head;
    time(&(new_head->epoch_time));
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
    time(&(head->epoch_time));
    head->next = NULL;

    return head;
}

Stack *load_stack(char *filename){
    FILE *fp;
    Stack *head = NULL;
    Stack *current = NULL;
    Stack *temp = (Stack *) malloc(sizeof(Stack));
    int id = 0;

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Error loading file!\n");
        return head;
    }

    while(fread(temp, sizeof(Stack), 1, fp)){
        if(head == NULL){
            head = (Stack * ) malloc(sizeof(Stack));
            current = head;
        } else {
            current->next = (Stack * ) malloc(sizeof(Stack));
            current = current->next;
        }
        strcpy(current->history, temp->history);
        current->epoch_time = temp->epoch_time;
        current->next = NULL;
    }

    if(head == NULL){
        fprintf(stderr, "File has zero data!\n\n");
    }

    fclose(fp);

    return head;
}