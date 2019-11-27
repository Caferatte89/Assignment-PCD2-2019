#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable:4996)

// Declaration of self-defined function.

// Function of logo design.
void bookingLogo();

// Function of adding a booking.
void addingBook(char tempID[]);

// Function of checking facility availability.
void checkAvailable();

// Function of searching a booking.
void searchBook();

// Function of delete student own booking.
void deleteBookStud(char tempID[]);

// Function of delete any booking for staff.
void deleteBookStaff(char selfID[]);

// Function of displaying own booking.
void displayBook(char tempID[]);

// Struct for booking.
typedef struct {
	char bookID[6], facID[6], userID[11];
	int bookStart, bookEnd;
	Date dateBooked, dateWhenBook;
} Book;


int main(void)
{
	char selection[2], user = 'S';
	char tempID[] = "S0001";

	bookingLogo();
	while (1)
	{
		printf("%58sMENU\n", "");
		printf("%38s-------------------------------------------\n", "");
		printf("%38s| [1] Adding a booking.                   |\n", "");
		if (user == 'S')
		{
			printf("%38s| [2] Delete a booking.                   |\n", "");
			printf("%38s| [3] Search a booking.                   |\n", "");
			printf("%38s| [4] Checking facility availability.     |\n", "");
			printf("%38s| [5] Display your booking.               |\n", "");
			printf("%38s| [6] Exit.                               |\n", "");
		}
		else
		{
			printf("%38s| [2] Delete your booking.                |\n", "");
			printf("%38s| [3] Checking facility availability.     |\n", "");
			printf("%38s| [4] Display your booking.               |\n", "");
			printf("%38s| [5] Exit.                               |\n", "");
		}
		printf("%38s-------------------------------------------\n", "");
		printf("%45sPlease choose a selection: ", "");
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
			else if (selection[i] != '1' && selection[i] != '2' &&
				selection[i] != '3' && selection[i] != '4' &&
				selection[i] != '5' && selection[i] != '6')
				continue;
			else
			{
				printf("%c", selection[i]);
				i++;
			}
		}
		printf("\n\n\n");
		switch (selection[0])
		{
		case '1':
			addingBook(tempID); break;
		case '2':
			if (user == 'S')
				deleteBookStaff(tempID);
			else
				deleteBookStud(tempID);
			break;
		case '3':
			if (user == 'S')
				searchBook();
			else
				checkAvailable();
			break;
		case '4':
			if (user == 'S')
				checkAvailable();
			else
				displayBook(tempID);
			break;
		case '5':
			if (user == 'S')
				displayBook(tempID);
			else
				return 0;
			break;
		case '6':
			return 0;
		}
		printf("\n\n");
	}
}

void bookingLogo()
{
	printf("%12s ____    ___    ___   __  _  ____  ____    ____      ___ ___   ___   ___    __ __  _        ___ \n", "");
	printf("%12s|    \\  /   \\  /   \\ |  |/ ]|    ||    \\  /    |    |   |   | /   \\ |   \\  |  |  || |      /  _]\n", "");
	printf("%12s|  o  )|     ||     ||  ' /  |  | |  _  ||   __|    | _   _ ||     ||    \\ |  |  || |     /  [_ \n", "");
	printf("%12s|     ||  O  ||  O  ||    \\  |  | |  |  ||  |  |    |  \\_/  ||  O  ||  D  ||  |  || |___ |    _]\n", "");
	printf("%12s|  O  ||     ||     ||     | |  | |  |  ||  |_ |    |   |   ||     ||     ||  :  ||     ||   [_ \n", "");
	printf("%12s|     ||     ||     ||  .  | |  | |  |  ||     |    |   |   ||     ||     ||     ||     ||     |\n", "");
	printf("%12s|_____| \\___/  \\___/ |__|\\_||____||__|__||___,_|    |___|___| \\___/ |_____| \\__,_||_____||_____|\n\n", "");
}

