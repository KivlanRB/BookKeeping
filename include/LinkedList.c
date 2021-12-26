#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int id;
    char title[40];
	char author[40];
	char publisher[50];
	int stock;
	int year;
    struct node *next;
};

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
    printf("%-5d%-20s\t%-20s\t%-20s\t%-6d\t%d", node->id, node->title, node->author, node->publisher, node->year, node->stock);
    printf("\n");
}

void print_list(Node * head){
    Node *current = head;
    printf("ID%-3sTitle%-22sAuthor%-18sPublisher%-15sYear%-4sStock\n", "", "", "", "","");

    while(current != NULL){
        print_node(current);
        current = current->next;
    }
}

void push(Node * head, char *title, char *author, char *publisher, int stock, int year){
    Node *current = head;
    int id = 1;

    while(current->next != NULL){
        current = current->next;
        id++;
    }

    current->next = (Node *) malloc(sizeof(Node));
    current->next->id = id;
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
    
    while(current != NULL && current->id != id){
        previous = current;
        current = current->next;
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
    b->id = a->id;
    b->stock = a->stock;
    b->year = a->year;
    strcpy(b->title,a->title);
    strcpy(b->publisher,a->publisher);
    strcpy(b->author,a->author);
}

Node *init(char *title, char *author, char *publisher, int stock, int year){
    Node *head = (Node *) malloc(sizeof(Node));
    head->next = NULL;
    head->id = 0;
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
        fprintf(stderr, "Error loading file!");
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
        current->id = id++;
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