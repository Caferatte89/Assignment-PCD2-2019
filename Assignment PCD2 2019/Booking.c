#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <conio.h>
#include <string.h>
#include "Header.h"
#pragma warning(disable:4996)

// Global struct declaration.
typedef struct
{
	char bookID[6], facID[6], userID[11];
	int startTime, endTime;
	Date dateBooked, dateWhenBook;
} BookData;
typedef struct
{
	char facCode;
	char facName[30];
	int facID;
	int startTime, endTime;
	int startWeek, endWeek;
} FacData;

// Various function declaration.
// Main functions declaration.
void mainBookingLogo();
void mainBookingMenu(char userType);

// Adding booking functions declaration.
void addingBook(char userID[]);
void addFacType(char* facName, char *confirm);
void addFacDate(int* day, int* month, int* year);
void addFacTime(int* getConfirm, BookData* BookData, int bookCount, Date tempDate, char* facName, char* facCode, int* startTime, int* endTime, char* facID);

// Deleting booking functions declaration.
void deleteBook(char password[], char userID[], char userType);
void deleteBookMenu();
void deleteBookMenuStaff();
int deleteFacType(char *showAll, char *getConfirm);
void deleteFacDate(int* startDay, int* startMonth, int* startYear, int* endDay, int* endMonth, int* endYear, char *getConfirm);
void deleteFacTime(int* startTime, int* endTime, char *getConfirm);

// Displaying booking functions declaration.
void displayBook(char userID[], char userType);
void displayBookMenu(char userType);
// Check filter condition for displaying booking.
int displayBookCheckFilterCondition(int choiceSelect[], char userID[], BookData bookData,
	char* tempName, char* tempFacID, char* showAll, Date* startDate, Date* endDate, int* startTime, int* endTime, char checkUserID[], char userType);

// Modifying booking functions declaration.
void modifyBook(char password[], char userID[], char userType);
void modifyBookMenu();
int modifyFacType(char *confirm, BookData* bookData, int* bookCount, Date* bookedDate, int* startTime, int* endTime, char* bookedFacID);
void modifyFacDate(char* confirm, BookData* bookData, int* bookCount, Date* bookedDate, int* startTime, int* endTime, char* bookFacID);
void modifyFacTime(char* confirm, BookData* BookData, int bookCount, Date tempDate, int* startTime, int* endTime, char* facID);

// To let user choose by just pressing up and down button. Maximum 10 digits for numbering selection.
int yearSelect(int start, int min, int max);
int monthSelect(int start, int min, int max, char lastChar);
int daySelect(int start, int min, int max);
int timeSelect(int start, int min, int max);
void passwordInput(char* input, int size);
// To get confirmation from user.
char confirmSelect(char X, char Y);
char confirmSelectWithX();

// To check date range.
int checkDateRange(Date startRange, Date endRange, Date bookDate);

int writeLog(FILE** _Stream, char const* const _Format, ...);


void BookingMod(char userType, char userID[], char password[])
{
	char again;
	int choice;

	// Show booking logo.
	mainBookingLogo();

	while (1)
	{
		// Calling booking menu function list the selection.
		mainBookingMenu(userType);
		// Get input of selection.
		printf("%45sPlease choose a selection: ", "");
		choice = numSelect(1, 1, 5);
		printf("\n\n");

		// Calling various functions for user inputed.
		do
		{
			switch (choice)
			{
			case 1:
				addingBook(userID);
				break;
			case 2:
				modifyBook(password, userID, userType);
				break;
			case 3:
				deleteBook(password, userID, userType);
				break;
			case 4:
				displayBook(userID, userType);
				break;
			case 5:
				return;
			}

			printf("\n\t------\n\tDo you want to execute again? (Y=yes, N=no): ");
			again = confirmSelect('Y', 'N');
			printf("\n\n");
		} while (again == 'Y');
	}
}
void mainBookingLogo()
{
	printf("%12s ____    ___    ___   __  _  ____  ____    ____      ___ ___   ___   ___    __ __  _        ___ \n", "");
	printf("%12s|    \\  /   \\  /   \\ |  |/ ]|    ||    \\  /    |    |   |   | /   \\ |   \\  |  |  || |      /  _]\n", "");
	printf("%12s|  o  )|     ||     ||  ' /  |  | |  _  ||   __|    | _   _ ||     ||    \\ |  |  || |     /  [_ \n", "");
	printf("%12s|     ||  O  ||  O  ||    \\  |  | |  |  ||  |  |    |  \\_/  ||  O  ||  D  ||  |  || |___ |    _]\n", "");
	printf("%12s|  O  ||     ||     ||     | |  | |  |  ||  |_ |    |   |   ||     ||     ||  :  ||     ||   [_ \n", "");
	printf("%12s|     ||     ||     ||  .  | |  | |  |  ||     |    |   |   ||     ||     ||     ||     ||     |\n", "");
	printf("%12s|_____| \\___/  \\___/ |__|\\_||____||__|__||___,_|    |___|___| \\___/ |_____| \\__,_||_____||_____|\n", "");
}
void mainBookingMenu(char userType)
{
	printf("\n%50sBOOKING MODULE MENU\n", "");
	printf("%38s-------------------------------------------\n", "");
	printf("%38s| [1] Adding a booking.                   |\n", "");
	if (userType == 'S')
	{
		printf("%38s| [2] Modify a booking.                   |\n", "");
		printf("%38s| [3] Delete a booking.                   |\n", "");
		printf("%38s| [4] Display a booking.                  |\n", "");

	}
	else
	{
		printf("%38s| [2] Modify your booking.                |\n", "");
		printf("%38s| [3] Delete your booking.                |\n", "");
		printf("%38s| [4] Display your booking.               |\n", "");
	}
	printf("%38s| [5] Exit.                               |\n", "");
	printf("%38s-------------------------------------------\n", "");
}

