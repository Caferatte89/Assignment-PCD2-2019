#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<time.h>
#include "Header.h"
#pragma warning(disable:4996)

typedef struct
{
	char bookID[6], facID[7], userID[11];
	int bookStart, bookEnd;
	Date dateWhenBooking, dateBooked;
} DateArrange;

typedef struct
{
	int facnum;
	char facname[30], facID, facItem[200], facDescription[300], facVenue[100], facDateTime[20];
}Facility;

typedef struct 
{
	char ID[6];
} Id;

typedef struct
{
	char attendance[20];
}Attendance;

void arrangeData();
void arrangFacility();
int checkMenu(char type);
void customizedReports();
void monthlyReport();
void yearlyReport();
void userReport(char id[]);
void attendance(char id[]);
int numSelectUsage(int start, int min, int max);
char checkValid;


void FacilityUsageMod(char type,char id[])
{
	int choise;
	arrangFacility();
	arrangeData();
	if (type == 'S')
	{
		do
		{
			choise = checkMenu(type);
			switch (choise)
			{
			case 1: attendance(id); break;
			case 2: customizedReports(); break;
			case 3: monthlyReport(); break;
			case 4: yearlyReport(); break;
			default:;
			}
		} while (choise != 5);
	}
	else
	{
		do
		{
			choise = checkMenu(type);
			switch (choise)
			{
			case 1: attendance(id); break;
			case 2: userReport(id); break;
			default:;
			}
		} while (choise != 3);
	}
}

