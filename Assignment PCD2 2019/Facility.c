#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include "Header.h"
#pragma warning(disable:4996)

typedef struct 
{
	int facID;
	char facName[30],facCode, facItem[200], facDescription[300], facVenue[100], facDateTime[20];

}Facility;
Facility fac1[100];//declaration of structure array to store facility info
Facility temp;//declaration of temporary structure array to store facility

typedef struct
{
	char name[30];
}Name;
Name name1[100];//declaration of temporary structure array to compare the name

struct note
{
	char info[200];
};
struct note note1;//declaration of temporary structure array for note. 


void viewfac();	//to view facilities
void addfac();  //to add facilitites
void editfac(); //to edit facilities
void delfac();  //to delete facilities
void searchfac();//to search facilities
void design();  //to show the main design
void mainmenu(); //to let the user press anything before return to main screen
int tocount();//to count the total facilities in file
int numSelect1(int start, int min, int max);//to let user select integer using arrow button on keyboard
int numSelect2(int start, int min, int max);//to let user select integer using arrow button on keyboard with spacing



void FacilityMod(char staffOrNot)
{
	int choice1;//to check whether is staff or not 
	
	if (staffOrNot == 'S')
	{
		while (1)
		{
			design();
			printf("\n\t____________________________"
				"\n\t||------------------------||"
				"\n\t||1.View Facility Info    ||"
				"\n\t||2.Add Facility Info     ||"
				"\n\t||3.Edit Facility Info    ||"
				"\n\t||4.Delete Facility       ||"
				"\n\t||5.Search Facility Info  ||"
				"\n\t||6.Exit                  ||"
				"\n\t||________________________||"
				"\n\t||------------------------||\n\n");
			printf("\tPlease select your choice by using the 'Up' and 'Down' arrow button :  ");
			choice1 = numSelect(1, 1, 6);
			system("cls");

			switch (choice1) //to direct user to different function
			{


			case 1:
				viewfac(); break;
			case 2:
				addfac(); break;
			case 3:
				editfac(); break;
			case 4:
				delfac(); break;
			case 5:
				searchfac(); break;
			default:
			{
				return;
			}

			}
			system("cls");
		}
	}
	else
	{
		while (1)
		{
			design();
			printf("\n\t____________________________"
				"\n\t||------------------------||"
				"\n\t||1.View Facility Info    ||"
				"\n\t||2.Search Facility Info  ||"
				"\n\t||3.Exit                  ||"
				"\n\t||________________________||"
				"\n\t||------------------------||\n\n");
			printf("\tPlease select your choice by using the 'Up' and 'Down' arrow button :  "); //to direct user to different function
			choice1 = numSelect(1, 1, 3);
			system("cls");

			switch (choice1)
			{

			case 1:
				viewfac(); break;
			case 2:
				searchfac(); break;
			default:
			{
				return;
			}

			}
			system("cls");
		}
	}
}
void viewfac()
{
	int i = 0;
	FILE*fp1 = fopen("facilitylist.txt", "r");
	FILE*fr = fopen("facilitynote.txt", "r");

	if (fp1 == NULL)
	{
		printf("Unable to open file facilitylist.txt\n");
		system("pause");
		return;
	}
	if (fr == NULL)
	{
		printf("Unable to open file facilitynote.txt\n");
		system("pause");
		return;
	}
	design();
	printf("\n");
	
	printf("________________________________________________________________________________________________________________________\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");//to show the list of code
	while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		printf("|  Facility Name           : %-90s|\n|  Facility Type           : %-90c|\n|  Facility ID             : A%03d\t\t\t\t\t\t\t\t\t\t\t|\n|  Facilities              : %-90s|\n|  Facility Description    : %-90s|\n|  Facility Venue          : %-90s|\n|  Facility Operation Hour : %-90s|\n|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", fac1[i].facName, fac1[i].facCode, fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime);
	}
	while (fscanf(fr, "%[^\n]\n", note1.info) != EOF) //to show the facility note
	{
		printf("|  %-116s|\n", note1.info);
	}
	printf("|%-118s|\n", "");
	printf("|______________________________________________________________________________________________________________________|\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	fclose(fp1);
	fclose(fr);
	mainmenu();
	return;
}