void addingBook(char userID[])
{
	FILE *fBook, *fLog;
	BookData bookData[100], tempBook;
	char facName[30], confirm, facCode, checkBookID[6];
	int countBook, getConfirm, written;

	printf("\tADDING BOOKING\n");
	printf("\t--------------\n");

	// Read booking log data into struct array. The file will created if cannot found.
	countBook = 0;
	fBook = fopen("BookingList.txt", "r");
	// Checking if file is exist.
	if (fBook == NULL)
		fBook = fopen("BookingList.txt", "w");
	else
	{
		for (int i = 0; !feof(fBook); i++)
		{
			fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%[^\n]\n", bookData[i].bookID,
				&bookData[i].dateWhenBook.day, &bookData[i].dateWhenBook.month, &bookData[i].dateWhenBook.year,
				&bookData[i].dateBooked.day, &bookData[i].dateBooked.month, &bookData[i].dateBooked.year,
				&bookData[i].startTime, &bookData[i].endTime, bookData[i].userID, bookData[i].facID);
			countBook++;
		}
	}
	fclose(fBook);

	do
	{
		// Generating and showing booking ID.
		for (int i = 0; i <= countBook; i++)
		{
			sprintf(tempBook.bookID, "B%04d", i + 1);
			if (strcmp(tempBook.bookID, bookData[i].bookID) != 0)
				break;
		}
		if (countBook == 0)
			strcpy(tempBook.bookID, "B0001");

		do
		{
			printf("\tYour Booking ID: %s\n", tempBook.bookID);

			// Get input of facility name.
			addFacType(facName, &confirm);
			if (confirm == 'X')
			{
				printf("\tCancelled.\n\n");
				return;
			}

			// Get input of booking date and time.
			addFacDate(&tempBook.dateBooked.day, &tempBook.dateBooked.month, &tempBook.dateBooked.year);
			addFacTime(&getConfirm, bookData, countBook, tempBook.dateBooked, facName, &facCode, &tempBook.startTime, &tempBook.endTime, tempBook.facID);
		} while (getConfirm == 0);

		// Get confirmation from user.
		printf("\n\n\tYour Booking:\n");
		printf("\t>> Booking ID: %s\n", tempBook.bookID);
		printf("\t>> Facility Venue: %s", facName);
		if (facCode != 'X')
			printf(" %c\n", facCode);
		else
			printf("\n");
		printf("\t>> Day Booked: %02d/%02d/%04d\n", tempBook.dateBooked.day, tempBook.dateBooked.month, tempBook.dateBooked.year);
		printf("\t>> Booked Time: %04d - %04d\n\n", tempBook.startTime, tempBook.endTime);
		printf("\tConfirm? (Y=yes, N=no, X=cancel): ");
		confirm = confirmSelectWithX();
		if (confirm == 'N')
			printf("\n");
	} while (confirm == 'N');

	// The program will cancelled if user select cancel.
	if (confirm == 'X')
	{
		printf("\tCancelled.\n\n");
		return;
	}

	// Adding the booking into the file.
	printf("\n\tAdding...\n");
	fBook = fopen("BookingList.txt", "w");
	written = 0;
	// Only adding the booking and not reading from array if no booking is existed.
	if (countBook == 0)
		fprintf(fBook, "%s|%02d/%02d/%04d|%02d/%02d/%04d|%04d-%04d|%s|%s\n", tempBook.bookID,
			todayDate("day"), todayDate("month"), todayDate("year"),
			tempBook.dateBooked.day, tempBook.dateBooked.month, tempBook.dateBooked.year,
			tempBook.startTime, tempBook.endTime, userID, tempBook.facID);
	else
	{
		for (int i = 0; i < countBook; i++)
		{
			sprintf(checkBookID, "B%04d", i + 1);
			if (strcmp(tempBook.bookID, checkBookID) == 0)
			{
				fprintf(fBook, "%s|%02d/%02d/%04d|%02d/%02d/%04d|%04d-%04d|%s|%s\n", tempBook.bookID,
					todayDate("day"), todayDate("month"), todayDate("year"),
					tempBook.dateBooked.day, tempBook.dateBooked.month, tempBook.dateBooked.year,
					tempBook.startTime, tempBook.endTime, userID, tempBook.facID);
				written = 1;
			}

			fprintf(fBook, "%s|%02d/%02d/%04d|%02d/%02d/%04d|%04d-%04d|%s|%s\n", bookData[i].bookID,
				bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year,
				bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year,
				bookData[i].startTime, bookData[i].endTime, bookData[i].userID, bookData[i].facID);
		}

		if (written == 0)
			fprintf(fBook, "%s|%02d/%02d/%04d|%02d/%02d/%04d|%04d-%04d|%s|%s\n", tempBook.bookID,
				todayDate("day"), todayDate("month"), todayDate("year"),
				tempBook.dateBooked.day, tempBook.dateBooked.month, tempBook.dateBooked.year,
				tempBook.startTime, tempBook.endTime, userID, tempBook.facID);
	}
	fclose(fBook);
	
	// Write booking history into booking log.
	writeLog(&fLog, "%04d/%02d/%02d %02d:%02d:%02d - %s - Adding booking - %s.\n",
		todayDate("year"), todayDate("month"), todayDate("day"), todayDate("hour"), todayDate("minute"), todayDate("second"),
		userID, tempBook.bookID);

	printf("\tAdding Successfully!\n");
}
void addFacType(char* facName, char *confirm)
{
	FILE *fFac;
	FacData tempFac[100];
	int n, temp, position[100], choice;

	do
	{
		temp = 0;
		fFac = fopen("facilitylist.txt", "r");
		printf("\t---------------------------------------\n");
		for (int i = 0; !feof(fFac); i++)
		{
			fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", tempFac[i].facName, &tempFac[i].facCode, &tempFac[i].facID);
			// Compare all facility name to avoid duplicate.
			for (n = 0; n < i; n++)
				if (strcmp(tempFac[i].facName, tempFac[n].facName) == 0)
					break;
			if (n == i)
			{
				position[temp] = i;
				printf("\t| %3d. %-30s |\n", temp + 1, tempFac[i].facName);
				temp++;
			}
		}
		printf("\t---------------------------------------\n");
		fclose(fFac);

		// Get input of booking venue.
		printf("\tPlease select a booking venue: ");
		choice = position[numSelect(1, 1, temp) - 1];

		// Get confirmation of the input.
		printf("\n\t>> The booking venue that you have chosen: %s\n", tempFac[choice].facName);
		printf("\tConfirm? (Y=yes, N=no, X=cancel): ");
		*confirm = confirmSelectWithX();
		if (*confirm == 'N')
			printf("\n");
	} while (*confirm == 'N');

	// The function will cancel and return if user choose X.
	if (*confirm == 'X')
		return;

	// Copy the facility name for showing purpose.
	strcpy(facName, tempFac[choice].facName);
}
void addFacDate(int* day, int* month, int* year)
{
	// Get input of booking date.
	printf("\n\tPlease enter booking date (YYYY/MM/DD): ");
	if (todayDate("month") == 12 && todayDate("day") == 31)
		*year = yearSelect(todayDate("year") + 1, todayDate("year") + 1, 9999);
	else
		*year = yearSelect(todayDate("year"), todayDate("year"), 9999);

	// Various checking to validate of inputed date.
	if (*year > todayDate("year"))
	{
		*month = monthSelect(1, 1, 12, '/');
		if (*month == 2)
		{
			if (checkLeap(*year) == 1)
				*day = daySelect(1, 1, 29);
			else
				*day = daySelect(1, 1, 28);
		}
		else if ((*month % 2 == 0 && *month < 7) || (*month % 2 != 0 && *month > 7))
			*day = daySelect(1, 1, 30);
		else
			*day = daySelect(1, 1, 31);
	}
	else
	{
		if ((todayDate("month") % 2 == 0 && todayDate("day") == 30) || (todayDate("month") % 2 != 0 && todayDate("day") == 31))
			*month = monthSelect(todayDate("month") + 1, todayDate("month") + 1, 12, '/');
		else
			*month = monthSelect(todayDate("month"), todayDate("month"), 12, '/');

		if (*month == 2)
		{
			if (*month > todayDate("month"))
			{
				if (checkLeap(*year) == 1)
					*day = daySelect(1, 1, 29);
				else
					*day = daySelect(1, 1, 28);
			}
			else
			{
				if (checkLeap(*year) == 1)
					*day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 29);
				else
					*day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 28);
			}

		}
		else if (*month > todayDate("month"))
		{
			if ((*month % 2 == 0 && *month < 7) || (*month % 2 != 0 && *month > 7))
				*day = daySelect(1, 1, 30);
			else
				*day = daySelect(1, 1, 31);
		}
		else
		{
			if ((*month % 2 == 0 && *month < 7) || (*month % 2 != 0 && *month > 7))
				*day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 30);
			else
				*day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 31);
		}
	}

}
void addFacTime(int* getConfirm, BookData* BookData, int bookCount, Date tempDate, char* facName, char* facCode, int* startTime, int* endTime, char* facID)
{
	// Local struct declaration.
	typedef struct {
		char facCode;
		char facName[30];
		char facID[5];
		int timeStart, timeEnd;
	} facList;

	typedef struct {
		int timeStart;
		int timeEnd;
		char facID[5];
		char facCode;
	} timeList;

	FILE *fFac;
	int tempStart, tempEnd, k, choice, firstTime;
	int tempFacIDInt, countFac, countBookTime;
	char checkTimeStart[6], checkTimeEnd[65];
	facList tempFacList[50];
	timeList tempTimeList[100];

	// Read facility list from file.
	fFac = fopen("facilitylist.txt", "r");
	countFac = 0;
	while (!feof(fFac))
	{
		fscanf(fFac, "%[^|]|%c|%d|%*[^|]|%*[^|]|%*[^|]|%d%[^ ] to %d%[^|]|\n", tempFacList[countFac].facName, &tempFacList[countFac].facCode,
			&tempFacIDInt, &tempFacList[countFac].timeStart, checkTimeStart, &tempFacList[countFac].timeEnd, checkTimeEnd);
		if (strcmp(tempFacList[countFac].facName, facName) == 0)
		{
			sprintf(tempFacList[countFac].facID, "A%03d", tempFacIDInt);
			if (strcmp(checkTimeStart, "a.m.") == 0)
				tempFacList[countFac].timeStart *= 100;
			else
				tempFacList[countFac].timeStart = tempFacList[countFac].timeStart * 100 + 1200;
			if (strcmp(checkTimeEnd, "a.m.") == 0)
				tempFacList[countFac].timeEnd *= 100;
			else
				tempFacList[countFac].timeEnd = tempFacList[countFac].timeEnd * 100 + 1200;
			countFac++;
		}
	}
	fclose(fFac);

	// Show available booking time.
	printf("\n\n\n\tNote: Maintenence time is between 1100 - 1200.\n");
	printf("\t-------------------\n");
	tempEnd = 0;
	countBookTime = 0;
	for (int i = 0; i < countFac; i++)
	{
		firstTime = 1;
		tempStart = tempFacList[i].timeStart;
		for (int j = 0; tempStart < tempFacList[i].timeEnd; j++)
		{
			if (tempStart == 1100)
			{
				tempStart += 100;
				tempEnd += 100;
			}
			tempEnd = tempStart + 200;

			for (k = 0; k < bookCount; k++)
			{
				if (tempDate.day == BookData[k].dateBooked.day && tempDate.month == BookData[k].dateBooked.month &&
					tempDate.year == BookData[k].dateBooked.year &&
					tempStart == BookData[k].startTime && strcmp(tempFacList[i].facID, BookData[k].facID) == 0)
					break;
			}

			if (k == bookCount)
			{
				tempTimeList[countBookTime].timeStart = tempStart;
				tempTimeList[countBookTime].timeEnd = tempEnd;
				tempTimeList[countBookTime].facCode = tempFacList[i].facCode;
				strcpy(tempTimeList[countBookTime].facID, tempFacList[i].facID);
				if (firstTime == 0 || tempFacList[i].facCode == 'X')
					printf("\t| %2d. %04d - %04d |\n", countBookTime + 1, tempStart, tempEnd);
				else
				{
					printf("\t| %2d. %04d - %04d | (%s %c)\n", countBookTime + 1, tempStart, tempEnd, tempFacList[i].facName, tempFacList[i].facCode);
					firstTime = 0;
				}
				countBookTime++;
			}

			tempStart = tempEnd;
		}
	}
	printf("\t-------------------\n");
	
	// The function will return if no booking time was available.
	if (countBookTime == 0)
	{
		printf("\tProcess terminated because no booking time was available for the date.\n");
		printf("\tPress any key to continue...");
		getch();
		printf("\n\n");
		*getConfirm = 0;
		return;
	}

	// Get input of booking time.
	printf("\tPlease choose your selection (Choose 0 to back): ");
	choice = numSelect(1, 0, countBookTime) - 1;
	if (choice == -1)
	{
		printf("\tCancelled.\n");
		printf("\t---------\n\n");
		*getConfirm = 0;
		return;
	}
	else
		*getConfirm = 1;

	// Copy data out to adding main function.
	*startTime = tempTimeList[choice].timeStart;
	*endTime = tempTimeList[choice].timeEnd;
	*facCode = tempTimeList[choice].facCode;
	strcpy(facID, tempTimeList[choice].facID);
}

