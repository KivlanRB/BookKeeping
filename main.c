#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

void addtitle();
void mainmenu();

// Movie/show data
struct movies{
	int index;
	char title[50];
	int episodes;
	int year;
}Movie;

// Main function
int main(){
	mainmenu();
	return 0;
}

// Main menu
void mainmenu(void){
	system("cls"); // clears screen
	int choice;
	printf("Main Menu\n(1) Library\n(2) To Watch\n(3) Add a Movie\n(4) Delete a Movie\n(5) Exit\n\n");
	
	while(1){
		printf("Enter a choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				
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
}

// Add title
void addtitle(){
	system("cls");
	FILE *sfile;
	sfile = fopen("ShowLibrary.txt", "a"); // opens txt record file
	printf("Title: ");
	fflush(stdin);
	scanf("%s", &Movie.title);
	fprintf(sfile, "%s\n\n", Movie.title);
	fclose(sfile);
	printf("Successfully recorded. Press any key to return to the main menu.");
	getch();
	mainmenu();
}
