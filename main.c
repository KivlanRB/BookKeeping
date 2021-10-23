/*
Kelompok 5:
- Kivlan Rafly Bahmid (1906305316)
- Nadine Almira Widjanarko (1906383955)
- Anindya Fawwaz Arrazi (1906384075)

Deskripsi program:
Program ini merupakan program yang mengatur buku-buku yang ada di suatu perpustakaan.
Program ini dapat meng-index semua buku. Program ini dapat untuk menambah, dan
mengurang stok buku. Program ini juga dapat menampilkan semua buku yang ada di perpustakaan
tersebut dan juga dapat di urut sesuai nama, tahun, publisher, genre, dan lain-lain.
Program ini dapat mengetahui semua buku yang pernah ditambah di sesi-sesi sebelumnya.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MAX_SIZE 100

//declare struct
typedef struct {
	char title[40];
	char author[40];
	char publisher[50];
	int stock;
	int year;
}books;
	
books book; //Temp var for book variable
long int booksize = sizeof(book); //For file functions (needs size of struct saving)
books arrBook[MAX_SIZE]; //array to list all books
int arrSize = 0; //The size of the array (excluding extra size allocated to empty structs)

//Declare funcs
void addtitle();
void library();
void modtitle();
void closeapp();
// void viewstats();
void about();

void sortbytitle();
void sortbyauthor();
void sortbypublisher();
void sortbyyear();
void sortbystock();
void booksearch();

// Open file func
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

// Main function (main menu)
int main(){
	char choice;
	FILE *fp = openfile();
	while(fread(&book,booksize,1,fp)==1){
		arrBook[arrSize] = book;
		arrSize++;
	}
    while(1){
    	system("cls");
    	printf("BOOK KEEPER\n--------------\n");
    	printf("(1) Library\n(2) Add a Title\n(3) Stats\n(4) About\n(5) Exit\n\n");
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
				// viewstats();
				break;
			case 4:
				about();
				break;
			case 5:
				closeapp();
			default:
				printf("Invalid entry.\n\n");
				break;
		}
	}
	
	return 0;
}

//closeapp function
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
		book = arrBook[i];
		fwrite(&book, booksize, 1, fp);
	}
	printf("Sucessfully saved the library!\n");
	printf("Press any key to exit.\n");
	getch();
	exit(0);
}

//library function
void library(){
	char choice;
	int i, idChoice;
	system("cls");
	printf("LIBRARY\n\n");
    printf("ID%-3sTitle%-22sAuthor%-18sPublisher%-15sYear%-5sStock\n", "", "", "", "","");
    for(i=0;i<67;i++){
    	printf("-");
	}
	printf("\n");
    for(i=0;i<arrSize;i++){
    	/* prints all movie data from file buffer
    	This filters the rating to not display rating when its -1
    	Also replaces int formatting of status to human-readable formatting
    	It'll also put the entire list of movies into an array for modifying
    	*/
    	
    	book = arrBook[i];
    	printf("%-5d", i);
    	printf("%-20s\t%-20s\t%-20s\t%-6d\t%d", book.title, book.author, book.publisher, book.year, book.stock);
		printf("\n");
	}
	
	printf("\nPress any key to return to the main menu.\nTo edit an entry, please press the button \"E\"\nPress 1 to sort by title, 2 to sort by author, 3 to sort by publisher,\n");
	printf("4 to sort by year, and 5 to sort by stock.\nPress \"S\" to do a search.");
	choice = getch();
    if(choice == 'e' || choice == 'E'){
    	printf("\n\nThe ID to modify: ");
    	scanf("%d", &idChoice);
    	modtitle(idChoice);
	}
	else if(choice == 's' || choice == 'S'){
		booksearch();
	}
	else if(choice == '1'){
		sortbytitle();
	}
	else if(choice == '2'){
		sortbyauthor();
	}
	else if(choice == '3'){
		sortbypublisher();
	}
	else if(choice == '4'){
		sortbyyear();
	}
	else if(choice == '5'){
		sortbystock();
	}
}

/* SORT AND SEARCH */
void booksearch(){
	int i;
	char temp;
	char searchstr[50];
	system("cls");
	printf("Search by title: ");
	scanf("%c", &temp);
	scanf("%[^\n]", searchstr);

	for(i=0;i<arrSize;i++){
		if(strcmp(arrBook[i].title, searchstr) == 0){
			printf("\n%-20s\t%-20s\t%-20s\t%-6d", arrBook[i].title, arrBook[i].author, arrBook[i].publisher, arrBook[i].year);
		}
	}

	printf("\n\nNo more search results found.");
	getch();
	library();
}

void sortbytitle(){
	int i, j;
	books temp;
	for(i=0; i<arrSize; i++){
		for(j=i+1; j<arrSize; j++){
			if(strcmp(arrBook[i].title, arrBook[j].title)>0){
				temp = arrBook[i];
				arrBook[i] = arrBook[j];
				arrBook[j] = temp;
			}
		}
	}
	system("cls");
	library();
}

