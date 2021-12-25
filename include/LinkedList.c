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
    int id = 0;

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