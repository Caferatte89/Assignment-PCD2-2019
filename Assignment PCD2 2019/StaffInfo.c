#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include "Header.h"
#pragma warning(disable:4996)

struct DateStaff
{
	int day;
	char month[10];
	int year;
}birth;

struct Staffinfo
{
	char idCode;
	int idNum;
	char staffId[6], staffName[31], password[21], gender;
	struct DateStaff birth;
	char email[31], phoneNum[13], position[21];
}staff,modify[100];

void errorStaff();
void addStaff(char loginacc[]);
void searchStaff(char loginacc[]);
void modifyStaff(char loginacc[]);
void displayStaff(char loginacc[]);
void delStaff(char loginacc[]);
void exitFunc(char loginacc[],char Y[]);
void endOfFunc(char loginacc[]);
void hidepwStaff(char password[21]);

char staffLogin(char* userType, char* userID, char* userpassword)
{
	FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
	FILE*wstaffInfo = fopen("StaffInfo.bin", "ab");
	//check if the file was exist or not
	if (rstaffInfo == NULL || wstaffInfo == NULL)
	{
		printf("%45s The StaffInfo.bin file cannot open!!!", "");
		system("pause");
		exit(-1);
	}

	printf("\t\t\t  _____ ______   ____  _____  _____      _       ___    ____  ____  ____  \n"
		"\t\t\t \\ ___/|      | /    ||     ||     |    | |     /   \\  /    ||    ||    \\ \n"
		"\t\t\t(   \\_ |      ||  o  ||   __||   __|    | |    |     ||   __| |  | |  _  |\n"
		"\t\t\t \\__  ||_|  |_||     ||  |_  |  |_      | |___ |  O  ||  |  | |  | |  |  |\n"
		"\t\t\t /  \\ |  |  |  |  _  ||   _] |   _]     |     ||     ||  |_ | |  | |  |  |\n"
		"\t\t\t \\    |  |  |  |  |  ||  |   |  |       |     ||     ||     | |  | |  |  |\n"
		"\t\t\t  \\___|  |__|  |__|__||__|   |__|       |_____| \\___/ |___,_||____||__|__|\n\n");
	char loginacc[6], password[21];
	int i, total;

	do
	{
		i = 0;
		total = 0;
		printf("%45s Enter (XXX) to back to the main menu.\n\n", "");
		printf("%45s Please login to your account:\n", "");
		printf("%45s Staff ID.\n", "");
		printf("%45s >>> ", "");
		rewind(stdin);
		scanf("%5s", &loginacc);
		if (strcmp(loginacc, "XXX") == 0 || strcmp(loginacc, "xxx") == 0)
		{
			system("cls");
			return'N';
		}
		FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
		while (fread(&staff, sizeof(staff), 1, rstaffInfo) != 0)
		{
			total++;
			while (strcmp(staff.staffId, loginacc) != 0)
			{
				i++;
				break;
			}
			if (strcmp(staff.staffId, loginacc) == 0)
				break;
		}
		if (total == i)
		{
			printf("%45s The staff ID do not exist! Please reenter.\n", "");
		}
	} while (total == i);
	do
	{
		printf("%45s password.\n", "");
		printf("%45s >>> ", "");
		rewind(stdin);
		hidepwStaff(password);
		printf("%45s \n", "");
		if (strcmp(password, "XXX") == 0 || strcmp(password, "xxx") == 0)
		{
			system("cls");
			return 'N';
		}
		if (strcmp(staff.password, password) == 0)
		{
			printf("%45s Login successful!\n\n", "");
			printf("%45s ", "");
			system("cls");
			*userType = 'S';
			strcpy(userID, loginacc);
			strcpy(userpassword, password);
			return 'Y';
		}
		else
		{
			errorStaff();
			printf("%45s Password incorrect! Please reenter.\n", "");
		}
	} while (strcmp(staff.password, password) != 0);
	fclose(rstaffInfo);
	fclose(wstaffInfo);
}

void errorStaff()
{
	printf("\t\t\t\t\t     ___ ___ ___  ___  ___   _ \n"
		"\t\t\t\t\t    | __| _ \\ _ \\/ _ \\| _ \\ | |\n"
		"\t\t\t\t\t    | _||   /   / (_) |   / |_|\n"
		"\t\t\t\t\t    |___|_|_\\_|_\\\\___/|_|_\\ (_)\n\n");
}

