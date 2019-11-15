#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable:4996)

int main()
{
	FILE *fBook;
	Date bookingDate;
	char bookID[7], userID[12], facilityID[7];
	int startTime, endTime;
	char confirm, valid;

	// Check whether if booking log is exist. If it isn't, the booking log will be created.
	if (fopen("BookingLog.txt", "r") != NULL)
		fBook = fopen("BookingLog.txt", "a");
	else
		fBook = fopen("BookingLog.txt", "w");

	do
	{
		// Get input of booking ID.
		printf("Booking ID: ");
		rewind(stdin);
		scanf("%6s", bookID);
		while (strlen(bookID) > 5)
		{
			printf("\nInvalid input! Maximum 5 characters!\n");
			printf("Booking ID: ");
			rewind(stdin);
			scanf("%6s", bookID);
		}

		// Get input of booking date.
		printf("Booking Date (DD/MM/YYYY): ");
		rewind(stdin);
		scanf("%d/%d/%d", &bookingDate.day, &bookingDate.month, &bookingDate.year);

		// Get input of booking time.
		printf("Booking Time (in 24-hour format): \n");
		printf("Start Time: ");
		rewind(stdin);
		scanf("%d%c", &startTime, &valid);
		while (startTime < 0 || startTime > 2400 || valid != '\n')
		{
			printf("Invalid input! Please enter again: \n");
			printf("Start Time: ");
			rewind(stdin);
			scanf("%d%c", &startTime, &valid);
		}
		printf("End Time: ");
		rewind(stdin);
		scanf("%d%c", &endTime, &valid);
		while (endTime < 0 || endTime > 2400 || valid != '\n' || endTime < startTime)
		{
			printf("Invalid input! Please enter again: \n");
			printf("End Time: ");
			rewind(stdin);
			scanf("%d%c", &endTime, &valid);
		}

		// Get input of user ID.
		printf("User ID: ");
		rewind(stdin);
		scanf("%11s", userID);
		while (strlen(userID) > 10)
		{
			printf("\nInvalid input! Maximum 10 character!\n");
			printf("User ID: ");
			rewind(stdin);
			scanf("%11s", userID);
		}

		// Get input of facility ID.
		printf("Facility ID: ");
		rewind(stdin);
		scanf("%6s", facilityID);
		while (strlen(facilityID) > 5)
		{
			printf("\nInvalid input! Maximum 5 character!\n");
			printf("Facility ID: ");
			rewind(stdin);
			scanf("%6s", facilityID);
		}

		// To get confirmation from user.
		printf("\n---\n");
		printf("Booking ID: %s\n", bookID);
		printf("Booking Date: %02d/%02d/%d\n", bookingDate.day, bookingDate.month, bookingDate.year);
		printf("Booking Time: %04d-%04d\n", startTime, endTime);
		printf("User ID: %s\n", userID);
		printf("Facility ID: %s\n", facilityID);

		printf("Confirm? (Y/N): ");
		rewind(stdin);
		scanf("%c%c", &confirm, &valid);
		while ((confirm != 'Y' && confirm != 'N') || valid != '\n')
		{
			printf("Invalid input! Please enter again.\n");
			printf("Confirm? (Y/N): ");
			rewind(stdin);
			scanf("%c%c", &confirm, &valid);
		}

		// Write into file if get confirmation.
		if (confirm == 'Y')
		{
			fprintf(fBook, "%s|%02d/%02d/%d|", bookID, bookingDate.day, bookingDate.month, bookingDate.year);
			fprintf(fBook, "%04d-%04d|%s|%s\n", startTime, endTime, userID, facilityID);
			printf("Booking Successfully!\n");
		}

		// Get input of start again the module.
		printf("\nStart again? (Y/N): ");
		rewind(stdin);
		scanf("%c%c", &confirm, &valid);
		while ((confirm != 'Y' && confirm != 'N') || valid != '\n')
		{
			printf("Invalid input! Please enter again.\n");
			printf("Confirm? (Y/N): ");
			rewind(stdin);
			scanf("%c%c", &confirm, &valid);
		}
		printf("---\n\n");
	} while (confirm == 'Y');

	fclose(fBook);
	system("pause");
	return 0;
}