void addingBook(char tempID[])
{
	FILE *fBook, *fNewBook, *fToCheck;
	Book getBook, tempBook;
	char temptoN[60], selection[2], checkValid, breakValid;
	char checkAPStart[5], checkAPEnd[5];
	int n, checkBookID, getFacID;

	// Set date when booking as today's date.
	getBook.dateWhenBook.day = todayDate("day");
	getBook.dateWhenBook.month = todayDate("month");
	getBook.dateWhenBook.year = todayDate("year");

	printf("ADDING A BOOKING\n");
	printf("----------------\n");

	fBook = fopen("BookingLog.txt", "r");
	if (fBook == NULL)
		fBook = fopen("BookingLog.txt", "w");
	// Generating booking ID.
	for (n = 1; !feof(fBook); n++)
	{
		fscanf(fBook, "B%d|%[^\n]\n", &checkBookID, temptoN);
		if (n != checkBookID)
			break;
	}
	sprintf(tempBook.bookID, "B%04d", n);
	strcpy(getBook.bookID, tempBook.bookID);
	printf("Booking ID: %s\n", tempBook.bookID);

	// Get input of facility ID.
	do
	{
		printf("Facility ID (e.g. A001) (-1 to cancel): ");
		rewind(stdin);
		scanf("%6s", getBook.facID);
		if (getBook.facID[0] == '-' && getBook.facID[1] == '1')
		{
			printf("Cancelled.\n");
			printf("----------");
			fclose(fBook);
			return;
		}
		getBook.facID[0] = toupper(getBook.facID[0]);
		if (strlen(getBook.facID) > 4)
			printf("Invalid! Facility ID should contain only 4 characters.\n\n");
		else
		{
			fToCheck = fopen("facilitylist.txt", "r");
			while (!feof(fToCheck))
			{
				fscanf(fToCheck, "%*[^|]|%d|%*[^\n]\n", &getFacID);
				sprintf(tempBook.facID, "A%03d", getFacID);
				if (strcmp(tempBook.facID, getBook.facID) == 0)
					break;
			}
			if (strcmp(tempBook.facID, getBook.facID) != 0)
				printf("Invalid! The facility cannot be found.\n\n");
			fclose(fToCheck);
		}
	} while (strlen(getBook.facID) > 4 || strcmp(tempBook.facID, getBook.facID) != 0);

	// Get input of booking date.
	do
	{
		printf("Booking Date (DD/MM/YYYY): ");
		rewind(stdin);
		scanf("%d/%d/%d%c", &getBook.dateBooked.day, &getBook.dateBooked.month, &getBook.dateBooked.year, &checkValid);
		if (checkValid != '\n')
			printf("Invalid input! Please enter again.\n\n");
		else if (getBook.dateBooked.day <= todayDate("day") + 1 || getBook.dateBooked.month < todayDate("month")
			|| getBook.dateBooked.year < todayDate("year"))
			printf("Invalid input! The Booking Date should at least one day in advance!\n\n");
	} while (checkValid != '\n' || getBook.dateBooked.day <= todayDate("day") + 1
		|| getBook.dateBooked.month < todayDate("month")
		|| getBook.dateBooked.year < todayDate("year"));


	// Get input of booking time.
	do
	{
		getBook.bookEnd = getBook.bookStart = -1024;
		breakValid = 'Y';
		printf("Booking Time (In 24 hours format):\n");
		printf("\tEnter -1 to cancel the booking.\n");
		do
		{
			printf("\tFrom: ");
			rewind(stdin);
			scanf("%d", &getBook.bookStart);
			if (getBook.bookStart == -1)
			{
				printf("Cancelled.\n");
				printf("----------");
				return;
			}
			if (checkTimeValid(getBook.bookStart) == 0)
				printf("\tInvalid time input!\n\n");
		} while (checkTimeValid(getBook.bookStart) == 0);

		printf("\tTo  : ");
		rewind(stdin);
		scanf("%d", &getBook.bookEnd);
		if (checkTimeValid(getBook.bookEnd) == 0 || getBook.bookStart >= getBook.bookEnd)
		{
			printf("\tInvalid time input!\n\n");
			breakValid = 'N';
		}
		if (breakValid == 'Y')
		{
			fToCheck = fopen("facilitylist.txt", "r");
			while (!feof(fToCheck))
			{
				fscanf(fToCheck, "%*[^|]|%d|%*[^|]|%*[^|]|%*[^|]|%d%[^t]to %d%[^,],%*[^\n]\n", &getFacID,
					&tempBook.bookStart, checkAPStart, &tempBook.bookEnd, checkAPEnd);
				sprintf(tempBook.facID, "A%03d", getFacID);
				if (strcmp(tempBook.facID, getBook.facID) == 0)
					break;
			}

			if (strcmp(checkAPStart, "a.m.") == 0)
				tempBook.bookStart *= 100;
			else
				tempBook.bookStart = (12 + tempBook.bookStart) * 100;

			if (strcmp(checkAPEnd, "a.m.") == 0)
				tempBook.bookEnd *= 100;
			else
				tempBook.bookEnd = (12 + tempBook.bookEnd) * 100;

			if (getBook.bookStart < tempBook.bookStart || getBook.bookEnd > tempBook.bookEnd)
			{
				printf("Invalid input! Booking time should within range of facility open time! (%04d - %04d)\n\n", tempBook.bookStart, tempBook.bookEnd);
				breakValid = 'N';
			}
		}
		if (breakValid == 'Y')
		{
			rewind(fBook);
			while (!feof(fBook))
			{
				fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", tempBook.bookID,
					&tempBook.dateWhenBook.day, &tempBook.dateWhenBook.month, &tempBook.dateWhenBook.year,
					&tempBook.dateBooked.day, &tempBook.dateBooked.month, &tempBook.dateBooked.year,
					&tempBook.bookStart, &tempBook.bookEnd, tempBook.userID, tempBook.facID);
				if (!((getBook.bookStart < tempBook.bookStart && getBook.bookEnd <= tempBook.bookStart
					&& getBook.bookStart < tempBook.bookEnd && getBook.bookEnd < tempBook.bookEnd) ||
					(getBook.bookStart > tempBook.bookStart && getBook.bookEnd > tempBook.bookStart
						&& getBook.bookStart >= tempBook.bookEnd && getBook.bookEnd > tempBook.bookEnd)) && strcmp(tempBook.facID, getBook.facID) == 0 &&
					getBook.dateBooked.day == tempBook.dateBooked.day && getBook.dateBooked.month == tempBook.dateBooked.month &&
					getBook.dateBooked.year == tempBook.dateBooked.year)
				{
					printf("\tInvalid input! The booking time %04d-%04d has been booked.\n\n", tempBook.bookStart, tempBook.bookEnd);
					breakValid = 'N';
					break;
				}
			}
		}
	} while (breakValid != 'Y');

	printf("----------------\n\n");
	printf("%6sYOUR BOOKING\n", "");
	printf("------------------------\n");
	printf("Booking ID  : %s\n", getBook.bookID);
	printf("Facility ID : %s\n", getBook.facID);
	printf("Booking Date: %02d/%02d/%d\n", getBook.dateBooked.day, getBook.dateBooked.month, getBook.dateBooked.year);
	printf("Booking Time: %04d-%04d\n", getBook.bookStart, getBook.bookEnd);
	printf("------------------------\n");
	printf("Confirm? (Type Y for yes and N for no): ");
	// To let user only input Y and N.
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
		else if (selection[i] != 'y' && selection[i] != 'Y' && selection[i] != 'n' && selection[i] != 'N')
			continue;
		else
		{
			printf("%c", selection[i]);
			i++;
		}
	}
	if (toupper(selection[0]) == 'Y')
	{
		printf("\nAdding...\n");
		fNewBook = fopen("tempBook.txt", "w");
		rewind(fBook);
		for (int x = 1; x < n; x++)
		{
			fscanf(fBook, "B%d|%[^\n]\n", &checkBookID, temptoN);
			fprintf(fNewBook, "B%04d|%s\n", checkBookID, temptoN);
		}
		fprintf(fNewBook, "%s|%02d/%02d/%d|%02d/%02d/%d|%04d-%04d|%s|%s\n", getBook.bookID,
			getBook.dateWhenBook.day, getBook.dateWhenBook.month, getBook.dateWhenBook.year,
			getBook.dateBooked.day, getBook.dateBooked.month, getBook.dateBooked.year,
			getBook.bookStart, getBook.bookEnd, tempID, getBook.facID);
		while (fscanf(fBook, "B%d|%[^\n]\n", &checkBookID, temptoN) != EOF)
		{
			fprintf(fNewBook, "B%04d|%s\n", checkBookID, temptoN);
		}

		// Close the file and rename the temp file into booking log file.
		fclose(fBook);
		fclose(fNewBook);
		system("del /f BookingLog.txt");
		system("ren tempBook.txt BookingLog.txt");

		printf("Added Successfully.\n");
		printf("-------------------");
	}
	else
	{
		printf("\nCancelled.\n");
		printf("----------");
	}
}

