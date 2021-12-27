#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct node {
    char title[50];
	char author[50];
	char publisher[50];
	unsigned int stock;
	unsigned int year;
    struct node *next;
} Node;

void save_stack(Node * head, char *filename);

void push_list(Node * head, char *title, char *author, char *publisher, int stock, int year);

void remove_list_by_id(Node *head, int id);

void print_list(Node * head);

void print_node(Node * node);

void sort_list(Node * head, int key);

void swap_node(Node * a, Node * b);

void copy_node(Node * a, Node * b);

int list_size(Node * node);

Node *init_list(char *title, char *author, char *publisher, int stock, int year);

Node *load_list(char *filename);

#endif