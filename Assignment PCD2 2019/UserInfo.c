#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<string.h>
#include"Header.h"
#pragma warning(disable:4996)

struct user
{
	char name[30], id[20], c[4], contact[16], code[6], password1[30], password2[30];
	int date, month, year, time1, time2, time3;
};

/* 》test to add gmail.
   》验证码*/

void main()
{
	FILE*fptra;
	FILE*fptrr;
	FILE*fptrw;
	fptra = fopen("userinput.txt", "a");
	fptrr = fopen("userinput.txt", "r");
	fptrw = fopen("userinput.txt", "w");

	struct user u;

	char answer = 'Y', ac, aw;
	int ans;

	while (toupper(answer) == 'Y')
	{
		printf("Welcome for use our booking system!\n");

		time_t t;
		time(&t);

		printf("\n\nToday's Date : %s\n\n", ctime(&t));

		printf("Welcome to Personal Users Interface!\n"
			"First,Please key in your user account.\n\n"
			"Do you have an account ? (Y\N) \n"
			">>");
		scanf("%c", &ac);
		rewind(stdin);
		if (toupper(ac) == 'Y')
		{
			printf("Now, Enter your user name > ");
			scanf("%[^\n]", u.name);
			rewind(stdin);


		}
		else if (toupper(ac) == 'N')
		{
			printf("OK.Are you create a new user account ? (Y/N)\n>>");
			scanf("%c", &aw);
			rewind(stdin);
			if (toupper(aw) == 'Y')
			{
				printf("OK. Now try enter your user name >");
				scanf("%[^\n]", u.name);
				rewind(stdin);
				printf("\nNext,Enter your user ID >");
				scanf("%s", u.id);
				rewind(stdin);
				printf("\nEnter your contact number (01XXXXXXXX) >");
				scanf("%s", u.contact);
				rewind(stdin);
				printf("Enter your password >");
				scanf("%s", u.password1);
				rewind(stdin);
				printf("Now,try to enter your password again.\nTo make sure it correct.\n>");
				scanf("%s", u.password2);
				rewind(stdin);
				if (strcmp(u.password1, u.password2) == 0)
				{
					fprintf(fptra, "%d | %d | %d | %d", u.name, u.id, u.contact, u.password1);
				}
				printf("Now, please select your Identity.\n");
				printf("1. Teacher. \n");
				printf("2. Student.\n");
				printf("3. staff member.\n");
				printf("4. Unrelated person.\n");
				printf("5. Other.");
				scanf("%d", &ans);
				switch (ans)
				{
				case 1:
					printf("Enter your name > ");
					scanf("%[^\n]", u.name);
					rewind(stdin);
					printf("Enter your ID (PMDXXXXX) > ");
					scanf("%s", u.id);
					rewind(stdin);
					printf("Enter your password > ");
					scanf("%s", u.password1);
					rewind(stdin);
					if (fscanf(fptrr, "%s", u.password1))

						printf("Enter your class code > ");
					scanf("%s", u.code);
					rewind(stdin);
					fprintf(fptra, "%s | %s | %s | %s", u.name, u.id, u.password1, u.code);
				case 2:
					break;
				}

			}
			else if (toupper(aw) == 'N')
			{
				printf("Thank for use our system.");
			}
			else
			{
				printf("Your reply is invalid.\nPlease try to enter again.\n\n>>");

			}
		}
		else
		{
			printf("Your reply is invalid.Please try again with Y = yes or N = no for continue your uses.\n");

		}


	}
	system("pause");
}