void checkAvailable()
{
	FILE *fBook, *fToCheck;
	char tempFacID[5], inputFacID[5], checkAPStart[5], checkAPEnd[5];
	int getFacID, timeStart, timeEnd, bookStart, bookEnd, counter;

	printf("CHECKING FACILITY AVAILBILITY\n");
	printf("-----------------------------\n");

	do
	{
		printf("Facility ID (e.g. A001) (-1 to cancel): ");
		rewind(stdin);
		scanf("%6s", inputFacID);
		if (inputFacID[0] == '-' && inputFacID[1] == '1')
		{
			printf("Cancelled.\n");
			printf("----------");
			return;
		}
		inputFacID[0] = toupper(inputFacID[0]);
		if (strlen(inputFacID) > 4)
			printf("Invalid! Facility ID should contain only 4 characters.\n\n");
		else
		{
			fToCheck = fopen("facilitylist.txt", "r");
			while (!feof(fToCheck))
			{
				fscanf(fToCheck, "%*[^|]|%d|%*[^|]|%*[^|]|%*[^|]|%d%[^t]to %d%[^,],%*[^\n]\n", &getFacID, &timeStart, checkAPStart, &timeEnd, checkAPEnd);
				sprintf(tempFacID, "A%03d", getFacID);
				if (strcmp(tempFacID, inputFacID) == 0)
					break;
			}
			if (strcmp(tempFacID, inputFacID) != 0)
				printf("Invalid! The facility cannot be found.\n\n");
			fclose(fToCheck);
		}
	} while (strlen(inputFacID) > 4 || strcmp(tempFacID, inputFacID) != 0);

	if (strcmp(checkAPStart, "a.m.") == 0)
		timeStart *= 100;
	else
		timeStart = (12 + timeStart) * 100;

	if (strcmp(checkAPEnd, "a.m.") == 0)
		timeEnd *= 100;
	else
		timeEnd = (12 + timeEnd) * 100;

	printf("\nThe Facility starts at %04d until %04d.\n", timeStart, timeEnd);
	printf("------------\n");
	printf("Booked Time\n");
	printf("------------\n");

	fBook = fopen("BookingLog.txt", "r");
	counter = 0;
	while (!feof(fBook))
	{
		fscanf(fBook, "%*[^|]|%*[^|]|%*[^|]|%d-%d|%*[^|]|%[^\n]\n", &bookStart, &bookEnd, tempFacID);
		if (strcmp(tempFacID, inputFacID) == 0)
		{
			counter++;
			printf("%d. %04d-%04d\n", counter, bookStart, bookEnd);
		}
	}
	printf("------------\n");
	printf("%d record(s) found.\n", counter);
	system("pause");
}

