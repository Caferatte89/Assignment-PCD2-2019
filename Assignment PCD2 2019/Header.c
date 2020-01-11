#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "Header.h"
#pragma warning(disable:4996)

int checkFile(char fileName[])
{
	int test;
	FILE *fp;
	if (fopen(fileName, "r") == NULL)
		return -1;
	else
	{
		fp = fopen(fileName, "r");
		if (fscanf(fp, "%d", &test) == EOF)
			return 0;
		else
			return 1;
	}
}

int checkTimeValid(int time)
{
	if (time < 0 || time > 2359 || time % 100 >= 60)
		return 0;
	else
		return 1;
}

int checkDateValid(int day, int month, int year)
{
	if (day < 1 || day > 31 || month < 1 || month > 12)
		return 0;
	else if (month == 2)
	{
		if (!(year % 4 == 0) && day == 29)
			return 0;
		else if (!(year % 100 == 0) && day == 28)
			return 0;
		else if (!(year % 400 == 0) && day == 29)
			return 0;
		else
			return 1;
	}
	else if (month < 8 && month % 2 == 0 && day == 31)
		return 0;
	else if (month > 8 && month % 2 != 0 && day == 31)
		return 0;
	else
		return 1;
}

int todayDate(char toDisplay[])
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	if (strcmp(toDisplay, "day") == 0)
		return tm.tm_mday;
	else if (strcmp(toDisplay, "month") == 0)
		return tm.tm_mon + 1;
	else if (strcmp(toDisplay, "year") == 0)
		return tm.tm_year + 1900;
	else if (strcmp(toDisplay, "hour") == 0)
		return tm.tm_hour;
	else if (strcmp(toDisplay, "minute") == 0)
		return tm.tm_min;
	else if (strcmp(toDisplay, "second") == 0)
		return tm.tm_sec;
	else
		return -1;
}

int checkLeap(int year)
{
	if (year % 4 != 0)
		return 0;
	else if (year % 100 != 0)
		return 1;
	else if (year % 400 != 0)
		return 0;
	else
		return 1;
}

char confirmSelect(char X, char Y)
{
	unsigned char choice1, choice2;
	char confirm = X;

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
			if (confirm == X)
				confirm = Y;
			else
				confirm = X;
		}
		else if (choice2 == 72)
		{
			if (confirm == X)
				confirm = Y;
			else
				confirm = X;
		}
		else
			continue;

		printf("\b");
		printf("%c", confirm);
	}

	printf("\n");
	return confirm;
}

int numSelect(int start, int min, int max)
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
	printf("\n");

	return i;
}