void deleteBook(char password[], char userID[], char userType)
{
	FILE *fFac, *fBook, *fLog;
	Date tempDateStart, tempDateEnd;
	BookData bookData[100];
	int choice, countBook, counter, store;
	int tempFacIDInt, startTime, endTime, position[100];
	char confirm, tempFacID[6], tempName[30], tempFacCode, showAllSameFac = 'N';
	char oneTimeUseName[30], oneTimeUseFacID[5], oneTimeUseFacCode;
	char checkName[30], checkCode, checkFacID[5];
	char checkUser[21], checkPass[21], again;
	char tempUserID[12], deleteOther = 'N';

	do
	{
		confirm = 'N';

		printf("\tDELETING BOOKING\n");
		printf("\t----------------\n");

		fFac = fopen("facilitylist.txt", "r");
		if (fFac == NULL)
			printf("Cannot open facility list!\n");
		fclose(fFac);

		// Ask staff user whether he/she need to delete own or other's user booking.
		if (userType == 'S')
		{
			printf("\tDo you want to delete other user's booking?\n");
			printf("\t(Y = yes, N = no and only delete your booking): ");
			deleteOther = confirmSelect('Y', 'N');
			printf("\n");
		}

		if (deleteOther != 'Y')
			deleteBookMenu();
		else
			deleteBookMenuStaff();
		printf("\tPlease choose a selection: ");
		choice = numSelect(1, 0, 5);

		// Getting input of what should be deleted.
		// Calling various deleting functions and selections.
		switch (choice)
		{
		case 0:
			printf("\n");
			return;
		case 1:
			tempFacIDInt = deleteFacType(&showAllSameFac, &confirm);
			sprintf(tempFacID, "A%03d", tempFacIDInt);
			break;
		case 2:
			do
			{
				printf("\tPlease enter Facility ID (AXXX) (Type -1 to cancel): ");
				rewind(stdin);
				scanf("%5s", tempFacID);
				if (tempFacID[0] == '-' && tempFacID[1] == '1')
				{
					printf("\tCancelled.\n\n");
					return;
				}
				tempFacID[0] = toupper(tempFacID[0]);
				if (strlen(tempFacID) != 4)
					printf("\tInvalid input! The facility ID should only in 4 characters.");
			} while (strlen(tempFacID) != 4);
			break;
		case 3:
			deleteFacDate(&tempDateStart.day, &tempDateStart.month, &tempDateStart.year, 
				&tempDateEnd.day, &tempDateEnd.month, &tempDateEnd.year, &confirm);
			break;
		case 4:
			deleteFacTime(&startTime, &endTime, &confirm);
			break;
		case 5:
			if (deleteOther == 'Y')
			{
				do
				{
					printf("\tPlease enter User ID (Type -1 to cancel): ");
					rewind(stdin);
					scanf("%11s", tempUserID);
					if (tempUserID[0] == '-' && tempUserID[1] == '1')
					{
						printf("\tCancelled.\n\n");
						return;
					}
					if (strlen(tempUserID) > 10)
						printf("\tInvalid input! The User ID should only within in 10 characters.");
				} while (strlen(tempUserID) > 10);
			}
			break;
		}
		
		printf("\n\n");
	} while (confirm == 'X');

	// Read booking log data into struct array.
	countBook = 0;
	fBook = fopen("BookingList.txt", "r");
	for (int i = 0; !feof(fBook); i++)
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%[^\n]\n", bookData[i].bookID, 
			&bookData[i].dateWhenBook.day, &bookData[i].dateWhenBook.month, &bookData[i].dateWhenBook.year,
			&bookData[i].dateBooked.day, &bookData[i].dateBooked.month, &bookData[i].dateBooked.year,
			&bookData[i].startTime, &bookData[i].endTime, bookData[i].userID, bookData[i].facID);
		countBook++;
	}

	store = choice;
	do
	{
		// Showing filtered booking list.
		switch (choice)
		{
		case 1:
		case 2:
			fFac = fopen("facilitylist.txt", "r");
			for (int i = 0;; i++)
			{
				fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", oneTimeUseName, &oneTimeUseFacCode, &tempFacIDInt);
				sprintf(oneTimeUseFacID, "A%03d", tempFacIDInt);
				if (strcmp(oneTimeUseFacID, tempFacID) == 0)
				{
					if (showAllSameFac == 'Y')
						printf("\tVenue: All venue of %s\n", oneTimeUseName);
					else if (oneTimeUseFacCode != 'X')
						printf("\tVenue: %s %c (%s)\n", oneTimeUseName, oneTimeUseFacCode, oneTimeUseFacID);
					else
						printf("\tVenue: %s (%s)\n", oneTimeUseName, oneTimeUseFacID);
					printf("\t-----\n");
					break;
				}
			}
			fclose(fFac);

			counter = 0;
			if (showAllSameFac == 'Y')
			{
				if (deleteOther != 'Y')
				{
					printf("\t%6s%-12s%-19s%-13s%-13s%-16s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Code");
					printf("\t%6s%-12s%-19s%-13s%-13s%-16s\n", "", "----------", "-----------------", "-----------", "-----------", "-------------");
				}
				else
				{
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-16s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID", "Facility Code");
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-16s\n", "", "----------", "-----------------", "-----------", "-----------", "----------", "-------------");
				}
				fFac = fopen("facilitylist.txt", "r");
				for (int i = 0; i < countBook; i++)
				{
					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", tempName, &tempFacCode, &tempFacIDInt);
						sprintf(tempFacID, "A%03d", tempFacIDInt);

						if (strcmp(tempName, oneTimeUseName) == 0 && strcmp(bookData[i].facID, tempFacID) == 0 &&
							(strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
						{
							position[counter] = i;
							counter++;
							printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d", counter, bookData[i].bookID,
								bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
								bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
								bookData[i].startTime, bookData[i].endTime);
							if (deleteOther == 'Y')
								printf("%2s%10s%2s%c\n", "", bookData[i].userID, "", tempFacCode);
							else
								printf("%2s%c\n", "", tempFacCode);
							break;
						}
					}
				}
				fclose(fFac);
			}
			else
			{
				if (deleteOther != 'Y')
				{
					printf("\t%6s%-12s%-19s%-13s%-13s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time");
					printf("\t%6s%-12s%-19s%-13s%-13s\n", "", "----------", "-----------------", "-----------", "-----------");
				}
				else
				{
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID");
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s\n", "", "----------", "-----------------", "-----------", "-----------", "----------");
				}
				for (int i = 0; i < countBook; i++)
				{
					if (strcmp(bookData[i].facID, tempFacID) == 0 && (strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
					{
						position[counter] = i;
						counter++;
						printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d", counter, bookData[i].bookID,
							bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
							bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
							bookData[i].startTime, bookData[i].endTime);
						if (deleteOther == 'Y')
							printf("%2s%10s\n", "", bookData[i].userID);
						else
							printf("\n");
					}
				}
			}
			break;

		case 3:
			fFac = fopen("facilitylist.txt", "r");
			printf("\tDate Range: From %02d/%02d/%04d to %02d/%02d/%04d\n",
				tempDateStart.day, tempDateStart.month, tempDateStart.year,
				tempDateEnd.day, tempDateEnd.month, tempDateEnd.year);
			printf("\t----------\n");

			if (deleteOther != 'Y')
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
			}
			else
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "----------", "--------------");
			}
			counter = 0;

			for (int i = 0; i < countBook; i++)
			{
				if (checkDateRange(tempDateStart, tempDateEnd, bookData[i].dateBooked) == 1 && (strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
				{
					position[counter] = i;
					counter++;
					printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
						bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
						bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
						bookData[i].startTime, bookData[i].endTime, "");

					if (deleteOther == 'Y')
						printf("%10s%2s", bookData[i].userID, "");

					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
						sprintf(checkFacID, "A%03d", tempFacIDInt);
						if (strcmp(checkFacID, bookData[i].facID) == 0)
						{
							if (checkCode == 'X')
								printf("%s\n", checkName);
							else
								printf("%s %c\n", checkName, checkCode);
						}
					}
				}
			}
			fclose(fFac);
			break;

		case 4:
			fFac = fopen("facilitylist.txt", "r");
			printf("\tTime Range: From %04d to %04d\n", startTime, endTime);
			printf("\t----------\n");

			if (deleteOther != 'Y')
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
			}
			else
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "----------", "--------------");
			}
			counter = 0;

			for (int i = 0; i < countBook; i++)
			{
				if (bookData[i].startTime >= startTime && bookData[i].endTime <= endTime && (strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
				{
					position[counter] = i;
					counter++;
					printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
						bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
						bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
						bookData[i].startTime, bookData[i].endTime, "");

					if (deleteOther == 'Y')
						printf("%10s%2s", bookData[i].userID, "");

					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
						sprintf(checkFacID, "A%03d", tempFacIDInt);
						if (strcmp(checkFacID, bookData[i].facID) == 0)
						{
							if (checkCode == 'X')
								printf("%s\n", checkName);
							else
								printf("%s %c\n", checkName, checkCode);
						}
					}
				}
			}
			fclose(fFac);
			break;

		case 5:
			fFac = fopen("facilitylist.txt", "r");
			if (deleteOther != 'Y')
				printf("\tShow all of your booking.\n");
			else
				printf("\tUser ID: %s\n", tempUserID);
			printf("\t----\n");

			printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
			printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
			counter = 0;

			for (int i = 0; i < countBook; i++)
			{
				if ((deleteOther != 'Y' && strcmp(bookData[i].userID, userID) == 0) || (deleteOther == 'Y' && strcmp(bookData[i].userID, tempUserID) == 0))
				{
					position[counter] = i;
					counter++;
					printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
						bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
						bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
						bookData[i].startTime, bookData[i].endTime, "");

					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
						sprintf(checkFacID, "A%03d", tempFacIDInt);
						if (strcmp(checkFacID, bookData[i].facID) == 0)
						{
							if (checkCode == 'X')
								printf("%s\n", checkName);
							else
								printf("%s %c\n", checkName, checkCode);
						}
					}
				}
			}
		}
		printf("\n\t\t--- %d record(s) found.\n", counter);

		// The function will return to main menu if no booking was found.
		if (counter == 0)
		{
			printf("\n\tProcess terminated because no booking was found...");
			return;
		}

		// Get input of booking selection and confirmation.
		printf("\n\tPlease choose a selection (0 to cancel): ");
		choice = numSelect(1, 0, counter) - 1;
		if (choice == -1)
		{
			printf("\tCancelled.\n\n");
			return;
		}
		printf("\n\tThe selection you have chosen to delete is...\n");
		printf("\t>> Booking ID: %s\n", bookData[position[choice]].bookID);

		fFac = fopen("facilitylist.txt", "r");
		while (!feof(fFac))
		{
			fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", oneTimeUseName, &oneTimeUseFacCode, &tempFacIDInt);
			sprintf(tempFacID, "A%03d", tempFacIDInt);
			if (strcmp(tempFacID, bookData[position[choice]].facID) == 0)
				break;
		}
		printf("\t>> Booking Venue: %s", oneTimeUseName);
		if (oneTimeUseFacCode != 'X')
			printf(" %c\n", oneTimeUseFacCode);
		else
			printf("\n");

		printf("\t>> Booking Time: %04d - %04d\n", bookData[position[choice]].startTime, bookData[position[choice]].endTime);
		printf("\t>> Booking Date (DD/MM/YYYY): %02d/%02d/%04d\n", bookData[position[choice]].dateBooked.day,
			bookData[position[choice]].dateBooked.month, bookData[position[choice]].dateBooked.year);
		printf("\n\tConfirm? (Y=yes, N=no, X=cancel): ");
		confirm = confirmSelectWithX();
		if (confirm == 'N')
			printf("\t---\n");
		else if (confirm == 'Y')
		{
			do
			{
				confirm = 'Y';
				again = 'N';
				printf("\tPlease enter user ID and password to proceed:\n");
				printf("\t\t>> User ID: ");
				rewind(stdin);
				scanf("%20[^\n]", checkUser);
				printf("\t\t>> Password: ");
				passwordInput(checkPass, sizeof(checkPass));

				if (strcmp(checkUser, userID) != 0 || strcmp(checkPass, password) != 0)
				{
					confirm = 'X';
					printf("\n\tUser ID or password error!\n");
					printf("\tDo you want to try again? (Y=yes, N=no): ");
					again = confirmSelect('Y', 'N');
				}
			} while (again == 'Y');
		}
		if (confirm == 'N')
		{
			printf("\t---\n\tPlease choose again:\n\n");
			choice = store;
		}
	} while (confirm == 'N');
	if (confirm == 'X')
	{
		printf("\tCancelled.\n\n");
		return;
	}

	printf("\tDeleting...\n");
	fBook = fopen("BookingList.txt", "w");
	for (int i = 0; i < countBook; i++)
	{
		if (i == position[choice])
			continue;
		fprintf(fBook, "%s|%02d/%02d/%04d|%02d/%02d/%04d|%04d-%04d|%s|%s\n", bookData[i].bookID,
			bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year,
			bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year,
			bookData[i].startTime, bookData[i].endTime, bookData[i].userID, bookData[i].facID);
	}

	// Write deleting history into booking log.
	writeLog(&fLog, "%04d/%02d/%02d %02d:%02d:%02d - %s - Deleting booking - %s.\n",
		todayDate("year"), todayDate("month"), todayDate("day"), todayDate("hour"), todayDate("minute"), todayDate("second"),
		userID, bookData[position[choice]].bookID);

	printf("\tDeleted Successfully!\n");
	fclose(fBook);
}
void deleteBookMenu()
{
	printf("\tShow booking list by...\n");
	printf("\t-----------------------\n");
	printf("\t| 1. Facility Venue   |\n");
	printf("\t| 2. Facility ID      |\n");
	printf("\t| 3. Booking Date     |\n");
	printf("\t| 4. Booking Time     |\n");
	printf("\t| 5. Show all         |\n");
	printf("\t| 0. Back             |\n");
	printf("\t-----------------------\n");
}
void deleteBookMenuStaff()
{
	printf("\tShow booking list by...\n");
	printf("\t-------------------------------\n");
	printf("\t| 1. Facility Venue           |\n");
	printf("\t| 2. Facility ID              |\n");
	printf("\t| 3. Booking Date             |\n");
	printf("\t| 4. Booking Time             |\n");
	printf("\t| 5. User ID                  |\n");
	printf("\t| 0. Back                     |\n");
	printf("\t-------------------------------\n");
}
int deleteFacType(char *showAll, char *getConfirm)
{
	FILE *fFac;
	FacData tempFac[100];
	char confirm;
	int position[100], temp, choice, numFac, n;
	
	do
	{
		temp = 0;
		// List all of facility venue.
		fFac = fopen("facilitylist.txt", "r");
		printf("\n\n\n\tFACILITY VENUE LIST\n");
		printf("\t-------------------\n");
		printf("\t---------------------------------------\n");
		for (numFac = 0; !feof(fFac); numFac++)
		{
			fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", tempFac[numFac].facName, &tempFac[numFac].facCode, &tempFac[numFac].facID);
			// Compare all facility name to avoid duplicate.
			for (n = 0; n < numFac; n++)
				if (strcmp(tempFac[numFac].facName, tempFac[n].facName) == 0)
					break;
			if (n == numFac)
			{
				position[temp] = numFac;
				printf("\t| %3d. %-30s |\n", temp + 1, tempFac[numFac].facName);
				temp++;
			}
		}
		printf("\t---------------------------------------\n");
		printf("\tPlease choose a selection: ");
		choice = position[numSelect(1, 1, temp) - 1];

		// List out sub-list of the vunue.
		if (tempFac[choice].facCode != 'X')
		{
			printf("\n\t");
			for (int i = 0; i < strlen(tempFac[choice].facName) + 13; i++)
				printf("-");
			printf("\n");

			for (n = 0, temp = 0; n < numFac; n++)
			{
				if (strcmp(tempFac[choice].facName, tempFac[n].facName) == 0)
				{
					printf("\t| %3d. %s %c   |\n", temp + 1, tempFac[n].facName, tempFac[n].facCode);
					position[temp] = n;
					temp++;
				}
			}

			// Adding show all into selection.
			printf("\t| %3d. Show all", temp += 1);
			position[temp] = position[0];
			for (int i = 0; i < strlen(tempFac[choice].facName) - 3; i++)
				printf(" ");
			printf("|\n");

			printf("\t");
			for (int i = 0; i < strlen(tempFac[choice].facName) + 13; i++)
				printf("-");
			printf("\n");

			// Get input of venue selection.
			printf("\tPlease choose a selection: ");
			choice = position[numSelect(1, 1, temp) - 1];
		}

		// Get confirmation from user.
		if (choice == position[temp - 1])
		{
			*showAll = 'Y';
			printf("\n\t>> Booking Venue: All venue of %s\n", tempFac[position[temp]].facName);
			choice = position[temp - 2];
		}
		else
		{
			printf("\n\t>> Booking Venue: %s", tempFac[choice].facName);
			if (tempFac[choice].facCode != 'X')
				printf(" %c\n", tempFac[choice].facCode);
			else
				printf("\n");
		}
		fclose(fFac);
		printf("\tConfirm? (Y=yes, N=no, X=cancel): ");
		confirm = confirmSelectWithX();
	} while (confirm == 'N');

	if (confirm == 'X')
		*getConfirm = confirm;
	return tempFac[choice].facID;
}
void deleteFacDate(int* startDay, int* startMonth, int* startYear, int* endDay, int* endMonth, int* endYear, char *getConfirm)
{
	char confirm;
	do
	{
		// Get input of date range.
		printf("\n\n\tPlease enter date range (YYYY/MM/DD):\n");
		printf("\t  > Start date range: ");
		*startYear = yearSelect(todayDate("year"), 1990, 9999);
		*startMonth = monthSelect(1, 1, 12, '/');

		// Validation of date range.
		if (*startMonth == 2)
		{
			if (checkLeap(*startYear) == 1)
				*startDay = daySelect(1, 1, 29);
			else
				*startDay = daySelect(1, 1, 28);
		}
		else if ((*startMonth % 2 == 0 && *startMonth < 7) || (*startMonth % 2 != 0 && *startMonth > 7))
			*startDay = daySelect(1, 1, 30);
		else
			*startDay = daySelect(1, 1, 31);

		printf("\n\t  > End date range  : ");
		*endYear = yearSelect(*startYear, *startYear, 9999);
		if (*endYear > *startYear)
		{
			*endMonth = monthSelect(1, 1, 12, '/');
			if (*endMonth == 2)
			{
				if (checkLeap(*endYear) == 1)
					*endDay = daySelect(1, 1, 29);
				else
					*endDay = daySelect(1, 1, 28);
			}
			else if ((*endMonth % 2 == 0 && *endMonth < 7) || (*endMonth % 2 != 0 && *endMonth > 7))
				*endDay = daySelect(1, 1, 30);
			else
				*endDay = daySelect(1, 1, 31);
		}
		else
		{
			*endMonth = monthSelect(*startMonth, *startMonth, 12, '/');
			if (*endMonth > *startMonth)
			{
				if (*endMonth == 2)
				{
					if (checkLeap(*endYear) == 1)
						*endDay = daySelect(1, 1, 29);
					else
						*endDay = daySelect(1, 1, 28);
				}
				else if ((*endMonth % 2 == 0 && *endMonth < 7) || (*endMonth % 2 != 0 && *endMonth > 7))
					*endDay = daySelect(1, 1, 30);
				else
					*endDay = daySelect(1, 1, 31);
			}
			else
			{
				if (*endMonth == 2)
				{
					if (checkLeap(*endYear) == 1)
						*endDay = daySelect(*startDay, *startDay, 29);
					else
						*endDay = daySelect(*startDay, *startDay, 28);
				}
				else if ((*endMonth % 2 == 0 && *endMonth < 7) || (*endMonth % 2 != 0 && *endMonth > 7))
					*endDay = daySelect(*startDay, *startDay, 30);
				else
					*endDay = daySelect(*startDay, *startDay, 31);
			}
		}

		printf("\n\n\t >> Date range: From %04d/%02d/%02d to %04d/%02d/%02d.\n", *startYear, *startMonth, *startDay,
			*endYear, *endMonth, *endDay);
		printf("\tConfirm? (Y=yes, N=no, X=cancel): ");
		confirm = confirmSelectWithX();
	} while (confirm == 'N');

	if (confirm == 'X')
		*getConfirm = confirm;
}
void deleteFacTime(int* startTime, int* endTime, char *getConfirm)
{
	char confirm;
	do
	{
		printf("\n\n\tPlease enter time range (in 24 hours format):\n");
		printf("\t\t> Start Time: ");
		*startTime = timeSelect(0, 0, 2000);
		printf("\n\t\t> End Time  : ");
		*endTime = timeSelect(*startTime + 200, *startTime + 200, 2200);
		printf("\n\n\t>> Booking Time: %04d - %04d\n", *startTime, *endTime);
		printf("\tConfirm? (Y=yes, N=no, X=cancel): ");
		confirm = confirmSelectWithX();
	} while (confirm == 'N');

	if (confirm == 'X')
		*getConfirm = confirm;
}

