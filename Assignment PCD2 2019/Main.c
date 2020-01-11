#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Header.h"
#pragma warning(disable:4996)

void mainLogo();
void loginMenu();
void mainMenu(char userType);
void newToOldBooking();

int main(char loginacc[])
{
	int choice;
	char success = 'Y';
	char userType, userID[10], password[20];

	newToOldBooking();

	while (1)
	{
		do
		{
			mainLogo();
			printf("\n\n");
			loginMenu();
			printf("%44sPress UP and DOWN button to select.\n", "");
			printf("%46sPlease choose a selection: ", "");
			choice = numSelect(1, 1, 3);

			system("cls");
			switch (choice)
			{
			case 1:
				studentLogin(&userType, userID, password);
				printf("%40sPress any key will continue...", "");
				getch();
				break;
			case 2:
				success = staffLogin(&userType, userID, password);
				break;
			case 3:
				exit(-1);
			}
		} while (success == 'N');

		while (1)
		{
			system("cls");
			mainLogo();
			printf("\n\n\n");
			mainMenu(userType);
			printf("%46sPlease choose a selection: ", "");
			if (userType == 'T')
			{
				choice = numSelect(1, 1, 5);
				system("cls");
				switch (choice)
				{
				case 1:
					BookingMod(userType, userID, password);
					break;
				case 2:
					UserInformationMod();
					break;
				case 3:
					FacilityMod(userType);
					break;
				case 4:
					FacilityUsageMod(userType, userID);
					break;
				case 5:
					break;
				}
				if (choice == 5)
					break;
			}
			else
			{
				choice = numSelect(1, 1, 6);
				system("cls");
				switch (choice)
				{
				case 1:
					BookingMod(userType, userID, password);
					break;
				case 2:
					UserInformationMod();
					break;
				case 3:
					StaffInformationMod(userID);
					break;
				case 4:
					FacilityMod(userType);
					break;
				case 5:
					FacilityUsageMod(userType, userID);
					break;
				case 6:
					break;
				}
				if (choice == 6)
					break;
			}
		}
	}

}

void mainLogo()
{
	printf("%7s  _____ ____   ___   ____  ______      _____   ____    __  ____  _      ____  ______  ____    ___  _____\n", "");
	printf("%7s / ___/|    \\ /   \\ |    \\|      |    |     | /    |  /  ]|    || |    |    ||      ||    |  /  _]/ ___/\n", "");
	printf("%7s(   \\_ |  o  )     ||  D  )      |    |   __||  o  | /  /  |  | | |     |  | |      | |  |  /  [_(   \\_ \n", "");
	printf("%7s \\__  ||   _/|  O  ||    /|_|  |_|    |  |_  |     |/  /   |  | | |___  |  | |_|  |_| |  | |    _]\\__  |\n", "");
	printf("%7s /  \\ ||  |  |     ||    \\  |  |      |   _] |  _  /   \\_  |  | |     | |  |   |  |   |  | |   [_ /  \\ |\n", "");
	printf("%7s \\    ||  |  |     ||  .  \\ |  |      |  |   |  |  \\     | |  | |     | |  |   |  |   |  | |     |\\    |\n", "");
	printf("%7s  \\___||__|   \\___/ |__|\\_| |__|      |__|   |__|__|\\____||____||_____||____|  |__|  |____||_____| \\___|\n", "");
}

void loginMenu()
{
	printf("%57sTARUC\n", "");
	printf("%48sSPORT FACILITIES SYSTEM\n", "");
	printf("%48s-----------------------\n", "");
	printf("%54sProduced By:\n", "");
	printf("%54s----------- \n", "");
	printf("%53sONG CHEN XIANG\n", "");
	printf("%55sNG JERIEL\n", "");
	printf("%54sCHONG KE WEI\n", "");
	printf("%53sCHIN SZE SING\n", "");
	printf("%54sKHAW ZHE XUE\n", "");
	printf("%49s---------------------\n", "");
	printf("%49s| [1] STUDENT LOGIN |\n", "");
	printf("%49s| [2] STAFF LOGIN   |\n", "");
	printf("%49s| [3] EXIT          |\n", "");
	printf("%49s---------------------\n", "");
}

void mainMenu(char userType)
{
	if (userType == 'T')
	{
		printf("%55sMAIN MENU\n", "");
		printf("%45s-----------------------------\n", "");
		printf("%45s| [1] Manage Booking        |\n", "");
		printf("%45s| [2] Manage User Profile   |\n", "");
		printf("%45s| [3] Check Facility Info   |\n", "");
		printf("%45s| [4] Check Facility Usage  |\n", "");
		printf("%45s| [5] Exit                  |\n", "");
		printf("%45s-----------------------------\n", "");
	}
	else
	{
		printf("%55sMAIN MENU\n", "");
		printf("%45s-----------------------------\n", "");
		printf("%45s| [1] Manage Booking        |\n", "");
		printf("%45s| [2] Manage Student Info   |\n", "");
		printf("%45s| [3] Manage Staff Info     |\n", "");
		printf("%45s| [4] Manage Facility Info  |\n", "");
		printf("%45s| [5] Check Facility Usage  |\n", "");
		printf("%45s| [6] Exit                  |\n", "");
		printf("%45s-----------------------------\n", "");
	}
}

void newToOldBooking()
{
	FILE *fOld, *fBook, *fNew;
	Date checkDate;
	int startTime, endTime;
	char thing1[10], thing2[20], thing3[60];

	fBook = fopen("BookingList.txt", "r");
	if (fBook == NULL)
		return;
	fOld = fopen("OldBookingList.txt", "a");
	if (fOld == NULL)
		fOld = fopen("OldBookingList.txt", "w");
	fNew = fopen("TempBookingList.txt", "w");

	while (!feof(fBook))
	{
		fscanf(fBook, "%[^|]|%[^|]|%d/%d/%d|%d-%d|%[^\n]\n", thing1, thing2, &checkDate.day, &checkDate.month, &checkDate.year, &startTime, &endTime, thing3);
		if (checkDate.day <= todayDate("day") && checkDate.month <= todayDate("month") && checkDate.year <= todayDate("year") &&
			endTime <= todayDate("hour") * 100 + todayDate("minute"))
			fprintf(fOld, "%s|%s|%02d/%02d/%04d|%04d-%04d|%s\n", thing1, thing2, checkDate.day, checkDate.month, checkDate.year, startTime, endTime, thing3);
		else
			fprintf(fNew, "%s|%s|%02d/%02d/%04d|%04d-%04d|%s\n", thing1, thing2, checkDate.day, checkDate.month, checkDate.year, startTime, endTime, thing3);
	}

	fclose(fBook);
	fclose(fOld);
	fclose(fNew);

	system("del BookingList.txt");
	system("ren TempBookingList.txt BookingList.txt");
}