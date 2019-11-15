/*
Staff Information Module - Chong Ke Wei
Facility Module - Ng Jeriel
User Information Module - Khaw Zhe Xue
Booking Module - Ong Chen Xiang
Facility Usage Module - Chin Sze Sing
*/

#include <stdio.h>
#include "Header.h"
#pragma warning(disable:4996)

void loginScreen();

int main3()
{
	int selection = -1;
	char valid;

	void loginScreen();
	while (1)
	{
		printf("\n1. Facility detail\n");
		printf("2. Checking facility usage\n");
		printf("3. Booking a facility\n");
		printf("4. Register\n");
		printf("5. Staff related perform\n");
		printf("6. Exit");

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

void loginScreen()
{

}