void StaffInformationMod(char loginacc[])
{
	//declaration
	int task;

	printf("\t\t\t\t\t __    __    ___  _        __   ___   ___ ___    ___ \n"
		"\t\t\t\t\t|  |__|  |  /  _]| |      /  ] /   \\ |   |   |  /  _]\n"
		"\t\t\t\t\t|  |  |  | /  [_ | |     /  / |     || _   _ | /  [_ \n"
		"\t\t\t\t\t|  |  |  ||    _]| |___ /  /  |  O  ||  \\_/  ||    _]\n"
		"\t\t\t\t\t|  `  '  ||   [_ |     /   \\_ |     ||   |   ||   [_ \n"
		"\t\t\t\t\t \\      / |     ||     \\     ||     ||   |   ||     |\n"
		"\t\t\t\t\t  \\_/\\_/  |_____||_____|\\____| \\___/ |___|___||_____|\n\n");

	FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
	while (fread(&staff, sizeof(staff), 1, rstaffInfo) != 0)
	{
		if (strcmp(staff.staffId, loginacc) == 0)
			break;
	}
	printf("%50s Hye,%s!=)\n\n", "", staff.staffName);
	printf("%35s    Select the number to perform the following tasks.\n\n", "");
	printf("%45s ---------------------------------------\n"
		   "%45s |  1.Adding new staff.                |\n"
		   "%45s |  2.Searching for a staff.           |\n"
		   "%45s |  3.Modify staff information.        |\n"
		   "%45s |  4.Display all staff info.          |\n"
	   	   "%45s |  5.Delete staff account.            |\n"
		   "%45s |  6.Exit.                            |\n"
		   "%45s ---------------------------------------\n\n", "", "", "", "", "", "","","");
	printf("%45s Please select your choice.\n", "");
	printf("%45s >>> ", "");
	task = numSelect(1, 1, 6);
	switch (task)
	{
	case 1:
		system("cls");
		addStaff(loginacc);
		break;
	case 2:
		system("cls");
		searchStaff(loginacc);
		break;
	case 3:
		system("cls");
		modifyStaff(loginacc);
		break;
	case 4:
		system("cls");
		displayStaff(loginacc);
		break;
	case 5:
		system("cls");
		delStaff(loginacc);
		break;
	case 6:
		system("cls");
		main(loginacc);
	}
}
void addStaff(char loginacc[])
{
	printf("\t\t\t\t  ____  ___    ___         _____ ______   ____  _____  _____ \n"
		"\t\t\t\t /    ||   \\  |   \\       / ___/|      | /    ||     ||     |\n"
		"\t\t\t\t|  o  ||    \\ |    \\     (   \\_ |      ||  o  ||   __||   __|\n"
		"\t\t\t\t|     ||  D  ||  D  |     \\__  ||_|  |_||     ||  |_  |  |_  \n"
		"\t\t\t\t|  _  ||     ||     |     /  \\ |  |  |  |  _  ||   _] |   _] \n"
		"\t\t\t\t|  |  ||     ||     |     \\    |  |  |  |  |  ||  |   |  |   \n"
		"\t\t\t\t|__|__||_____||_____|      \\___|  |__|  |__|__||__|   |__|   \n\n");
	printf("%45s (Enter (XXX) to exit the add function.)\n", "");
	//declaration
	char password[21], confirmPW[21], store[5], choice = 'Y';
	int month, last = 0, i, counter = 0, leap;    

	do
	{
		FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
		FILE*wstaffInfo = fopen("StaffInfo.bin", "ab");
		while (fread(&staff, sizeof(staff), 1, rstaffInfo) != 0)
		{
			//find the last number of the staff id
			if (staff.idNum > last)
			{
				last = staff.idNum;
			}
			else
				continue;
		}
		if (last < 9)
		{
			staff.idNum = last + 1;
			staff.idCode = 'S';
			strcpy(staff.staffId, "S000");
			sprintf(store, "%d", last + 1);
			strcat(staff.staffId, store);
		}
		else if (last < 99)
		{
			staff.idNum = last + 1;
			staff.idCode = 'S';
			strcpy(staff.staffId, "S00");
			sprintf(store, "%d", last + 1);
			strcat(staff.staffId, store);
		}
		else if (last < 999)
		{
			staff.idNum = last + 1;
			staff.idCode = 'S';
			strcpy(staff.staffId, "S0");
			sprintf(store, "%d", last + 1);
			strcat(staff.staffId, store);
		}
		else if (last < 9999)
		{
			staff.idNum = last + 1;
			staff.idCode = 'S';
			strcpy(staff.staffId, "S");
			sprintf(store, "%d", last + 1);
			strcat(staff.staffId, store);
		}
		printf("%45s Staff ID\n", "");
		printf("%45s >>> %s\n", "", staff.staffId);
		do
		{
			printf("%45s Name.\n", "");
			printf("%45s >>> ", "");
			rewind(stdin);
			scanf("%[^\n]", &staff.staffName);
			exitFunc(loginacc, staff.staffName);
			counter = 0;
			for (i = 0; i < strlen(staff.staffName); i++)
			{
				if (isalpha(staff.staffName[i]) == 0 && staff.staffName[i] != ' ')
				{
					counter++;
					printf("%45s The name must contain only characters!\n", "");
					printf("%45s Please reenter.\n", "");
					break;
				}
				else
					continue;
			}
		} while (counter != 0);
		do
		{
			printf("%45s Password(8-20characters)\n", "");
			printf("%45s >>> ", "");
			rewind(stdin);
			hidepwStaff(password);
			exitFunc(loginacc, password);
			while (strlen(password) < 8 || strlen(password) > 20)
			{
				printf("%45s Please enter only 8 to 20 characters for the password!\n", "");
				printf("%45s Password(8-20characters)\n", "");
				printf("%45s >>> ", "");
				rewind(stdin);
				hidepwStaff(password);
				exitFunc(loginacc, password);
			}
			do
			{
				printf("%45s Please confirm your password.\n", "");
				printf("%45s >>> ", "");
				rewind(stdin);
				hidepwStaff(confirmPW);
				exitFunc(loginacc, confirmPW);
				if (strcmp(confirmPW, "YYY") == 0 || strcmp(confirmPW, "yyy") == 0)
				{
					break;
				}
				if (strcmp(password, confirmPW) == 0)
				{
					strcpy(staff.password, password);
				}
				else
				{
					printf("%45s The password was not match! Please confirm your password.\n", "");
					printf("%45s (Enter (YYY) to reenter the password.)\n\n", "");
				}
			} while (strcmp(password, confirmPW) != 0);
		} while (strcmp(confirmPW, "YYY") == 0 || strcmp(confirmPW, "yyy") == 0);
		printf("%45s Gender(F=female,M=male)\n", "");
		printf("%45s >>> ", "");
		staff.gender = confirmSelect('M', 'F');
		printf("%45s Birth date:\n", "");
		printf("%45s Year.\n", "");
		printf("%45s >>> ", "");
		staff.birth.year = numSelect(1940, 1940, 2019);
		printf("%45s Month(1-12)\n", "");
		printf("%45s >>> ", "");
		month = numSelect(1, 1, 12);
		switch (month)
		{
		case 1:
			strcpy(staff.birth.month, "January");
			break;
		case 2:
			strcpy(staff.birth.month, "February");
			break;
		case 3:
			strcpy(staff.birth.month, "March");
			break;
		case 4:
			strcpy(staff.birth.month, "April");
			break;
		case 5:
			strcpy(staff.birth.month, "May");
			break;
		case 6:
			strcpy(staff.birth.month, "June");
			break;
		case 7:
			strcpy(staff.birth.month, "July");
			break;
		case 8:
			strcpy(staff.birth.month, "August");
			break;
		case 9:
			strcpy(staff.birth.month, "September");
			break;
		case 10:
			strcpy(staff.birth.month, "October");
			break;
		case 11:
			strcpy(staff.birth.month, "November");
			break;
		case 12:
			strcpy(staff.birth.month, "December");
			break;
		}
		switch (month)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			printf("%45s Day(1-31)\n", "");
			printf("%45s >>> ", "");
			staff.birth.day = numSelect(1, 1, 31);
			break;
		case 4: case 6: case 9: case 11:
			printf("%45s Day(1-30)\n", "");
			printf("%45s >>> ", "");
			staff.birth.day = numSelect(1, 1, 30);
			break;
		case 2:
			leap = checkLeap(staff.birth.year);
			if (leap == 1)
			{
				printf("%45s Day(1-29)\n", "");
				printf("%45s >>> ", "");
				staff.birth.day = numSelect(1, 1, 29);
			}
			else
			{
				printf("%45s Day(1-28)\n", "");
				printf("%45s >>> ", "");
				staff.birth.day = numSelect(1, 1, 28);
			}
			break;
		}
			printf("%45s E-mail.\n", "");
			printf("%45s >>> ", "");
			rewind(stdin);
			scanf("%s", &staff.email);
			exitFunc(loginacc, staff.email);

			while (1)
			{
				printf("%45s Phone number(eg:0123456789)\n", "");
				printf("%45s >>> ", "");
				rewind(stdin);
				scanf("%s", &staff.phoneNum);
				exitFunc(loginacc, staff.phoneNum);
				for (i = 0; i < strlen(staff.phoneNum); i++)
				{
					if (isdigit(staff.phoneNum[i]) == 0)
					{
						printf("%45s The phone number must contain only digits!\n", "");
						printf("%45s Please reenter.\n", "");
						break;
					}
				}
				if (strlen(staff.phoneNum) > 15)
				{
					printf("%45s The length of the phone number must not exceed 15 characters!\n", "");
					printf("%45s Please reenter.\n\n", "");
				}
				if (i == strlen(staff.phoneNum) && strlen(staff.phoneNum) < 16)
					break;
			}
			strcpy(staff.position, "Staff");
			fwrite(&staff, sizeof(staff), 1, wstaffInfo);
			fclose(wstaffInfo);
			fclose(rstaffInfo);
			printf("%45s Any staff information to add?(Y=yes,N=no)\n", "");
			printf("%45s >>> ", "");
			choice = confirmSelect('Y', 'N');
			if (choice == 'N')
			{
				printf("%45s The new staff information added sucessfully!\n", "");
				endOfFunc(loginacc);
			}
	}while (choice == 'Y');
}

