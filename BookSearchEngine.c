#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{          
	char book[100];
	char authors[350];
	int year;
	char available[50];
}data;

typedef struct NODE{      
	data d;
	struct NODE* next;
}NODE;

void AvailableSearch(NODE * first, char* status);                     
void TitleSearch(NODE * first, char* song_t);            
void RangeYearsSearch(NODE * first, int from, int to);   
void YearSearch(NODE * first, int year);                 
void AuthorSearch(NODE * first, char* art);
void printList(NODE *first);
//25
NODE* SortedMergeYears(NODE* a, NODE* b);
void FrontBackSplit(NODE* source, NODE** frontRef, NODE** backRef);
void MergeSortYears(NODE** headRef); 
void MergeSortAlphabetically(NODE** headRef);
NODE* SortedAlphabetically(NODE *a, NODE *b);

char books[20] = "BOOK";
char authour[20] = "AUTHORS";
char dated[20] = "DATE";
char occupied[20] = "STATUS";
int choice;



int main()
{
	FILE *fp;


	char buffer[200];
	char arr[50], arr_two[50], arr_three[50];
	int yearsearch, from, to;
	char input;
	char *title, *writer, *vacant;
	int date;
	NODE *first = NULL;
	NODE *temp, *p, *pre;
	char filename[30] = "Project.txt"; 
	int linecount = 0;

	fp = fopen(filename, "r");   
	if (fp == NULL)
	{
		printf("file can't open");
	}

	while (fgets(buffer, sizeof(buffer), fp) != NULL) 
	{
		title = strtok(buffer, ";");   
		writer = strtok(NULL, ";");   
		date = atoi(strtok(NULL, ";"));
		vacant = strtok(NULL, ";");

		temp = (NODE*)malloc(sizeof(NODE));
		strcpy(temp->d.book, title);
		strcpy(temp->d.authors, writer);   
		temp->d.year = date;               
		strcpy(temp->d.available, vacant);
		temp->next = NULL;
		pre = first;
		p = first;
		while (p != NULL)
		{
			pre = p;
			p = p->next;
		}
		if (pre != NULL)
			pre->next = temp;
		else
			first = temp;
	}



	do
	{
		printf("\nMenu:\n");
		printf("1. Search Book Title\n");
		printf("2. Search Book Author(s)\n");
		printf("3. Search Book Year\n");
		printf("4. Search Book Range Years\n");
		printf("5. Search Book Availability\n");
		printf("6. Sort Book by year\n");
		printf("7. Sort Book by alphabetically\n");
		printf("8. Quit\n");

		printf("\nYourChoice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Put the title of the Book: \n");
			scanf(" %[^\n]s", arr);
			TitleSearch(first, arr);
			break;
		case 2:
			printf("Put the name of the authors: \n");
			scanf(" %[^\n]s", arr_two);        
			AuthorSearch(first, arr_two);
			break;
		case 3:
			printf("Put the year of the book: \n"); 
			scanf("%d", &yearsearch);
			YearSearch(first, yearsearch);
			break;
		case 4:
			printf("Put the range of the years of the book you want to search: "); 
			printf("\nFrom year:");
			scanf("%d", &from);
			printf("\nTo year:");
			scanf("%d", &to);
			RangeYearsSearch(first, from, to);
			break;
		case 5:
			printf("Type Available: \n");
			scanf(" %[^\n]s", &arr_three);
			printf("Available Books: ");   
			AvailableSearch(first, arr_three);
			break;
		 case 6:
			MergeSortYears(&first); 
			printList(first);
			break; 
		case 7:
			MergeSortAlphabetically(&first);
			printList(first);
			break; 
		case 8: printf("Goodbye\n");
			break;
		default: printf("Wrong Choice. Enter again\n");
			break;
		}

	} while (choice != 8);

	fclose(fp);
	return 0;
}



void AuthorSearch(NODE * first, char* art)  
{
	NODE *p;
	int i = 0;
	p = first;
	printf("\n%-34s | %-15s | %-5d | %-10s\n", books, authour, dated, occupied);
	printf("-------------------------------------------------------------------------\n");
	while (p != NULL)
	{
		if (strcmp(p->d.authors, art) == 0)
		{
			printf("%-15s | %-15s | %-5d | %-10s\n", p->d.book, p->d.authors, p->d.year, p->d.available);
		}
		i++;
		p = p->next;
	}
	if (i == 0)
		printf("Could not find that book");
}

