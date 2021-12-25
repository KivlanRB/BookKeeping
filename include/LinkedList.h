#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct node Node;

void save(Node * head, char *filename);

void push(Node * head, char *title, char *author, char *publisher, int stock, int year);

void remove_by_id(Node *head, int id);

void print_list(Node * head);

void print_node(Node * node);

Node *init(char *title, char *author, char *publisher, int stock, int year);

Node *load(char *filename);

#endif