void searchBook()
{
	FILE *fBook;
	Book readBook;
	int i = 0, counter = 0, valid;
	char selection[2], ID[12];

	printf("SEARCH A BOOKING\n");
	printf("----------------\n");

	printf("-----------------------\n");
	printf("| [1] By User ID.     |\n");
	printf("| [2] By Booking ID.  |\n");
	printf("| [3] By Facility ID. |\n");
	printf("-----------------------\n");
	printf("Please choose a selection to search: ");

	// To let user only input 1, 2 and 3.
	while (1)
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
		else if (selection[i] != '1' && selection[i] != '2' && selection[i] != '3')
			continue;
		else
		{
			printf("%c", selection[i]);
			i++;
		}
	}

	switch (selection[0])
	{
	case '1':
		do
		{
			printf("\nUser ID: ");
			scanf("%11s", ID);
			while (strlen(ID) > 10)
				printf("Invalid input! User ID should only contain 10 characters.\n");
		} while (strlen(ID) > 10);
		break;
	case '2':
		do
		{
			printf("\nBooking ID: ");
			scanf("%6s", ID);
			while (strlen(ID) > 5)
				printf("Invalid input! Booking ID should only contain 5 characters.\n");
		} while (strlen(ID) > 5);
		break;
	case '3':
		do
		{
			printf("\nFacility ID: ");
			scanf("%6s", ID);
			while (strlen(ID) > 5)
				printf("Invalid input! Facility ID should only contain 5 characters.\n");
		} while (strlen(ID) > 5);
	}

	for (int i = 0; i < strlen(ID); i++)
		ID[i] = toupper(ID[i]);

	// Open the booking log file and check whether it is exist.
	fBook = fopen("BookingLog.txt", "r");
	if (fBook == NULL)
	{
		printf("The file cannot open successfully! Perhaps no one was booking before?\n");
		return;
	}

	printf("\n%-15s%-20s%-16s%-15s%-16s%s\n", "Booking ID", "Date of Booking", "Date Booked", "   Time   ", "  User ID ", "Facility ID");
	printf("%-15s%-20s%-16s%-15s%-16s%s\n", "----------", "---------------", "-----------", "----------", "-----------", "-----------");
	while (!feof(fBook))
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
			&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
			&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
			&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
		switch (selection[0])
		{
		case '1':
			valid = strcmp(readBook.userID, ID); break;
		case '2':
			valid = strcmp(readBook.bookID, ID); break;
		case '3':
			valid = strcmp(readBook.facID, ID); break;
		}
		if (valid == 0)
		{
			printf("%-15s%02d/%02d/%d%10s%02d/%02d/%d%6s%04d-%04d%6s%-16s%s\n", readBook.bookID,
				readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
				"", readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
				"", readBook.bookStart, readBook.bookEnd, "", readBook.userID, readBook.facID);
			counter++;
		}
	}
	printf("-----\n%d record(s) found.\n", counter);
	fclose(fBook);
	system("pause");
	return;
}

