#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LinkedList.h"
#include "Stack.h"

#define DATANAME "LIBRARY.DAT"
#define HISTNAME "HISTORY.DAT"
#define MAX_UINT_INP 9999

Node *head;
Stack *hist;

void input(char *string, int length){

    fgets(string,length,stdin);
    if(strrchr(string, '\n') == NULL){ //If the ending of string is not a newline, then a input overflow has occured
		int c;
		while((c = getchar()) != '\n' && c != EOF); //Clear stdin
	}
	while(*string){
		if(*string != NULL){
			if(*string == '\n'){
				*string = '\0';
			}
			*string++;
		} else {
			break;
		}
	}
}

void addbook();
void library(int key);
void pushhist(char *history);
void get_input(char *title, char *author, char *publisher, unsigned int *stock, unsigned int *year);

int main(){
	head = load_list(DATANAME);
	hist = load_stack(HISTNAME);
	char *choice = malloc(sizeof(char));
	int i;

	while(1){
		system("cls");
		printf("LIBRARY BOOK KEEPER\n===================\n");
    	printf("(1) Library\n(2) Add New Title\n(3) History\n(4) About Program\n(5) Exit\n\n");
		printf("Enter a choice: ");
		input(choice, 2);
		if(sscanf(choice, "%d", &i) == 1){
			switch(i){
				case 1:
					system("cls");
					printf("===========================================LIBRARY===========================================\n");
					print_list(head);
					printf("\n(1) Edit a book\n(2) Delete a book\n(3) Sort library\n(4) Back to menu\n\nChoice: ");
					input(choice, 2);
					if(sscanf(choice, "%d", &i) == 1){
						library(i);
					} else {
						fprintf(stderr, "Please input a correct choice!\n");
						getch();
						continue;
					}
					printf("Press any key to continue...");
					getch();
					break;
				case 2:
					addbook(); 
					break;
				case 3:
					system("cls");
					printf("================HISTORY================\n");
					print_stack(hist);
					printf("Press any key to continue...");
					getch();
					break;
				case 4:
					system("cls");
					printf("This source code was made by Kivlan Rafly B., Nadine Almira W., and Anindya Fawwaz A. as a final programming assignment in Odd Semester 2020/2021 for Algorithms and Programming (ENEE604023) in Undergraduate Electrical Engineering study program, Department of Electrical Engineering, Faculty of Engineering, University of Indonesia.\n");
					printf("\n\nPress any key to continue...");
					getch();
					break;
				case 5:
					save_list(head, DATANAME);
					save_stack(hist, HISTNAME);
					printf("Library saved. See you again!\nPress any key to continue...");
					getch();
					exit(1);
					break;
				default:
					fprintf(stderr, "Please input a correct choice!");
					getch();
			}
		} else{
			fprintf(stderr, "Please input a correct choice!\n");
			getch();
		}
	}
	return 0;
}

void addbook(){
	char *temp = (char *) malloc(sizeof(char));
	char *author = (char *) malloc(sizeof(char));
	char *publisher = (char *) malloc(sizeof(char));
	char *title = (char *) malloc(sizeof(char));
	unsigned int year, stock;

	system("cls");
	printf("===ADD NEW BOOK===\n");
	get_input(title, author, publisher, &stock, &year);
	
	if(head == NULL){
		head = init_list(title, author, publisher, stock, year);
	} else {
		push_list(head, title, author, publisher, stock, year);
	}
	printf("Successfully added book!\nPress any key to conitnue...");
	sprintf(temp, "\"%s\" was added to the library with %u stocks left", title, stock);
	pushhist(temp);
	getch();
	return;
}

void library(int key){
	char *choice = (char *) malloc(sizeof(char));
	int i;
	switch (key)
	{
	case 1: //Editing
		printf("Book ID to edit: ");
		input(choice, 2);
		if(sscanf(choice, "%d", &i) == 1 && (i >= 0 && i < list_size(head))){
			char *temp = (char *) malloc(sizeof(char));
			char *author = (char *) malloc(sizeof(char));
			char *publisher = (char *) malloc(sizeof(char));
			char *title = (char *) malloc(sizeof(char));
			unsigned int stock, year;

			get_input(title, author, publisher, &stock, &year);
			edit_node(head, i, title, author, publisher, stock, year);
			sprintf(temp, "Book ID %d was edited with new title \"%s\".", i, title);
			pushhist(temp);
			printf("Book edited!\n");
		} else {
			fprintf(stderr, "You typed an invalid number, try again!\n");
			return;
		}
		break;
	case 2: //Delete
		printf("Book ID to delete: ");
		input(choice, 2);
		if(sscanf(choice, "%d", &i) == 1 && (i >= 0 && i < list_size(head))){
			char *temp = (char *) malloc(sizeof(char));
			char *title = (char *) malloc(sizeof(char));
			strcpy(title, get_node(head, i)->title);
			remove_list_by_id(head, i);
			sprintf(temp, "Book ID %d with title \"%s\" was removed.", i, title);
			pushhist(temp);
			printf("Book removed!\n");
		} else {
			fprintf(stderr, "You typed an invalid number, try again!\n");
			return;
		}
		break;
	case 3: //Sorting
		printf("Sort by:\n(1) Title\n(2) Author\n(3) Publisher\n(4) Year\n(5) Stock\n\nChoice: ");
		input(choice, 2);
		if(sscanf(choice, "%d", &i) == 1 && (i > 0 && i < 6)){
			sort_list(head, i);
			pushhist("Library resorted.");
			printf("Library sorted!\n");
		} else {
			fprintf(stderr, "You typed an invalid number, try again!\n");
			return;
		}
		break;
	case 4:
		return;
	default:
		fprintf(stderr, "Invalid choice!\n");
		getch();
		break;
	}

}

void pushhist(char *history){
	if(hist == NULL){
		hist = init_stack(history);
	} else {
		push_stack(&hist, history);
	}
	save_stack(hist, HISTNAME);
	save_list(head, DATANAME);
}

void get_input(char *title, char *author, char *publisher, unsigned int *stock, unsigned int *year){
	char *temp = (char *) malloc(sizeof(char));
	printf("Title: ");
	input(title, 50);
	printf("Author: ");
	input(author, 50);
	printf("Publisher: ");
	input(publisher, 50);
	printf("Year: ");
	input(temp, 5);
	if(sscanf(temp, "%u", year) != 1){
		fprintf(stderr, "You typed an invalid number, try again!\n");
		return;
	} else if (*year > MAX_UINT_INP){
		fprintf(stderr, "You typed an invalid number, try again!\n");
		return;
	}
	printf("Stock: ");
	if(sscanf(temp, "%u", stock) != 1){
		fprintf(stderr, "You typed an invalid number, try again!\nPress any key to continue...");
		getch();
		return;
	} else if (*stock > MAX_UINT_INP){
		fprintf(stderr, "You typed an invalid number, try again!\nPress any key to continue...");
		getch();
		return;
	}
	input(temp, 6);
	sscanf(temp, "%d", stock);
}