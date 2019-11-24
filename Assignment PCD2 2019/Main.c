/*
Staff Information Module - Chong Ke Wei
Facility Module - Ng Jeriel
User Information Module - Khaw Zhe Xue
Booking Module - Ong Chen Xiang
Facility Usage Module - Chin Sze Sing
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Header.h"
#pragma warning(disable:4996)

// Declaration of self-defined function.

// Art of Login Screen.
void loginArt();
// Login Screen. It return user inputed selection.
char loginScreen();

int main7870()
{
	int i = 0;
	char menuSelection, selection[2];

	loginArt();
	menuSelection = loginScreen();
	switch (menuSelection)
	{
	case '1':
		break;
	case '2':
		break;
	case '3':
		return 0;
	}

	system("cls");
	while (1)
	{
		printf("\n%55sMAIN MENU%55s", "", "");
		printf("\n%55s---------%55s", "", "");
		printf("%48sToday's Date: %02d/%02d/%d\n", "", todayDate("day"), todayDate("month"), todayDate("year"));
		printf("%43s---------------------------------%43s\n", "", "");
		printf("%43s| [1] Staff Information Module  |%43s\n", "", "");
		printf("%43s| [2] Facility Module           |%43s\n", "", "");
		printf("%43s| [3] Facility Usage Module     |%43s\n", "", "");
		printf("%43s| [4] Booking Module            |%43s\n", "", "");
		printf("%43s| [5] Exit                      |%43s\n", "", "");
		printf("%43s---------------------------------%43s\n", "", "");

		// Let user to choose a selection.
		// To let user only input 1, 2 and 3.
		printf("%45sPlease choose a selection: ", "");
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
			else if (selection[i] != '1' && selection[i] != '2' && selection[i] != '3' && selection[i] != '4' && selection[i] != '5')
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
			//Facility(); break;
		case '2':
			//FacilityUsage(); break;
		case '3':
			//Booking(); break;
		case '4':
			//StaffInformation();
			break;
		case '5':
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
	for (int i = 0; i < 120; i++)
		printf("-");
	printf("\n\n");
}

char loginScreen()
{
	int i = 0;
	char selection[2];

	printf("%49sSPORT FACILITY SYSTEM%49s\n", "", "");
	printf("%51s-----------------%51s\n", "", "");
	printf("%51s| [1]  LOGIN    |%51s\n", "", "");
	printf("%51s| [2]  REGISTER |%51s\n", "", "");
	printf("%51s| [3]  EXIT     |%51s\n", "", "");
	printf("%51s-----------------%51s\n", "", "");
	printf("%48sToday's Date: %02d/%02d/%d\n", "", todayDate("day"), todayDate("month"), todayDate("year"));
	printf("%48sWritten by: Ong Chen Xiang\n", "");
	printf("%48s            Ng Jeriel\n", "");
	printf("%48s            Chong Ke Wei\n", "");
	printf("%48s            Chin Sze Sing\n", "");
	printf("%48s            Khaw Zhe Xue\n\n", "");
	printf("%47sPlease choose a selection: ", "");
	
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

	return selection[0];
}