void displayBook(char userID[], char userType)
{
	FILE *fBook, *fFac;
	Date startDate, endDate;
	BookData bookData[100];
	int choice, choiceSelect[5], countBook, counter;
	int tempFacIDInt, startTime, endTime;
	char confirm, showAll, getConfirm, checkName[30], checkCode;
	char tempFacID[5], tempName[30], checkFacID[5];
	char oneTimeUseName[30], oneTimeUseFacID[5], oneTimeUseFacCode;
	char tempUserID[12];

	printf("\tDISPLAYING BOOKING\n");
	printf("\t------------------\n");

	// Read booking log data into struct array.
	countBook = 0;
	fBook = fopen("BookingList.txt", "r");
	for (int i = 0; !feof(fBook); i++)
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%[^\n]\n", bookData[i].bookID,
			&bookData[i].dateWhenBook.day, &bookData[i].dateWhenBook.month, &bookData[i].dateWhenBook.year,
			&bookData[i].dateBooked.day, &bookData[i].dateBooked.month, &bookData[i].dateBooked.year,
			&bookData[i].startTime, &bookData[i].endTime, bookData[i].userID, bookData[i].facID);
		countBook++;
	}

	// Get input of whether user want to use filter for booking list.
	printf("\tDo you want to use filter for booking list?\n");
	printf("\tY=yes, N=no and show all, X=cancel: ");
	confirm = confirmSelectWithX();
	printf("\n");

	// Various filter call function.
	if (confirm == 'Y')
	{
		choiceSelect[0] = choiceSelect[1] = choiceSelect[2] = choiceSelect[3] = 0;

		do
		{
			displayBookMenu(userType);

			if (choiceSelect[0] == 1 || choiceSelect[1] == 1 || choiceSelect[2] == 1 || choiceSelect[3] == 1 || choiceSelect[4] == 1)
				printf("\n\tFilter applied: \n\t--------------\n");
			if (choiceSelect[0] == 1)
			{
				fFac = fopen("facilitylist.txt", "r");
				for (int i = 0;; i++)
				{
					fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", oneTimeUseName, &oneTimeUseFacCode, &tempFacIDInt);
					sprintf(oneTimeUseFacID, "A%03d", tempFacIDInt);
					if (strcmp(oneTimeUseFacID, tempFacID) == 0)
					{
						if (showAll == 'Y')
							printf("\t>> Facility Venue: All venue of %s\n", oneTimeUseName);
						else if (oneTimeUseFacCode != 'X')
							printf("\t>> Facility Venue: %s %c (%s)\n", oneTimeUseName, oneTimeUseFacCode, oneTimeUseFacID);
						else
							printf("\t>> Facility Venue: %s (%s)\n", oneTimeUseName, oneTimeUseFacID);
						break;
					}
				}
				fclose(fFac);
			}
			if (choiceSelect[1] == 1)
				printf("\t>> Facility ID: %s\n", tempFacID);
			if (choiceSelect[2] == 1)
				printf("\t>> Date Range: From %02d-%02d-%04d until %02d-%02d-%04d.\n",
					startDate.day, startDate.month, startDate.year,
					endDate.day, endDate.month, endDate.year);
			if (choiceSelect[3] == 1)
				printf("\t>> Time Range: From %04d until %04d.\n", startTime, endTime);
			if (choiceSelect[4] == 1)
				printf("\t>> User ID: %s\n", tempUserID);
			if (choiceSelect[0] == 1 || choiceSelect[1] == 1 || choiceSelect[2] == 1 || choiceSelect[3] == 1 || choiceSelect[4] == 1)
				printf("\t--------------\n\n");

			if (userType == 'T')
			{
				printf("\tChoose <5> to confirm filter and proceed.\n");
				printf("\tPlease choose a selection for filter: ");
				choice = numSelect(1, 0, 5);
			}
			else
			{
				printf("\tChoose <6> to confirm filter and proceed.\n");
				printf("\tPlease choose a selection for filter: ");
				choice = numSelect(1, 0, 6);
			}

			switch (choice)
			{
			case 0:
				return;
			case 1:
				tempFacIDInt = deleteFacType(&showAll, &getConfirm);
				if (getConfirm != 'X')
				{
					sprintf(tempFacID, "A%03d", tempFacIDInt);
					if (showAll == 'Y')
					{
						fFac = fopen("facilitylist.txt", "r");
						for (int i = 0;; i++)
						{
							fscanf(fFac, "%[^|]|%*c|%d|%*[^\n]\n", tempName, &tempFacIDInt);
							sprintf(checkFacID, "A%03d", tempFacIDInt);
							if (strcmp(checkFacID, tempFacID) == 0)
								break;
						}
						fclose(fFac);
					}
					else
						showAll = 'N';
					choiceSelect[0] = 1;
				}
				printf("\n");
				break;
			case 2:
				do
				{
					printf("\tPlease enter Facility ID (AXXX) (Type -1 to cancel): ");
					rewind(stdin);
					scanf("%5s", tempFacID);
					if (tempFacID[0] == '-' && tempFacID[1] == '1')
					{
						printf("\n\tCancelled.\n\n");
						return;
					}
					tempFacID[0] = toupper(tempFacID[0]);
					if (strlen(tempFacID) != 4)
						printf("\tInvalid input! The facility ID should only in 4 characters.");
					else
						choiceSelect[1] = 1;
				} while (strlen(tempFacID) != 4);
				printf("\n");
				break;
			case 3:
				deleteFacDate(&startDate.day, &startDate.month, &startDate.year,
					&endDate.day, &endDate.month, &endDate.year, &getConfirm);
				if (getConfirm != 'X')
					choiceSelect[2] = 1;
				printf("\n");
				break;
			case 4:
				deleteFacTime(&startTime, &endTime, &getConfirm);
				if (getConfirm != 'X')
					choiceSelect[3] = 1;
				printf("\n");
				break;
			case 5:
				if (userType == 'T')
				{
					fFac = fopen("facilitylist.txt", "r");
					printf("\n\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
					printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
					counter = 0;

					for (int i = 0; i < countBook; i++)
					{
						if (displayBookCheckFilterCondition(choiceSelect, userID, bookData[i], tempName, tempFacID, &showAll,
							&startDate, &endDate, &startTime, &endTime, tempUserID, userType) == 1)
						{
							counter++;
							printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
								bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
								bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
								bookData[i].startTime, bookData[i].endTime, "");

							rewind(fFac);
							while (!feof(fFac))
							{
								fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
								sprintf(checkFacID, "A%03d", tempFacIDInt);
								if (strcmp(checkFacID, bookData[i].facID) == 0)
								{
									if (checkCode == 'X')
										printf("%s\n", checkName);
									else
										printf("%s %c\n", checkName, checkCode);
								}
							}
						}
					}
					fclose(fFac);
				}
				else
				{
					do
					{
						printf("\n\tPlease enter User ID (Type -1 to cancel): ");
						rewind(stdin);
						scanf("%11s", tempUserID);
						if (tempUserID[0] == '-' && tempUserID[1] == '1')
						{
							printf("\tCancelled.\n\n");
							return;
						}
						if (strlen(tempUserID) > 10)
							printf("\tInvalid input! The User ID should only within in 10 characters.");
					} while (strlen(tempUserID) > 10);
					if (tempUserID[0] != '-' && tempUserID[1] != '1')
						choiceSelect[4] = 1;
				}
				break;
			case 6:
				fFac = fopen("facilitylist.txt", "r");
				printf("\n\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "----------", "--------------");
				counter = 0;

				for (int i = 0; i < countBook; i++)
				{
					if (displayBookCheckFilterCondition(choiceSelect, userID, bookData[i], tempName, tempFacID, &showAll,
						&startDate, &endDate, &startTime, &endTime, tempUserID, userType) == 1)
					{
						counter++;
						printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
							bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
							bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
							bookData[i].startTime, bookData[i].endTime, "");
						printf("%-10s%2s", bookData[i].userID, "");
						rewind(fFac);
						while (!feof(fFac))
						{
							fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
							sprintf(checkFacID, "A%03d", tempFacIDInt);
							if (strcmp(checkFacID, bookData[i].facID) == 0)
							{
								if (checkCode == 'X')
									printf("%s\n", checkName);
								else
									printf("%s %c\n", checkName, checkCode);
							}
						}
					}
				}
				fclose(fFac);
			}
			printf("\n");
		} while ((choice != 5 && userType == 'T') || (choice != 6 && userType == 'S'));
	}
	else if (confirm == 'N')
	{
		fFac = fopen("facilitylist.txt", "r");
		printf("\tShow all of your booking.\n");
		printf("\t----\n");

		printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
		printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
		counter = 0;

		for (int i = 0; i < countBook; i++)
		{
			if (strcmp(bookData[i].userID, userID) == 0)
			{
				counter++;
				printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
					bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
					bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
					bookData[i].startTime, bookData[i].endTime, "");

				rewind(fFac);
				while (!feof(fFac))
				{
					fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
					sprintf(checkFacID, "A%03d", tempFacIDInt);
					if (strcmp(checkFacID, bookData[i].facID) == 0)
					{
						if (checkCode == 'X')
							printf("%s\n", checkName);
						else
							printf("%s %c\n", checkName, checkCode);
					}
				}
			}
		}
		fclose(fFac);
	}
	else
	{
		printf("\n\tCancelled.\n\n");
		return;
	}

	printf("\n\t\t--- %d record(s) found.\n", counter);
}
void displayBookMenu(char userType)
{
	printf("\tFilter booking list by...\n");
	printf("\t-----------------------\n");
	printf("\t| 1. Facility Venue   |\n");
	printf("\t| 2. Facility ID      |\n");
	printf("\t| 3. Booking Date     |\n");
	printf("\t| 4. Booking Time     |\n");
	if (userType == 'S')
		printf("\t| 5. User ID          |\n");
	printf("\t| 0. Back             |\n");
	printf("\t-----------------------\n");
}
int displayBookCheckFilterCondition(int choiceSelect[], char userID[], BookData bookData,
	char* tempName, char* tempFacID, char* showAll, Date* startDate, Date* endDate, int* startTime, int* endTime, char checkUserID[], char userType)
{
	FILE *fFac;
	char fileFacName[30], fileFacID[5];
	int fileFacIDInt;

	/*
	Choice select check condition for displaying booking:
	0 - Show by facility.
	1 - Show by facility ID.
	2 - Show by date.
	3 - Show by time.
	4 - Show by user ID (staff only).
	*/

	if (choiceSelect[0] == 0 && choiceSelect[1] == 0 && choiceSelect[2] == 0 && choiceSelect[3] == 0 && (choiceSelect[4] == 0 || userType == 'T'))
		return 0;

	if (choiceSelect[0] == 1 && *showAll == 'Y')
	{
		fFac = fopen("facilitylist.txt", "r");
		while (!feof(fFac))
		{
			fscanf(fFac, "%[^|]|%*c|%d|%*[^\n]\n", fileFacName, &fileFacIDInt);
			sprintf(fileFacID, "A%03d", fileFacIDInt);
			if (strcmp(bookData.facID, fileFacID) == 0 && strcmp(fileFacName, tempName) == 0 && (strcmp(bookData.userID, userID) == 0 || userType == 'S'))
				break;
		}
		if (feof(fFac))
			return 0;
		fclose(fFac);
	}

	if (choiceSelect[0] == 1 && *showAll == 'N')
	{
		if (!(strcmp(bookData.facID, tempFacID) == 0 && (strcmp(bookData.userID, userID) == 0 || userType == 'S')))
			return 0;
	}

	if (choiceSelect[1] == 1)
	{
		if (!(strcmp(bookData.facID, tempFacID) == 0 && (strcmp(bookData.userID, userID) == 0 || userType == 'S')))
			return 0;
	}

	if (choiceSelect[2] == 1)
	{
		if (!(checkDateRange(*startDate, *endDate, bookData.dateBooked) == 1 && (strcmp(bookData.userID, userID) == 0 || userType == 'S')))
			return 0;
	}

	if (choiceSelect[3] == 1)
	{
		if (!(bookData.startTime >= *startTime && bookData.endTime <= *endTime && (strcmp(bookData.userID, userID) == 0 || userType == 'S')))
			return 0;
	}

	if (choiceSelect[4] == 1)
	{
		if (!(strcmp(bookData.userID, checkUserID) == 0))
			return 0;
	}

	return 1;
}

