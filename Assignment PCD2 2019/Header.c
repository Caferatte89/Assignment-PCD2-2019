#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int todayDate(char toDisplay[])
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	if (toDisplay == "day")
		return tm.tm_mday;
	else if (toDisplay == "month")
		return tm.tm_mon + 1;
	else if (toDisplay == "year")
		return tm.tm_year + 1900;
	else
		return -1;
}