void YearSearch(NODE * first, int year) 
{
	NODE *p;
	int i = 0;
	p = first;
	printf("\n%-34s | %-15s | %-5d | %-10s\n", books, authour, dated, occupied);
	printf("-------------------------------------------------------------------------\n");
	while (p != NULL)
	{
		if (p->d.year == year)
		{
			printf("%-15s | %-15s | %-5d | %-10s\n", p->d.book, p->d.authors, p->d.year, p->d.available);
		}
		i++;
		p = p->next;
	}
}

void RangeYearsSearch(NODE * first, int from, int to)  
{
	NODE *p;
	int i = 0;
	p = first;
	printf("%\n-34s | %-15s | %-5d | %-10s\n", books, authour, dated, occupied);
	printf("-------------------------------------------------------------------------\n");
	while (p != NULL)
	{
		if (p->d.year >= from && p->d.year <= to)
			printf("%-15s | %-15s | %-5d | %-10s \n", p->d.book, p->d.authors, p->d.year, p->d.available);
		i++;
		p = p->next;
	}
}



void TitleSearch(NODE * first, char* book_t)  
{
	NODE *p;
	int i = 0;
	p = first;
	printf("%\n-34s | %-15s | %-5d | %-10s\n", books, authour, dated, occupied);
	printf("-------------------------------------------------------------------------\n");
	while (p != NULL)
	{

		if (strcmp(p->d.book, book_t) == 0)
		{
			printf("%-15s | %-15s | %-5d | %-10s \n", p->d.book, p->d.authors, p->d.year, p->d.available);
			i++;
		}
		p = p->next;
	}
	if (i == 0)
		printf("Could not find that book");
}

void AvailableSearch(NODE * first, char* status)  
{
	NODE *p;
	int i = 0;
	p = first;
	printf("%\n-34s | %-15s | %-5d | %-10s\n", books, authour, dated, occupied);
	printf("-------------------------------------------------------------------------\n");
	while (p != NULL)
	{
		if (strcmp(p->d.available, status) == 0)
		{
			printf("%-15s | %-15s | %-5d | %-10s \n", p->d.book, p->d.authors, p->d.year, p->d.available);
		}
		i++;
		p = p->next;
	}
	return;
}

void MergeSortYears(NODE** headRef)
{
	NODE* head = *headRef;
	NODE* a;
	NODE* b;

	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	FrontBackSplit(head, &a, &b);
	MergeSortYears(&a);
	MergeSortYears(&b);

	*headRef = SortedMergeYears(a, b);
}

void MergeSortAlphabetically(NODE** headRef)
{
	NODE* head = *headRef;
	NODE* a;
	NODE* b;

	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	FrontBackSplit(head, &a, &b);
	MergeSortAlphabetically(&a);
	MergeSortAlphabetically(&b);

	*headRef = SortedAlphabetically(a, b);
}

NODE* SortedMergeYears(NODE *a, NODE *b)
{
	NODE* result = NULL;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;

	if (a->d.year <= b->d.year)
	{
		result = a;
		result->next = SortedMergeYears(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMergeYears(a, b->next);
	}
	return result;
}

NODE* SortedAlphabetically(NODE *a, NODE *b)
{
	NODE* result = NULL;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;

	if (strcmp(a->d.book, b->d.book)==-1) // -1
	{
		result = a;
		result->next = SortedAlphabetically(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedAlphabetically(a, b->next);
	}
	return result;
}

void FrontBackSplit(NODE* source, NODE** frontRef, NODE** backRef)
{
	NODE* fast;
	NODE* slow;
	if (source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
} 




void printList(NODE *first)  
{
	printf("BOOK     |     AUTHOR    | YEAR  |    STATUS   \n");
	while (first != NULL)
	{
		printf("%-15s | %-15s | %-5d | %-10s\n", first->d.book, first->d.authors, first->d.year, first->d.available);
		first = first->next;
	}
	
}