int numSelectUsage(int start, int min, int max)
{
	unsigned char choice1, choice2;
	int i;
	char c[10];

	printf("%-10d", start);
	sprintf(c, "%d", start);
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

void arrangFacility()
{
	Facility fac1[100], temp;

	int num, num1 = 0, num2 = 1;

	FILE *facility = fopen("facilitylist.txt", "r");
	FILE *fFacility = fopen("ArrangeFacility.txt", "w");

	num = 0;
	//read and stor the data from BookingLog.txt
	while (!feof(facility))
	{
		fscanf(facility, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[num].facname, &fac1[num].facID,
			&fac1[num].facnum, fac1[num].facItem, fac1[num].facDescription, fac1[num].facVenue, fac1[num].facDateTime);
		num++;
	}

	//arrange the year data
	for (num1 = 0; num1 < num; num1++)
	{
		if (strcmp(fac1[num1].facname, fac1[num1 + 1].facname) == 0)
		{
			fprintf(fFacility, "%s|%c|%d|%s|%s|%s|%s|\n", fac1[num1].facname, fac1[num1].facID,
				fac1[num1].facnum, fac1[num1].facItem, fac1[num1].facDescription, fac1[num1].facVenue, fac1[num1].facDateTime);
		}
		else
		{
			fprintf(fFacility, "%s|%c|%d|%s|%s|%s|%s|\n", fac1[num1].facname, fac1[num1].facID,
				fac1[num1].facnum, fac1[num1].facItem, fac1[num1].facDescription, fac1[num1].facVenue, fac1[num1].facDateTime);

			for (num2 = num1 + 1; num2 < num; num2++)
			{
				if (strcmp(fac1[num1].facname, fac1[num2].facname) == 0)
				{
					temp = fac1[num1 + 1];
					fac1[num1 + 1] = fac1[num2];
					fac1[num2] = temp;
				}
			}
		}
	}

	fclose(facility);
	fclose(fFacility);
}

void arrangeData()
{
	int num, num1, num2;
	char month[10], year[5], day[4];
	char attendence[20] = "Absent";

	strcpy(year, "year");
	strcpy(month, "month");
	strcpy(day, "day");

	DateArrange da[100], temp;

	FILE *fbooking = fopen("BookingList.txt", "r");
	FILE *fArrange = fopen("Arrange.txt", "w");

	//check the file can open or not
	if (!fbooking)
	{
		printf("file BookingLog.txt cannot open");
		system("pause");
		exit(-1);
	}

	//check the file can open or not
	if (!fArrange)
	{
		printf("file arrangeBooked.txt cannot open");
		system("pause");
		exit(-1);
	}

	num = 0;
	//read and stor the data from BookingLog.txt
	while (!feof(fbooking))
	{
		fscanf(fbooking, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", da[num].bookID,
			&da[num].dateWhenBooking.day, &da[num].dateWhenBooking.month, &da[num].dateWhenBooking.year,
			&da[num].dateBooked.day, &da[num].dateBooked.month, &da[num].dateBooked.year,
			&da[num].bookStart, &da[num].bookEnd, da[num].userID, da[num].facID);
		num++;
	}

	//arrange the year data
	for (num1 = 0; num1 < num; num1++)
	{
		for (num2 = 0; num2 < num - num1; num2++)
		{
			if (da[num2].dateBooked.year > da[num2 + 1].dateBooked.year)
			{
				temp = da[num2];
				da[num2] = da[num2 + 1];
				da[num2 + 1] = temp;
			}
		}
	}

	//arrange the month data
	for (num1 = 0; num1 < num; num1++)
	{
		for (num2 = 0; num2 < num - num1; num2++)
		{
			if (da[num2].dateBooked.month > da[num2 + 1].dateBooked.month &&
				da[num2].dateBooked.year == da[num2 + 1].dateBooked.year)
			{
				temp = da[num2];
				da[num2] = da[num2 + 1];
				da[num2 + 1] = temp;
			}
		}
	}

	//arrange the day data
	for (num1 = 0; num1 < num; num1++)
	{
		for (num2 = 0; num2 < num - num1; num2++)
		{
			if (da[num2].dateBooked.day > da[num2 + 1].dateBooked.day &&
				da[num2].dateBooked.month == da[num2 + 1].dateBooked.month &&
				da[num2].dateBooked.year == da[num2 + 1].dateBooked.year)
			{
				temp = da[num2];
				da[num2] = da[num2 + 1];
				da[num2 + 1] = temp;
			}
		}
	}

	//arrange the time 
	for (num1 = 0; num1 < num; num1++)
	{
		for (num2 = 0; num2 < num - num1; num2++)
		{
			if (da[num2].bookStart > da[num2 + 1].bookStart &&
				da[num2].dateBooked.day == da[num2 + 1].dateBooked.day &&
				da[num2].dateBooked.month == da[num2 + 1].dateBooked.month &&
				da[num2].dateBooked.year == da[num2 + 1].dateBooked.year)
			{
				temp = da[num2];
				da[num2] = da[num2 + 1];
				da[num2 + 1] = temp;
			}
		}
	}

	//store the booking detail after arrange to arrangeBooked.txt
	for (num1 = 0; num1 < num + 1; num1++)
	{
		if (da[num1].dateWhenBooking.day > 0 && da[num1].dateWhenBooking.day < 31)
		{
			if (da[num1].dateBooked.year <= todayDate(year))
			{
				if ((da[num1].dateBooked.month > todayDate(month)) && (da[num1].dateBooked.year == todayDate(year)))
				{
				}
				else
				{
					if (da[num1].dateBooked.day > todayDate(day) && ((da[num1].dateBooked.month == todayDate(month)) && (da[num1].dateBooked.year == todayDate(year))))
					{
					}
					else
					{
						fprintf(fArrange, "%s|%02d/%02d/%d|%02d/%02d/%d|%04d-%04d|%s|%s|%s\n", da[num1].bookID,
							da[num1].dateWhenBooking.day, da[num1].dateWhenBooking.month, da[num1].dateWhenBooking.year,
							da[num1].dateBooked.day, da[num1].dateBooked.month, da[num1].dateBooked.year,
							da[num1].bookStart, da[num1].bookEnd, da[num1].userID, da[num1].facID, attendence);
					}
				}
			}
		}
	}

	fclose(fbooking);
	fclose(fArrange);
}

int checkMenu(char type) 
{
	int choise;
	printf("\n _____   ____    __  ____  _      ____  ______  __ __      __ __  _____  ____   ____    ___ \n"
	"|     | /    |  /  ]|    || |    |    ||      ||  |  |    |  |  |/ ___/ /    | /    |  /  _]\n"
    "|   __||  o  | /  /  |  | | |     |  | |      ||  |  |    |  |  (   \\_ |  o  ||   __| /  [_ \n"
	"|  |_  |     |/  /   |  | | |___  |  | |_|  |_||  ~  |    |  |  |\\__  ||     ||  |  ||    _]\n"
	"|   _] |  _  /   \\_  |  | |     | |  |   |  |  |___, |    |  :  |/  \\ ||  _  ||  |_ ||   [_ \n"
	"|  |   |  |  \\     | |  | |     | |  |   |  |  |     |    |     |\\    ||  |  ||     ||     |\n"
	"|__|   |__|__|\\____||____||_____||____|  |__|  |____/      \\__,_| \\___||__|__||___,_||_____|\n");

	if (type == 'S')
	{
		//let user enter the detail user want to check
		printf("\n -----------------------\n"
			" |    Staff  Menu      |\n"
			" -----------------------\n"
			" |1.Attandence         |\n"
			" |2.Customized reports |\n"
			" |3.Monthly reports    |\n"
			" |4.Yearly reports     |\n"
			" |5.Back               |\n"
			" ----------------------\n");
		printf(" Select your choise >>> ");
		choise = numSelectUsage(1, 1, 5);
	}
	else
	{
		//let user enter the detail user want to check
		printf("\n -----------------------\n"
			" |     User  Menu      |\n"
			" -----------------------\n"
			" |1.Attandence         |\n"
			" |2 Reports            |\n"
			" |3.Back               |\n"
			" ----------------------\n");
		printf(" Select your choise >>> ");
		choise = numSelectUsage(1, 1, 3);
	}
	return choise;
}

void monthlyReport()
{
	int months, years, count = 0;
	char file[30], fileYear[30];
	char choise, get, year[5],month[10];

	strcpy(year, "year");
	strcpy(month, "month");

	DateArrange da;
	
	do
	{
		FILE *fArrange = fopen("ArrangeBooked.txt", "r");
		do {
			//let user select the year want to check
			printf("\n\n Select the year     : ");
			years = numSelectUsage(2015, 2015, todayDate("year"));

			//transfer the (int)year to (string)year
			sprintf(fileYear, "%d", years);
			strcpy(file, fileYear);

			if (years == todayDate(year))
			{
				printf("\n Select the month    : ");
				months = numSelectUsage(1, 1, todayDate(month));
			}
			else
			{
				printf("\n Select the month    : ");
				months = numSelectUsage(1, 1, 12);
			}

			//confirm the year and month
			printf("\n Do you sure you want to check the year : %d month : %d ? (y=yes,n=no) : ", years, months);
			choise = confirmSelect('n', 'y');

		} while (toupper(choise) == 'N');

		switch (months)
		{
		case 1:strcat(file, "JanuaryReport.txt"); break;
		case 2:strcat(file, "FebruaryReport.txt"); break;
		case 3:strcat(file, "MarchReport.txt"); break;
		case 4:strcat(file, "AprilReport.txt"); break;
		case 5:strcat(file, "MayReport.txt"); break;
		case 6:strcat(file, "JuneReport.txt"); break;
		case 7:strcat(file, "JulyReport.txt"); break;
		case 8:strcat(file, "AugustReport.txt"); break;
		case 9:strcat(file, "SeptemberReport.txt"); break;
		case 10:strcat(file, "OctoberReport.txt"); break;
		case 11:strcat(file, "NovemberReport.txt"); break;
		default:strcat(file, "DecemberReport.txt");
		}

		//creat a file for stor the monthly report
		FILE *fMonthly = fopen(file, "w");

		//show the monthly report
		printf("\n\n\t======================================================================================\n");
		printf("\t| %-11s  %-15s   %-14s %-10s %-14s %s|", "Booking ID", "Date of Booking", "Date Booked", "   Time   ", "  User ID ", "Facility ID");
		printf("\n\t======================================================================================\n");
		while (!feof(fArrange))
		{
			fscanf(fArrange, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", da.bookID,
				&da.dateWhenBooking.day, &da.dateWhenBooking.month, &da.dateWhenBooking.year,
				&da.dateBooked.day, &da.dateBooked.month, &da.dateBooked.year,
				&da.bookStart, &da.bookEnd, da.userID, da.facID);

			if (da.dateBooked.month == months && da.dateBooked.year == years)
			{
				//save the data into the monthly file
				fprintf(fMonthly, "%s|%02d/%02d/%02d|%02d/%02d/%02d|%02d-%02d|%s|%s\n", da.bookID,
					da.dateWhenBooking.day, da.dateWhenBooking.month, da.dateWhenBooking.year,
					da.dateBooked.day, da.dateBooked.month, da.dateBooked.year,
					da.bookStart, da.bookEnd, da.userID, da.facID);

				printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", da.bookID,
					da.dateWhenBooking.day, da.dateWhenBooking.month, da.dateWhenBooking.year,
					da.dateBooked.day, da.dateBooked.month, da.dateBooked.year,
					da.bookStart, da.bookEnd, da.userID, da.facID);

				count++;
			}
		}

		printf("\t======================================================================================\n");
		//show the number of booking and show the hours of booking
		printf("\n\t Total hours of booking : %d hour(s)\n\t Total number of use    : %d record(s)\n", count, count);

		printf("\n\t Do you want check more monthly report? (Y=yes,N=no) >>> ");
		get = confirmSelect('Y', 'N');

		fclose(fMonthly);
		fclose(fArrange);

		count = 0;
	}while (get == 'Y');

}

