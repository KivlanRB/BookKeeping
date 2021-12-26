#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LinkedList.h"

#define DATANAME "LIBRARY.DAT"
#define MAX_UINT_INP 9999

Node *head;

void input(char *string, int length){

    fgets(string,length,stdin);
    if(strrchr(string, '\n') == NULL){ //If the ending of string is not a newline, then a buffer overflow has occured
		int c;
		while((c = getchar()) != '\n' && c != EOF);
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

int main(){
	head = load(DATANAME);
	char *choice = malloc(sizeof(char));
	int i;

	while(1){
		system("cls");
		printf("LIBRARY BOOK KEEPER\n===================\n");
    	printf("(1) Library\n(2) Add New Title\n(3) About Library\n(4) About Program\n(5) Exit\n\n");
		printf("Enter a choice: ");
		input(choice, 2);
		if(sscanf(choice, "%d", &i) == 1){
			switch(i){
				case 1:
					system("cls");
					print_list(head);
					getchar();
					break;
				case 2:
					addbook(); 
					break;
				case 3:
					printf("About library\n"); //TODO
					break;
				case 4:
					printf("About program\n"); //TODO
					break;
				case 5:
					save(head, DATANAME);
					printf("Library saved. See you again!\nPress any key to continue...");
					getch();
					exit(1);
					break;
				default:
					fprintf(stderr, "Please input a correct choice!");
			}
		} else{
			fprintf(stderr, "Please input a correct choice!\n");
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
	printf("===ADD NEW BOOK===\nTitle: ");
	input(title, 50);
	printf("Author: ");
	input(author, 50);
	printf("Publisher: ");
	input(publisher, 50);
	printf("Year: ");
	input(temp, 5);
	if(sscanf(temp, "%u", &year) != 1){
		fprintf(stderr, "You typed an invalid number, try again!\n");
		return;
	} else if (year > MAX_UINT_INP){
		fprintf(stderr, "You typed an invalid number, try again!\n");
		return;
	}
	printf("Stock: ");
	if(sscanf(temp, "%u", &year) != 1){
		fprintf(stderr, "You typed an invalid number, try again!\n");
		return;
	} else if (stock > MAX_UINT_INP){
		fprintf(stderr, "You typed an invalid number, try again!\n");
		return;
	}
	input(temp, 6);
	sscanf(temp, "%d", &stock);
	
	if(head == NULL){
		head = init(title, author, publisher, stock, year);
		return;
	} else {
		push(head, title, author, publisher, stock, year);
	}
}