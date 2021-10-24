/*
Program Book Keeping
Proyek UTS Algoritma dan Pemrograman-02

Kelompok 5:
- Kivlan Rafly Bahmid (1906305316)
- Nadine Almira Widjanarko (1906383955)
- Anindya Fawwaz Arrazi (1906384075)

Deskripsi program:
Program ini merupakan program yang mengatur buku-buku yang ada di suatu perpustakaan.
Program ini dapat untuk menambah dan mengurang stok buku. Program ini juga dapat
menampilkan semua buku yang ada di perpustakaan tersebut dan juga dapat diurut
sesuai nama, penulis, publisher, tahun, dan stock.
*/

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 100 // 

// book struct
typedef struct {
	char title[40];
	char author[40];
	char publisher[50];
	int stock;
	int year;
}books;
	
books book; // V
books arrBook[MAX_SIZE]; // array for all books
long int booksize = sizeof(book); // size of variable book
int arrSize = 0; // size of array

// main menu functions
void addtitle();
void library();
void modtitle();
void closeapp();
void about();
void aboutlibrary();

int sumnumber(int start, int len);

// sort and search functions
void sortbytitle();
void sortbyauthor();
void sortbypublisher();
void sortbyyear();
void sortbystock();
void booksearch();

// read save file
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

/* MAIN MENU */
int main(){
	char choice;
	FILE *fp = openfile();
	while(fread(&book,booksize,1,fp)==1){
		arrBook[arrSize] = book;
		arrSize++;
	}

    while(1){
    	system("cls");
    	printf("LIBRARY BOOK KEEPER\n===================\n");
    	printf("(1) Library\n(2) Add New Title\n(3) About Library\n(4) About Program\n(5) Exit\n\n");
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
				aboutlibrary();
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

// exit program
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
	printf("Sucessfully saved!\nPress any key to exit.\n");
	getch();
	exit(0);
}

//library function
void library(){
	char choice;
	int i, idChoice;
	system("cls");
	printf("LIBRARY\n\n");
    printf("ID%-3sTitle%-22sAuthor%-18sPublisher%-15sYear%-4sStock\n", "", "", "", "","");
    for(i=0;i<94;i++){
    	printf("-");
	}
	printf("\n");
    for(i=0;i<arrSize;i++){
		// prints all books
    	book = arrBook[i];
    	printf("%-5d", i);
    	printf("%-20s\t%-20s\t%-20s\t%-6d\t%d", book.title, book.author, book.publisher, book.year, book.stock);
		printf("\n");
	}
	
	printf("\nPress any key to return to the main menu.\nPress \"E\" to edit a book.\nPress \"S\" to do a search.");
	printf("\nPress \"1\" to sort by title, \"2\" to sort by author, \"3\" to sort by publisher,\n");
	printf("\"4\" to sort by year, or \"5\" to sort by stock.\n");
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
	int i, j;
	books temp;
	for(i=0; i<arrSize-1; i++){
		for(j=0; j<arrSize-i-1; j++){
			if(arrBook[j].year > arrBook[j+1].year){
				temp = arrBook[j];
				arrBook[j] = arrBook[j+1];
				arrBook[j+1] = temp;
			}
		}
	}
	library();
}

void sortbystock(){
	int i, j;
	books temp;
	for(i=0; i<arrSize-1; i++){
		for(j=0; j<arrSize-i-1; j++){
			if(arrBook[j].stock > arrBook[j+1].stock){
				temp = arrBook[j];
				arrBook[j] = arrBook[j+1];
				arrBook[j+1] = temp;
			}
		}
	}
	library();
}

/* ADD, MODIFY, ABOUT */
// add new book title
void addtitle(){
	char temp;
	system("cls");
	
	printf("Title: ");
	scanf("%c", &temp); // clears buffer from previous inputs
	scanf("%[^\n]", book.title);
	printf("Author: ");
	scanf("%c", &temp);
	scanf("%[^\n]", book.author);
	printf("Publisher: ");
	scanf("%c", &temp);
	scanf("%[^\n]", book.publisher);
	printf("Year: ");
	scanf("%c", &temp);
	scanf("%d", &book.year);
	printf("Stock: ");
	scanf("%c", &temp);
	scanf("%d", &book.stock);
	arrBook[arrSize] = book;
	arrSize++;
	printf("\nAdded new entry with ID %d. Press any key to return to the main menu.", arrSize-1);
	getch();
}

// title modfication function
void modtitle(int id){
	int i;
	int choice, stock_choice;
	short toDelete = 0; //for marking ID for deletion
	char temp;
	
	system("cls");
	
	for(i = 0;i<arrSize;i++){
		if(i == id){
			book = arrBook[i];
			printf("(1) Title\n(2) Author\n(3) Publisher\n(4) Year\n(5) Stock\n(6) Delete\n\nChoose what to edit: ");
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
					printf("Current stock: %d\n", book.stock);
					printf("What would you like to do?\n\n(1)Edit the stock\n(2)Add the stock by 1\n(3)Remove the stock by 1\n\n");
					stock_choice = getch();
					switch(stock_choice){
						case '1':
							printf("Stock: ");
							scanf("%c", &temp);
							scanf("%d", &book.stock);
							break;
						case '2':
							book.stock++;
							break;
						case '3':
							book.stock--;
							break;
					}
					printf("The stock is now: %d\n", book.stock);
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
	printf("Saved. Press any key to return to the main menu.");
	getch();
}

void aboutlibrary(){
	int i, min = 2021;
	char booktitle[50], bookauthor[50];
	system("cls");
	printf("ABOUT LIBRARY\n\n");
	for(i=0; i<arrSize; i++){
		if(arrBook[i].year < min){
			min = arrBook[i].year;
			strcpy(booktitle, arrBook[i].title);
			strcpy(bookauthor, arrBook[i].author);
		}
	}
	printf("Total titles: %d\nTotal books in stock: %d\n", arrSize, sumnumber(0, arrSize));
	printf("The oldest title in the library is %s by %s published in %d.\n\n", booktitle, bookauthor, min);
	printf("Press any key to return to the main menu.");
	getch();
}

// recursive function to count books in stock
int sumnumber(int start, int len){
	if(start >= len){
		return 0;
	}
	return (arrBook[start].stock + sumnumber(start+1, len));
}

//about us & lisence function
void about(){
	system("cls");
	printf("Created by:\nKivlan Rafly Bahmid (1906305316)\nNadine Almira Widjanarko (1906383955)\nAnindya Fawwaz Arrazi (1906384075)\n");
	printf("as a project for the course Algoritma dan Pemrograman-02.");
	getch();
}