void yearlyReport()
{
	int years, count = 0;
	char file[30], fileYear[30];
	char choise, get,year[5];

	strcpy(year, "year");

	DateArrange da;
	

	do
	{
		FILE *fArrange = fopen("ArrangeBooked.txt", "r");
		do {
			//let user select the year
			printf("\n\n Select the year      : ");
			years = numSelectUsage(2015, 2015, todayDate(year));

			sprintf(fileYear, "%d", years);
			strcpy(file, fileYear);

			//confirm the year
			printf("\n The year you want to check is %d ? (y=yes,n=no) >>> ", years);
			choise = confirmSelect('n', 'y');

		} while (toupper(choise) == 'N');

		strcat(file, "Report.txt");
		//creat a file for stor the yearly report
		FILE *fYearly = fopen(file, "w");

		//show the yearly report to user
		printf("\n\n\t======================================================================================\n");
		printf("\t| %-11s  %-15s   %-14s %-10s %-14s %s|", "Booking ID", "Date of Booking", "Date Booked", "   Time   ", "  User ID ", "Facility ID");
		printf("\n\t======================================================================================\n");
		while (!feof(fArrange))
		{
			fscanf(fArrange, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", da.bookID,
				&da.dateWhenBooking.day, &da.dateWhenBooking.month, &da.dateWhenBooking.year,
				&da.dateBooked.day, &da.dateBooked.month, &da.dateBooked.year,
				&da.bookStart, &da.bookEnd, da.userID, da.facID);

			if (da.dateBooked.year == years)
			{
				//save the data into the yearly report file
				fprintf(fYearly, "%s|%02d/%02d/%02d|%02d/%02d/%02d|%02d-%02d|%s|%s\n", da.bookID,
					da.dateWhenBooking.day, da.dateWhenBooking.month, da.dateWhenBooking.year,
					da.dateBooked.day, da.dateBooked.month, da.dateBooked.year,
					da.bookStart, da.bookEnd, da.userID, da.facID);

				printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", da.bookID,
					da.dateWhenBooking.day, da.dateWhenBooking.month, da.dateWhenBooking.year,
					da.dateBooked.day, da.dateBooked.month, da.dateBooked.year,
					da.bookStart, da.bookEnd, da.userID, da.facID);

				count++;
			}
		}

		//show the number of booking and the total hours of use
		printf("\t======================================================================================\n");
		printf("\n\t Total hours of booking : %d hour(s)\n\t Total number of use    : %d record(s)\n", count, count);

		printf("\n\t Do you want to check more yearly report ? ('Y','N') >>> ");
		get = confirmSelect('Y', 'N');

		fclose(fYearly);
		fclose(fArrange);

		count = 0;

	} while (get == 'Y');


}

