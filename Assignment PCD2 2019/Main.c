/*
Staff Information Module - Chong Ke Wei
Facility Module - Ng Jeriel
User Information Module - Khaw Zhe Xue
Booking Module - Ong Chen Xiang
Facility Usage Module - Chin Sze Sing
*/

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#pragma warning(disable:4996)

// Declaration of self-defined function.
void loginArt();
void loginScreen();

int main0()
{
	int selection = -1;
	char valid;

	loginArt();
	loginScreen();
	while (1)
	{
		printf("1. Facility detail\n");
		printf("2. Checking facility usage\n");
		printf("3. Booking a facility\n");
		printf("4. Register\n");
		printf("5. Staff related perform\n");
		printf("6. Exit\n");

		// Let user to choose a selection.
		printf("Choose a selection to proceed: ");
		rewind(stdin);
		scanf("%d%c", &selection, &valid);

		while (selection < 1 || selection > 6 || valid != '\n')
		{
			printf("Invalid input! Please try again: ");
			selection = -1;
			rewind(stdin);
			scanf("%d%c", &selection, &valid);
		}

		switch (selection)
		{
		case 1:
			//Facility(); break;
		case 2:
			//FacilityUsage(); break;
		case 3:
			//Booking(); break;
		case 4:
			//UserInformation(); break;
		case 5:
			//StaffInformation();
			break;
		case 6:
			return 0;
		}
	}
}

void loginArt()
{
	printf("%16s  _________                     __    ___________             .__.__  .__  __          %16s\n", "", "");
	printf("%16s /   _____/_____   ____________/  |_  \\_   _____/____    ____ |__|  | |__|/  |_ ___.__.%16s\n", "", "");
	printf("%16s \\_____  \\\\____ \\ /  _ \\_  __ \\   __\\  |    __) \\__  \\ _/ ___\\|  |  | |  \\   __<   |  |%16s\n", "", "");
	printf("%16s /        \\  |_> >  <_> )  | \\/|  |    |     \\   / __ \\\\  \\___|  |  |_|  ||  |  \\___  |%16s\n", "", "");
	printf("%16s/_______  /   __/ \\____/|__|   |__|    \\___  /  (____  /\\___  >__|____/__||__|  / ____|%16s\n", "", "");
	printf("%16s        \\/|__|                             \\/        \\/     \\/                  \\/     %16s\n", "", "");
}

void loginScreen()
{
	int i = 0;
	char selection[2];

	printf("\n%49sSPORT FACILITY SYSTEM%49s\n", "", "");
	printf("%51s-----------------%51s\n", "", "");
	printf("%51s| [1]  LOGIN    |%51s\n", "", "");
	printf("%51s| [2]  REGISTER |%51s\n", "", "");
	printf("%51s| [3]  EXIT     |%51s\n", "", "");
	printf("%51s-----------------%51s\n\n", "", "");
	printf("%46sPlease choose a selection: ", "");
	
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
		else if (selection[i] == '\n' || selection[i] == '\b' || selection[i] == '\r')
			continue;
		else
		{
			printf("%c", selection[i]);
			i++;
		}
	}
	system("cls");
}