void deleteBookStud(char tempID[])
{
	FILE *fBook, *fNewBook;
	Book readBook;
	int counter;
	char tempBookID[7], selection[2];
		
	printf("DELETE YOUR BOOKING\n");
	printf("-------------------\n\n");

	// Open the booking log file and check whether it is exist.
	fBook = fopen("BookingLog.txt", "r");
	if (fBook == NULL)
	{
		printf("The file cannot open successfully! Perhaps no one was booking before?\n");
		return;
	}

	printf("%-15s%-20s%-16s%-15s%s\n", "Booking ID", "Date of Booking", "Date Booked", "   Time  ", "Facility ID");
	printf("%-15s%-20s%-16s%-15s%s\n", "----------", "---------------", "-----------", "---------", "-----------");
	counter = 0;
	while (!feof(fBook))
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
			&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
			&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
			&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
		if (strcmp(readBook.userID, tempID) == 0)
		{
			printf("%-15s%02d/%02d/%d%10s%02d/%02d/%d%6s%04d-%04d%6s%s\n", readBook.bookID,
				readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
				"", readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
				"", readBook.bookStart, readBook.bookEnd, "", readBook.facID);
			counter++;
		}
	}
	printf("-----\n%d record(s) found.\n", counter);

	printf("Please enter booking ID you wanted to delete (-1 to cancel): ");
	do
	{
		do
		{
			rewind(stdin);
			scanf("%6s", tempBookID);
			tempBookID[0] = toupper(tempBookID[0]);
			if (tempBookID[0] == '-' && tempBookID[1] == '1')
			{
				printf("Cancelled.\n");
				printf("----------");
				return;
			}
			if (strlen(tempBookID) != 5)
				printf("Invalid input! Please enter again: ");
		} while (strlen(tempBookID) != 5);

		// Open a new file to fill in the data except that needed to delete.
		fNewBook = fopen("tempBook.txt", "w");
		rewind(fBook);
		while (!feof(fBook))
		{
			fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
				&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
				&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
				&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
			if (strcmp(tempBookID, readBook.bookID) == 0 && strcmp(tempID, readBook.userID) == 0)
				break;
			else
				fprintf(fNewBook, "%s|%02d/%02d/%d|%02d/%02d/%d|%04d-%04d|%s|%s\n", readBook.bookID,
					readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
					readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
					readBook.bookStart, readBook.bookEnd, readBook.userID, readBook.facID);
		}
		if (feof(fBook) && strcmp(tempBookID, readBook.bookID) != 0)
		{
			printf("Invalid input! The Booking ID %s is not found in the record.\n", tempBookID);
			fclose(fNewBook);
			printf("Please type again: ");
		}
		else
		{
			printf("Confirm? (Type Y for yes and N for no): ");
			// To let user only input Y and N.
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
				else if (selection[i] != 'y' && selection[i] != 'Y' && selection[i] != 'n' && selection[i] != 'N')
					continue;
				else
				{
					printf("%c", selection[i]);
					i++;
				}
			}
		}
		if (toupper(selection[0]) == 'N')
		{
			fclose(fNewBook);
			system("del /f tempBook.txt");
			printf("\nCancelled.\n");
			printf("----------");
			return;
		}
	} while (feof(fBook) && strcmp(tempBookID, readBook.bookID) != 0);
	printf("\nDeleting...");
	while (!feof(fBook))
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
			&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
			&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
			&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
		fprintf(fNewBook, "%s|%02d/%02d/%d|%02d/%02d/%d|%04d-%04d|%s|%s\n", readBook.bookID,
			readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
			readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
			readBook.bookStart, readBook.bookEnd, readBook.userID, readBook.facID);
	}

	// Close the file and rename the temp file into booking log file.
	fclose(fBook);
	fclose(fNewBook);
	system("del /f BookingLog.txt");
	system("ren tempBook.txt BookingLog.txt");

	printf("\nDelete successfully.");
	printf("\n--------------------");
}