void customizedReports()
{

	Date df, dt;
	Facility fac1[100];
	DateArrange temp;
	
	char get;
	char facilitysearch, daterangesearch, useridsearch, cid, comfirm, staffID[10], userId[10];
	int choise, num, row = 0, col = 0, num1 = 0, num2 = 1, num4[100][100], i, count = 0, getf = 0, leap;
	int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	char month[10], year[5], day[4];

	strcpy(year, "year");
	strcpy(month, "month");
	strcpy(day, "day");
	
	do
	{

		FILE *fArrange = fopen("ArrangeBooked.txt", "r");
		FILE *facility = fopen("ArrangeFacility.txt", "r");

		choise = 0;
		num = 0;
		row = 0;
		col = 0;
		num1 = 0;
		num2 = 1;
		i = 0;
		count = 0;
		getf = 0;
		leap = 0;
		for (int x = 0; x < 100; x++)
		{
			for (int y = 0; y < 100; y++)
			{
				num4[x][y] = 0 ;
			}
		}

		while (!feof(facility))
		{
			fscanf(facility, "%[^|]|%c|%d|%[^|]|%[^|]|%[^|]|%[^|]|\n", fac1[num].facname, &fac1[num].facID,
				&fac1[num].facnum, fac1[num].facItem, fac1[num].facDescription, fac1[num].facVenue, fac1[num].facDateTime);
			num++;
		}

		do
		{
			cid = 'Y';
			getf = 0;
			//let user select the detail subject
			printf("\n\n Select the subject want to check (Y = search, N = don't search) \n\n");

			printf(" Fcility      : ");
			facilitysearch = confirmSelect('Y', 'N');

			printf(" Date Range   : ");
			daterangesearch = confirmSelect('Y', 'N');

			printf(" User ID      : ");
			useridsearch = confirmSelect('Y', 'N');

			do {
				if (facilitysearch == 'Y')
				{

					num2 = 1;
					num1 = 0;
					row = 0;
					col = 0;

					//let user enter the number of facility want to change
					printf("\n %5s---------------------\n"
						" %5s|     Facility NO    |\n"
						" %5s---------------------\n", "", "", "");
					printf(" %5s| %d. %-15s |\n", "", num2, fac1[num1].facname);
					num4[row][col] = fac1[num1].facnum;
					col++;
					num2++;
					for (num1 = 1; num1 < num; num1++)
					{
						if (strcmp(fac1[num1].facname, fac1[num1 - 1].facname) != 0)
						{
							row++;

							col = 0;
							num4[row][col] = fac1[num1].facnum;
							printf(" %5s| %d. %-15s |\n", "", num2, fac1[num1].facname);
							num2++;
							col++;
						}
						else
						{
							num4[row][col] = fac1[num1].facnum;
							col++;
						}
					}
					printf(" %5s----------------------\n", "");

					printf("\n Facility NO %9s : ", "");
					choise = numSelectUsage(1, 1, num2 - 1);

				}

				if (daterangesearch == 'Y')
				{

					//let user enter the date start from
					printf("\n Date start from       : ");
					df.year = numSelectUsage(2015, 2015, todayDate(year));
					printf("/");
					if (df.year == todayDate(year))
					{
						df.month = numSelectUsage(1, 1, todayDate(month));
						printf("/");
					}
					else
					{
						df.month = numSelectUsage(1, 1, 12);
						printf("/");
					}

					leap = checkLeap(df.year);
					if (leap == 1)
					{
						months[1] = 29;
					}
					else
					{
						months[1] = 28;
					}

					if ((df.year == todayDate(year)) && (df.month == todayDate(month)))
					{
						df.day = numSelectUsage(1, 1, todayDate(day));
					}
					else
					{
						df.day = numSelectUsage(1, 1, months[df.month - 1]);
					}

					//let user enter the date end to
					printf("\n Date end to           : ");
					dt.year = numSelectUsage(df.year, df.year, todayDate(year));
					printf("/");

					if (dt.year == todayDate(year))
					{
						dt.month = numSelectUsage(1, 1, (todayDate(month)));
						printf("/");
					}
					else if (dt.year == df.year && (df.year != todayDate(year)))
					{

						dt.month = numSelectUsage(df.month, df.month, 12);
						printf("/");
					}
					else
					{
						dt.month = numSelectUsage(1, 1, 12);
						printf("/");
					}

					leap = checkLeap(dt.year);
					if (leap == 1)
					{
						months[1] = 29;
					}
					else
					{
						months[1] = 28;
					}

					if ((dt.year == todayDate(year)) && (dt.month == todayDate(month)))
					{
						dt.day = numSelectUsage(1, 1, todayDate(day));
					}
					else if (dt.year == df.year && dt.month == df.month)
					{
						dt.day = numSelectUsage(df.day, df.day, months[dt.month - 1]);
					}
					else
					{
						dt.day = numSelectUsage(1, 1, months[dt.month - 1]);
					}



				}

				if (useridsearch == 'Y')
				{

					printf("\n staff or user(S = staff, U = user) : ");
					comfirm = confirmSelect('S', 'U');

					if (comfirm == 'U')
					{
						printf(" Plese enter the ID (e.g.1904032) : ");
						rewind(stdin);
						scanf("%[^\n]%c", userId, &checkValid);
						while (strlen(userId) != 7 || checkValid != '\n')
						{
							printf("\n\n%10s<!> invalid plese enter again <!> \n\n", "");
							printf(" Plese enter the ID (e.g.1904032) : ");
							rewind(stdin);
							scanf("%[^\n]%c", userId, &checkValid);
						}
						for (int i = 0; i < strlen(userId); i++)
						{
							if (isalpha(userId[i]) != 0)
							{
								printf("\n\n%10s<!> invalid plese enter again <!> \n\n", "");
								printf(" Plese enter the ID (e.g.1904032) : ");
								rewind(stdin);
								scanf("%[^\n]%c", userId, &checkValid);
							}
						}
					}
					else
					{
						printf(" Plese enter the ID (e.g.S0001) : ");
						rewind(stdin);
						scanf("%[^\n]%c", staffID, &checkValid);
						while (strlen(staffID) != 5 || checkValid != '\n' || toupper(staffID[0]) != 'S' || isalpha(staffID[1]) != 0 || isalpha(staffID[2]) != 0 || isalpha(staffID[3]) != 0 || isalpha(staffID[4]) != 0)
						{
							printf("\n\n%10s<!> invalid plese enter again <!> \n\n", "");
							printf(" Plese enter the ID (e.g.S0001) : ");
							rewind(stdin);
							scanf("%[^\n]%c", staffID, &checkValid);
						}
						staffID[0]=toupper(staffID[0]);
					}
				}



				if (useridsearch != 'N' || daterangesearch != 'N' || facilitysearch != 'N')
				{
					printf("\n Do you confirm the DATA want to check is coract ?(Y = yes, N = no): ");
					cid = confirmSelect('Y', 'N');
				}

			} while (cid == 'N' && (useridsearch != 'N' || daterangesearch != 'N' || facilitysearch != 'N'));

			if (facilitysearch == 'N' && daterangesearch == 'N' && useridsearch == 'N')
			{
				printf("\n Are you sure you don't want to chek the report and back to the check menu (1 = menu,2 = reenter) : ");
				getf = numSelectUsage(1, 1, 2);

				if (getf == 1)
				{
					return;
				}
			}

		} while (getf == 2);

		//print the output to user
		printf("\n\n\t======================================================================================\n");
		printf("\t| %-11s  %-15s   %-14s %-10s %-14s %s|", "Booking ID", "Date of Booking", "Date Booked", "   Time   ", "  User ID ", "Facility ID");
		printf("\n\t======================================================================================\n");
		while (!feof(fArrange))
		{
			fscanf(fArrange, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", temp.bookID,
				&temp.dateWhenBooking.day, &temp.dateWhenBooking.month, &temp.dateWhenBooking.year, &temp.dateBooked.day, &temp.dateBooked.month, &temp.dateBooked.year,
				&temp.bookStart, &temp.bookEnd, temp.userID, temp.facID);
			if (temp.dateBooked.year <= todayDate(year))
			{
				if ((temp.dateBooked.month > todayDate(month)) && (temp.dateBooked.year == todayDate(year)))
				{
				}
				else
				{
					if (temp.dateBooked.day > todayDate(day) && ((temp.dateBooked.month > todayDate(month)) && (temp.dateBooked.year == todayDate(year))))
					{
					}
					else
					{
						if (facilitysearch == 'Y')
						{
							sscanf(temp.facID, "A%d", &num);
							for (i = 0; i < 99; i++)
							{
								if (num == num4[choise - 1][i])
								{
									if (daterangesearch == 'Y')
									{
										if (temp.dateBooked.year >= df.year && temp.dateBooked.year <= dt.year)
										{
											if ((temp.dateBooked.month >= df.month && temp.dateBooked.year == df.year) || (temp.dateBooked.month <= dt.month&&temp.dateBooked.year == dt.year) || (temp.dateBooked.year > df.year && temp.dateBooked.year < dt.year))
											{
												if ((temp.dateBooked.day >= df.day && temp.dateBooked.month == df.month) || (temp.dateBooked.day <= dt.day && temp.dateBooked.month == dt.month) || (temp.dateBooked.month > df.month && temp.dateBooked.month < dt.month))
												{
													if (useridsearch == 'Y')
													{
														if (comfirm == 'U')
														{
															if (strcmp(userId, temp.userID) == 0)
															{
																printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
																	temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
																	temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
																count++;
															}
														}
														else
														{
															if (strcmp(staffID, temp.userID) == 0)
															{
																printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
																	temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
																	temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
																count++;
															}
														}
													}
													else
													{
														printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
															temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
															temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
														count++;
													}
												}

											}
										}
									}


									else if (useridsearch == 'Y')
									{
										if (comfirm == 'U')
										{
											if (strcmp(userId, temp.userID) == 0)
											{
												printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
													temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
													temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
												count++;
											}
										}
										else
										{
											if (strcmp(staffID, temp.userID) == 0)
											{
												printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
													temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
													temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
												count++;
											}
										}
									}
									else
									{
										printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
											temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
											temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
										count++;
									}
								}
							}
						}
						else if (daterangesearch == 'Y')
						{
							if (temp.dateBooked.year >= df.year && temp.dateBooked.year <= dt.year)
							{
								if ((temp.dateBooked.month >= df.month && temp.dateBooked.year == df.year) || (temp.dateBooked.month <= dt.month&&temp.dateBooked.year == dt.year) || (temp.dateBooked.year > df.year && temp.dateBooked.year < dt.year))
								{
									if ((temp.dateBooked.day >= df.day && temp.dateBooked.month == df.month) || (temp.dateBooked.day <= dt.day && temp.dateBooked.month == dt.month) || (temp.dateBooked.month > df.month && temp.dateBooked.month < dt.month))
									{
										if (useridsearch == 'Y')
										{
											if (comfirm == 'U')
											{
												if (strcmp(userId, temp.userID) == 0)
												{
													printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
														temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
														temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
													count++;
												}
											}
											else
											{
												if (strcmp(staffID, temp.userID) == 0)
												{
													printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
														temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
														temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
													count++;
												}
											}
										}
										else
										{
											printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
												temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
												temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
											count++;
										}
									}

								}
							}
						}
						else
						{
							if (comfirm == 'U')
							{
								if (strcmp(userId, temp.userID) == 0)
								{
									printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
										temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
										temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
									count++;
								}
							}
							else
							{
								if (strcmp(staffID, temp.userID) == 0)
								{
									printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", temp.bookID,
										temp.dateWhenBooking.day, temp.dateWhenBooking.month, temp.dateWhenBooking.year, temp.dateBooked.day, temp.dateBooked.month, temp.dateBooked.year,
										temp.bookStart, temp.bookEnd, temp.userID, temp.facID);
									count++;
								}
							}
						}
					}
				}
			}
		}
		printf("\t======================================================================================\n");
		//show the number of booking and show the hours of booking
		printf("\n\t Total hours of booking : %d hour(s)\n\t Total number of use    : %d record(s)\n", count, count);

		printf("\n\t Do you want check more customized report? (Y=yes,N=no) >>> ");
		get = confirmSelect('Y', 'N');

		fclose(facility);
		fclose(fArrange);

	} while (get == 'Y');

}

