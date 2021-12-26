#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save(Node * head, char *filename){
    FILE *fp;
    fp = fopen(filename, "wb");
    if (fp == NULL){
        fprintf(stderr, "Error opening file!");
        return;
    }

    Node *current = head;

    while (current != NULL){
        fwrite(current, sizeof(Node), 1, fp);
        current = current->next;
    }

    fclose(fp);
}

void print_node(Node * node){
    printf("%-20s\t%-20s\t%-20s\t%-6u\t%u\n", node->title, node->author, node->publisher, node->year, node->stock);
}

void print_list(Node * head){
    Node *current = head;
    int id;
    printf("ID%-3sTitle%-22sAuthor%-18sPublisher%-15sYear%-4sStock\n", "", "", "", "","");

    while(current != NULL){
        printf("%-5d", id++);
        print_node(current);
        current = current->next;
    }
}

void push(Node * head, char *title, char *author, char *publisher, int stock, int year){
    Node *current = head;

    while(current->next != NULL){
        current = current->next;
    }

    current->next = (Node *) malloc(sizeof(Node));
    strcpy(current->next->author, author);
    strcpy(current->next->title, title);
    strcpy(current->next->publisher, publisher);
    current->next->year = year;
    current->next->stock = stock;
    current->next->next = NULL;
}

void remove_by_id(Node * head, int id){
    Node *current = head;
    Node *previous = NULL;
    
    while(current != NULL && id > 0){
        previous = current;
        current = current->next;
        id--;
    }

    if(current != NULL){
        previous->next = current->next;
        free(current);
    }
}

void sort(Node * head, int key){
    //TODO: Create insertion sort
}

void swap(Node * a, Node * b){
    Node * temp = (Node *) malloc(sizeof(Node));

    //TODO: Create swap func
}

void copy(Node * a, Node * b){
    b->stock = a->stock;
    b->year = a->year;
    strcpy(b->title,a->title);
    strcpy(b->publisher,a->publisher);
    strcpy(b->author,a->author);
}

Node *init(char *title, char *author, char *publisher, int stock, int year){
    Node *head = (Node *) malloc(sizeof(Node));
    head->next = NULL;
    head->year = year;
    head->stock = stock;
    strcpy(head->author, author);
    strcpy(head->title, title);
    strcpy(head->publisher, publisher);
    return head;
}

Node *load(char *filename){
    FILE *fp;
    Node *head = NULL;
    Node *current = NULL;
    Node *temp = (Node *) malloc(sizeof(Node));
    int id = 0;

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "Error loading file!\n");
        return head;
    }

    while(fread(temp, sizeof(Node), 1, fp)){
        if(head == NULL){
            head = (Node *) malloc(sizeof(Node));
            current = head;
        } else {
            current->next = (Node *) malloc(sizeof(Node));
            current = current->next;
        }
        current->next = NULL;
        current->year = temp->year;
        current->stock = temp->stock;
        strcpy(current->author, temp->author);
        strcpy(current->title, temp->title);
        strcpy(current->publisher, temp->publisher);
    }

    if(head == NULL){
        fprintf(stderr, "File has zero data!\n\n");
    }

    fclose(fp);

    return head;
}

int size(Node * node){
    Node* current = node;
    int len = 0;
    while(current != NULL){
        len++;
        current = current->next;
    }

    return len;
}