void deleteBookStaff(char selfID[])
{
	FILE *fBook, *fNewBook;
	Book readBook;
	int counter;
	char tempBookID[7], selection[2], tempID[12];

	printf("DELETE A BOOKING\n");
	printf("----------------\n");

	do
	{
		printf("Please enter user ID (Enter SELF for your own ID): ");
		rewind(stdin);
		scanf("%11s", tempID);
		if (strlen(tempID) > 10)
			printf("Invalid input! The user ID should contain within 10 characters!\n");
	} while (strlen(tempID) > 10);

	// Change ID to own ID if the user type "SELF".
	for (int i = 0; i < strlen(tempID); i++)
		tempID[i] = toupper(tempID[i]);
	if (strcmp("SELF", tempID) == 0)
		strcpy(tempID, selfID);

	// Open the booking log file and check whether it is exist.
	fBook = fopen("BookingLog.txt", "r");
	if (fBook == NULL)
	{
		printf("The file cannot open successfully! Perhaps no one was booking before?\n");
		return;
	}

	printf("\n%-15s%-20s%-16s%-15s%s\n", "Booking ID", "Date of Booking", "Date Booked", "   Time  ", "Facility ID");
	printf("%-15s%-20s%-16s%-15s%s\n", "----------", "---------------", "-----------", "----------", "-----------");
	counter = 0;
	while (!feof(fBook))
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
			&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
			&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
			&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
		if (strcmp(readBook.userID, tempID) == 0)
		{
			printf("%-15s%02d/%02d/%d%10s%02d/%02d/%d%6s%04d-%04d%6s%s\n", readBook.bookID,
				readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
				"", readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
				"", readBook.bookStart, readBook.bookEnd, "", readBook.facID);
			counter++;
		}
	}
	printf("-----\n%d record(s) found.\n", counter);

	if (counter == 0)
	{
		printf("Process terminated because no records found.\n");
		system("pause");
		return;
	}

	printf("Please enter booking ID you wanted to delete (-1 to cancel): ");
	do
	{
		do
		{
			rewind(stdin);
			scanf("%6s", tempBookID);
			tempBookID[0] = toupper(tempBookID[0]);
			if (tempBookID[0] == '-' && tempBookID[1] == '1')
			{
				printf("\nCancelled.\n");
				printf("----------");
				return;
			}
			if (strlen(tempBookID) != 5)
				printf("Invalid input! Please enter again: ");
		} while (strlen(tempBookID) != 5);

		// Open a new file to fill in the data except that needed to delete.
		fNewBook = fopen("tempBook.txt", "w");
		rewind(fBook);
		while (!feof(fBook))
		{
			fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
				&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
				&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
				&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
			if (strcmp(tempBookID, readBook.bookID) == 0 && strcmp(tempID, readBook.userID) == 0)
				break;
			else
				fprintf(fNewBook, "%s|%02d/%02d/%d|%02d/%02d/%d|%04d-%04d|%s|%s\n", readBook.bookID,
					readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
					readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
					readBook.bookStart, readBook.bookEnd, readBook.userID, readBook.facID);
		}
		if (feof(fBook) && strcmp(tempBookID, readBook.bookID) != 0)
		{
			printf("Invalid input! The Booking ID %s is not found in the record.\n", tempBookID);
			fclose(fNewBook);
			printf("Please type again: ");
		}
		else
		{
			printf("Confirm? (Type Y for yes and N for no): ");
			// To let user only input Y and N.
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
				else if (selection[i] != 'y' && selection[i] != 'Y' && selection[i] != 'n' && selection[i] != 'N')
					continue;
				else
				{
					printf("%c", selection[i]);
					i++;
				}
			}
		}
		if (toupper(selection[0]) == 'N')
		{
			fclose(fNewBook);
			system("del /f tempBook.txt");
			printf("\nCancelled.\n");
			printf("----------");
			return;
		}
	} while (feof(fBook) && strcmp(tempBookID, readBook.bookID) != 0);
	printf("\nDeleting...");
	while (!feof(fBook))
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
			&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
			&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
			&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
		fprintf(fNewBook, "%s|%02d/%02d/%d|%02d/%02d/%d|%04d-%04d|%s|%s\n", readBook.bookID,
			readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
			readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
			readBook.bookStart, readBook.bookEnd, readBook.userID, readBook.facID);
	}

	// Close the file and rename the temp file into booking log file.
	fclose(fBook);
	fclose(fNewBook);
	system("del /f BookingLog.txt");
	system("ren tempBook.txt BookingLog.txt");

	printf("\nDelete successfully.");
	printf("\n--------------------");
}