void addfac()
{
	char ans,choice,counter='A',i=0;
	int count = 0, time1,time2, code = 0,x=0,y;
	FILE*fp1 = fopen("facilitylist.txt", "r");

    if (fp1 == NULL)
	{
		printf("Unable to open file facilitylist.txt\n");
		system("pause");                                                        
		exit(-1);
	}
	design();
	count = tocount();//to count the facilities in the text file

	printf("\tExisting Facilties or New Facilities (E/N)   :  ");
	ans=confirmSelect('E','N');
	if (ans == 'E') //to show the all facilities for once only except gymnasium
	{
		int j, facCount;
		i = 0;
		facCount = 0;
		while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
		{
			for (j = 0; j < i; j++)
			{
				if (strcmp(fac1[i].facName, fac1[j].facName) == 0)
					break;
			}
			if (j == i)
			{
				if (strcmp(fac1[i].facName, "Gymnasium") != 0)
				{
					strcpy(name1[facCount].name, fac1[i].facName);
					facCount++;
				}
			}
			i++;
		}
		rewind(fp1);
		printf("\t-----------------------------------------\n");
		printf("\tNo. \t\t   Facility Name    \n");
		printf("\t-----------------------------------------\n");
		for (i = 0; i < facCount; i++)
		{
			printf("\t%d \t\t  %-20s \n", i + 1, name1[i].name);
		}
		printf("\t-----------------------------------------\n");
		printf("\tPlease select the facility that you want to add  :  ");
		choice = numSelect(1, 1, facCount);
		//to know how many times a facility show in the file
		for(i=0;i<count;i++)
		{
			if (strcmp(fac1[i].facName,name1[choice-1].name)==0)
			{
				counter++;
			}

		}
	
		
		//to obtain correct new facility id
		i = 0,x=1;
		while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
		{
			if (x != fac1[i].facID)
			{
				break;
			}
			x++;
			i++;
		}
		
		rewind(fp1);
		//to get the information of the selected facility
		i = 0;
		while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
		{
			if (strcmp(fac1[i].facName, name1[choice - 1].name) == 0)
			{
				break;
			}
			i++;
		}
		fclose(fp1);
		printf("________________________________________________________________________________________________________________________\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("|  Facility Name           : %-90s|\n|  Facility Type           : %-90c|\n|  Facility ID             : A%03d\t\t\t\t\t\t\t\t\t\t\t|\n|  Facilities              : %-90s|\n|  Facility Description    : %-90s|\n|  Facility Venue          : %-90s|\n|  Facility Operation Hour : %-90s|\n|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", fac1[i].facName, counter ,x, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime);
		printf("________________________________________________________________________________________________________________________\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		strcpy(temp.facName, fac1[i].facName);
		temp.facCode =counter;
		temp.facID = x;
		strcpy(temp.facItem, fac1[i].facItem);//to copy the information into temporary structure array
		strcpy(temp.facDescription, fac1[i].facDescription);
		strcpy(temp.facVenue, fac1[i].facVenue);
		strcpy(temp.facDateTime, fac1[i].facDateTime);

		printf("\tAre you sure you want to add this facility?  (Y/N)   :  ");
		ans = confirmSelect('Y', 'N');	
		int written = 0;
		if (ans == 'Y')
		{
			FILE*fp2 = fopen("facilitylist.txt", "w+");
			for (i = 0; i < count; i++)
			{
				if (i==temp.facID-1)
				{
				fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
						temp.facName,
						temp.facCode,
						temp.facID,
						temp.facItem,                  //to print the data into file before other facilities clashes with it
						temp.facDescription,  
						temp.facVenue,
						temp.facDateTime);
				written = 1;
				}
		     	fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
					fac1[i].facName,
					fac1[i].facCode,
					fac1[i].facID,
					fac1[i].facItem,                     //to print the new facility info into text file
					fac1[i].facDescription,
					fac1[i].facVenue,
					fac1[i].facDateTime);
			}
			if (i == count && written == 0)
			{
				fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
					temp.facName,
					temp.facCode,
					temp.facID,                      //to print the data into the end of the file if other data doesn't clash with it
					temp.facItem,
					temp.facDescription,
					temp.facVenue,
					temp.facDateTime);
			}
			fclose(fp2);
			printf("\tAdding...\n");
			printf("\tCongratulations,new facility has been added.\n");
			printf("\n\n\t1.Continue\n\t2.Back to facility menu\n\n");
			printf("\tYour choice  :  ");
			ans = numSelect(2, 1, 2);
			if (ans == 1)
			{
				system("cls");
				addfac();
			}
			else
			{
				printf("\tYou will be redirect to facility menu now...\n");
				mainmenu();
				return;
			}
		}
		else
		{
			printf("\tAdding...\n");
			printf("\tAdding failed...\n");
			printf("\tNew facility has not been added.\n");
			printf("\n\n\t1.Continue\n\t2.Back to facility menu\n\n");
			printf("\tYour choice  :  ");
			ans=numSelect(2,1,2);
			if (ans == 1)
			{
				system("cls");
				addfac();
			}
			else
			{
				printf("\tYou will be redirect to facility menu now...\n");
				mainmenu();
				return;
			}

		}

	}
	else
	{
     	count = 0;
    	count = tocount();
	    //to obtain new correct facility id
		x = 1;
		while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
		{
			if (x != fac1[i].facID)
			{
					break;
			}
			x++;
			i++;
		}
		rewind(fp1);

		printf("________________________________________________________________________________________________________________________\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
        do
		{
			y = 0;
			printf("Please enter new Facility Name  (eg:Badminton Court...)                      :  ");
			rewind(stdin);
			scanf("%19[^\n]", temp.facName);
			for (i = 0; i < count; i++)
			{
				if (strcmp(fac1[i].facName, temp.facName) == 0)
				{
					printf("\tFacility name already exist!!!!\n");
					y++;
					break;
				}
			}
			if (strlen(temp.facName) == 0)
			{
				y++;
				printf("\tThe facility name cannot be blank!!!!.\n");
			}
			for (i = 0; i < strlen(temp.facName); i++)
			{
				
				if (isalpha(temp.facName[i]) == 0 && temp.facName[i] != ' ')
				{
					y++;
					printf("Invalid input, please enter alphabet only.\n");
					break;
				}
			}
		} while (y!= 0);
		printf("Facility Code                                                                :  A\n");
		printf("facility ID                                                                  :  A%03d\n", x);
		y = 0;
		do
		{
			y = 0;
			printf("Please enter new Facilites Info    (eg:Court,shuttlecocks...)                :  ");
			rewind(stdin);
			scanf("%199[^\n]", temp.facItem);
			if (strlen(temp.facItem) == 0)
			{
				y++;
				printf("\tThe facility info cannot be blank!!!!.\n");
			}
			for (i = 0; i < strlen(temp.facItem); i++)
			{

				if (isalpha(temp.facItem[i]) == 0 && temp.facItem[i] !=' ')
				{
					y++;
					printf("Invalid input, please enter alphabet only.\n");
					break;
				}
			}

		} while (y != 0);
		do {
			y = 0;
			printf("Please enter new Facility Description (eg:Please book before using...)       :  ");
			rewind(stdin);
			scanf("%299[^\n]", temp.facDescription);
			if (strlen(temp.facDescription) == 0)
			{
				y++;
				printf("\tThe facility description cannot be blank!!!!.\n");
			}
			for (i = 0; i < strlen(temp.facDescription); i++)
			{

				if (isalpha(temp.facDescription[i]) == 0 && temp.facDescription[i] != ' ')
				{
					y++;
					printf("Invalid input, please enter alphabet only.\n");
					break;
				}
			}
		} while (y != 0);
		do {
			printf("Please enter new Facility Venue (room 3001,third floor of ...)               :  ");
			rewind(stdin);
			scanf("%99[^\n]", temp.facVenue);
			if (temp.facVenue[0] == NULL)
			{
				printf("\tThe facility venue cannot be blank.!!!!\n");
			}
		} while (temp.facVenue[0] == NULL);
		printf("Please select new Facility Time  (must between 9a.m. and 11p.m.,12pm-1pm is staff rest time)  :  ");
		time1 = numSelect2(9, 9, 11); printf("a.m. to "); time2 = numSelect2(1, 1, 11); printf("p.m.");
		sprintf(temp.facDateTime, "%da.m. to %dp.m.", time1, time2);
		i = count - 1;
		printf("\nDo you want to edit the information you enter just now? (Y/N)         :   ");
		ans = confirmSelect('Y', 'N');
		do
		{

			if (ans == 'Y')
			{
				printf("\n\twhich information do you want to edit\n");
				printf("\t1.Facility name\n\t2.Facility Info\n\t3.Facility Description\n\t4.Facility Venue\n\t5.Facility Time\n\n");
				printf("\tYour choice  :  ");
				choice = numSelect(1, 1, 5);
				switch (choice)
				{
				case 1:
				{
					i = 0; y = 0;
					do
					{
						y = 0;
						printf("Please enter new Facility Name  (eg:Badminton Court...)                      :  ");
						rewind(stdin);
						scanf("%19[^\n]", temp.facName);
						for (i = 0; i < count; i++)
						{
							if (strcmp(fac1[i].facName, temp.facName) == 0)
							{
								printf("\tFacility name already exist!!!!\n");
								y++;
								break;
							}
						}
						if (strlen(temp.facName) == 0)
						{
							y++;
							printf("\tThe facility name cannot be blank!!!!.\n");
						}
						for (i = 0; i < strlen(temp.facName); i++)
						{

							if (isalpha(temp.facName[i]) == 0 && temp.facName[i] != ' ')
							{
								y++;
								printf("Invalid input, please enter alphabet only.\n");
								break;
							}
						}
					} while (y != 0);
					break;
				}
				case 2:
				{
					do
					{
						y = 0;
						printf("Please enter new Facilites Info    (eg:Court,shuttlecocks...)                :  ");
						rewind(stdin);
						scanf("%199[^\n]", temp.facItem);
						if (strlen(temp.facItem) == 0)
						{
							y++;
							printf("\tThe facility info cannot be blank!!!!.\n");
						}
						for (i = 0; i < strlen(temp.facItem); i++)
						{

							if (isalpha(temp.facItem[i]) == 0 && temp.facItem[i] != ' ')
							{
								y++;
								printf("Invalid input, please enter alphabet only.\n");
								break;
							}
						}

					} while (y != 0);
					break;
				}
				case 3:
				{
					do {
						y = 0;
						printf("Please enter new Facility Description (eg:Please book before using...)       :  ");
						rewind(stdin);
						scanf("%299[^\n]", temp.facDescription);
						if (strlen(temp.facDescription) == 0)
						{
							y++;
							printf("\tThe facility description cannot be blank!!!!.\n");
						}
						for (i = 0; i < strlen(temp.facDescription); i++)
						{

							if (isalpha(temp.facDescription[i]) == 0 && temp.facDescription[i] != ' ')
							{
								y++;
								printf("Invalid input, please enter alphabet only.\n");
								break;
							}
						}
					} while (y != 0);
					break;
				}
				case 4:
				{
					do {
						printf("Please enter new Facility Venue (room 3001,third floor of ...)               :  ");
						rewind(stdin);
						scanf("%99[^\n]", temp.facVenue);
						if (temp.facVenue[0] == NULL)
						{
							printf("\tThe facility venue cannot be blank.!!!!\n");
						}
					} while (temp.facVenue[0] == NULL);
					break;
				}
				case 5:
				{
					printf("Please select new Facility Time  (must between 9a.m. and 11p.m.,12pm-1pm is staff rest time)  :  ");
					time1 = numSelect2(9, 9, 11); printf("a.m. to "); time2 = numSelect2(1, 1, 11); printf("p.m.");
					sprintf(temp.facDateTime, "%da.m. to %dp.m.", time1, time2); break;
				}
				}
			}
			else
			{
				break;

			}
			printf("\n\tDo you want to further edit the information you enter just now? (Y/N)         :   ");
			ans = confirmSelect('Y', 'N');
		} while (ans == 'Y');
		printf("________________________________________________________________________________________________________________________\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("|  Facility Name           : %-90s|\n|  Facility Type           : %-90c|\n|  Facility ID             : A%03d\t\t\t\t\t\t\t\t\t\t\t|\n|  Facilities              : %-90s|\n|  Facility Description    : %-90s|\n|  Facility Venue          : %-90s|\n|  Facility Operation Hour : %-90s|\n|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", temp.facName, 'A', x, temp.facItem, temp.facDescription, temp.facVenue, temp.facDateTime);
		printf("________________________________________________________________________________________________________________________\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		strcpy(temp.facName, temp.facName);
		temp.facCode = 'A';
		temp.facID = x;
		strcpy(temp.facItem, temp.facItem);
		strcpy(temp.facDescription, temp.facDescription);
		strcpy(temp.facVenue, temp.facVenue);
		strcpy(temp.facDateTime, temp.facDateTime);

		printf("\tAre you sure you want to add this facility?  (Y/N)   :  ");
		ans = confirmSelect('Y', 'N');
		int written = 0;
		if (ans == 'Y')
		{
			FILE*fp2 = fopen("facilitylist.txt", "w+");
			for (i = 0; i < count; i++)
			{
				if (i == temp.facID - 1)
				{
					fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
						temp.facName,
						temp.facCode,
						temp.facID,
						temp.facItem,                                 //to print the data into file before other facilities clashes with it
						temp.facDescription,
						temp.facVenue,
						temp.facDateTime);
					written = 1;
				}
				fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
					fac1[i].facName,
					fac1[i].facCode,
					fac1[i].facID,
					fac1[i].facItem,
					fac1[i].facDescription,                           //to print the new facility info into text file
					fac1[i].facVenue,
					fac1[i].facDateTime);
			}
			if (i == count && written == 0)
			{
				fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
					temp.facName,
					temp.facCode,
					temp.facID,            //to print the data into the end of the file if other data doesn't clash with it
					temp.facItem,
					temp.facDescription,
					temp.facVenue,
					temp.facDateTime);
			}
			fclose(fp2);
			printf("\tAdding...\n");
			printf("\tCongratulations,new facility has been added.\n");
			printf("\n\n\t1.Continue\n\t2.Back to facility menu\n\n");
			printf("\tYour choice  :  ");
			ans = numSelect(2, 1, 2);
			if (ans == 1)
			{
				system("cls");
				addfac();
			}
			else
			{
				printf("\tYou will be redirect to facility menu now...\n");
				mainmenu();
				return;
			}
		}
		else
		{
			printf("\tAdding...\n");
			printf("\tAdding failed...\n");
			printf("\tnew facility has not been added.\n");
			printf("\n\n\t1.Continue\n\t2.Back to facility menu\n\n");
			printf("\tYour choice  :  ");
			ans = numSelect(2, 1, 2);
			if (ans == 1)
			{
				system("cls");
				addfac();
			}
			else
			{
				printf("\tYou will be redirect to facility menu now...\n");
				mainmenu();
				return;
			}

		}

	}



}

