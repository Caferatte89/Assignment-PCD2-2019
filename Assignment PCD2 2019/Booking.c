#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable:4996)

int main1()
{
	FILE *fBook;
	Date bookingDate;
	char bookID[6 + 1], userID[11 + 1], facilityID[6 + 1];

	if (fopen("BookingLog.txt", "r") != NULL)
		fBook = fopen("BookingLog.txt", "a");
	else
		fBook = fopen("BookingLog.txt", "w");

	printf("Please enter facility ID: ");
	rewind(stdin);
	scanf("%6s", bookID);
	while (strlen(bookID) > 5)
	{
		printf("\nInvalid input! Maximum 5 character!\n");
		printf("Please enter facility ID again: ");
		rewind(stdin);
		scanf("%6s", bookID);
	}


	system("pause");
	return 0;
}