void modifyBook(char password[], char userID[], char userType)
{
	FILE *fFac, *fBook, *fLog;
	Date tempDateStart, tempDateEnd;
	BookData bookData[100];
	int choice, countBook, counter, store;
	int tempFacIDInt, startTime, endTime, position[100], chosen;
	char confirm, tempFacID[6], tempName[30], tempFacCode, showAllSameFac = 'N';
	char oneTimeUseName[30], oneTimeUseFacID[5], oneTimeUseFacCode;
	char checkName[30], checkCode, checkFacID[5];
	char checkUser[21], checkPass[21], again;
	char tempUserID[12], deleteOther = 'N';

	do
	{
		confirm = 'N';

		printf("\tMODIFYING BOOKING\n");
		printf("\t----------------\n");

		fFac = fopen("facilitylist.txt", "r");
		if (fFac == NULL)
			printf("Cannot open facility list!\n");
		fclose(fFac);

		// Get input of whether staff user need to modify other and own booking.
		if (userType == 'S')
		{
			printf("\tDo you want to modify other user's booking?\n");
			printf("\t(Y = yes, N = no and only modify your booking): ");
			deleteOther = confirmSelect('Y', 'N');
			printf("\n");
		}

		if (deleteOther != 'Y')
			deleteBookMenu();
		else
			deleteBookMenuStaff();

		// Get input of delete booking filter selection.
		printf("\tPlease choose a selection: ");
		choice = numSelect(1, 0, 5);

		switch (choice)
		{
		case 0:
			printf("\n");
			return;
		case 1:
			tempFacIDInt = deleteFacType(&showAllSameFac, &confirm);
			sprintf(tempFacID, "A%03d", tempFacIDInt);
			break;
		case 2:
			do
			{
				printf("\tPlease enter Facility ID (AXXX) (Type -1 to cancel): ");
				rewind(stdin);
				scanf("%5s", tempFacID);
				if (tempFacID[0] == '-' && tempFacID[1] == '1')
				{
					printf("\tCancelled.\n\n");
					return;
				}
				tempFacID[0] = toupper(tempFacID[0]);
				if (strlen(tempFacID) != 4)
					printf("\n\tInvalid input! The facility ID should only in 4 characters.\n");
			} while (strlen(tempFacID) != 4);
			break;
		case 3:
			deleteFacDate(&tempDateStart.day, &tempDateStart.month, &tempDateStart.year,
				&tempDateEnd.day, &tempDateEnd.month, &tempDateEnd.year, &confirm);
			break;
		case 4:
			deleteFacTime(&startTime, &endTime, &confirm);
			break;
		case 5:
			if (deleteOther == 'Y')
			{
				do
				{
					printf("\tPlease enter User ID (Type -1 to cancel): ");
					rewind(stdin);
					scanf("%11s", tempUserID);
					if (tempUserID[0] == '-' && tempUserID[1] == '1')
					{
						printf("\tCancelled.\n\n");
						return;
					}
					if (strlen(tempUserID) > 10)
						printf("\n\tInvalid input! The User ID should only within in 10 characters.\n");
				} while (strlen(tempUserID) > 10);
			}
		}

		printf("\n\n");
	} while (confirm == 'X');

	// Read booking log data into struct array.
	countBook = 0;
	fBook = fopen("BookingList.txt", "r");
	for (int i = 0; !feof(fBook); i++)
	{
		fscanf(fBook, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%[^\n]\n", bookData[i].bookID,
			&bookData[i].dateWhenBook.day, &bookData[i].dateWhenBook.month, &bookData[i].dateWhenBook.year,
			&bookData[i].dateBooked.day, &bookData[i].dateBooked.month, &bookData[i].dateBooked.year,
			&bookData[i].startTime, &bookData[i].endTime, bookData[i].userID, bookData[i].facID);
		countBook++;
	}

	store = choice;
	do
	{
		// Showing booking list.
		switch (choice)
		{
		case 1:
		case 2:
			fFac = fopen("facilitylist.txt", "r");
			for (int i = 0;; i++)
			{
				fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", oneTimeUseName, &oneTimeUseFacCode, &tempFacIDInt);
				sprintf(oneTimeUseFacID, "A%03d", tempFacIDInt);
				if (strcmp(oneTimeUseFacID, tempFacID) == 0)
				{
					if (showAllSameFac == 'Y')
						printf("\tVenue: All venue of %s\n", oneTimeUseName);
					else if (oneTimeUseFacCode != 'X')
						printf("\tVenue: %s %c (%s)\n", oneTimeUseName, oneTimeUseFacCode, oneTimeUseFacID);
					else
						printf("\tVenue: %s (%s)\n", oneTimeUseName, oneTimeUseFacID);
					printf("\t-----\n");
					break;
				}
			}
			fclose(fFac);

			counter = 0;
			if (showAllSameFac == 'Y')
			{
				if (deleteOther != 'Y')
				{
					printf("\t%6s%-12s%-19s%-13s%-13s%-16s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Code");
					printf("\t%6s%-12s%-19s%-13s%-13s%-16s\n", "", "----------", "-----------------", "-----------", "-----------", "-------------");
				}
				else
				{
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-16s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID", "Facility Code");
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-16s\n", "", "----------", "-----------------", "-----------", "-----------", "----------", "-------------");
				}
				fFac = fopen("facilitylist.txt", "r");
				for (int i = 0; i < countBook; i++)
				{
					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", tempName, &tempFacCode, &tempFacIDInt);
						sprintf(tempFacID, "A%03d", tempFacIDInt);

						if (strcmp(tempName, oneTimeUseName) == 0 && strcmp(bookData[i].facID, tempFacID) == 0 &&
							(strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
						{
							position[counter] = i;
							counter++;
							printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d", counter, bookData[i].bookID,
								bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
								bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
								bookData[i].startTime, bookData[i].endTime);
							if (deleteOther == 'Y')
								printf("%2s%10s%2s%c\n", "", bookData[i].userID, "", tempFacCode);
							else
								printf("%2s%c\n", "", tempFacCode);
							break;
						}
					}
				}
				fclose(fFac);
			}
			else
			{
				if (deleteOther != 'Y')
				{
					printf("\t%6s%-12s%-19s%-13s%-13s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time");
					printf("\t%6s%-12s%-19s%-13s%-13s\n", "", "----------", "-----------------", "-----------", "-----------");
				}
				else
				{
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID");
					printf("\t%6s%-12s%-19s%-13s%-13s%-12s\n", "", "----------", "-----------------", "-----------", "-----------", "----------");
				}
				for (int i = 0; i < countBook; i++)
				{
					if (strcmp(bookData[i].facID, tempFacID) == 0 && (strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
					{
						position[counter] = i;
						counter++;
						printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d", counter, bookData[i].bookID,
							bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
							bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
							bookData[i].startTime, bookData[i].endTime);
						if (deleteOther == 'Y')
							printf("%2s%10s\n", "", bookData[i].userID);
						else
							printf("\n");
					}
				}
			}
			break;

		case 3:
			fFac = fopen("facilitylist.txt", "r");
			printf("\tDate Range: From %02d/%02d/%04d to %02d/%02d/%04d\n",
				tempDateStart.day, tempDateStart.month, tempDateStart.year,
				tempDateEnd.day, tempDateEnd.month, tempDateEnd.year);
			printf("\t----------\n");

			if (deleteOther != 'Y')
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
			}
			else
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "----------", "--------------");
			}
			counter = 0;

			for (int i = 0; i < countBook; i++)
			{
				if (checkDateRange(tempDateStart, tempDateEnd, bookData[i].dateBooked) == 1 && (strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
				{
					position[counter] = i;
					counter++;
					printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
						bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
						bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
						bookData[i].startTime, bookData[i].endTime, "");

					if (deleteOther == 'Y')
						printf("%10s%2s", bookData[i].userID, "");

					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
						sprintf(checkFacID, "A%03d", tempFacIDInt);
						if (strcmp(checkFacID, bookData[i].facID) == 0)
						{
							if (checkCode == 'X')
								printf("%s\n", checkName);
							else
								printf("%s %c\n", checkName, checkCode);
						}
					}
				}
			}
			fclose(fFac);
			break;

		case 4:
			fFac = fopen("facilitylist.txt", "r");
			printf("\tTime Range: From %04d to %04d\n", startTime, endTime);
			printf("\t----------\n");

			if (deleteOther != 'Y')
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
			}
			else
			{
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "User ID", "Facility Venue");
				printf("\t%6s%-12s%-19s%-13s%-13s%-12s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "----------", "--------------");
			}
			counter = 0;

			for (int i = 0; i < countBook; i++)
			{
				if (bookData[i].startTime >= startTime && bookData[i].endTime <= endTime && (strcmp(bookData[i].userID, userID) == 0 || deleteOther == 'Y'))
				{
					position[counter] = i;
					counter++;
					printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
						bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
						bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
						bookData[i].startTime, bookData[i].endTime, "");

					if (deleteOther == 'Y')
						printf("%10s%2s", bookData[i].userID, "");

					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
						sprintf(checkFacID, "A%03d", tempFacIDInt);
						if (strcmp(checkFacID, bookData[i].facID) == 0)
						{
							if (checkCode == 'X')
								printf("%s\n", checkName);
							else
								printf("%s %c\n", checkName, checkCode);
						}
					}
				}
			}
			fclose(fFac);
			break;

		case 5:
			fFac = fopen("facilitylist.txt", "r");
			if (deleteOther != 'Y')
				printf("\tShow all of your booking.\n");
			else
				printf("\tUser ID: %s\n", tempUserID);
			printf("\t----\n");

			printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "Booking ID", "Date When Booking", "Date Booked", "Time", "Facility Venue");
			printf("\t%6s%-12s%-19s%-13s%-13s%-17s\n", "", "----------", "-----------------", "-----------", "-----------", "--------------");
			counter = 0;

			for (int i = 0; i < countBook; i++)
			{
				if ((deleteOther != 'Y' && strcmp(bookData[i].userID, userID) == 0) || (deleteOther == 'Y' && strcmp(bookData[i].userID, tempUserID) == 0))
				{
					position[counter] = i;
					counter++;
					printf("\t%3d.  %-12s%02d/%02d/%04d%9s%02d/%02d/%04d%3s%04d - %04d%2s", counter, bookData[i].bookID,
						bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year, "",
						bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year, "",
						bookData[i].startTime, bookData[i].endTime, "");

					rewind(fFac);
					while (!feof(fFac))
					{
						fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", checkName, &checkCode, &tempFacIDInt);
						sprintf(checkFacID, "A%03d", tempFacIDInt);
						if (strcmp(checkFacID, bookData[i].facID) == 0)
						{
							if (checkCode == 'X')
								printf("%s\n", checkName);
							else
								printf("%s %c\n", checkName, checkCode);
						}
					}
				}
			}
		}
		printf("\n\t\t--- %d record(s) found.\n", counter);
		if (counter == 0)
		{
			printf("\n\tProcess terminated because no booking was found...");
			return;
		}

		// Get input of delete booking selection.
		printf("\n\tPlease choose a selection (0 to cancel): ");
		choice = numSelect(1, 0, counter) - 1;
		if (choice == -1)
		{
			printf("\tCancelled.\n\n");
			return;
		}
		printf("\n\tThe selection you have chosen to modify is...\n");
		printf("\t>> Booking ID: %s\n", bookData[position[choice]].bookID);

		fFac = fopen("facilitylist.txt", "r");
		while (!feof(fFac))
		{
			fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", oneTimeUseName, &oneTimeUseFacCode, &tempFacIDInt);
			sprintf(tempFacID, "A%03d", tempFacIDInt);
			if (strcmp(tempFacID, bookData[position[choice]].facID) == 0)
				break;
		}
		printf("\t>> Booking Venue: %s", oneTimeUseName);
		if (oneTimeUseFacCode != 'X')
			printf(" %c\n", oneTimeUseFacCode);
		else
			printf("\n");

		printf("\t>> Booking Time: %04d - %04d\n", bookData[position[choice]].startTime, bookData[position[choice]].endTime);
		printf("\t>> Booking Date (DD/MM/YYYY): %02d/%02d/%04d\n", bookData[position[choice]].dateBooked.day,
			bookData[position[choice]].dateBooked.month, bookData[position[choice]].dateBooked.year);
		printf("\n\tConfirm? (Y=yes, N=no, X=cancel): ");
		confirm = confirmSelectWithX();
		if (confirm == 'N')
		{
			printf("\t---\n\tPlease choose again:\n\n");
			choice = store;
		}
	} while (confirm == 'N');
	if (confirm == 'X')
	{
		printf("\tCancelled.\n\n");
		return;
	}

	printf("\n");
	modifyBookMenu();
	printf("\tPlease choose a selection to modify: ");
	chosen = numSelect(1, 0, 3);

	switch (chosen)
	{
	case 0:
		printf("\tCancelled.\n");
		printf("\t---------\n\n");
		return;
	case 1:
		tempFacIDInt = modifyFacType(&confirm, bookData, &countBook, &bookData[position[choice]].dateBooked,
			&bookData[position[choice]].startTime, &bookData[position[choice]].endTime, bookData[position[choice]].facID);
		sprintf(bookData[position[choice]].facID, "A%03d", tempFacIDInt);
		break;
	case 2:
		modifyFacDate(&confirm, bookData, &countBook, &bookData[position[choice]].dateBooked, &bookData[position[choice]].startTime,
			&bookData[position[choice]].endTime, bookData[position[choice]].facID);
		break;
	case 3:
		modifyFacTime(&confirm, bookData, countBook, bookData[position[choice]].dateBooked,
			&bookData[position[choice]].startTime,
			&bookData[position[choice]].endTime, bookData[position[choice]].facID);
		break;
	}

	if (confirm == 'Y')
	{
		printf("\n\n\tModified Booking:\n");
		printf("\t----------------\n");
		printf("\t>> Booking ID: %s\n", bookData[position[choice]].bookID);

		fFac = fopen("facilitylist.txt", "r");
		while (!feof(fFac))
		{
			fscanf(fFac, "%[^|]|%c|%d|%*[^\n]\n", oneTimeUseName, &oneTimeUseFacCode, &tempFacIDInt);
			sprintf(tempFacID, "A%03d", tempFacIDInt);
			if (strcmp(tempFacID, bookData[position[choice]].facID) == 0)
				break;
		}
		printf("\t>> Booking Venue: %s", oneTimeUseName);
		if (oneTimeUseFacCode != 'X')
			printf(" %c\n", oneTimeUseFacCode);
		else
			printf("\n");
		printf("\t>> Booking Time: %04d - %04d\n", bookData[position[choice]].startTime, bookData[position[choice]].endTime);
		printf("\t>> Booking Date (DD/MM/YYYY): %02d/%02d/%04d\n", bookData[position[choice]].dateBooked.day,
			bookData[position[choice]].dateBooked.month, bookData[position[choice]].dateBooked.year);
		printf("\n\tConfirm? (Y=yes, N=no): ");
		confirm = confirmSelect('Y', 'N');
		if (confirm == 'Y')
		{
			do
			{
				confirm = 'Y';
				again = 'N';
				printf("\tPlease enter user ID and password to proceed:\n");
				printf("\t\t>> User ID: ");
				rewind(stdin);
				scanf("%20[^\n]", checkUser);
				printf("\t\t>> Password: ");
				passwordInput(checkPass, sizeof(checkPass));

				if (strcmp(checkUser, userID) != 0 || strcmp(checkPass, password) != 0)
				{
					confirm = 'N';
					printf("\n\tUser ID or password error!\n");
					printf("\tDo you want to try again? (Y=yes, N=no): ");
					again = confirmSelect('Y', 'N');
				}
			} while (again == 'Y');
		}

		if (confirm == 'N')
		{
			confirm = 'X';
			printf("\n\tCancelled\n\t---\n");
		}


		if (confirm == 'Y')
		{
			printf("\n\tModifying...\n");
			fBook = fopen("BookingList.txt", "w");
			for (int i = 0; i < countBook; i++)
			{
				fprintf(fBook, "%s|%02d/%02d/%04d|%02d/%02d/%04d|%04d-%04d|%s|%s\n", bookData[i].bookID,
					bookData[i].dateWhenBook.day, bookData[i].dateWhenBook.month, bookData[i].dateWhenBook.year,
					bookData[i].dateBooked.day, bookData[i].dateBooked.month, bookData[i].dateBooked.year,
					bookData[i].startTime, bookData[i].endTime, bookData[i].userID, bookData[i].facID);
			}
			fclose(fBook);

			writeLog(&fLog, "%04d/%02d/%02d %02d:%02d:%02d - %s - Modifying booking - %s.\n",
				todayDate("year"), todayDate("month"), todayDate("day"), todayDate("hour"), todayDate("minute"), todayDate("second"),
				userID, bookData[position[choice]].bookID);

			printf("\tModifying Successfully!\n");
		}
	}

}
void modifyBookMenu()
{
	printf("\n\tMODIFY BOOKING\n");
	printf("\t--------------\n");
	printf("\t-----------------------\n");
	printf("\t| 1. Facility Venue   |\n");
	printf("\t| 2. Booking Date     |\n");
	printf("\t| 3. Booking Time     |\n");
	printf("\t| 0. Cancel           |\n");
	printf("\t-----------------------\n");
}
int modifyFacType(char *confirm, BookData* bookData, int* bookCount, Date* bookedDate, int* startTime, int* endTime, char* bookedFacID)
{
	FILE *fFac;
	FacData tempFac[100];
	int facCount, counter, j;
	int choice, position[100];
	char checkAPStart[6], checkAPEnd[6], checkFacID[6];

	fFac = fopen("facilitylist.txt", "r");
	facCount = 0;

	// Read facility list into struct array.
	for (int i = 0; !feof(fFac); i++)
	{
		fscanf(fFac, "%[^|]|%c|%d|%*[^|]|%*[^|]|%*[^|]|%d%[^ ] to %d%[^|]|\n", tempFac[i].facName, &tempFac[i].facCode,
			&tempFac[i].facID, &tempFac[i].startTime, checkAPStart, &tempFac[i].endTime, checkAPEnd);
		if (strcmp(checkAPStart, "a.m.") == 0)
			tempFac[i].startTime *= 100;
		else
			tempFac[i].startTime = tempFac[i].startTime * 100 + 1200;
		if (strcmp(checkAPEnd, "a.m.") == 0)
			tempFac[i].endTime *= 100;
		else
			tempFac[i].endTime = tempFac[i].endTime * 100 + 1200;
		facCount++;
	}
	fclose(fFac);

	// Showing facility venue that available during the date and time.
	do
	{
		printf("\n\tYour booking time: %04d - %04d\n", *startTime, *endTime);
		printf("\tYour booking date: %02d/%02d/%04d\n", bookedDate->day, bookedDate->month, bookedDate->year);
		printf("\tFacility venue available during that date and time:\n");
		printf("\t---------------------------------------\n");
		counter = 0;
		for (int i = 0; i < facCount; i++)
		{
			sprintf(checkFacID, "A%03d", tempFac[i].facID);
			for (j = 0; j < *bookCount; j++)
			{
				if (strcmp(checkFacID, bookData[j].facID) != 0)
					continue;
				else
				{
					if (bookData[j].dateBooked.day != bookedDate->day || bookData[j].dateBooked.month != bookedDate->month ||
						bookData[j].dateBooked.year != bookedDate->year)
						continue;
					else
					{
						if (bookData[j].startTime == *startTime && bookData[j].endTime == *endTime)
							break;
						else
							continue;
					}
				}
			}

			if (j == *bookCount)
			{
				position[counter] = i;
				counter++;
				if (tempFac[i].facCode != 'X')
					printf("\t%3d. %s %c\n", counter, tempFac[i].facName, tempFac[i].facCode);
				else
					printf("\t%3d. %s\n", counter, tempFac[i].facName);
			}
		}
		printf("\t---------------------------------------\n");

		// Get input of facility venue selection.
		printf("\tPlease select a facility venue (Select 0 to cancel): ");
		choice = numSelect(1, 0, counter) - 1;
		if (choice == -1)
		{
			printf("\tCancelled.\n");
			*confirm = 'X';
			return -1;
		}

		choice = position[choice];
		if (tempFac[choice].facCode != 'X')
			printf("\n\tFacility venue you have chosen: %s %c\n", tempFac[choice].facName, tempFac[choice].facCode);
		else
			printf("\n\tFacility venue you have chosen: %s\n", tempFac[choice].facName);

		printf("\tConfirm? (Y=yes, N=no, X=cancel): ");
		*confirm = confirmSelectWithX();

		printf("\n\n");
	} while (*confirm == 'N');

	if (*confirm == 'X')
		return -1;

	return tempFac[choice].facID;
}
void modifyFacDate(char* confirm, BookData* bookData, int* bookCount, Date* bookedDate, int* startTime, int* endTime, char* bookFacID)
{
	FILE *fFac;
	FacData tempFac[100];
	int facCount, toCheck;
	char checkAPStart[6], checkAPEnd[6];
	Date tempDate;

	fFac = fopen("facilitylist.txt", "r");
	facCount = 0;
	// Read facility list into struct array.
	for (int i = 0; !feof(fFac); i++)
	{
		fscanf(fFac, "%[^|]|%c|%d|%*[^|]|%*[^|]|%*[^|]|%d%[^ ] to %d%[^|]|\n", tempFac[i].facName, &tempFac[i].facCode,
			&tempFac[i].facID, &tempFac[i].startTime, checkAPStart, &tempFac[i].endTime, checkAPEnd);
		if (strcmp(checkAPStart, "a.m.") == 0)
			tempFac[i].startTime *= 100;
		else
			tempFac[i].startTime = tempFac[i].startTime * 100 + 1200;
		if (strcmp(checkAPEnd, "a.m.") == 0)
			tempFac[i].endTime *= 100;
		else
			tempFac[i].endTime = tempFac[i].endTime * 100 + 1200;
		facCount++;
	}
	fclose(fFac);

	// Get input of booking date.
	do
	{
		printf("\n\tPlease enter booking date (YYYY/MM/DD): ");
		if (todayDate("month") == 12 && todayDate("day") == 31)
			tempDate.year = yearSelect(todayDate("year") + 1, todayDate("year") + 1, 9999);
		else
			tempDate.year = yearSelect(todayDate("year"), todayDate("year"), 9999);
		if (tempDate.year > todayDate("year"))
		{
			tempDate.month = monthSelect(1, 1, 12, '/');
			if (tempDate.month == 2)
			{
				if (checkLeap(tempDate.year) == 1)
					tempDate.day = daySelect(1, 1, 29);
				else
					tempDate.day = daySelect(1, 1, 28);
			}
			else if ((tempDate.month % 2 == 0 && tempDate.month < 7) || (tempDate.month % 2 != 0 && tempDate.month > 7))
				tempDate.day = daySelect(1, 1, 30);
			else
				tempDate.day = daySelect(1, 1, 31);
		}
		else
		{
			if ((todayDate("month") % 2 == 0 && todayDate("day") == 30) || (todayDate("month") % 2 != 0 && todayDate("day") == 31))
				tempDate.month = monthSelect(todayDate("month") + 1, todayDate("month") + 1, 12, '/');
			else
				tempDate.month = monthSelect(todayDate("month"), todayDate("month"), 12, '/');
			if (tempDate.month == 2)
			{
				if (tempDate.month > todayDate("month"))
				{
					if (checkLeap(tempDate.year) == 1)
						tempDate.day = daySelect(1, 1, 29);
					else
						tempDate.day = daySelect(1, 1, 28);
				}
				else
				{
					if (checkLeap(tempDate.year) == 1)
						tempDate.day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 29);
					else
						tempDate.day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 28);
				}

			}
			else if (tempDate.month > todayDate("month"))
			{
				if ((tempDate.month % 2 == 0 && tempDate.month < 7) || (tempDate.month % 2 != 0 && tempDate.month > 7))
					tempDate.day = daySelect(1, 1, 30);
				else
					tempDate.day = daySelect(1, 1, 31);
			}
			else
			{
				if ((tempDate.month % 2 == 0 && tempDate.month < 7) || (tempDate.month % 2 != 0 && tempDate.month > 7))
					tempDate.day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 30);
				else
					tempDate.day = daySelect(todayDate("day") + 1, todayDate("day") + 1, 31);
			}
		}

		for (toCheck = 0; toCheck < *bookCount; toCheck++)
		{
			if (strcmp(bookData[toCheck].facID, bookFacID) != 0)
				continue;
			else
			{
				if (bookData[toCheck].dateBooked.day != tempDate.day || bookData[toCheck].dateBooked.month != tempDate.month ||
					bookData[toCheck].dateBooked.year != tempDate.year)
					continue;
				else
				{
					if (bookData[toCheck].startTime == *startTime && bookData[toCheck].endTime == *endTime)
						break;
					else
						continue;
				}
			}
		}

		if (toCheck != *bookCount)
		{
			printf("\n\tSorry, the venue has been booked for that date and time.\n");
			printf("\tPlease proceed to delete booking and adding again if you wish to modify whole booking info.\n");
			printf("\tTry again? (Y=yes, N=no): ");
			*confirm = confirmSelect('Y', 'N');
			if (*confirm == 'Y')
				*confirm = 'N';
			else
				*confirm = 'X';
		}
		else
		{
			printf("\n\n\tBooking date for the booking will be changed to: %04d/%02d/%02d\n", tempDate.year, tempDate.month, tempDate.day);
			printf("\tConfirm? (Y=yes, N=no, X=cancel): ");
			*confirm = confirmSelectWithX();
		}
	} while (*confirm == 'N');

	if (*confirm == 'Y')
	{
		bookedDate->day = tempDate.day;
		bookedDate->month = tempDate.month;
		bookedDate->year = tempDate.year;
	}
}
void modifyFacTime(char* confirm, BookData* BookData, int bookCount, Date tempDate, int* startTime, int* endTime, char* facID)
{
	struct {
		char facCode;
		char facName[30];
		char facID[5];
		int timeStart, timeEnd;
	} tempFac;

	typedef struct {
		int timeStart;
		int timeEnd;
		char facID[5];
		char facCode;
	} timeList;

	FILE *fFac;
	int tempStart, tempEnd, k, choice;
	int tempFacIDInt, countBookTime;
	char checkTimeStart[6], checkTimeEnd[65];
	timeList tempTimeList[100];

	fFac = fopen("facilitylist.txt", "r");
	// Read facility list into struct array.
	while (!feof(fFac))
	{
		fscanf(fFac, "%[^|]|%c|%d|%*[^|]|%*[^|]|%*[^|]|%d%[^ ] to %d%[^|]|\n", tempFac.facName, &tempFac.facCode,
			&tempFacIDInt, &tempFac.timeStart, checkTimeStart, &tempFac.timeEnd, checkTimeEnd);
		sprintf(tempFac.facID, "A%03d", tempFacIDInt);
		if (strcmp(tempFac.facID, facID) == 0)
		{	
			if (strcmp(checkTimeStart, "a.m.") == 0)
				tempFac.timeStart *= 100;
			else
				tempFac.timeStart = tempFac.timeStart * 100 + 1200;
			if (strcmp(checkTimeEnd, "a.m.") == 0)
				tempFac.timeEnd *= 100;
			else
				tempFac.timeEnd = tempFac.timeEnd * 100 + 1200;
			break;
		}
	}
	fclose(fFac);

	// Showing available booking time list.
	printf("\n\n\n\tNote: Maintenence time is between 1100 - 1200.\n");
	printf("\t-------------------\n");
	countBookTime = 0;
	tempStart = tempFac.timeStart;
	tempEnd = 0;
	for (int j = 0; tempStart < tempFac.timeEnd; j++)
	{
		if (tempStart == 1100)
		{
			tempStart += 100;
			tempEnd += 100;
		}
		tempEnd = tempStart + 200;

		for (k = 0; k < bookCount; k++)
		{
			if (tempDate.day == BookData[k].dateBooked.day && tempDate.month == BookData[k].dateBooked.month &&
				tempDate.year == BookData[k].dateBooked.year &&
				tempStart == BookData[k].startTime && strcmp(tempFac.facID, BookData[k].facID) == 0)
				break;
		}

		if (k == bookCount)
		{
			tempTimeList[countBookTime].timeStart = tempStart;
			tempTimeList[countBookTime].timeEnd = tempEnd;
			tempTimeList[countBookTime].facCode = tempFac.facCode;
			strcpy(tempTimeList[countBookTime].facID, tempFac.facID);
			printf("\t| %2d. %04d - %04d |\n", countBookTime + 1, tempStart, tempEnd);
			countBookTime++;
		}

		tempStart = tempEnd;
	}
	printf("\t-------------------\n");
	// Get input of booking time.
	printf("\tPlease choose your selection (Choose 0 to back): ");
	choice = numSelect(1, 0, countBookTime) - 1;
	if (choice == -1)
	{
		printf("\tCancelled.\n");
		printf("\t---------\n\n");
		*confirm = 'X';
		return;
	}
	else
		*confirm = 'Y';
	*startTime = tempTimeList[choice].timeStart;
	*endTime = tempTimeList[choice].timeEnd;
}