void editfac()
{
	int count = 0, choice,time1,time2,i=0,x,y;
	char toedit,ans;
	FILE*fp1 = fopen("facilitylist.txt", "r");
	if (fp1 == NULL)
	{
		printf("\tUnable to open file facilitylist.txt\n");
		system("pause");
		exit(-1);
	}
	//to obtain new correct facility id
	x = 1;
	while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		if (x != fac1[i].facID)
		{
			break;
		}
		x++;
		i++;
	}
	rewind(fp1);
	design();
	count = tocount();
	printf("\t------------------------------------------------\n");
	printf("\tNo. \t   Facility Name             Facility ID\n");
	printf("\t------------------------------------------------\n");
	i = 1;
	while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		printf("\t%-5d      %-20s          A%03d\n", i, fac1[i].facName, fac1[i].facID);
		i++;
	}
	rewind(fp1);
	printf("\t________________________________________________\n");
	printf("\t------------------------------------------------\n\n");
	printf("\tWhich facility do you want to edit  :  ");
	toedit = numSelect(1, 1, count)-1;
	printf("\t________________________________________________________________________________________________________________\n");
	printf("\t----------------------------------------------------------------------------------------------------------------\n");
	i = 0;	//to compare the information in the file and show the selected information
	while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		if (i == toedit)
		{
			printf("\t|  Facility Name           : %-82s|\n\t|  Facility Type           : %-82c|\n\t|  Facility ID             : A%03d\t\t\t\t\t\t\t\t\t\t|\n\t|  Facilities              : %-82s|\n\t|  Facility Description    : %-82s|\n\t|  Facility Venue          : %-82s|\n\t|  Facility Operation Hour : %-82s|\n\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|", fac1[toedit].facName, fac1[toedit].facCode, fac1[toedit].facID, fac1[toedit].facItem, fac1[toedit].facDescription, fac1[toedit].facVenue, fac1[toedit].facDateTime);

		}
		i++;
	}
	printf("\t\t|______________________________________________________________________________________________________________|\n");
	printf("\t----------------------------------------------------------------------------------------------------------------\n");
	fclose(fp1);
	printf("\tIs this the facility that you want to edit? (Y/N)    :  ");
	ans = confirmSelect('Y', 'N');
	do
	{

		if (ans == 'Y')
		{
			printf("\tWhich information do you want to edit\n");
			printf("\n\t1.Facility Info\n\t2.Facility Description\n\t3.Facility Venue\n\t4.Facility Time\n\n");
			printf("\tYour choice  :  ");
			choice = numSelect(1, 1, 4);
			switch (choice)
			{
			
			case 1:
			{
				do
				{
					y = 0;
					printf("Please enter new Facilites Info    (eg:Court,shuttlecocks...)                :  ");
					rewind(stdin);
					scanf("%199[^\n]", fac1[toedit].facItem);
					if (strlen(fac1[toedit].facItem) == 0)
					{
						y++;
						printf("\tThe facility info cannot be blank!!!!.\n");
					}
					for (i = 0; i < strlen(fac1[toedit].facItem); i++)
					{

						if (isalpha(fac1[toedit].facItem[i]) == 0 && fac1[toedit].facItem[i] != " ")
						{
							y++;
							printf("Invalid input, please enter alphabet only.\n");
							break;
						}
					}

				} while (y != 0);
				break;
			}
			
			case 2:
			{
				do {
					y = 0;
					printf("Please enter new Facility Description (eg:Please book before using...)       :  ");
					rewind(stdin);
					scanf("%299[^\n]", fac1[toedit].facDescription);
					if (strlen(fac1[toedit].facDescription) == 0)
					{
						y++;
						printf("\tThe facility description cannot be blank!!!!.\n");
					}
					for (i = 0; i < strlen(fac1[toedit].facDescription); i++)
					{

						if (isalpha(fac1[toedit].facDescription[i]) == 0 && fac1[toedit].facDescription[i] != " ")
						{
							y++;
							printf("Invalid input, please enter alphabet only.\n");
							break;
						}
					}
				} while (y != 0);
				break;
			}
			case 3:
			{
				do {
					printf("Please enter new Facility Venue (room 3001,third floor of ...)               :  ");
					rewind(stdin);
					scanf("%99[^\n]", fac1[toedit].facVenue);
					if (fac1[toedit].facVenue[0] == NULL)
					{
						printf("\tThe facility venue cannot be blank.!!!!\n");
					}
				} while (fac1[toedit].facVenue[0] == NULL);
				break;
			}
			case 4:
			{
				printf("\tPlease select new Facility Time  (must between 9a.m. and 11p.m.,12pm-1pm is staff rest time)  :  ");
				time1 = numSelect2(9, 9, 11); printf("a.m. to "); time2 = numSelect2(1, 1, 11); printf("p.m.");
				sprintf(fac1[toedit].facDateTime, "%da.m. to %dp.m.", time1, time2); break;
			}
			}
		}
		else
		{
			return;

		}
		printf("\tDo you want to further edit the information you enter just now? (Y/N)         :   ");
		ans = confirmSelect('Y', 'N');
	} while (ans == 'Y');

	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("________________________________________________________________________________________________________________________\n");

	printf("|  Facility Name           : %-90s|\n|  Facility Type           : %-90c|\n|  Facility ID             : A%03d\t\t\t\t\t\t\t\t\t\t\t|\n|  Facilities              : %-90s|\n|  Facility Description    : %-90s|\n|  Facility Venue          : %-90s|\n|  Facility Operation Hour : %-90s|\n|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", fac1[toedit].facName, 'A', toedit+1, fac1[toedit].facItem, fac1[toedit].facDescription, fac1[toedit].facVenue, fac1[toedit].facDateTime);
	printf("|______________________________________________________________________________________________________________________|\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	strcpy(fac1[toedit].facName, fac1[toedit].facName);
	fac1[toedit].facCode = 'A';
	fac1[toedit].facID = toedit+1;
	strcpy(fac1[toedit].facItem, fac1[toedit].facItem);
	strcpy(fac1[toedit].facDescription, fac1[toedit].facDescription);
	strcpy(fac1[toedit].facVenue, fac1[toedit].facVenue);
	strcpy(fac1[toedit].facDateTime, fac1[toedit].facDateTime);

	printf("\tAre you sure you want to edit this facility?  (Y/N)   :  ");
	ans = confirmSelect('Y', 'N');
	if (ans == 'Y')
	{
		FILE*fp2 = fopen("facilitylist.txt", "w+");
		for (i = 0; i < count; i++)
		{
			
			fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
				fac1[i].facName,
				fac1[i].facCode,
				fac1[i].facID,
				fac1[i].facItem,                      //to print the information into the file
				fac1[i].facDescription,
				fac1[i].facVenue,
				fac1[i].facDateTime);
		}
		fclose(fp2);
		printf("\tAdding...\n");
		printf("\tCongratulations,facility has been edited.\n");
		printf("\n\n\t1.Continue\n\t2.Back to facility menu\n\n");
		printf("\tYour choice  :  ");
		ans = numSelect(2, 1, 2);
		if (ans == 1)
		{
			system("cls");
			addfac();
		}
		else
		{
			printf("\tYou will be redirect to facility menu now...\n");
			mainmenu();
			return;
		}
	}
	else
	{
		printf("\tEditing...\n");
		printf("\tEditing failed...\n");
		printf("\tFacility has not been editted.\n");
		printf("\n\n\t1.Continue\n\t2.Back to facility menu\n\n");
		printf("\tYour choice  :  ");
		ans = numSelect(2, 1, 2);
		if (ans == 1)
		{
			system("cls");
			editfac();
		}
		else
		{
			printf("\tYou will be redirect to facility menu now...\n");
			mainmenu();
			return;
		}

	}

}
void delfac()
{
	int count=0,choice,i=0;
	char todelete;
	FILE*fp1=fopen("facilitylist.txt", "r");
	if (fp1 == NULL)
	{
		printf("Unable to open file facilitylist.txt\n");
		system("pause");
		exit(-1);
	}

	design();
	count = tocount();
	printf("\t------------------------------------------------\n");
	printf("\tNo. \t   Facility Name             Facility ID\n");
	printf("\t------------------------------------------------\n");
	i = 0;
	while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		printf("\t%-5d      %-20s          A%03d\n", i + 1,fac1[i].facName,fac1[i].facID);
		i++;
    }

	rewind(fp1);
	printf("\t________________________________________________\n");
	printf("\t------------------------------------------------\n\n");
	printf("\tWhich facility ID do you want to delete ?\n\n  ");
	printf("\tYour Choice  :  ");
	choice=numSelect(1,1,count) - 1;
	printf("\t________________________________________________________________________________________________________________\n");
	printf("\t----------------------------------------------------------------------------------------------------------------\n");
	i = 0;
	//to compare the facility to delete in the file
	while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		if (i == choice)
		{
			printf("\t|  Facility Name           : %-82s|\n\t|  Facility Type           : %-82c|\n\t|  Facility ID             : A%03d\t\t\t\t\t\t\t\t\t\t|\n\t|  Facilities              : %-82s|\n\t|  Facility Description    : %-82s|\n\t|  Facility Venue          : %-82s|\n\t|  Facility Operation Hour : %-82s|\n\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|", fac1[i].facName, fac1[i].facCode, fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime);

		}
		i++;
	}
	printf("\t\t|______________________________________________________________________________________________________________|\n");
	printf("\t----------------------------------------------------------------------------------------------------------------\n");
	fclose(fp1);
	printf("\tIs this the facility that you want to delete? (Y/N)    :  ");
	todelete=confirmSelect('Y', 'N');
	i = 0;
	if (todelete == 'Y')
	{
		FILE*fp2 = fopen("facilitylist.txt", "w+");
		for(i=0;i<count;i++)
		{
			if (i == choice)
			{
				continue;
			}
			fprintf(fp2, "%s|%c|%d|%s|%s|%s|%s|\n",
				fac1[i].facName,
				fac1[i].facCode,
				fac1[i].facID,
				fac1[i].facItem,
				fac1[i].facDescription,
				fac1[i].facVenue,
				fac1[i].facDateTime);
		}

		printf("\tDeleting...\n");
		printf("\tFacility A%03d have been deleted.\n ",fac1[choice].facID);
		fclose(fp2);
		mainmenu();
		return;
	}
	else
	{
		fclose(fp1);
		system("cls");
		return;
	}
}

