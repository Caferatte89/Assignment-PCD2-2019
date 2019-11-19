#include <stdio.h>
#include <stdlib.h>
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