int yearSelect(int start, int min, int max)
{
	unsigned char choice1, choice2;
	int i;
	char c[10];

	printf("%-10d", start);
	sprintf(c, "%d", start);
	for (int x = 0; x < 10 - strlen(c); x++)
		printf("\b");
	printf("/");
	for (i = start;;)
	{
		rewind(stdin);
		choice1 = getch();

		if (choice1 == '\n' || choice1 == '\r')
			break;
		else if (choice1 != 224)
			continue;

		rewind(stdin);
		choice2 = getch();

		if ((i == min && choice2 == 72) || (i == max && choice2 == 80))
			continue;
		else
		{
			if (choice2 == 72)
				i--;
			else if (choice2 == 80)
				i++;
			else
				continue;

			for (int x = 0; x < 10 - strlen(c); x++)
				printf(" ");
			for (int x = 0; x < 10 + 1; x++)
				printf("\b");
			printf("%-10d", i);
			sprintf(c, "%d", i);
			for (int x = 0; x < 10 - strlen(c); x++)
				printf("\b");
			printf("/");
		}
	}

	return i;
}
int monthSelect(int start, int min, int max, char lastChar)
{
	unsigned char choice1, choice2;
	int i;
	char c[10];

	printf("%02d", start);
	sprintf(c, "%02d", start);
	for (int x = 0; x < 2 - strlen(c); x++)
		printf("\b");
	printf("%c", lastChar);
	for (i = start;;)
	{
		rewind(stdin);
		choice1 = getch();

		if (choice1 == '\n' || choice1 == '\r')
			break;
		else if (choice1 != 224)
			continue;

		rewind(stdin);
		choice2 = getch();

		if ((i == min && choice2 == 72) || (i == max && choice2 == 80))
			continue;
		else
		{
			if (choice2 == 72)
				i--;
			else if (choice2 == 80)
				i++;
			else
				continue;

			for (int x = 0; x < 2 - strlen(c); x++)
				printf(" ");
			for (int x = 0; x < 2 + 1; x++)
				printf("\b");
			printf("%02d", i);
			sprintf(c, "%02d", i);
			for (int x = 0; x < 2 - strlen(c); x++)
				printf("\b");
			printf("%c", lastChar);
		}
	}

	return i;
}
int daySelect(int start, int min, int max)
{
	unsigned char choice1, choice2;
	int i;
	char c[10];

	printf("%02d", start);
	sprintf(c, "%02d", start);
	for (int x = 0; x < 2 - strlen(c); x++)
		printf("\b");
	for (i = start;;)
	{
		rewind(stdin);
		choice1 = getch();

		if (choice1 == '\n' || choice1 == '\r')
			break;
		else if (choice1 != 224)
			continue;

		rewind(stdin);
		choice2 = getch();

		if ((i == min && choice2 == 72) || (i == max && choice2 == 80))
			continue;
		else
		{
			if (choice2 == 72)
				i--;
			else if (choice2 == 80)
				i++;
			else
				continue;

			for (int x = 0; x < 2 - strlen(c); x++)
				printf(" ");
			for (int x = 0; x < 2; x++)
				printf("\b");
			printf("%02d", i);
			sprintf(c, "%02d", i);
			for (int x = 0; x < 2 - strlen(c); x++)
				printf("\b");
		}
	}

	return i;
}
int timeSelect(int start, int min, int max)
{
	unsigned char choice1, choice2;
	int i;
	char c[10];

	printf("%04d", start);
	sprintf(c, "%04d", start);
	for (int x = 0; x < 4 - strlen(c); x++)
		printf("\b");
	for (i = start;;)
	{
		rewind(stdin);
		choice1 = getch();

		if (choice1 == '\n' || choice1 == '\r')
			break;
		else if (choice1 != 224)
			continue;

		rewind(stdin);
		choice2 = getch();

		if ((i == min && choice2 == 72) || (i == max && choice2 == 80))
			continue;
		else
		{
			if (choice2 == 72)
				i -= 100;
			else if (choice2 == 80)
				i += 100;
			else
				continue;

			for (int x = 0; x < 4 - strlen(c); x++)
				printf(" ");
			for (int x = 0; x < 4; x++)
				printf("\b");
			printf("%04d", i);
			sprintf(c, "%04d", i);
			for (int x = 0; x < 4 - strlen(c); x++)
				printf("\b");
		}
	}

	return i;
}
void passwordInput(char* input, int size)
{
	int i = 0;
	while (i <= size - 1)
	{
		input[i] = getch();

		if ((i == 0 && input[i] == '\b') || i == size - 1)
			continue;
		else if (input[i] == '\b')
		{
			printf("\b \b");
			i--;
		}
		else if (input[i] == '\n' || input[i] == '\r')
		{
			input[i] = '\0';
			printf("\n");
			break;
		}
		else
		{
			printf("*");
			i++;
		}
	}
}
char confirmSelectWithX()
{
	unsigned char choice1, choice2;
	char confirm = 'Y';

	printf("%c", confirm);
	while (1)
	{
		rewind(stdin);
		choice1 = getch();

		if (choice1 == '\n' || choice1 == '\r')
			break;
		else if (choice1 != 224)
			continue;

		rewind(stdin);
		choice2 = getch();

		if (choice2 == 80)
		{
			if (confirm == 'Y')
				confirm = 'N';
			else if (confirm == 'N')
				confirm = 'X';
			else
				confirm = 'Y';
		}
		else if (choice2 == 72)
		{
			if (confirm == 'Y')
				confirm = 'X';
			else if (confirm == 'X')
				confirm = 'N';
			else
				confirm = 'Y';
		}
		else
			continue;

		printf("\b");
		printf("%c", confirm);
	}

	printf("\n");
	return confirm;
}