void searchfac()
{
	int count = 0, tosearch; char choice, i = 0;
	FILE*fp;
	fp = fopen("facilitylist.txt", "r");
	if (fp == NULL)
	{

		printf("Unable to open file facilitylist.txt\n");
		system("pause");
		exit(-1);
	}
	count=tocount();
	design();
	printf("\tPlease enter the facility id you want to search  :  A00");
	tosearch=numSelect1(1, 1, count);
	printf("________________________________________________________________________________________________________________________\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	i = 1;
	//to compare the information to search in the file
	while (fscanf(fp, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		if (i == tosearch)
		{
			printf("|  Facility Name           : %-90s|\n|  Facility Type           : %-90c|\n|  Facility ID             : A%03d\t\t\t\t\t\t\t\t\t\t\t|\n|  Facilities              : %-90s|\n|  Facility Description    : %-90s|\n|  Facility Venue          : %-90s|\n|  Facility Operation Hour : %-90s|\n|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n", fac1[i].facName, fac1[i].facCode, fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime);

		}
		i++;
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("________________________________________________________________________________________________________________________\n");
	printf("\tDo you want to continue searching (Y/N)   :  ");
	choice = confirmSelect('Y', 'N');
	if (choice=='Y')
	{
		system("cls");
		searchfac();
	}
	else
	{
		mainmenu();
		return;
	}

}

void design()
{
	printf("\t _____   ____    __  ____  _      ____  ______  __ __      ___ ___   ___   ___    __ __  _        ___ \n"
		"\t|     | /    |  /  ]|    || |    |    ||      ||  |  |    |   |   | /   \\ |   \\  |  |  || |      /  _]\n"
		"\t|   __||  o  | /  /  |  | | |     |  | |      ||  |  |    | _   _ ||     ||    \\ |  |  || |     /  [_ \n"
		"\t|  |_  |     |/  /   |  | | |___  |  | |_|  |_||  ~  |    |  \\_/  ||  O  ||  D  ||  |  || |___ |    _]\n"
		"\t|   _] |  _  /   \\_  |  | |     | |  |   |  |  |___, |    |   |   ||     ||     ||  :  ||     ||   [_ \n"
		"\t|  |   |  |  \\     | |  | |     | |  |   |  |  |     |    |   |   ||     ||     ||     ||     ||     |\n"
		"\t|__|   |__|__|\\____||____||_____||____|  |__|  |____/     |___|___| \\___/ |_____| \\__,_||_____||_____|\n");
}

void mainmenu()
{
	char anything;

	printf("\tPress any key to back to main screen (*^~0~^*)  :  ");
	rewind(stdin);
	scanf("%c", &anything);
	system("cls");
}

int tocount()
{
	int i = 0;
	FILE *fp1 = fopen("facilitylist.txt", "r");
	int count1 = 0;
	while (fscanf(fp1, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[i].facName, &fac1[i].facCode, &fac1[i].facID, fac1[i].facItem, fac1[i].facDescription, fac1[i].facVenue, fac1[i].facDateTime) != EOF)
	{
		count1++;
	}
	rewind(fp1);
	return count1;
}

int numSelect1(int start, int min, int max)
{
	unsigned char choice1, choice2;
	int i=0;
	char c[10];
	printf("%-10d", start);
	sprintf(c, "%02d", start);
	for (int x = 0; x < 10 - strlen(c); x++)
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

			for (int x = 0; x < 10 - strlen(c); x++)
				printf(" ");
			for (int x = 0; x < 10; x++)
				printf("\b");
			printf("%-10d", i);
			sprintf(c, "%d", i);
			for (int x = 0; x < 10 - strlen(c); x++)
				printf("\b");
		}
	}printf("\n");
	return i;
}
int numSelect2(int start, int min, int max)
{
	unsigned char choice1, choice2;
	int i=0;
	char c[10];
	printf("%-10d", start);
	sprintf(c, "%02d", start);
	for (int x = 0; x < 10 - strlen(c); x++)
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

			for (int x = 0; x < 10 - strlen(c); x++)
				printf(" ");
			for (int x = 0; x < 10; x++)
				printf("\b");
			printf("%-10d", i);
			sprintf(c, "%d", i);
			for (int x = 0; x < 10 - strlen(c); x++)
				printf("\b");
		}
	}
	return i;
}