void searchStaff(char loginacc[])
{
	printf("\t\t\t  _____   ___   ____  ____      __  __ __    _____ ______   ____  _____  _____ \n"
		"\t\t\t / ___/  /  _] /    ||    \\    /  ]|  |  |  / ___/|      | /    ||     ||     |\n"
		"\t\t\t(   \\_  /  [_ |  o  ||  D  )  /  / |  |  | (   \\_ |      ||  o  ||   __||   __|\n"
		"\t\t\t \\__  ||    _]|     ||    /  /  /  |  _  |  \\__  ||_|  |_||     ||  |_  |  |_  \n"
		"\t\t\t /  \\ ||   [_ |  _  ||    \\ /   \\_ |  |  |  /  \\ |  |  |  |  _  ||   _] |   _] \n"
		"\t\t\t \\    ||     ||  |  ||  .  \\\\     ||  |  |  \\    |  |  |  |  |  ||  |   |  |   \n"
		"\t\t\t  \\___||_____||__|__||__|\\_| \\____||__|__|   \\___|  |__|  |__|__||__|   |__|   \n\n");

	char id[6],choice;
	int i = 0, total = 0;
	printf("%45s Please select the digit to perform the following task.\n", "");
	printf("%45s ------------------------\n", "");
	printf("%45s | [1] Search staff.    |\n", "");
	printf("%45s | [2] Exit.            |\n", "");
	printf("%45s ------------------------\n", "");
	printf("%45s >>> ", "");
	choice = numSelect(1, 1, 2);
	if (choice == 1)
	{
		do
		{
			printf("\n%45s Please enter the staff ID.\n", "");
			printf("%45s >>> ", "");
			scanf("%s", &id);
			rewind(stdin);
			FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
			while (fread(&staff, sizeof(staff), 1, rstaffInfo) != 0)
			{
				total++;
				while (strcmp(staff.staffId, id) != 0)
				{
					i++;
					break;
				}
				if (strcmp(staff.staffId, id) == 0)
					break;
			}
			if (strcmp(staff.staffId, id) == 0)
			{
				printf("\n%45s Staff ID     : %s \n", "", staff.staffId);
				printf("%45s Name         : %s \n", "", staff.staffName);
				printf("%45s Gender       : %c \n", "", staff.gender);
				printf("%45s Birth date   : %d %s %d \n", "", staff.birth.day, staff.birth.month, staff.birth.year);
				printf("%45s E-mail       : %s \n", "", staff.email);
				printf("%45s Phone number : %s \n", "", staff.phoneNum);
				printf("%45s Position     : %s \n\n", "", staff.position);
				printf("%45s Do you want to continue to search?(Y=yes,N=No)\n", "");
				printf("%45s >>> ", "");
				choice = confirmSelect('Y', 'N');
			}
			else
			{
				printf("%45s The staff ID you had entered is not exist!\n", "");
				printf("%45s Do you want to continue to search for staff?(Y=yes,N=No)\n", "");
				printf("%45s >>> ", "");
				choice = confirmSelect('Y', 'N');
			}
			if (choice == 'N')
			{
				endOfFunc(loginacc);
			}
			fclose(rstaffInfo);
		} while (choice == 'Y');
	}
	else if (choice == 2)
	{
		system("cls");
		StaffInformationMod(loginacc);;
	}
}

