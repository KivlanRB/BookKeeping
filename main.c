#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

struct movies{
	char title[40];
	int status;
	int rating;
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
    printf("Title%-40s\tStatus%-6sRating\n\n", "", "");
    while(fread(&mov,movsize,1,fp)==1){
    	/* prints all movie data from file buffer
    	This filters the rating to not display rating when its -1
    	Also replaces int formatting of status to human-readable formatting
    	*/
    	printf("%-40s\t", mov.title);
    	switch(mov.status){
    		case 1:
    			printf("Wishlist%-4s", "");
    			break;
    		case 2:
    			printf("Dropped%-5s", "");
    			break;
    		case 3:
    			printf("Watching%-4s", "");
    			break; 
    		case 4:
    			printf("Finished%-4s", "");
    			break;
		}
		if(mov.rating != -1){
			printf("%-5d", mov.rating);
		}
		printf("\n");
	}
	fflush(stdin);
	fclose(fp);
	printf("\nPress any key to return to the main menu.");
    getch();
}

void addtitle(){
	char temp;
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
	scanf("%c", &temp); //Clears buffer from previous inputs
	scanf("%[^\n]", mov.title);
	printf("(1) Wishlist\n");
	printf("(2) Dropped\n");
	printf("(3) Watching\n");
	printf("(4) Finished\n");
	printf("Input using the number.\n\n");
	printf("Status: ");
	scanf("%d", &mov.status);
	switch(mov.status){
		case 1:
			mov.rating = -1;
			break; //Skip asking for rating to unwatched movies and mark it as unwatched
		case 2:
		case 3:
		case 4:
			printf("Personal Rating (0-100): ");
			scanf("%d", &mov.rating);
			break;	
	}
	fwrite(&mov, movsize, 1, fp);
	printf("\nSuccessfully recorded. Press any key to return to the main menu.");
	
	fflush(stdin);
	fclose(fp);
	getch();
}

void deletetitle(){
	char title;
	system ("cls");
	FILE *fp;
	fp = fopen("Library.DAT", "rb+");
	printf("Enter Movie Title to Delete: ");
	scanf("%s", &title);
	rewind(fp);
	
	while(fread(&mov, movsize, 1, fp) == 1){
		if(strcmp(mov.title, title) != 0){
			fwrite(&mov, movsize, 1, ft);
		}
	}
	fclose(fp);
    fclose(ft);
    remove("LIBRARY.DAT");
    fp = fopen("LIBRARY.DAT","rb+");
    printf("Delete another record(y/n)");
    fflush(stdin);
    another = getche();
}
