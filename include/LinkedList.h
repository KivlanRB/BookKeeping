#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct node Node;

void push(Node * head, char *title, char *author, char *publisher, int stock, int year);

Node *init(char *title, char *author, char *publisher, int stock, int year);

void print_list(Node * head);

void print_node(Node * node);

#endif