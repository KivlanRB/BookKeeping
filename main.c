#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MAX_SIZE 100

typedef struct {
	char title[40];
	int status;
	int rating;
}movie;
	
movie mov; //Temp var for movie variable
long int movsize = sizeof(mov); //For file functions (needs size of struct saving)
movie arrMovie[MAX_SIZE]; //array to list all movies
int arrSize = 0; //The size of the array (excluding extra size allocated to empty structs)

//Declare funcs
void addtitle();
void library();
void modtitle();
void closeapp();
void viewstats();

FILE *openfile(){
	FILE *fp;
	fp = fopen("LIBRARY.DAT", "rb+");
	if(fp == NULL){ //If no file is found, create file for writing
		fp = fopen("LIBRARY.DAT","wb+");
        if(fp == NULL){ //If file still null, something horrible happened.
            printf("Cannot open file!");
            exit(1);
        }
	}
	return fp;
}

// Main function
int main(){
	char choice;
	FILE *fp = openfile();
	while(fread(&mov,movsize,1,fp)==1){
		arrMovie[arrSize] = mov;
		arrSize++;
	}
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
				viewstats();
				break;
			case 4:
				closeapp();
			default:
				printf("Invalid entry.\n\n");
				break;
		}
	}
	
	return 0;
}

void closeapp(){
	printf("Saving library...\n");
	int i;
	FILE *fp;
	fp = fopen("LIBRARY.DAT", "wb+");
	if(fp == NULL){ //If no file is found, create file for writing
        printf("Cannot open file!");
        exit(1);
        }
	for(i=0;i<arrSize;i++){
		mov = arrMovie[i];
		fwrite(&mov, movsize, 1, fp);
	}
	printf("Sucessfully saved the library!\n");
	printf("Press any key to exit...\n");
	getch();
	exit(0);
}

void library(){
	char choice;
	int i, idChoice;
	system("cls");
	
    printf("ID%-3sTitle%-35s\tStatus%-6sRating\n\n", "", "", "");
    for(i=0;i<arrSize;i++){
    	/* prints all movie data from file buffer
    	This filters the rating to not display rating when its -1
    	Also replaces int formatting of status to human-readable formatting
    	It'll also put the entire list of movies into an array for modifying
    	*/
    	
    	mov = arrMovie[i];
    	printf("%-5d", i);
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
	
	printf("\nPress any key to return to the main menu.\nTo edit an entry, please press the button \"E\"");
	choice = getch();
    if(choice == 'e' || choice == 'E'){
    	printf("\n\nThe ID to modify: ");
    	scanf("%d", &idChoice);
    	modtitle(idChoice);
	}
}

void addtitle(){
	char temp;
	system("cls");
	
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
	arrMovie[arrSize] = mov;
	arrSize++;
	printf("\nSuccessfully recorded movie with ID %d. Press any key to return to the main menu.", arrSize-1);
	getch();
}

void modtitle(int id){
	int i;
	int choice;
	short toDelete = 0; //for marking ID for deletion
	char temp;
	
	system("cls");
	
	for(i = 0;i<arrSize;i++){
		if(i == id){
			mov = arrMovie[i];
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
				case 4:
					printf("Deleting...\n");
					toDelete = 1;
			}
			arrMovie[i] = mov;
		}
	}
	
	if(toDelete == 1){
		for(i = id;i<arrSize;i++){
			arrMovie[i] = arrMovie[i+1];
		}
		arrSize--;
	}
	printf("Done! Press any key to return to menu...");
	getch();
}

void viewstats(){
	int i, freq, cwish, cdrop, cwatch, cfinish;
	cwish = cdrop = cwatch = cfinish = 0;
	float total, mean;
	total = freq = 0;
	system("cls");
	printf("Total Movies: %d\n", arrSize);
	
    for(i=0;i<arrSize;i++){
    	mov = arrMovie[i];
    	// Untuk mean score
    	if(mov.rating != -1){
    		total += mov.rating;
    		freq++;
		}
		switch(mov.status){
			case 1:
				cwish++;
				break;
			case 2:
				cdrop++;
				break;
			case 3:
				cwatch++;
				break;
			case 4:
				cfinish++;
				break;
		}
	}
	
	// If library is empty
	if(freq == 0){
		mean = 0;
	}
	else{
		mean = total/freq;
	}
	printf("\nWishlist: %d\nDropped: %d\nWatching: %d\nFinished: %d\nMean Score: %f\n", cwish, cdrop, cwatch, cfinish, mean);
	
	getch();
}

