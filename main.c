#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

struct movies{
	char title[40];
	int rating;
	int year;
};
	
struct movies mov;
long int movsize = sizeof(mov);

void addtitle();
void library();
void deletetitle();

// Main function
int main(){
	char another, choice;
    while(1){
    	system("cls");
    	printf("Main Menu\n(1) Library\n(2) To Watch\n(3) Add a Movie\n(4) Delete a Movie\n(5) Exit\n\n");
		printf("Enter a choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				library();
				break;
			case 2:
				
				break;
			case 3:
				addtitle();
				break;	
			case 4:
				
				break;
			case 5:
				exit(0);
			default:
				printf("Invalid entry.\n\n");
				break;
		}
	}
	
	return 0;
}

void library(){
	system("cls");
	FILE *fp;
	fp = fopen("LIBRARY.DAT","rb+");
	if(fp == NULL){
		fp = fopen("LIBRARY.DAT","wb+");
        if(fp == NULL){
            printf("Cannot open file!");
            exit(1);
        }
    }
    rewind(fp);
    while(fread(&mov,movsize,1,fp)==1){
    	printf("\n%s %d %d",mov.title,mov.rating,mov.year); /// print the name, age and basic salary
	}
	fflush(stdin);
	fclose(fp);
    getch();
}

void addtitle(){
	system("cls");
	FILE *fp;
	fp = fopen("LIBRARY.DAT","rb+");
	if(fp == NULL){
		fp = fopen("LIBRARY.DAT","wb+");
        if(fp == NULL){
            printf("Cannot open file!");
            exit(1);
        }
    }
	fseek(fp, 0, SEEK_END);
	
	printf("Title: ");
	scanf("%s", mov.title);
	printf("Personal Rating (0-100): ");
	scanf("%d", &mov.rating);
	printf("Year: ");
	scanf("%d", &mov.year);
	fwrite(&mov, movsize, 1, fp);
	printf("Successfully recorded. Press any key to return to the main menu.");
	
	fflush(stdin);
	fclose(fp);
	getch();
}
