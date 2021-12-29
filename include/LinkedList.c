#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void save_list(Node * head, char *filename){
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
    int id = 0;
    printf("ID%-3sTitle%-22sAuthor%-18sPublisher%-15sYear%-4sStock\n", "", "", "", "","");

    while(current != NULL){
        printf("%-5d", id++);
        print_node(current);
        current = current->next;
    }
}

void push_list(Node * head, char *title, char *author, char *publisher, int stock, int year){
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

void remove_list_by_id(Node * head, int id){
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

void sort_list(Node * head, int key){
    if(head == NULL || head->next == NULL){
        return;
    }

    char *element = (char *) malloc(sizeof(char));
    int i,j;
    unsigned int elm_int;
    int size = list_size(head);

    switch(key){
        case 1: //Sort by title
            for(i = 1; i < size; i++){
                strcpy(element, get_node(head, i)->title);
                j = i-1;

                while(j>=0 && strcmp(get_node(head, j)->title, element) > 0){
                    swap_node(head, j, j+1);
                    j--;
                }
            }
            break;
        case 2: //sort by author
            for(i = 1; i < size; i++){
                strcpy(element, get_node(head, i)->author);
                j = i-1;

                while(j>=0 && strcmp(get_node(head, j)->author, element) > 0){
                    swap_node(head, j, j+1);
                    j--;
                }
            }
            break;
        case 3: //Sort by publisher
            for(i = 1; i < size; i++){
                strcpy(element, get_node(head, i)->publisher);
                j = i-1;

                while(j>=0 && strcmp(get_node(head, j)->publisher, element) > 0){
                    swap_node(head, j, j+1);
                    j--;
                }
            }
            break;
        case 4: //Sort by year of publish
            for(i = 1; i < size; i++){
                elm_int = get_node(head, i)->year;
                j = i-1;

                while(j>=0 && get_node(head, j)->year > elm_int){
                    swap_node(head, j, j+1);
                    j--;
                }
            }
            break;
        case 5: //Sort by stock
            for(i = 1; i < size; i++){
                elm_int = get_node(head, i)->stock;
                j = i-1;

                while(j>=0 && get_node(head, j)->stock > elm_int){
                    swap_node(head, j, j+1);
                    j--;
                }
            }
            break;
        default:
            return;
    }
}

void swap_node(Node * head, int i, int j){
    int temp = i;
    Node *temp_a = (Node *) malloc(sizeof(Node));
    Node *temp_b = (Node *) malloc(sizeof(Node));
    Node *current = head;

    int size = list_size(head);
    if(size < i || size < j || i == j){
        return;
    }
    if(i > j){
        i = j;
        j = temp;
    }

    while(current != NULL && i > 0){
        current = current->next;
        i--;
        j--;
    }
    if(current == NULL){
        return;
    } else{
        copy_node(current, temp_a);
    }
    while(current != NULL && j > 0){
        current = current->next;
        j--;
    }
    if(current == NULL){
        return;
    } else{
        copy_node(current, temp_b);
        copy_node(temp_a, current);
    }

    current = head;
    i = temp;

    while(current != NULL && i > 0){
        current = current->next;
        i--;
    }
    if(current == NULL){
        return;
    } else{
        copy_node(temp_b, current);
    }
}

void copy_node(Node * a, Node * b){
    b->stock = a->stock;
    b->year = a->year;
    strcpy(b->title,a->title);
    strcpy(b->publisher,a->publisher);
    strcpy(b->author,a->author);
}

void edit_node(Node * head, int index, char *title, char *author, char *publisher, int stock, int year){
    Node *current = head;

    while(current != NULL && index > 0){
        index--;
        current = current->next;
    }

    if(current == NULL){
        return;
    }

    current->stock = stock;
    current->year = year;
    strcpy(current->title,title);
    strcpy(current->publisher,publisher);
    strcpy(current->author,author);
}

Node *get_node(Node * head, int index){
    Node *curr = head;

    while (curr != NULL && index > 0){
        curr = curr->next;
        index--;
    }
    
    return curr;
}

Node *init_list(char *title, char *author, char *publisher, int stock, int year){
    Node *head = (Node *) malloc(sizeof(Node));
    head->next = NULL;
    head->year = year;
    head->stock = stock;
    strcpy(head->author, author);
    strcpy(head->title, title);
    strcpy(head->publisher, publisher);
    return head;
}

Node *load_list(char *filename){
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

int list_size(Node * node){
    Node* current = node;
    int len = 0;
    while(current != NULL){
        len++;
        current = current->next;
    }

    return len;
}