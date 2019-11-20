#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable:4996)

// Declaration of self-defined function.

// Function of adding a booking.
void addingBook();
// Function of delete student own booking.
void deleteBookStud();
// Function of delete any booking for staff.
void deleteBookStaff();


int main(void)
{
	char selection[2], user = 'S';

	printf("-------------------------------------------\n");
	printf("%14sBOOKING MODULE\n", "");
	printf("-------------------------------------------\n\n");
	printf("-------------------------------------------\n");
	printf("| [1] Adding a booking.                   |\n");
	if (user == 'S')
	{
		printf("| [2] Delete a booking.                   |\n");
		printf("| [3] Checking specific user's booking.   |\n");
		printf("| [4] Checking facility availability.     |\n");
		printf("| [5] Display your booking.               |\n");
		printf("| [6] Exit.                               |\n");
	}
	else
	{
		printf("| [2] Delete your booking.                |\n");
		printf("| [3] Checking facility availability.     |\n");
		printf("| [4] Display your booking.               |\n");
		printf("| [5] Exit.                               |\n");
	}
	printf("-------------------------------------------\n");
	printf("Please choose a selection: ");
	for (int i = 0;;)
	{
		selection[i] = getch();
		if (i == 1)
		{
			if (selection[i] == '\n' || selection[i] == '\r')
				break;
			else if (selection[i] == '\b')
			{
				printf("\b \b");
				i--;
			}
		}
		else if (selection[i] == '6' && user != 'S')
			continue;
		else if (selection[i] != '1' && selection[i] != '2' && selection[i] != '3' && selection[i] != '4' && selection[i] != '5' && selection[i] != '6')
			continue;
		else
		{
			printf("%c", selection[i]);
			i++;
		}
	}
	printf("\n\n");
	switch (selection[0])
	{
	case '1':
		addingBook(); break;
	case '2':
		if (user == 'S');
			//deleteBookStaff();
		else
			deleteBookStud();
	case '3':
		break;
	case '4':
		break;
	case '5':
		if (user == 'S');
		else
			return 0;
		break;
	case '6':
		return 0;
	}

	system("pause");
	return 0;
}

void addingBook()
{
	char bookID[6], facID[7], userID[11];
	int bookStart, bookEnd;
	Date bookDate;

	printf("ADDING A BOOKING\n");
	printf("----------------\n");

	// 要做bookId.

	// Get input of facility ID.
	printf("Facility ID (e.g. B1116): ");
	rewind(stdin);
	scanf("%6s", facID);
	while (strlen(facID) > 5)
	{
		printf("Invalid! booking ID should contain only 5 characters.\n");
		printf("Facility ID (e.g. B1116): ");
		rewind(stdin);
		scanf("%6s", facID);
	}
	// 要check有没有这个facility.

	// Get input of booking date.
	printf("Booking Date (DD/MM/YYYY)");
	scanf("%d/%d/%d", &bookDate.day, &bookDate.month, &bookDate.year);

	// Get input of booking time.
	printf("Booking Time (In 24 hours format):\n");
	do
	{
		printf("\tFrom: ");
		rewind(stdin);
		scanf("%d", &bookStart);
		// 要加check 时间 facility file.
		while (checkTimeValid(bookStart) == 0)
		{
			printf("\tInvalid time input!\n");
			printf("\tFrom: ");
			scanf("%d", &bookStart);
		}
		printf("\tTo  : ");
		rewind(stdin);
		scanf("%d", &bookEnd);
		// 要加check 时间file.
		if (checkTimeValid(bookEnd) == 0 || bookStart >= bookEnd)
			printf("\tInvalid time input!\n");
	} while (checkTimeValid(bookEnd) == 0 || bookStart >= bookEnd);

	// 要放 userid.
}

void deleteBookStud()
{
	FILE *fBook;
	char studID[] = "19WMD09123";
		
	printf("DELETE YOUR BOOKING\n");
	printf("-------------------\n");

	fBook = fopen("BookingLog.txt", "r");

}