void modifyStaff(char loginacc[])
{
	FILE*wstaffInfo;
	FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
	printf("\t\t\t ___ ___   ___   ___    ____  _____  __ __    _____ ______   ____  _____  _____ \n"
		"\t\t\t|   |   | /   \\ |   \\  |    ||     ||  |  |  / ___/|      | /    ||     ||     |\n"
		"\t\t\t| _   _ ||     ||    \\  |  | |   __||  |  | (   \\_ |      ||  o  ||   __||   __|\n"
		"\t\t\t|  \\_/  ||  O  ||  D  | |  | |  |_  |  ~  |  \\__  ||_|  |_||     ||  |_  |  |_  \n"
		"\t\t\t|   |   ||     ||     | |  | |   _] |___, |  /  \\ |  |  |  |  _  ||   _] |   _] \n"
		"\t\t\t|   |   ||     ||     | |  | |  |   |     |  \\    |  |  |  |  |  ||  |   |  |   \n"
		"\t\t\t|___|___| \\___/ |_____||____||__|   |____/    \\___|  |__|  |__|__||__|   |__|   \n\n");
	printf("%35s ----------------------------------------------------------\n", "");
	printf("%35s | Note:                                                  |\n", "");
	printf("%35s | 1.The staff ID and user ID cannot be modified.         |\n", "");
	printf("%35s | 2.Staff can only modify your own information.          |\n", "");
	printf("%35s | 3.Staff cannot modify your own position.               |\n", "");
	printf("%35s | 4.Other staff info can only modified by administrator. |\n", "");
	printf("%35s | 5.Enter (XXX) anywhere to exit the modify function.    |\n", "");
	printf("%35s ----------------------------------------------------------\n", "");
	char password[21], confirmPW[21], choice, confirm,position,id[6];
	int num, criteria[7], month, i = 0, counter = 0, total = 0, x = 0, y=0,mdf = 0, leap;
	while (fread(&staff, sizeof(staff), 1, rstaffInfo) != 0)
	{
		counter++;
	}
	rstaffInfo = fopen("StaffInfo.bin", "rb");
	for (i = 0; i<counter; i++)
	{
		fread(&modify[i], sizeof(staff), 1, rstaffInfo);
	}
	fclose(rstaffInfo);
	for (i = 0; i < counter; i++)
	{
		if (strcmp(loginacc, modify[i].staffId) == 0)
			break;
	}
	if (strcmp(modify[i].position, "Administrator") == 0)
	{
		printf("%40s Please select your choice.\n", "");
		printf("%40s ------------------------------------------\n", "");
		printf("%40s | [1] Modify own information.            |\n", "");
		printf("%40s | [2] Modify other staff information.    |\n", "");
		printf("%40s | [3] Exit.                              |\n", "");
		printf("%40s ------------------------------------------\n", "");
		printf("%40s >>> ", "");
		choice = numSelect(1, 1, 3);
		switch (choice)
		{
		case 1:
			for (mdf = 0; mdf < counter; mdf++)
			{
				if (strcmp(modify[mdf].staffId, loginacc) == 0)
					break;
			}

			printf("\n%45s Staff ID     : %s \n", "", modify[mdf].staffId);
			printf("%45s Password     : %s \n", "", modify[mdf].password);
			printf("%45s Name         : %s \n", "", modify[mdf].staffName);
			printf("%45s Gender       : %c \n", "", modify[mdf].gender);
			printf("%45s Birth date   : %d %s %d \n", "", modify[mdf].birth.day, modify[mdf].birth.month, modify[mdf].birth.year);
			printf("%45s E-mail       : %s \n", "", modify[mdf].email);
			printf("%45s Phone number : %s \n", "", modify[mdf].phoneNum);
			printf("%45s Position     : %s \n\n", "", modify[mdf].position);

			printf("%45s How many information you wanted to modify?\n", "");
			printf("%45s >>> ", "");
			num = numSelect(1, 1, 7);
			do
			{
				while (num != 7)
				{
					printf("\n%45s ----------------------------\n", "");
					printf("%45s | [1] Name.                |\n", "");
					printf("%45s | [2] Password.            |\n", "");
					printf("%45s | [3] Gender.              |\n", "");
					printf("%45s | [4] Birth date.          |\n", "");
					printf("%45s | [5] E-mail.              |\n", "");
					printf("%45s | [6] Phone number.        |\n", "");
					printf("%45s | [7] Position.            |\n", "");
					printf("%45s ----------------------------\n", "");
					printf("%45s Please select the digit of the criteria you wanted to modify.\n", "");
					for (i = 0; i < num; i++)
					{
						printf("%45s >>> ", "");
						rewind(stdin);
						criteria[i] = numSelect(1, 1, 7);
						for (x = 0; x < num; x++)
						{
							if (i != x)
							{
								if (criteria[i] == criteria[x])
								{
									printf("%45s This criteria already selected!\n", "");
									printf("%45s Please select another criteria.\n\n", "");
									i--;
									break;
								}
							}
						}
					}
					break;
				}
				if (num == 7)
				{
					for (i = 0; i < 7; i++)
						criteria[i] = i + 1;
				}
				printf("\n%45s Please enter the new information.\n", "");
				for (i = 0; i < num; i++)
				{
					switch (criteria[i])
					{
					case 1:
						do
						{
							printf("%45s Name\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							scanf("%[^\n]", &modify[mdf].staffName);
							exitFunc(loginacc, modify[mdf].staffName);
							total = 0;
							for (y = 0; y < strlen(modify[mdf].staffName); y++)
							{
								if (isalpha(modify[mdf].staffName[y]) == 0 && modify[mdf].staffName[y] != ' ')
								{
									total++;
									printf("%45s The name must contain only characters!\n", "");
									printf("%45s Please reenter.\n", "");
									break;
								}
								else
									continue;
							}
						} while (total != 0);
						break;
					case 2:
						printf("%45s New password.\n", "");
						printf("%45s >>> ", "");
						rewind(stdin);
						hidepwStaff(password);
						exitFunc(loginacc, password);
						while (strlen(password) < 8 || strlen(password) > 16)
						{
							printf("%45s Please enter only 8 to 16 characters for the password!\n", "");
							printf("%45s New password.\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							hidepwStaff(password);
							exitFunc(loginacc, password);
						}
						do
						{
							printf("%45s Please confirm your password.\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							hidepwStaff(confirmPW);
							exitFunc(loginacc, confirmPW);
							if (strcmp(password, confirmPW) == 0)
							{
								strcpy(modify[mdf].password, password);
							}
							else
							{
								printf("%45s The password was not match! Please reenter your password.\n\n", "");
							}
						} while (strcmp(password, confirmPW) != 0);
						break;
					case 3:
						printf("%45s Gender(F=female,M=male)\n", "");
						printf("%45s >>> ", "");
						modify[mdf].gender = confirmSelect('M', 'F');
						break;
					case 4:
						printf("%45s Birth date:\n", "");
						printf("%45s Year.\n", "");
						printf("%45s >>> ", "");
						modify[mdf].birth.year = numSelect(1940, 1940, 2019);
						printf("%45s Month(1-12)\n", "");
						printf("%45s >>> ", "");
						month = numSelect(1, 1, 12);
						switch (month)
						{
						case 1:
							strcpy(modify[mdf].birth.month, "January");
							break;
						case 2:
							strcpy(modify[mdf].birth.month, "February");
							break;
						case 3:
							strcpy(modify[mdf].birth.month, "March");
							break;
						case 4:
							strcpy(modify[mdf].birth.month, "April");
							break;
						case 5:
							strcpy(modify[mdf].birth.month, "May");
							break;
						case 6:
							strcpy(modify[mdf].birth.month, "June");
							break;
						case 7:
							strcpy(modify[mdf].birth.month, "July");
							break;
						case 8:
							strcpy(modify[mdf].birth.month, "August");
							break;
						case 9:
							strcpy(modify[mdf].birth.month, "September");
							break;
						case 10:
							strcpy(modify[mdf].birth.month, "October");
							break;
						case 11:
							strcpy(modify[mdf].birth.month, "November");
							break;
						case 12:
							strcpy(modify[mdf].birth.month, "December");
							break;
						}
						switch (month)
						{
						case 1: case 3: case 5: case 7: case 8: case 10: case 12:
							printf("%45s Day(1-31)\n", "");
							printf("%45s >>> ", "");
							modify[mdf].birth.day = numSelect(1, 1, 31);
							break;
						case 4: case 6: case 9: case 11:
							printf("%45s Day(1-30)\n", "");
							printf("%45s >>> ", "");
							modify[mdf].birth.day = numSelect(1, 1, 30);
							break;
						case 2:
							leap = checkLeap(modify[mdf].birth.year);
							if (leap == 1)
							{
								printf("%45s Day(1-29)\n", "");
								printf("%45s >>> ", "");
								modify[mdf].birth.day = numSelect(1, 1, 29);
							}
							else
							{
								printf("%45s Day(1-28)\n", "");
								printf("%45s >>> ", "");
								modify[mdf].birth.day = numSelect(1, 1, 28);
							}
							break;
						}
						break;
					case 5:
						printf("%45s E-mail\n", "");
						printf("%45s >>> ", "");
						rewind(stdin);
						scanf("%s", &modify[mdf].email);
						exitFunc(loginacc, modify[mdf].email);

						break;
					case 6:
						while (1)
						{
							printf("%45s Phone number(eg:0123456789)\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							scanf("%s", &modify[mdf].phoneNum);
							exitFunc(loginacc, modify[mdf].phoneNum);
							for (y = 0; y < strlen(modify[mdf].phoneNum); y++)
							{
								if (isdigit(modify[mdf].phoneNum[y]) == 0)
								{
									printf("%45s The phone number must contain only digits!\n", "");
									printf("%45s Please reenter.\n", "");
									break;
								}
							}
							if (strlen(modify[mdf].phoneNum) > 15)
							{
								printf("%45s The length of the phone number must not exceed 15 characters!\n", "");
								printf("%45s Please reenter.\n\n", "");
							}
							if (y == strlen(modify[mdf].phoneNum) && strlen(modify[mdf].phoneNum) < 16)
								break;
						}
						break;
					case 7:
						printf("%45s Position(A=Administrator,S=Staff)\n", "");
						printf("%45s >>> ", "");
						position = confirmSelect('A', 'S');
						if (position = 'A')
							strcpy(modify[mdf].position, "Administrator");
						else
							strcpy(modify[mdf].position, "Staff");
						break;
					}
				}
				printf("\n%45s Modified information:\n", "");
				printf("\n%45s Staff ID     : %s \n", "", modify[mdf].staffId);
				printf("%45s Name         : %s \n", "", modify[mdf].staffName);
				printf("%45s Password     : %s \n", "", modify[mdf].password);
				printf("%45s Gender       : %c \n", "", modify[mdf].gender);
				printf("%45s Birth date   : %d %s %d \n", "", modify[mdf].birth.day, modify[mdf].birth.month, modify[mdf].birth.year);
				printf("%45s E-mail       : %s \n", "", modify[mdf].email);
				printf("%45s Phone number : %s \n", "", modify[mdf].phoneNum);
				printf("%45s Position     : %s \n\n", "", modify[mdf].position);
				printf("%45s Do the information correct?(Y=yes,N=no)\n", "");
				printf("%45s >>> ", "");
				confirm = confirmSelect('Y', 'N');
				if (toupper(confirm) == 'Y')
				{
					wstaffInfo = fopen("StaffInfo.bin", "wb");
					for (i = 0; i < counter; i++)
					{
						fwrite(&modify[i], sizeof(modify[i]), 1, wstaffInfo);
					}
					fclose(wstaffInfo);
					printf("%45s The information had suessfully modified!\n\n", "");
					endOfFunc(loginacc);
				}
				else
				{
					printf("%45s \n", "");
					num = 1;
				}
			} while (toupper(confirm) == 'N');
			break;
		case 2:
			do
			{
				do
				{
					printf("\n%45s Please enter the staff ID to modify the staff information.\n", "");
					printf("%45s >>> ", "");
					rewind(stdin);
					scanf("%s", &id);
					exitFunc(loginacc, id);
					for (mdf = 0; mdf < counter; mdf++)
					{
						if (strcmp(id, loginacc) == 0)
						{
							printf("%45s You cannot enter your staff ID here!\n", "");
							printf("%45s You may enter(XXX) to exit this function.\n", "");
							break;
						}

					}
				} while (strcmp(id, loginacc) == 0);
				total = 0;
				for (mdf = 0; mdf < counter; mdf++)
				{
					total++;
					while (strcmp(modify[mdf].staffId, id) != 0)
					{
						x++;
						break;
					}
					if (strcmp(modify[mdf].staffId, id) == 0)
						break;
				}
				if (total != x)
				{
					printf("\n%45s Staff ID     : %s \n", "", modify[mdf].staffId);
					printf("%45s Name         : %s \n", "", modify[mdf].staffName);
					printf("%45s Gender       : %c \n", "", modify[mdf].gender);
					printf("%45s Birth date   : %d %s %d \n", "", modify[mdf].birth.day, modify[mdf].birth.month, modify[mdf].birth.year);
					printf("%45s E-mail       : %s \n", "", modify[mdf].email);
					printf("%45s Phone number : %s \n", "", modify[mdf].phoneNum);
					printf("%45s Position     : %s \n\n", "", modify[mdf].position);
				}
				else
				{
					printf("%45s The staff ID you had entered is not exist!\n", "");
				}
			} while (x == total);

			printf("%45s How many information you wanted to modify?\n", "");
			printf("%45s >>> ", "");
			num = numSelect(1, 1, 6);
			do
			{
				while (num != 6)
				{
					printf("\n%45s ----------------------------\n", "");
					printf("%45s | [1] Name.                |\n", "");
					printf("%45s | [2] Gender.              |\n", "");
					printf("%45s | [3] Birth date.          |\n", "");
					printf("%45s | [4] E-mail.              |\n", "");
					printf("%45s | [5] Phone number.        |\n", "");
					printf("%45s | [6] Position.            |\n", "");
					printf("%45s ----------------------------\n", "");
					printf("%45s Please select the digit of the criteria you wanted to modify.\n", "");
					for (i = 0; i < num; i++)
					{
						printf("%45s >>> ", "");
						rewind(stdin);
						criteria[i] = numSelect(1, 1, 6);
						for (x = 0; x < num; x++)
						{
							if (i != x)
							{
								if (criteria[i] == criteria[x])
								{
									printf("%45s This criteria already selected!\n", "");
									printf("%45s Please select another criteria.\n\n", "");
									i--;
									break;
								}
							}
						}
					}
					break;
				}
				if (num == 6)
				{
					for (i = 0; i < 6; i++)
						criteria[i] = i + 1;
				}
				printf("\n%45s Please enter the new information.\n", "");
				for (i = 0; i < num; i++)
				{
					switch (criteria[i])
					{
					case 1:
						do
						{
							printf("%45s Name\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							scanf("%[^\n]", &modify[mdf].staffName);
							exitFunc(loginacc, modify[mdf].staffName);
							total = 0;
							for (y = 0; y < strlen(modify[mdf].staffName); y++)
							{
								if (isalpha(modify[mdf].staffName[y]) == 0 && modify[mdf].staffName[y] != ' ')
								{
									total++;
									printf("%45s The name must contain only characters!\n", "");
									printf("%45s Please reenter.\n", "");
									break;
								}
								else
									continue;
							}
						} while (total != 0);
						break;
					case 2:
						printf("%45s Gender(F=female,M=male)\n", "");
						printf("%45s >>> ", "");
						modify[mdf].gender = confirmSelect('M', 'F');
						break;
					case 3:
						printf("%45s Birth date:\n", "");
						printf("%45s Year\n", "");
						printf("%45s >>> ", "");
						modify[mdf].birth.year = numSelect(1940, 1940, 2019);
						printf("%45s Month(1-12)\n", "");
						printf("%45s >>> ", "");
						month = numSelect(1, 1, 12);
						switch (month)
						{
						case 1:
							strcpy(modify[mdf].birth.month, "January");
							break;
						case 2:
							strcpy(modify[mdf].birth.month, "February");
							break;
						case 3:
							strcpy(modify[mdf].birth.month, "March");
							break;
						case 4:
							strcpy(modify[mdf].birth.month, "April");
							break;
						case 5:
							strcpy(modify[mdf].birth.month, "May");
							break;
						case 6:
							strcpy(modify[mdf].birth.month, "June");
							break;
						case 7:
							strcpy(modify[mdf].birth.month, "July");
							break;
						case 8:
							strcpy(modify[mdf].birth.month, "August");
							break;
						case 9:
							strcpy(modify[mdf].birth.month, "September");
							break;
						case 10:
							strcpy(modify[mdf].birth.month, "October");
							break;
						case 11:
							strcpy(modify[mdf].birth.month, "November");
							break;
						case 12:
							strcpy(modify[mdf].birth.month, "December");
							break;
						}
						switch (month)
						{
						case 1: case 3: case 5: case 7: case 8: case 10: case 12:
							printf("%45s Day(1-31)\n", "");
							printf("%45s >>> ", "");
							modify[mdf].birth.day = numSelect(1, 1, 31);
							break;
						case 4: case 6: case 9: case 11:
							printf("%45s Day(1-30)\n", "");
							printf("%45s >>> ", "");
							modify[mdf].birth.day = numSelect(1, 1, 30);
							break;
						case 2:
							leap = checkLeap(modify[mdf].birth.year);
							if (leap == 1)
							{
								printf("%45s Day(1-29)\n", "");
								printf("%45s >>> ", "");
								modify[mdf].birth.day = numSelect(1, 1, 29);
							}
							else
							{
								printf("%45s Day(1-28)\n", "");
								printf("%45s >>> ", "");
								modify[mdf].birth.day = numSelect(1, 1, 28);
							}
							break;
						}
						break;
					case 4:
						printf("%45s E-mail\n", "");
						printf("%45s >>> ", "");
						rewind(stdin);
						scanf("%s", &modify[mdf].email);
						exitFunc(loginacc, modify[mdf].email);
						break;
					case 5:
						while (1)
						{
							printf("%45s Phone number(eg:0123456789)\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							scanf("%s", &modify[mdf].phoneNum);
							exitFunc(loginacc, modify[mdf].phoneNum);
							for (y = 0; y < strlen(modify[mdf].phoneNum); y++)
							{
								if (isdigit(modify[mdf].phoneNum[y]) == 0)
								{
									printf("%45s The phone number must contain only digits!\n", "");
									printf("%45s Please reenter.\n", "");
									break;
								}
							}
							if (strlen(modify[mdf].phoneNum) > 15)
							{
								printf("%45s The length of the phone number must not exceed 15 characters!\n", "");
								printf("%45s Please reenter.\n\n", "");
							}
							if (y == strlen(modify[mdf].phoneNum) && strlen(modify[mdf].phoneNum) < 16)
								break;
						}
						break;
					case 6:
						printf("%45s Position(A=Administrator,S=Staff)\n", "");
						printf("%45s >>> ", "");
						position = confirmSelect('A', 'S');
						if (position = 'A')
							strcpy(modify[mdf].position, "Administrator");
						else
							strcpy(modify[mdf].position, "Staff");
						break;
					}
				}
				printf("\n%45s Modified information:\n", "");
				printf("\n%45s Staff ID     : %s \n", "", modify[mdf].staffId);
				printf("%45s Name         : %s \n", "", modify[mdf].staffName);
				printf("%45s Gender       : %c \n", "", modify[mdf].gender);
				printf("%45s Birth date   : %d %s %d \n", "", modify[mdf].birth.day, modify[mdf].birth.month, modify[mdf].birth.year);
				printf("%45s E-mail       : %s \n", "", modify[mdf].email);
				printf("%45s Phone number : %s \n", "", modify[mdf].phoneNum);
				printf("%45s Position     : %s \n\n", "", modify[mdf].position);
				printf("%45s Do the information correct?(Y=yes,N=no)\n", "");
				printf("%45s >>> ", "");
				confirm = confirmSelect('Y', 'N');
				if (toupper(confirm) == 'Y')
				{
					wstaffInfo = fopen("StaffInfo.bin", "wb");
					for (i = 0; i < counter; i++)
					{
						fwrite(&modify[i], sizeof(modify[i]), 1, wstaffInfo);
					}
					fclose(wstaffInfo);
					printf("%45s The information had suessfully modified!\n\n", "");
					endOfFunc(loginacc);
				}
				else
				{
					printf("%45s \n", "");
					num = 1;
				}
			} while (toupper(confirm) == 'N');
			case 3:
				system("cls");
				StaffInformationMod(loginacc);
				break;
		}
	}
	else
	{
		printf("%45s Please select your choice.\n", "");
		printf("%45s ------------------------------------------\n", "");
		printf("%45s | [1] Modify own information.            |\n", "");
		printf("%45s | [2] Exit.                              |\n", "");
		printf("%45s ------------------------------------------\n", "");
		printf("%45s >>> ", "");
		choice = numSelect(1, 1, 2);
		switch (choice)
		{
		case 1:
			for (mdf = 0; mdf < counter; mdf++)
			{
				if (strcmp(modify[mdf].staffId, loginacc) == 0)
					break;
			}

			printf("\n%45s Staff ID     : %s \n", "", modify[mdf].staffId);
			printf("%45s Password     : %s \n", "", modify[mdf].password);
			printf("%45s Name         : %s \n", "", modify[mdf].staffName);
			printf("%45s Gender       : %c \n", "", modify[mdf].gender);
			printf("%45s Birth date   : %d %s %d \n", "", modify[mdf].birth.day, modify[mdf].birth.month, modify[mdf].birth.year);
			printf("%45s E-mail       : %s \n", "", modify[mdf].email);
			printf("%45s Phone number : %s \n", "", modify[mdf].phoneNum);

			printf("%45s How many information you wanted to modify?\n", "");
			printf("%45s >>> ", "");
			num = numSelect(1, 1, 6);
			do
			{
				while (num != 6)
				{
					printf("\n%45s ----------------------------\n", "");
					printf("%45s | [1] Name.                |\n", "");
					printf("%45s | [2] Password.            |\n", "");
					printf("%45s | [3] Gender.              |\n", "");
					printf("%45s | [4] Birth date.          |\n", "");
					printf("%45s | [5] E-mail.              |\n", "");
					printf("%45s | [6] Phone number.        |\n", "");
					printf("%45s ----------------------------\n", "");
					printf("%45s Please select the digit of the criteria you wanted to modify.\n", "");
					for (i = 0; i < num; i++)
					{
						printf("%45s >>> ", "");
						rewind(stdin);
						criteria[i] = numSelect(1, 1, 6);
						for (x = 0; x < num; x++)
						{
							if (i != x)
							{
								if (criteria[i] == criteria[x])
								{
									printf("%45s This criteria already selected!\n", "");
									printf("%45s Please select another criteria.\n\n", "");
									i--;
									break;
								}
							}
						}
					}
					break;
				}
				if (num == 6)
				{
					for (i = 0; i < 6; i++)
						criteria[i] = i + 1;
				}
				printf("\n%45s Please enter the new information.\n", "");
				for (i = 0; i < num; i++)
				{
					switch (criteria[i])
					{
					case 1:
						do
						{
							printf("%45s Name\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							scanf("%[^\n]", &modify[mdf].staffName);
							exitFunc(loginacc, modify[mdf].staffName);
							total = 0;
							for (y = 0; y < strlen(modify[mdf].staffName); y++)
							{
								if (isalpha(modify[mdf].staffName[y]) == 0 && modify[mdf].staffName[y] != ' ')
								{
									total++;
									printf("%45s The name must contain only characters!\n", "");
									printf("%45s Please reenter.\n", "");
									break;
								}
								else
									continue;
							}
						} while (total != 0);
						break;
					case 2:
						printf("%45s New password.\n", "");
						printf("%45s >>> ", "");
						rewind(stdin);
						hidepwStaff(password);
						exitFunc(loginacc, password);
						while (strlen(password) < 8 || strlen(password) > 16)
						{
							printf("%45s Please enter only 8 to 16 characters for the password!\n", "");
							printf("%45s New password.\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							hidepwStaff(password);
							exitFunc(loginacc, password);
						}
						do
						{
							printf("%45s Please confirm your password.\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							hidepwStaff(confirmPW);
							exitFunc(loginacc, confirmPW);
							if (strcmp(password, confirmPW) == 0)
							{
								strcpy(modify[mdf].password, password);
							}
							else
							{
								printf("%45s The password was not match! Please reenter your password.\n\n", "");
							}
						} while (strcmp(password, confirmPW) != 0);
						break;
					case 3:
						printf("%45s Gender(F=female,M=male)\n", "");
						printf("%45s >>> ", "");
						modify[mdf].gender = confirmSelect('M', 'F');
						break;
					case 4:
						printf("%45s Birth date:\n", "");
						printf("%45s Year.\n", "");
						printf("%45s >>> ", "");
						modify[mdf].birth.year = numSelect(1940, 1940, 2019);
						printf("%45s Month(1-12)\n", "");
						printf("%45s >>> ", "");
						month = numSelect(1, 1, 12);
						switch (month)
						{
						case 1:
							strcpy(modify[mdf].birth.month, "January");
							break;
						case 2:
							strcpy(modify[mdf].birth.month, "February");
							break;
						case 3:
							strcpy(modify[mdf].birth.month, "March");
							break;
						case 4:
							strcpy(modify[mdf].birth.month, "April");
							break;
						case 5:
							strcpy(modify[mdf].birth.month, "May");
							break;
						case 6:
							strcpy(modify[mdf].birth.month, "June");
							break;
						case 7:
							strcpy(modify[mdf].birth.month, "July");
							break;
						case 8:
							strcpy(modify[mdf].birth.month, "August");
							break;
						case 9:
							strcpy(modify[mdf].birth.month, "September");
							break;
						case 10:
							strcpy(modify[mdf].birth.month, "October");
							break;
						case 11:
							strcpy(modify[mdf].birth.month, "November");
							break;
						case 12:
							strcpy(modify[mdf].birth.month, "December");
							break;
						}
						switch (month)
						{
						case 1: case 3: case 5: case 7: case 8: case 10: case 12:
							printf("%45s Day(1-31)\n", "");
							printf("%45s >>> ", "");
							modify[mdf].birth.day = numSelect(1, 1, 31);
							break;
						case 4: case 6: case 9: case 11:
							printf("%45s Day(1-30)\n", "");
							printf("%45s >>> ", "");
							modify[mdf].birth.day = numSelect(1, 1, 30);
							break;
						case 2:
							leap = checkLeap(modify[mdf].birth.year);
							if (leap == 1)
							{
								printf("%45s Day(1-29)\n", "");
								printf("%45s >>> ", "");
								modify[mdf].birth.day = numSelect(1, 1, 29);
							}
							else
							{
								printf("%45s Day(1-28)\n", "");
								printf("%45s >>> ", "");
								modify[mdf].birth.day = numSelect(1, 1, 28);
							}
							break;
						}
						break;
					case 5:
						printf("%45s E-mail\n", "");
						printf("%45s >>> ", "");
						rewind(stdin);
						scanf("%s", &modify[mdf].email);
						exitFunc(loginacc, modify[mdf].email);

						break;
					case 6:
						while (1)
						{
							printf("%45s Phone number(eg:0123456789)\n", "");
							printf("%45s >>> ", "");
							rewind(stdin);
							scanf("%s", &modify[mdf].phoneNum);
							exitFunc(loginacc, modify[mdf].phoneNum);
							for (y = 0; y < strlen(modify[mdf].phoneNum); y++)
							{
								if (isdigit(modify[mdf].phoneNum[y]) == 0)
								{
									printf("%45s The phone number must contain only digits!\n", "");
									printf("%45s Please reenter.\n", "");
									break;
								}
							}
							if (strlen(modify[mdf].phoneNum) > 15)
							{
								printf("%45s The length of the phone number must not exceed 15 characters!\n", "");
								printf("%45s Please reenter.\n\n", "");
							}
							if (y == strlen(modify[mdf].phoneNum) && strlen(modify[mdf].phoneNum) < 16)
								break;
						}
						break;
					}
				}
				printf("\n%45s Modified information:\n", "");
				printf("\n%45s Staff ID     : %s \n", "", modify[mdf].staffId);
				printf("%45s Name         : %s \n", "", modify[mdf].staffName);
				printf("%45s Password     : %s \n", "", modify[mdf].password);
				printf("%45s Gender       : %c \n", "", modify[mdf].gender);
				printf("%45s Birth date   : %d %s %d \n", "", modify[mdf].birth.day, modify[mdf].birth.month, modify[mdf].birth.year);
				printf("%45s E-mail       : %s \n", "", modify[mdf].email);
				printf("%45s Phone number : %s \n", "", modify[mdf].phoneNum);
				printf("%45s Position     : %s \n\n", "", modify[mdf].position);
				printf("%45s Do the information correct?(Y=yes,N=no)\n", "");
				printf("%45s >>> ", "");
				confirm = confirmSelect('Y', 'N');
				if (toupper(confirm) == 'Y')
				{
					wstaffInfo = fopen("StaffInfo.bin", "wb");
					for (i = 0; i < counter; i++)
					{
						fwrite(&modify[i], sizeof(modify[i]), 1, wstaffInfo);
					}
					fclose(wstaffInfo);
					printf("%45s The information had suessfully modified!\n\n", "");
					endOfFunc(loginacc);
				}
				else
				{
					printf("%45s \n", "");
					num = 1;
				}
			} while (toupper(confirm) == 'N');
			break;
			case 2:
				system("cls");
				StaffInformationMod(loginacc);
				break;
		}

	}
}

void displayStaff(char loginacc[])
{
	FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
	printf("\t\t\t ___    ____ _____ ____  _       ____  __ __       _____ ______   ____  _____  _____ \n"
		"\t\t\t|   \\  |    / ___/|    \\| |     /    ||  |  |     / ___/|      | /    ||     ||     |\n"
		"\t\t\t|    \\  |  (   \\_ |  o  ) |    |  o  ||  |  |    (   \\_ |      ||  o  ||   __||   __|\n"
		"\t\t\t|  D  | |  |\\__  ||   _/| |___ |     ||  ~  |     \\__  ||_|  |_||     ||  |_  |  |_  \n"
		"\t\t\t|     | |  |/  \\ ||  |  |     ||  _  ||___, |     /  \\ |  |  |  |  _  ||   _] |   _] \n"
		"\t\t\t|     | |  |\\    ||  |  |     ||  |  ||     |     \\    |  |  |  |  |  ||  |   |  |   \n"
		"\t\t\t|_____||____|\\___||__|  |_____||__|__||____/       \\___|  |__|  |__|__||__|   |__|   \n\n");

	while (fread(&staff, sizeof(staff), 1, rstaffInfo) != 0)
	{
		printf("\n%45s Staff ID     : %s \n", "", staff.staffId);
		printf("%45s Name         : %s \n", "", staff.staffName);
		printf("%45s Gender       : %c \n", "", staff.gender);
		printf("%45s Birth date   : %d %s %d \n", "", staff.birth.day, staff.birth.month, staff.birth.year);
		printf("%45s E-mail       : %s \n", "", staff.email);
		printf("%45s Phone number : %s \n", "", staff.phoneNum);
		printf("%45s Position     : %s \n\n", "", staff.position);
	}
	fclose(rstaffInfo);
	endOfFunc(loginacc);
}

void delStaff(char loginacc[])
{
	FILE*rstaffInfo = fopen("StaffInfo.bin", "rb");
	FILE*wstaffInfo;

	int counter = 0, i = 0, total = 0, del = 0;
	char id[6], choice;

	while (fread(&staff, sizeof(staff), 1, rstaffInfo) != 0)
	{
		counter++;
	}
	fclose(rstaffInfo);
	rstaffInfo = fopen("StaffInfo.bin", "rb");
	for (i = 0; i < counter; i++)
	{
		fread(&modify[i], sizeof(staff), 1, rstaffInfo);
	}
	fclose(rstaffInfo);
	printf("\t\t\t ___      ___  _        ___ ______    ___       _____ ______   ____  _____  _____ \n"
		"\t\t\t|   \\    /  _]| |      /  _]      |  /  _]     / ___/|      | /    ||     ||     |\n"
		"\t\t\t|    \\  /  [_ | |     /  [_|      | /  [_     (   \\_ |      ||  o  ||   __||   __|\n"
		"\t\t\t|  D  ||    _]| |___ |    _]_|  |_||    _]     \\__  ||_|  |_||     ||  |_  |  |_  \n"
		"\t\t\t|     ||   [_ |     ||   [_  |  |  |   [_      /  \\ |  |  |  |  _  ||   _] |   _] \n"
		"\t\t\t|     ||     ||     ||     | |  |  |     |     \\    |  |  |  |  |  ||  |   |  |   \n"
		"\t\t\t|_____||_____||_____||_____| |__|  |_____|      \\___|  |__|  |__|__||__|   |__|   \n\n");
	printf("%45s (Enter (XXX) to exit the add function.)\n\n", "");

	for (del = 0; del < counter; del++)
	{
		if (strcmp(modify[del].staffId, loginacc) == 0)
			break;
	}
	if (strcmp(modify[del].position, "Administrator") != 0)
	{
		printf("%45s You are not allow to delete other staff information!\n\n", "");
		endOfFunc(loginacc);
	}
	else
	{
		do
		{
			do
			{
				printf("%45s Please enter the staff ID that wanted to delete.\n", "");
				printf("%45s >>> ", "");
				rewind(stdin);
				scanf("%s", &id);
				exitFunc(loginacc, id);
				if (strcmp(id, loginacc) == 0)
				{
					printf("%45s You cannot delete your own account!\n\n", "");
				}
			} while (strcmp(id, loginacc) == 0);
			i = 0;
			for (del = 0; del < counter; del++)
			{
				total++;
				if (strcmp(modify[del].staffId, id) == 0)
					break;
				else
					i++;
			}
			if (total != i)
			{
				printf("\n%45s Staff ID     : %s \n", "", modify[del].staffId);
				printf("%45s Name         : %s \n", "", modify[del].staffName);
				printf("%45s Gender       : %c \n", "", modify[del].gender);
				printf("%45s Birth date   : %d %s %d \n", "", modify[del].birth.day, modify[del].birth.month, modify[del].birth.year);
				printf("%45s E-mail       : %s \n", "", modify[del].email);
				printf("%45s Phone number : %s \n", "", modify[del].phoneNum);
				printf("%45s Position     : %s \n\n", "", modify[del].position);
				printf("%45s Are you sure you wanted to delete this account?(Y=yes,N=No)\n","");
				printf("%45s >>> ", "");
				choice = confirmSelect('Y', 'N');
				if (choice == 'Y')
				{
					wstaffInfo = fopen("StaffInfo.bin", "wb");
					for (i = 0; i < counter; i++)
					{
						if (i == del)
							continue;
						else
						fwrite(&modify[i], sizeof(modify[i]), 1, wstaffInfo);
					}
					fclose(wstaffInfo);
					printf("%45s The staff information had been deleted.\n", "");
					endOfFunc(loginacc);
				}
			}
			else
			{
				printf("%45s The staff ID you had entered is not exist!\n", "");
				printf("%45s Please reenter.\n\n", "");
			}
		} while (total == i || choice == 'N');
	}
}

void exitFunc(char loginacc[],char Y[])
{
	if ((strcmp(Y, "XXX") == 0 || strcmp(Y, "xxx") == 0))
	{
		system("cls");
		StaffInformationMod(loginacc);
	}
}

void endOfFunc(char loginacc[])
{
	int task;
	printf("%45s Choose the digit to perform the following task.\n", "");
	printf("%45s ------------------------------\n", "");
	printf("%45s | [1] Back to staff menu.    |\n", "");
	printf("%45s | [2] Back to main menu.     |\n", "");
	printf("%45s ------------------------------\n", "");
	printf("%45s >>> ", "");
	task = numSelect(1, 1, 2);
	switch (task)
	{
	case 1:
		system("cls");
		StaffInformationMod(loginacc);
		break;
	case 2:
		system("cls");
		main(loginacc);
		break;
	}
}

void hidepwStaff(char password[21]) 
{
	int y = 0,x;
	while (y <= 30)
	{
		password[y] = getch();
		x = password[y];
		//if user press enter(ASCII value=13),stop the looping
		if (x == 13)
		{
			password[y] = '\0';
			printf("\n");
			break;
		}
		//if user press backspace(ASCII value=8),delete the previous character inserted
		else if (x == 8)
		{
			if (y > 0)
			{
				y--;
				printf("\b \b");
			}
		}
		//blankspace(ASCII value=32)
		else if (x == 32)
		{
			continue;
		}
		else
		{
			printf("*");
			y++;
		}
	}
}
