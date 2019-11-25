#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"Header.h"
#pragma warning(disable:4996)

typedef struct
{
	char facID[10], facType[200], facDescription[300], facVenue[100], facDateTime[20];

}Facility;
Facility fac1;

typedef struct
{
	char facname[30];
}FacName;
FacName facName;

char check, anything;

void viewfac();
void addfac();
void editfac();
void searchfac();

void main1234()
{
	int choice1;

	printf(" _____   ____    __  ____  _      ____  ______  __ __      ___ ___   ___   ___    __ __  _        ___ \n"
		"|     | /    |  /  ]|    || |    |    ||      ||  |  |    |   |   | /   \\ |   \\  |  |  || |      /  _]\n"
		"|   __||  o  | /  /  |  | | |     |  | |      ||  |  |    | _   _ ||     ||    \\ |  |  || |     /  [_ \n"
		"|  |_  |     |/  /   |  | | |___  |  | |_|  |_||  ~  |    |  \\_/  ||  O  ||  D  ||  |  || |___ |    _]\n"
		"|   _] |  _  /   \\_  |  | |     | |  |   |  |  |___, |    |   |   ||     ||     ||  :  ||     ||   [_ \n"
		"|  |   |  |  \\     | |  | |     | |  |   |  |  |     |    |   |   ||     ||     ||     ||     ||     |\n"
		"|__|   |__|__|\\____||____||_____||____|  |__|  |____/     |___|___| \\___/ |_____| \\__,_||_____||_____|\n");
	printf("\n1.View Facility Info\n2.Add Facility Info\n3.Edit Facility Module\n4.Search Facility Info\n5.Exit\n\n ");
	printf("Please enter your choice  :  ");
	rewind(stdin);
	scanf("%d%c", &choice1, &check);
	while (choice1 <= 0 || choice1 >= 6 || check != '\n')
	{
		printf("Invalid Input,Please enter 1 or 2 or 3 or 4 or 5 only. ;]  :  ");
		rewind(stdin);
		scanf("%d%c", &choice1, &check);
	}
	system("cls");

	switch (choice1)
	{


	case 1:
		viewfac(); break;
	case 2:
		addfac(); break;
	case 3:
		editfac(); break;
	case 4:
		searchfac(); break;
	default:
	{
		printf("Link to main page");
		system("pause"); break;
	}

	}
	system("pause");
}
void viewfac()
{


	FILE*fp;
	FILE*fq;
	fp = fopen("facilitylist.txt", "r");
	fq = fopen("facilityname.txt", "r");
	if (fp == NULL)
	{
		printf("Unable to open file facilitylist.txt\n");
		system("pause");
		exit(-1);
	}

	if (fq == NULL)
	{
		printf("Unable to open file facilityname.txt\n");
		system("pause");
		exit(-1);
	}


	printf(" _____   ____    __  ____  _      ____  ______  __ __      ___ ___   ___   ___    __ __  _        ___ \n"
		"|     | /    |  /  ]|    || |    |    ||      ||  |  |    |   |   | /   \\ |   \\  |  |  || |      /  _]\n"
		"|   __||  o  | /  /  |  | | |     |  | |      ||  |  |    | _   _ ||     ||    \\ |  |  || |     /  [_ \n"
		"|  |_  |     |/  /   |  | | |___  |  | |_|  |_||  ~  |    |  \\_/  ||  O  ||  D  ||  |  || |___ |    _]\n"
		"|   _] |  _  /   \\_  |  | |     | |  |   |  |  |___, |    |   |   ||     ||     ||  :  ||     ||   [_ \n"
		"|  |   |  |  \\     | |  | |     | |  |   |  |  |     |    |   |   ||     ||     ||     ||     ||     |\n"
		"|__|   |__|__|\\____||____||_____||____|  |__|  |____/     |___|___| \\___/ |_____| \\__,_||_____||_____|\n\n");
	while (fscanf(fq, "%[^|]|\n", &facName.facname) != EOF)
	{
		printf("%s\n", &facName.facname);
	}

	printf("\n");
	printf("________________________________________________________________________________________________________________________\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|\n", 
		&fac1.facID, &fac1.facType, &fac1.facDescription, &fac1.facVenue, &fac1.facDateTime) != EOF)
	{
		printf("|  Facility ID             : %-90s|\n|  Facility Type           : %-90s|\n|  Facility Description    : %-90s|\n|  Facility Venue          : %-90s|\n|  Facility Operation Hour : %-90s|\n|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", fac1.facID, fac1.facType, fac1.facDescription, fac1.facVenue, fac1.facDateTime);

	}
	printf("________________________________________________________________________________________________________________________\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");

	fclose(fp);
	fclose(fq);
	printf("Press any key to back to main screen (*^~0~^*)  :  ");
	rewind(stdin);
	scanf("%c", &anything);
	system("cls");
	//main();
}