void displayBook(char tempID[])
{
	FILE *fBook;
	Book readBook;
	int counter = 0;

	printf("DISPLAYING YOUR BOOKING\n");
	printf("-----------------------\n\n");

	// Open the booking log file and check whether it is exist.
	fBook = fopen("BookingLog.txt", "r");
	if (fBook == NULL)
	{
		printf("The file cannot open successfully! Perhaps no one was booking before?\n");
		return;
	}

	printf("%-15s%-20s%-16s%-15s%s\n", "Booking ID", "Date of Booking", "Date Booked", "   Time   ", "Facility ID");
	printf("%-15s%-20s%-16s%-15s%s\n", "----------", "---------------", "-----------", "----------", "-----------");
	while (!feof(fBook))
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", readBook.bookID,
			&readBook.dateWhenBook.day, &readBook.dateWhenBook.month, &readBook.dateWhenBook.year,
			&readBook.dateBooked.day, &readBook.dateBooked.month, &readBook.dateBooked.year,
			&readBook.bookStart, &readBook.bookEnd, readBook.userID, readBook.facID);
		if (strcmp(readBook.userID, tempID) == 0)
		{
			printf("%-15s%02d/%02d/%d%10s%02d/%02d/%d%6s%04d-%04d%6s%s\n", readBook.bookID,
				readBook.dateWhenBook.day, readBook.dateWhenBook.month, readBook.dateWhenBook.year,
				"", readBook.dateBooked.day, readBook.dateBooked.month, readBook.dateBooked.year,
				"", readBook.bookStart, readBook.bookEnd, "", readBook.facID);
			counter++;
		}
	}
	printf("-----\n%d record(s) found.\n", counter);
	fclose(fBook);
	system("pause");
	return;
}