void userReport(char id[])   
{
	int count = 0;
	id[0] = toupper(id[0]);
	char comfirm;

	DateArrange da;
	FILE *fArrange = fopen("ArrangeBooked.txt", "r");

	printf("\n\n\t======================================================================================\n");
	printf("\t| %-11s  %-15s   %-14s %-10s %-14s %s|", "Booking ID", "Date of Booking", "Date Booked", "   Time   ", "  User ID ", "Facility ID");
	printf("\n\t======================================================================================\n");
	while (!feof(fArrange))
	{
		fscanf(fArrange, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%s\n", da.bookID,
			&da.dateWhenBooking.day, &da.dateWhenBooking.month, &da.dateWhenBooking.year,
			&da.dateBooked.day, &da.dateBooked.month, &da.dateBooked.year,
			&da.bookStart, &da.bookEnd, da.userID, da.facID);
		if (strcmp(id, da.userID) == 0)
		{
			printf("\t| %-11s  %-02d/%02d/%02d        %-02d/%02d/%02d     %04d-%04d    %-11s  %-11s|\n", da.bookID,
				da.dateWhenBooking.day, da.dateWhenBooking.month, da.dateWhenBooking.year,
				da.dateBooked.day, da.dateBooked.month, da.dateBooked.year,
				da.bookStart, da.bookEnd, da.userID, da.facID);

			count++;
		}
	}

	//show the number of booking and the total hours of use
	printf("\t======================================================================================\n");
	printf("\n\t Total hours of booking : %d hour(s)\n\t Total number of use    : %d record(s)\n", count, count);
	printf("\n\t Enter the X to back menu : ");
	comfirm = confirmSelect('X', 'X');
	printf("\n");
	fclose(fArrange);
}