void addfac()
{
	char ans2;
	FILE*fp;
	FILE*fq;
	fp = fopen("facilitylist.txt", "a");
	fq = fopen("facilityname.txt", "a");
	if (fp == NULL)
	{

		printf("Unable to open file facilitylist.txt\n");
		system("pause");
		exit(-1);
	}
	if (fq == NULL)
	{

		printf("Unable to open file facilityname.txt\n");
		system("pause");
		exit(-1);
	}
	printf(" _____   ____    __  ____  _      ____  ______  __ __      ___ ___   ___   ___    __ __  _        ___ \n"
		"|     | /    |  /  ]|    || |    |    ||      ||  |  |    |   |   | /   \\ |   \\  |  |  || |      /  _]\n"
		"|   __||  o  | /  /  |  | | |     |  | |      ||  |  |    | _   _ ||     ||    \\ |  |  || |     /  [_ \n"
		"|  |_  |     |/  /   |  | | |___  |  | |_|  |_||  ~  |    |  \\_/  ||  O  ||  D  ||  |  || |___ |    _]\n"
		"|   _] |  _  /   \\_  |  | |     | |  |   |  |  |___, |    |   |   ||     ||     ||  :  ||     ||   [_ \n"
		"|  |   |  |  \\     | |  | |     | |  |   |  |  |     |    |   |   ||     ||     ||     ||     ||     |\n"
		"|__|   |__|__|\\____||____||_____||____|  |__|  |____/     |___|___| \\___/ |_____| \\__,_||_____||_____|\n\n");

	printf("Please enter new facility name  :  ");
	rewind(stdin);
	scanf("%[^\n]%c", &facName.facname, &check);
	while (check != '\n')
	{
		printf("Invalid Input,Please enter again\n");
		printf("Please enter new facility name  :  ");
		rewind(stdin);
		scanf("%[^\n]%c", &facName.facname, &check);
	}
	fprintf(fq, "A006 : %s|\n", facName.facname);

	printf("Are you a staff of Dewan Ah Lock multipurpose hall?(y/n)  :  ");
	scanf("%c", &ans2);
	while (toupper(ans2) != 'Y' && toupper(ans2) != 'N')
	{
		printf("Invalid input! Please enter y or n only { ;~( }\n");
		printf("Are you a staff of Dewan Ah Lock multipurpose hall?(y/n)    :  ");
		rewind(stdin);
		scanf("%c", &ans2);
	}
	if (toupper(ans2) == 'Y')
	{
		printf("Facility ID (Eg:A001)                                       :  ");
		rewind(stdin);
		scanf("%[^\n]", &fac1.facID);
		printf("Facility Type (Eg:shuttlecocks,scoreboards)                 :  ");
		rewind(stdin);
		scanf("%[^\n]", &fac1.facType);
		printf("Facility Description (Eg:Each player must...)               :  ");
		rewind(stdin);
		scanf("%[^\n]", &fac1.facDescription);
		printf("Facility ID (Eg:ground floor of Dewan Ah Lock)              :  ");
		rewind(stdin);
		scanf("%[^\n]", &fac1.facVenue);
		printf("Facility Opertation time (Eg:9a.m.-3p.m.,Monday to Thursday):  ");
		rewind(stdin);
		scanf("%[^\n]", &fac1.facDateTime);
		printf("\nCongratulations,you have sucessfully add a new facility info.\n");
		fprintf(fp, "%s|%s|%s|%s|%s|\n", fac1.facID, fac1.facType, fac1.facDescription, fac1.facVenue, fac1.facDateTime);
		printf("Press any key to back to main screen (*^~0~^*)  :  ");
		rewind(stdin);
		scanf("%c", &anything);
		fclose(fp);
		fclose(fq);
		system("cls");
		//main();
	}
	else
	{
		printf("Sorry,only staff of Dewan Ah Lock is allowed to add facility info.\n");
		printf("Press any key to back to main screen (*^~0~^*)  :  ");
		rewind(stdin);
		scanf("%c", &anything);
		fclose(fp);
		fclose(fq);
		system("cls");
		//main();
	}
}

void editfac()
{
	FILE*fp;
	FILE*fq;
	fp = fopen("facilitylist.txt", "a");
	fq = fopen("facilityname.txt", "a");
	if (fp == NULL)
	{

		printf("Unable to open file facilitylist.txt\n");
		system("pause");
		exit(-1);
	}
	if (fq == NULL)
	{

		printf("Unable to open file facilityname.txt\n");
		system("pause");
		exit(-1);
	}
	printf("Please enter the facility id to delete");
}

void searchfac()
{
	printf("yaya");
}

