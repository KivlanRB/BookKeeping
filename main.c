#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct {
	int id;
	char title[40];
	int status;
	int rating;
}movie;
	
movie mov; //Temp var for movie variable
long int movsize = sizeof(mov); //For file functions (needs size of struct saving)

//Declare funcs
void addtitle();
void library();
void modtitle();

// Main function
int main(){
	char another, choice;
    while(1){
    	system("cls");
    	printf("Main Menu\n(1) Library\n(2) Add a Movie\n(3) Stats\n(4) Exit\n\n");
		printf("Enter a choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				library();
				break;
			case 2:
				addtitle();
				break;
			case 3:
				
				break;
			case 4:
				exit(0);
			default:
				printf("Invalid entry.\n\n");
				break;
		}
	}
	
	return 0;
}

void library(){
	char choice;
	int idChoice;
	int i = 0;
	movie arrMovie[100];
	system("cls");
	FILE *fp;
	fp = fopen("LIBRARY.DAT","rb+");
	if(fp == NULL){ //If no file is found, create file for writing
		fp = fopen("LIBRARY.DAT","wb+");
        if(fp == NULL){ //If file still null, something horrible happened.
            printf("Cannot open file!");
            exit(1);
        }
    }
    rewind(fp);
    printf("ID%-5sTitle%-40s\tStatus%-6sRating\n\n", "", "", "");
    while(fread(&mov,movsize,1,fp)==1){
    	/* prints all movie data from file buffer
    	This filters the rating to not display rating when its -1
    	Also replaces int formatting of status to human-readable formatting
    	It'll also put the entire list of movies into an array for modifying
    	*/
    	
    	arrMovie[i] = mov;
    	i++;
    	printf("%-5d", mov.id);
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
	printf("\nPress any key to return to the main menu.\nTo edit an entry, please press the button \"E\"");
	choice = getch();
    if(choice == 'e' || choice == 'E'){
    	printf("\n\nThe ID to modify: ");
    	scanf("%d", &idChoice);
    	modtitle(idChoice, arrMovie, i);
	}
}

void addtitle(){
	char temp;
	int totalMovies;
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
    
	while(fread(&mov,movsize,1,fp)==1){
		totalMovies++;
	}
	
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
			while(1){
				printf("Personal Rating (0-100): ");
				scanf("%d", &mov.rating);
				if(mov.rating <= 100 && mov.rating >= 0){
					break;
				} else {
					printf("Rating is outside range!\nPlease retry\n\n");
				}
			}
			
			break;	
	}
	mov.id = totalMovies;
	fwrite(&mov, movsize, 1, fp);
	printf("\nSuccessfully recorded movie with ID %d. Press any key to return to the main menu.", mov.id);
	
	fflush(stdin);
	fclose(fp);
	getch();
}

void modtitle(int id, movie arrMovie[], int arrSize){
	FILE *fp;
	int i,j, choice, temp;
	
	system("cls");
	fp = fopen("LIBRARY.DAT","wb+");
    if(fp == NULL){
        printf("Cannot open file!");
        exit(1);
    }
	
	for(i = 0;i<arrSize;i++){
		mov = arrMovie[i];
		if(mov.id == id){
			printf("(1) Title\n(2) Status\n(3) Rating\n(4) Delete\nInput any other number to go back to menu\n\nChoose what to modify: ");
			scanf("%d", &choice);
			switch(choice){
				case 1:
					printf("Title: ");
					scanf("%c", &temp); //Clears buffer from previous inputs
					scanf("%[^\n]", mov.title);
					break;
				case 2:
					printf("(1) Wishlist\n(2) Dropped\n(3) Watching\n(4) Finished\nInput any other number to go back to menu\n\nChoose a number: ");
					scanf("%d", &temp);
					if(temp <= 4 && temp >= 1){
						mov.status = temp;
					}
					break;
				case 3:
					printf("Rating: ");
					scanf("%d", &temp);
					if(temp <= 100 && temp >= 0){
						mov.rating = temp;
					}
					break;
			}
		}
		fwrite(&mov, movsize, 1, fp);
	}
	fflush(stdin);
	fclose(fp);
}