void sortbyauthor(){
	int i, j;
	books temp;
	for(i=0; i<arrSize; i++){
		for(j=i+1; j<arrSize; j++){
			if(strcmp(arrBook[i].author, arrBook[j].author)>0){
				temp = arrBook[i];
				arrBook[i] = arrBook[j];
				arrBook[j] = temp;
			}
		}
	}
	system("cls");
	library();
}

void sortbypublisher(){
	int i, j;
	books temp;
	for(i=0; i<arrSize; i++){
		for(j=i+1; j<arrSize; j++){
			if(strcmp(arrBook[i].publisher, arrBook[j].publisher)>0){
				temp = arrBook[i];
				arrBook[i] = arrBook[j];
				arrBook[j] = temp;
			}
		}
	}
	system("cls");
	library();
}

void sortbyyear(){
	int i, j, temp;
	for(i=0; i<arrSize-1; i++){
		for(j=0; j<arrSize-i-1; j++){
			if(arrBook[j].year > arrBook[j+1].year){
				temp = arrBook[j].year;
				arrBook[j].year = arrBook[j+1].year;
				arrBook[j+1].year = temp;
			}
		}
	}
	library();
}

void sortbystock(){
	int i, j, temp;
	for(i=0; i<arrSize-1; i++){
		for(j=0; j<arrSize-i-1; j++){
			if(arrBook[j].stock > arrBook[j+1].stock){
				temp = arrBook[j].stock;
				arrBook[j].stock = arrBook[j+1].stock;
				arrBook[j+1].stock = temp;
			}
		}
	}
	library();
}

/* ADD, MODIFY, ABOUT */
//add title function
void addtitle(){
	char temp;
	system("cls");
	
	printf("Title: ");
	scanf("%c", &temp); //Clears buffer from previous inputs
	scanf("%[^\n]", book.title);
	arrBook[arrSize] = book;
	arrSize++;
	printf("\nSuccessfully recorded movie with ID %d. Press any key to return to the main menu.", arrSize-1);
	getch();
}

//title modfication function
void modtitle(int id){
	int i;
	int choice;
	short toDelete = 0; //for marking ID for deletion
	char temp;
	
	system("cls");
	
	for(i = 0;i<arrSize;i++){
		if(i == id){
			book = arrBook[i];
			printf("(1) Title\n(2) Author\n(3) Publisher\n(4) Year\n(5) Stock\n(6) Delete\nInput any other number to go back to menu\n\nChoose what to modify: ");
			scanf("%d", &choice);
			switch(choice){
				case 1:
					printf("Title: ");
					scanf("%c", &temp); //Clears buffer from previous inputs
					scanf("%[^\n]", book.title);
					break;
				case 2:
					printf("Author: ");
					scanf("%c", &temp);
					scanf("%[^\n]", book.author);
					break;
				case 3:
					printf("Publisher: ");
					scanf("%c", &temp);
					scanf("%[^\n]", book.publisher);
					break;
				case 4:
					printf("Year: ");
					scanf("%c", &temp);
					scanf("%d", &book.year);
					break;
				case 5:
					printf("Stock: ");
					scanf("%c", &temp);
					scanf("%d", &book.stock);
					break;
				case 6:
					printf("Deleting...\n");
					toDelete = 1;
			}
			arrBook[i] = book;
		}
	}
	
	if(toDelete == 1){
		for(i = id;i<arrSize;i++){
			arrBook[i] = arrBook[i+1];
		}
		arrSize--;
	}
	printf("Done! Press any key to return to the main menu.");
	getch();
}

//view stats function
// void viewstats(){
// 	int i, freq, cwish, cdrop, cwatch, cfinish;
// 	cwish = cdrop = cwatch = cfinish = 0;
// 	float total, mean;
// 	total = freq = 0;
// 	system("cls");
// 	printf("STATS\n-----\nTotal Movies: %d\n", arrSize);
	
//     for(i=0;i<arrSize;i++){
//     	book = arrBook[i];
//     	// Untuk mean score
//     	if(book.rating != -1){
//     		total += book.rating;
//     		freq++;
// 		}
// 		switch(book.status){
// 			case 1:
// 				cwish++;
// 				break;
// 			case 2:
// 				cdrop++;
// 				break;
// 			case 3:
// 				cwatch++;
// 				break;
// 			case 4:
// 				cfinish++;
// 				break;
// 		}
// 	}
	
// 	// If library is empty
// 	if(freq == 0){
// 		mean = 0;
// 	}
// 	else{
// 		mean = total/freq;
// 	}
// 	printf("\nWishlist: %d\nDropped: %d\nWatching: %d\nFinished: %d\nMean Rating: %f\n", cwish, cdrop, cwatch, cfinish, mean);
// 	printf("\nPress any key to return to the main menu.");
// 	getch();
// }

//about us & lisence function
void about(){
	system("cls");
	printf("Insert about kita di sini");
	getch();
}
