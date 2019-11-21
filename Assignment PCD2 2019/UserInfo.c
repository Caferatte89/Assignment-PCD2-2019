#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<string.h>
#include"Header.h"
#pragma warning(disable:4996)

char ans;

UserInfo u;
StudentInfo s;

void student();
void staff();

/*Gmail, List user, yanzhengma, */
	/*Register*/

void main()
{
	FILE *fptr;
	fptr = fopen("userinput.txt", "a");
	printf("Enter your user name \n>>");
	scanf("%[^\n]", u.name);
	rewind(stdin);
	printf("\nPlease enter your user ID (XXXXXXXXXX)\n>>");
	scanf("%s", u.id);
	rewind(stdin);
	printf("\nEnter your IC (XXXXXX-XX-XXXX)\n>>");
	scanf("%s", u.IC);
	rewind(stdin);
	printf("\nEnter your gender.(B = Boy/G = Girl)\n>>");
	scanf("%s", u.gender);
	rewind(stdin);
	printf("\nEnter your contact number. (01X-XXXX XXX)\n>>");
	scanf("%[^\n]", u.phoneNum);
	rewind(stdin);
	printf("\n\nChoose your Identity.\n"
		"1.Student\n"
		"2.Staff Member\n\n>>");
	scanf("%d", &u.choose1);
	rewind(stdin);
	switch (u.choose1)
	{
	case 1:
		student();
		fprintf(fptr,"%s %s %d year %d sem\n %s %s %s %s",
			       u.name,s.classroom,s.yearstu,s.semstu,u.id,u.IC,u.gender,u.phoneNum);
		break;

	case 2:
		printf("Please enter your job occupation. "
			"1.Teacher \n"
			"2.Staff Member \n"
			"3.Guest \n\n>>");
		scanf("%d", &u.chooset);
		rewind(stdin);
		switch (u.chooset)
		{
		case 1:
			printf("Success for register.\n");
			fprintf(fptr, "%s Teacher \n %s %s %s %s",
				u.name, u.id, u.IC, u.gender, u.phoneNum);
			break;

		case 2:
			printf("Success for register.\n");
			fprintf(fptr, "%s Staff Member \n %s %s %s %s",
				u.name, u.id, u.IC, u.gender, u.phoneNum);
			break;

		case 3:
			printf("Success for register.\n");
			fprintf(fptr, "%s Guest \n %s %s %s %s",
				u.name, u.id, u.IC, u.gender, u.phoneNum);
			break;

		default:
			printf("Your reply is invaid. Please entry again.");
			break;
		}

	default :
		printf("Your reply is invaid. Please entry again.");
		break;
	}
	fclose(fptr);
	system("pause");
}

void student()
{
	printf("Enter your class (DCO) \n>");
	scanf("%s", s.classroom);
	rewind(stdin);
	printf("Enter your Year in Study (1-3) \n>>");
	scanf("%d", s.yearstu);
	rewind(stdin);
	printf("Enter your sem in year (1-3)\n>>");
	scanf("%d", s.semstu);
	rewind(stdin);
}

void staff()
{
	
}