int checkDateRange(Date startRange, Date endRange, Date bookDate)
{
	if (bookDate.year > startRange.year && bookDate.year < endRange.year)
		return 1;
	else if (bookDate.year == startRange.year && bookDate.year == endRange.year)
	{
		if (bookDate.month > startRange.month && bookDate.month < endRange.month)
			return 1;
		else if (bookDate.month == startRange.month && bookDate.month == endRange.month)
		{
			if (bookDate.day >= startRange.day && bookDate.day <= endRange.day)
				return 1;
			else
				return 0;
		}
		else if (bookDate.month == startRange.month)
		{
			if (bookDate.day >= startRange.day)
				return 1;
			else
				return 0;
		}
		else if (bookDate.month == endRange.month)
		{
			if (bookDate.day <= endRange.day)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (bookDate.year == startRange.year)
	{
		if (bookDate.month > startRange.month)
			return 1;
		else if (bookDate.month == startRange.month)
		{
			if (bookDate.day >= startRange.day)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (bookDate.year == endRange.year)
	{
		if (bookDate.month < endRange.month)
			return 1;
		else if (bookDate.month == endRange.month)
		{
			if (bookDate.day <= endRange.day)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

int writeLog(FILE** _Stream, char const* const _Format, ...)
{
	FILE *fBook;
	int year, month, day, hour, minute, second;
	char userID[9], bookID[8], desc[30];

	*_Stream = fopen("TempBookingLog.txt", "w");
	int _Result;
	va_list _ArgList;
	va_start(_ArgList, _Format);
	_Result = vfprintf(*_Stream, _Format, _ArgList);
	va_end(_ArgList);

	fBook = fopen("BookingLog.txt", "r");
	if (fBook != NULL)
	{
		while (!feof(fBook))
		{
			fscanf(fBook, "%d/%d/%d %d:%d:%d - %[^ ] - %[^-]- %[^.].\n", &year, &month, &day, &hour, &minute, &second,
				userID, desc, bookID);
			fprintf(*_Stream, "%04d/%02d/%02d %02d:%02d:%02d - %s - %s- %s.\n", year, month, day, hour, minute, second, userID, desc, bookID);
		}
		fclose(fBook);
	}
	fclose(*_Stream);

	if (fBook != NULL)
		system("del BookingLog.txt");
	system("ren TempBookingLog.txt BookingLog.txt");
	return _Result;
}