void attendance(char id[])
{
	id[0] = toupper(id[0]);
	int count = 0, num = 0, num1 = 0;
	char month[10], year[5], day[4], hour[5], comfirm, atten[12], menu, attendance[20];

	strcpy(atten, "Attendance");
	strcpy(hour, "hour");
	strcpy(year, "year");
	strcpy(month, "month");
	strcpy(day, "day");

	DateArrange da[100];

	FILE *fArrange = fopen("Arrange.txt", "r");

	FILE *fBooking = fopen("ArrangeBooked.txt", "a");

	num = 0;
	num1 = 0;

	while (!feof(fArrange))
	{
		fscanf(fArrange, "%[^|]|%d/%d/%d|%d/%d/%d|%d-%d|%[^|]|%[^|]|%[^\n]\n", da[num].bookID,
			&da[num].dateWhenBooking.day, &da[num].dateWhenBooking.month, &da[num].dateWhenBooking.year,
			&da[num].dateBooked.day, &da[num].dateBooked.month, &da[num].dateBooked.year,
			&da[num].bookStart, &da[num].bookEnd, da[num].userID, da[num].facID, attendance);

		if (strcmp(attendance, atten) != 0);
		{
			if (strcmp(id, da[num].userID) == 0)
			{
				if ((da[num].dateBooked.day == todayDate(day)) && (da[num].dateBooked.month == todayDate(month)) && (da[num].dateBooked.year == todayDate(year)) && (da[num].bookStart == todayDate(hour) * 100))
				{
					printf("\n\n\t %s|%d/%d/%d|%d/%d/%d|%02d-%02d|%s|%s|%s\n", da[num].bookID,
						da[num].dateWhenBooking.day, da[num].dateWhenBooking.month, da[num].dateWhenBooking.year,
						da[num].dateBooked.day, da[num].dateBooked.month, da[num].dateBooked.year,
						da[num].bookStart, da[num].bookEnd, da[num].userID, da[num].facID, attendance);

					printf("\n You want take the attendance ? (Y=yes,N=no) :");
					comfirm = confirmSelect('Y', 'N');

					if (comfirm == 'Y')
					{
						printf("\n\t %s|%d/%d/%d|%d/%d/%d|%d-%d|%s|%s|%s\n", da[num].bookID,
							da[num].dateWhenBooking.day, da[num].dateWhenBooking.month, da[num].dateWhenBooking.year,
							da[num].dateBooked.day, da[num].dateBooked.month, da[num].dateBooked.year,
							da[num].bookStart, da[num].bookEnd, da[num].userID, da[num].facID, atten);

						num1 = num;

						printf("\n You take the attendance successful\n");

						fprintf(fBooking, "%s|%02d/%02d/%02d|%02d/%02d/%02d|%02d-%02d|%s|%s\n", da[num].bookID,
							da[num].dateWhenBooking.day, da[num].dateWhenBooking.month, da[num].dateWhenBooking.year,
							da[num].dateBooked.day, da[num].dateBooked.month, da[num].dateBooked.year,
							da[num].bookStart, da[num].bookEnd, da[num].userID, da[num].facID);
					}
					count++;
				}

			}
			num++;
		}
	}

	fclose(fArrange);

	FILE *farrange = fopen("Arrange.txt", "w");
	for (num = 0; num < 100; num++)
	{
		if (num != num1 && da[num].dateBooked.day > 0 && da[num].dateBooked.day < 32)
		{
			fprintf(farrange, "%s|%02d/%02d/%d|%02d/%02d/%d|%04d-%04d|%s|%s|%s\n", da[num].bookID,
				da[num].dateWhenBooking.day, da[num].dateWhenBooking.month, da[num].dateWhenBooking.year,
				da[num].dateBooked.day, da[num].dateBooked.month, da[num].dateBooked.year,
				da[num].bookStart, da[num].bookEnd, da[num].userID, da[num].facID, attendance);
		}
	}
	fclose(farrange);

	if (count == 0)
	{
		printf("\n\n NOT have booking now");
		printf("\n Return to menu ");
	}


	printf("\n Enter the X bake to menu : ");
	menu = confirmSelect('X', 'X');
	fclose(fBooking);
}
