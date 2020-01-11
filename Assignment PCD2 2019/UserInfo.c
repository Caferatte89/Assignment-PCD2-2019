#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include <time.h>
#include<conio.h>
#include "Header.h"
#pragma warning(disable:4996)


void hidepw(char* password);//let password words become **
char randGenAlph();//use random to make a question to prove user is not a robot
//void login();
void logout();
void errorID();
void verificationCode();//random question to user
void passwordAnswer();
void wrongPassword();//function when user key in wrong password
void wrongId();
void userMenu();
void welcome_menu();
void main_menu();
void mamual();//display mamual
void errorMessage();
void titleRegister();//header Register
void userInterface();
void error();
void backToUserMenu();
void modifyMenu();//function modify
void searchMenu();//function search user
void exitMenu();
void registerUser();//Function for Register
void verificationCode();//The question to let user key in 
int isInvalidName(char* name);//Username Valitation
char* getUserName();//Function to get the User Name and Valitation
char* getUserGender();//Fuction to get the user Gender and Valitation 
char*getUserPassword();


void endyearFunction(UserInfo* user);
void changeNameMenu(UserInfo user);//change name function in Modify
void changePhoneNum(UserInfo user);//change phoneNum function in Modify
void changePasswordmenu(UserInfo user);//change password function in Modify
void changeExitMenu();//for exit function in modify
UserInfo SearchByPhoneNum(char * user_phoneNum);
UserInfo SearchByPassword(char * user_password);
UserInfo SearchById(char* user_id);
UserInfo SearchByIc(char * user_ic);//Search Function
UserInfo SearchByPasswordAnswer(char * user_passwordAnswer);//Check the password Answer
void AddUser(UserInfo user);//Add user such as include Register Function
void displayUser(UserInfo user);//User search one user and display that user
void displayAllUser();//Function to Display All User
void modifyUser(UserInfo user, int type, char* oldValue, char * newValue);//Modify Function
int isInvalidID(UserInfo user, char *id);//Valitation of ID in function getUserID
int isInvalidIC(UserInfo user, char *ic);//Valitation of IC in function getUserIC
int checkPassword(UserInfo user, char* userpassword);//Password Valitation
void passwordAnswerChoose(UserInfo *user);//get the user Password Answer and Valitation
char* getUserID(UserInfo user);//get the user ID and function Valitation
char* getUserIC(UserInfo user);//get the user IC and function Valitation
char*getUserphoneNum(UserInfo user);//get the user phoneNum and function Valitation

void UserInformationMod()
{
	welcome_menu();
	userMenu();
	system("pause");
}

char randGenAlph()
{
	char character;

	do
	{
		character = rand() % 58 + 65;
	} while (!((character >= 65 && character <= 90) || (character >= 97 && character <= 122)));

	return character;
}


void hidepw(char* password) {
	int y = 0, x;
	while (y <= strlen(password))
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

UserInfo SearchById(char * user_id)
{
	UserInfo user;

	FILE*fptr;
	fptr = fopen("userInfo.bin", "rb");
	if (fptr == NULL)
	{
		fptr = fopen("userInfo.bin", "wb");
	}
	while (fread(&user, sizeof(user), 1, fptr) != 0)
	{

		if (strcmp(user.id, user_id) == 0)
		{
			break;
		}
	}

	fclose(fptr);

	return user;
}

UserInfo SearchByPhoneNum(char * user_phoneNum)
{
	UserInfo user;

	FILE*fptr;
	fptr = fopen("userInfo.bin", "rb");
	while (fread(&user, sizeof(user), 1, fptr) != 0)
	{

		if (strcmp(user.IC, user_phoneNum) == 0)
		{
			break;
		}
	}

	fclose(fptr);

	return user;
}

UserInfo SearchByIc(char * user_ic)
{
	UserInfo user;

	FILE*fptr;
	fptr = fopen("userInfo.bin", "rb");
	while (fread(&user, sizeof(user), 1, fptr) != 0)
	{

		if (strcmp(user.IC, user_ic) == 0)
		{
			break;
		}
	}

	fclose(fptr);

	return user;
}

UserInfo SearchByPasswordAnswer(char * user_answerpassword)
{
	UserInfo user;

	FILE*fptr;
	fptr = fopen("userInfo.bin", "rb");
	while (fread(&user, sizeof(user), 1, fptr) != 0)
	{

		if (strcmp(user.answerpassword, user_answerpassword) == 0)
		{
			break;
		}
	}

	fclose(fptr);

	return user;
}

UserInfo SearchByPassword(char * user_password)
{
	UserInfo user;

	FILE*fptr;
	fptr = fopen("userInfo.bin", "rb");
	while (fread(&user, sizeof(user), 1, fptr) != 0)
	{

		if (strcmp(user.password, user_password) == 0)
		{
			break;
		}
	}

	fclose(fptr);

	return user;
}

void AddUser(UserInfo user)
{
	FILE*fptra = fopen("userInfo.bin", "ab");

	fwrite(&user, sizeof(user), 1, fptra);

	fclose(fptra);
}

void displayUser(UserInfo user)
{
	printf("\n%40s***********************************************\n", "");
	printf("%40sUser name : %s\n", "", user.userName);
	printf("%40s Position : Student\n", "");
	printf("%40s Gender   : %s\n", "", user.gender);
	printf("%40s   ID     : %s\n", "", user.id);
	printf("%40s   IC     : %s\n", "", user.IC);
	printf("%40s PhoneNum : %s\n\n", "", user.phoneNum);
	printf("%40s Your User Account will end in %d/%d/%d\n", "", user.date.day, user.date.month, user.date.year);
	printf("%40s***********************************************\n", "");
}

void modifyUser(UserInfo user, int type, char* oldValue, char * newValue)
{
	// type: 0: change username, 1: change phonenumber, 2: change password
	FILE *fp;
	fp = fopen("userInfo.bin", "r+b");
	if (!fp)
		return;
	while (fread(&user, sizeof(user), 1, fp) != 0)
	{
		if (type == 0)
		{
			if (strcmp(user.userName, oldValue) == 0)
			{
				strcpy(user.userName, newValue);
				fseek(fp, ftell(fp) - sizeof(user), SEEK_SET);
				fwrite(&user, sizeof(user), 1, fp);
				break;
			}
		}

		else if (type == 1)
		{
			if (strcmp(user.phoneNum, oldValue) == 0)
			{
				strcpy(user.phoneNum, newValue);
				fseek(fp, ftell(fp) - sizeof(user), SEEK_SET);
				fwrite(&user, sizeof(user), 1, fp);
				break;
			}

		}
		else if (type == 2)
		{
			if (strcmp(user.password, oldValue) == 0)
			{
				strcpy(user.password, newValue);
				fseek(fp, ftell(fp) - sizeof(user), SEEK_SET);
				fwrite(&user, sizeof(user), 1, fp);
				break;
			}

		}

	}
	fclose(fp);
}

void displayAllUser()
{
	UserInfo user;

	FILE*fptr;
	fptr = fopen("userInfo.bin", "rb");
	while ((fread(&user, sizeof(user), 1, fptr) != 0))
	{
		displayUser(user);
	}

	fclose(fptr);
}

void main_menu()//main menu
{
	int input;

	printf("\n%48sWelcome to Main Menu !\n", "");
	printf("%48s----------------------\n\n", "");
	printf("%50s-----------------\n", "");
	printf("%50s| 1. | Register |\n", "");
	printf("%50s-----------------\n", "");
	printf("%50s| 2. | Login    |\n", "");
	printf("%50s-----------------\n", "");
	printf("%50s| 3. | Exit     |\n", "");
	printf("%50s-----------------\n\n%48s>>", "", "");
	input = numSelect(1, 1, 3);
	switch (input)
	{
	case 1:
		registerUser();
		return;

	case 2:
		return;

	case 3:
		exitMenu();
	default:
		errorMessage();
		break;
	}
}

void welcome_menu()//welcome menu
{
	printf("\n%30s========================================================\n", "");
	printf("%30s  __    __    ___  _        __   ___   ___ ___    ___ \n", "");
	printf("%30s |  |__|  |  /  _]| |      /  ] /   \\ |   |   |  /  _] \n", "");
	printf("%30s |  |  |  | /  [_ | |     /  / |     || _   _ | /  [_ |\n", "");
	printf("%30s |  |  |  ||    _]| |___ /  /  |  O  ||  \\_/  ||    _]  \n", "");
	printf("%30s |  `  '  ||   [_ |     /    \\_ |     ||   |   ||   [_   \n", "");
	printf("%30s  \\      / |     ||     \\      ||   ||   |   ||     |\n", "");
	printf("%30s   \\_/\\_/  |_____||_____|\\____| \\___/ |___|___||___|\n", "");
	printf("%30s========================================================\n\n", "");
	printf("%44sWelcome to our booking system.\n", "");
	printf("%40s-------------------------------------\n", "");
	printf("%27sLog in with your Account to get your bookmarks, history, passwords, \n % 40sand other settings on all your devices.\n\n", "", "");
	printf("%35s>> Extremely grateful for using our Booking system!! <<\n", "");
	printf("%35s-------------------------------------------------------\n", "");
	printf("\n%39s[Please choose between the following options.]\n\n", "");
	printf("%37sYou can press 'UP' and 'DOWN' to choose your answer.\n", "");
	printf("%37s----------------------------------------------------\n", "");

}

void titleRegister()//header menu
{
	printf("\n%15s|--------------------------------------------------------------------------------------|\n", "");
	printf("%15s|  _    _                 _____            _     _                 _   _               |\n"
		"%15s| | |  | |               |  __ \\          (_)   | |               | | (_)              |\n"
		"%15s| | |  | |___  ___ _ __  | |__) |___  __ _ _ ___| |_ ___ _ __ __ _| |_ _  ___  _ __    |\n"
		"%15s| | |  | / __|/ _ \\ '__| |  _  // _ \\/ _` | / __| __/ _ \\ '__/ _` | __| |/ _ \\| '_ \\   |\n"
		"%15s| | |__| \\__ \\  __/ |    | | \\ \\  __/ (_| | \\__ \\ ||  __/ | | (_| | |_| | (_) | | | |  |\n"
		"%15s|  \\____/|___/\\___|_|    |_|  \\_\\___|\\__, |_|___/\\__\\___|_|  \\__,_|\\__|_|\\___/|_| |_|  |\n"
		"%15s|                                     __/ |                                            |\n"
		"%15s|                                   |___/                                              |\n", "", "", "", "", "", "", "", "");
	printf("%15s|--------------------------------------------------------------------------------------|\n\n", "");
	printf("%45sWelcome to User Registeration Interface !\n", "");
	printf("%45s-----------------------------------------\n\n", "");

}

void userInterface()// 
{
	printf("%30s+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n", "");
	printf("%30s  _    _                 _____       _             __                         \n", "");
	printf("%30s | |  | |               |_   _|     | |           // _|              \n", "");
	printf("%30s | |  | |___  ___ _ __    | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___ \n", "");
	printf("%30s | |  | / __|// _ \\ '__|   | | | '_ \\| __// _ \\ '__|  _// _` |// __// _ \\ \n", "");
	printf("%30s | |__| \\__ \\  __/ |     _| |_| | | | ||  __/ |  | || (_| | (_|  __// \n", "");
	printf("%30s  \\____/|___/\\___|_|    |_____|_| |_|\\__\\___|_|  |_| \\__,_|\\___\\___| \n", "");
	printf("%30s+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n", "");

}

void errorMessage()
{
	printf("%30s<!>-----------------------------------<!>\n", "");
	printf("%30s|     ___  ____   ____   ___   ____    |\n", "");
	printf("%30s|    /  _]|    \\ |    \\ /   \\ |    \\   |\n", "");
	printf("%30s|   /  [_ |  D  )|  D  )     ||  D  )  |\n", "");
	printf("%30s|  |    _]|    / |    /|  O  ||    /   |\n", "");
	printf("%30s|  |   [_ |    \\ |    \\|     ||    \\   |\n", "");
	printf("%30s|  |     ||  .  \\|  .  \\     ||  .  \\  |\n", "");
	printf("%30s|  |_____||__|\\_||__|\\_|\\___/ |__|\\_|  |\n", "");
	printf("%30s<!>-----------------------------------<!>\n\n", "");
	printf("%30s <!> Warning, Error Message !!\n", "");
	printf("%30sAs a precaution, system will Automatice save User Data and transfer to Main Menu.\n", "");
	main_menu();
}

void userMenu()
{
	int as;

	printf("\n%40sWelcome to User Interface !!\n", "");
	printf("%40s----------------------------\n", "");
	printf("%40sThis is your User Menu.\n", "");
	printf("%40s-----------------------\n", "");
	printf("%40s-----------------------------------------------\n", "");
	printf("%40s| 1.Display User Information                   |\n", "");
	printf("%40s-----------------------------------------------\n", "");
	printf("%40s| 2.Modify User Information                    |\n", "");
	printf("%40s-----------------------------------------------\n", "");
	printf("%40s| 3.Search Another User Information            |\n", "");
	printf("%40s-----------------------------------------------\n", "");
	printf("%40s| 4.Exit                                       |\n", "");
	printf("%40s-----------------------------------------------\n", "");
	printf("%40s>>", "");
	as = numSelect(1, 1, 4);
	switch (as)
	{
	case 1:
		displayAllUser();
		backToUserMenu();
		break;

	case 2:
		modifyMenu();
		break;

	case 3:
		searchMenu();
		break;

	case 4:
		logout();
		break;

	default:
		errorMessage();
		break;
	}
}

void modifyMenu()
{
	int input;
	char id[10];
	UserInfo user;

	do {
		printf("%40sNow is Modify Interface.\n", "");
		printf("%40sWelcome to User Modify System.\n", "");
		printf("%40s---------------------------\n", "");
		printf("%42sUse your User Account\n", "");
		printf("%42s---------------------\n\n", "");
		printf("%40sEnter your userID (1906246)\n", "");
		printf("%40s---------------------------\n", "");
		printf("%40s>>", "");
		rewind(stdin);
		scanf("%s", id);
		user = SearchById(id);
	} while (strcmp(user.id, id) != 0);

	do {

		printf("\n%40sPlease choose according to the following options\n", "");
		printf("%40s------------------------------------------------\n", "");
		printf("%40s1.Name\n", "");
		printf("%40s2.PhoneNum\n", "");
		printf("%40s3.Password\n", "");
		printf("%40s4.Exit. (Back to User Menu)\n\n", "");
		printf("%36sIF you want to modify your ID setting, Gender setting and other.\n", "");
		printf("%36s----------------------------------------------------------------\n", "");
		printf("%40sYou can went to our counter to making your Modify.\n", "");
		printf("%40s--------------------------------------------------\n\n", "");
		printf("%45s->>", "");
		input = numSelect(1, 1, 4);
		switch (input)
		{
		case 1:
			changeNameMenu(user);
			break;
		case 2:
			changePhoneNum(user);
			break;

		case 3:
			changePasswordmenu(user);
			break;

		case 4:
			changeExitMenu();
			break;

		default:
			errorMessage();
			break;
		}
	} while (1);
}


void mamual()
{
	printf("%40s********************************************************\n", "");
	printf("%40s| 1.    You can make your register in Main Menu.       |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 2. Please remember your studentID and your password. |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 3. You will use it in your log in function.          |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 4. Then, you can setting your answer in UserMenu     |\n", "");
	printf("%40s|              & in Register Function.                 |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 5. This can use when you forgrt your password or     |\n", "");
	printf("%40s|          your StudentID in Log In function           |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 6.    You also can do Modify Information Function    |\n", "");
	printf("%40s|            in your User Interface                    |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 7.        You also can view your Information         |\n", "");
	printf("%40s|                in your User Information              |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 8.     You can press 'UP' AND 'DOWN' to control      |\n", "");
	printf("%40s|                     your reply.                      |\n", "");
	printf("%40s--------------------------------------------------------\n", "");
	printf("%40s| 9. IF you have any question, Please call 019-4132207 |\n", "");
	printf("%40s|        or send email to xxxwer@gmail.com.            |\n", "");
	printf("%40s********************************************************\n\n", "");
	printf("%40sIF you have any Temporary problem, you can find our counter to solve your question.\n", "");
	printf("%40sThank for looking Beginner's Manual.\n", "");
	printf("%40s------------------------------------\n", "");
	printf("%40sHope our system can bring you the best service.\n", "");
	printf("%40s-----------------------------------------------\n", "");
}


void error()
{
	printf("%30s<!>-----------------------------------<!>\n", "");
	printf("%30s|     ___  ____   ____   ___   ____    |\n", "");
	printf("%30s|    /  _]|    \\ |    \\ /   \\ |    \\   |\n", "");
	printf("%30s|   /  [_ |  D  )|  D  )     ||  D  )  |\n", "");
	printf("%30s|  |    _]|    / |    /|  O  ||    /   |\n", "");
	printf("%30s|  |   [_ |    \\ |    \\|     ||    \\   |\n", "");
	printf("%30s|  |     ||  .  \\|  .  \\     ||  .  \\  |\n", "");
	printf("%30s|  |_____||__|\\_||__|\\_|\\___/ |__|\\_|  |\n", "");
	printf("%30s<!>-----------------------------------<!>\n\n", "");
}

void backToUserMenu()
{
	int input, input1;

	printf("%35sAre you want to back your User Menu ?\n", "");
	printf("%40s1.Yes\n", "");
	printf("%40s2.No\n\n%40s>>", "", "");
	input = numSelect(1, 1, 2);
	switch (input)
	{
	case 1:
		userMenu();
		break;

	case 2:
		printf("%40sAre you want to stay in user Information Interface ?\n", "");
		printf("%40s1.Yes, I want stay here.\n", "");
		printf("%40s2.Ern, Maybe I need to do some additional Modify.\n\n%40s>>", "", "");
		input1 = numSelect(1, 1, 2);
		switch (input1)
		{
		case 1:
			displayAllUser();
			backToUserMenu();
			break;

		case 2:
			modifyMenu();
			break;

		default:
			errorMessage();
			break;
		}

	default:
		errorMessage();
		break;
	}
}


void searchMenu()
{
	char uid[8], checkValid;
	int input, input1;
	UserInfo user;
	do
	{
		printf("%40sPlease Enter The User's ID that you want to search.\n%40s->>", "", "");
		rewind(stdin);
		scanf("%s%c", uid, &checkValid);

		user = SearchById(uid);

		if (strcmp(user.id, uid) == 0)
		{
			displayUser(user);
			printf("%40sAre you want to continue ?\n", "");
			printf("%40s--------------------------\n", "");
			printf("%40s 1. Yes\n", "");
			printf("%40s 2. No\n\n%40s->>", "", "");
			input1 = numSelect(1, 1, 2);
			switch (input1)
			{
			case 1:
				searchMenu();
				break;

			case 2:
				printf("%40sBack to User Menu.\n\n", "");
				userMenu();
				break;

			default:
				errorMessage();
				break;
			}
		}
		else
		{
			printf("%40sSearch Complete !\n\n", "");
			printf("%40sQuery failed...\n", "");
			printf("%40s----------------------------------------------\n", "");
			printf("%40sAre you want to continue to search ? \n", "");
			printf("%40s 1. Yes\n", "");
			printf("%40s 2. No [Back to User Menu]\n\n%40s->>", "", "");
			input = numSelect(1, 1, 2);
			switch (input)
			{
			case 1:
				break;

			case 2:
				userMenu();
				break;

			default:
				errorMessage();
				break;
			}
		}

	} while (strcmp(user.id, uid) != 0);
}

void exitMenu()
{
	int input;
	printf("%45sAre you sure to exit our system ?\n", "");
	printf("%45s=================================\n", "");
	printf("%45s          1.  Yes.               \n", "");
	printf("%45s          2.   No. \n            \n", "");
	printf("%45s>>", "");
	input = numSelect(1, 1, 2);
	switch (input)
	{
	case 1:
		printf("%40sThank you for use our system !!", "");
		exit(-1);
		break;

	case 2:
		printf("%45sPlease make sure your Decide.\n", "");
		printf("%45s-----------------------------\n\n", "");
		main_menu();
		break;

	default:
		errorMessage();
		break;
	}
}

void changeNameMenu(UserInfo user)
{
	int input;
	char name[30];
	do
	{
		do {
			printf("%40sUser Name Modify\n", "");
			printf("%40s----------------\n", "");
			printf("%40sBefore Modify ->> %s\n\n", "", user.userName);
			printf("%40sAfter Modify ->>", "");
			rewind(stdin);
			scanf("%[^\n]", name);
		} while (isInvalidName(name));
		printf("%40sDoS you confirm your change ?\n", "");
		printf("%40s1.Yes. (Back to Modify Function)\n", "");
		printf("%40s2.No\n\n%40s->>", "", "");
		input = numSelect(1, 1, 2);
		switch (input)
		{
		case 1:
			modifyUser(user, 0, user.userName, name);
			modifyMenu();
			break;

		case 2:
			break;

		default:
			errorMessage();
			break;
		}
	} while (input == 2 || (1));
}

void changePhoneNum(UserInfo user)
{
	char phoneNum[10];
	char checkValid;
	int input;
	do
	{
		printf("%40sUser PhoneNumber Modify\n", "");
		printf("%40s-----------------------\n", "");
		printf("%40sBefore Modify --> %s\n", "", user.phoneNum);
		printf("%40sAfter Modify ->>", "");
		rewind(stdin);
		scanf("%s", phoneNum);
		if (strlen(phoneNum) < 10)//Phone Number must be more than 10
		{
			printf("%40sError !! Your Phone Number must more than 10 number value.\n", "");
		}
		for (unsigned int x = 0; x < strlen(phoneNum); x++)
		{
			if (isdigit(phoneNum[x]) == 0)
			{
				printf("%40sError, Phone number must not contain alphabet !!\n%40sPlease try again.\n", "", "");
				printf("%40s---------------------------------------------------------------------\n\n", "");
				printf("\n%40sEnter your contact number. (01XXXXXXXX)\n%35s>>", "", "");
				rewind(stdin);
				scanf("%s%c", phoneNum, &checkValid);
				x = 0;
			}
		}
		if (strlen(phoneNum) < 10)
		{
			printf("%40s The phone number must not less than 10 digits!\n", "");
		}
		printf("%40sAre you confrom your change ?\n", "");
		printf("%40s1.Yes. (Back to Modify Function)\n", "");
		printf("%40s2.No\n\n%40s->>", "", "");
		input = numSelect(1, 1, 2);
		switch (input)
		{
		case 1:
			modifyUser(user, 1, user.phoneNum, phoneNum);
			modifyMenu();
			break;

		case 2:
			break;

		default:
			errorMessage();
			break;
		}
	} while (input == 2 || (1));
}

void changePasswordmenu(UserInfo user)
{
	char password[30];
	int input;
	do {
		printf("%40sUser Password Modify\n", "");
		printf("%40s--------------------\n", "");
		printf("%40sBefore Modify, Please enter your original password.\n%40s>>", "", "");
		hidepw(password);
		if (strcmp(user.password, password) == 0)
		{
			printf("%40sUser password Confirmation completed!\n", "");
			printf("%40s-------------------------------\n\n", "");
		}
		printf("%40sNow, Enter your new password.\n", "");
		printf("%40s->>", "");
		hidepw(password);
		printf("%40sAre you confrom your change ?\n", "");
		printf("%40s1.Yes. (Back to Modify Function)\n", "");
		printf("%40s2.No\n\n%40s->>", "", "");
		input = numSelect(1, 1, 2);
		switch (input)
		{
		case 1:
			modifyUser(user, 2, user.password, password);
			printf("%40sModify Complete.\n", "");
			break;

		case 2:


		default:
			errorMessage();
			break;
		}
	} while (input == 2);
}

void changeExitMenu()
{
	int input;
	do {
		printf("%40sAre yousure want to leave Modify Interface ?\n", "");
		printf("%40s--------------------------------------------\n", "");
		printf("%40s 1. Yes\n", "");
		printf("%40s 2. No\n%40s->>", "", "");
		input = numSelect(1, 1, 2);
		switch (input)
		{
		case 1:
			userMenu();
			break;

		case 2:

			break;

		default:
			error();
			errorMessage();
			break;
		}
	} while (input == 2);

}

void endyearFunction(UserInfo* user)
{
	int yearend;
	printf("%40sEnter your first year in Study >>", "");
	yearend = numSelect((todayDate("year") - 4), todayDate("year") - 4, todayDate("year"));
	printf("%40sEnter your Month (1-12) ->>", "");
	user->date.month = numSelect(1, 1, 12);
	switch (user->date.month)
	{
		if (yearend == todayDate("year"))
		{
			user->date.month = numSelect(1, 1, todayDate("month"));
		}
		else
		{
			user->date.month = numSelect(1, 1, 12);
		}
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		printf("%40s Enter your Day(1-31)>>", "");
		if (user->date.month == todayDate("month"))
		{
			user->date.day = numSelect(1, 1, todayDate("day"));
		}
		else
		{
			user->date.day = numSelect(1, 1, 31);
		}
		break;

	case 4: case 6: case 9: case 11:
		printf("%40s Enter your Day(1-30)>>", "");
		if (user->date.month == todayDate("month"))
		{
			user->date.day = numSelect(1, 1, todayDate("day"));
		}
		else
		{
			user->date.day = numSelect(1, 1, 30);
		}
		break;

	case 2:
		if (yearend % 4 == 0)
		{
			printf("%40sEnter your Day (1-29)>>", "");
			user->date.day = numSelect(1, 1, 29);
			if (user->date.month == todayDate("month"))
			{
				user->date.day = numSelect(1, 1, todayDate("day"));
			}
			else
			{
				user->date.day = numSelect(1, 1, 29);
			}
			break;
		}
		else
		{
			printf("%40sEnter your Day (1-28)>>", "");
			user->date.day = numSelect(1, 1, 28);
			if (user->date.month == todayDate("month"))
			{
				user->date.day = numSelect(1, 1, todayDate("day"));
			}
			else
			{
				user->date.day = numSelect(1, 1, 28);
			}
			break;
		}

	default:
		errorMessage();
		break;
	}

	user->date.year = yearend + 4;
	printf("\n%40sNow, This is your User Information.\n", "");
	printf("%35sPlease Take Attandance and Remember your User Information!", "");
	printf("\n%40s<!> Please Attandance ! <!>\n", "");
	printf("%40s-----------------------------\n", "");
	printf("%40s<!> Your user's account will end at %d/%d/%d <!>\n\n", "", user->date.day, user->date.month, user->date.year);
}

void verificationCode()
{
	char test[10];
	char check[10];

	printf("\n%35s>> [I'm not a Robot] <<\n", "");
	printf("%30sPlease answer the following questions to prove that you are not a robot\n", "");
	printf("\n%40s->>Please prove you're not a arobot", "");
	printf("\n%37s--------------------------------------------\n\n", "");
	printf("%40s  ->> ", "");
	srand(time(NULL));
	int i;
	for (i = 0; i < 9; i++)
	{
		test[i] = randGenAlph();
		printf("%c", test[i]);
	}
	test[9] = '\0';

	printf("\n%37s--------------------------------------------\n\n", "");
	printf("%35sType the above words:\n%45s>>", "", "");
	scanf("%s", check);
	if (strcmp(test, check) == 0)
	{
		printf("%40s----------------\n", "");
		printf("%40sEntry Correct !!\n", "");
		printf("%40s----------------\n", "");
		printf("\n%40sYou are not a robot !\n", "");
		printf("%40s---------------------\n\n", "");
	}
	else
	{
		printf("\n%40sInvalid answer !", "");
		printf("%s != %s", test, check);
		printf("\n%40s<!> Warning !! Please try enter again ! <!>\n", "");
		verificationCode();
	}
}

void passwordAnswerChoose(UserInfo *user)
{
	printf("%30s<!> You can change your answer setting after your registration <!>\n", "");
	printf("%27s------------------------------------------------------------------\n", "");
	printf("%35s<!> IF you have any problem, You can go to our counter to slove your question <!>\n", "");
	printf("%35s---------------------------------------------------------------------------------\n", "");
	printf("%40s Now, Start your question.\n", "");
	printf("%40s--------------------------\n\n", "");
	printf("%40sWhat is your The most memorable thing\n", "");
	printf("%40s--------------------------------------- \n", "");
	printf("%40s->>", "");
	rewind(stdin);
	scanf("%s", user->answerpassword);
	printf("%40sYou can make the modify in your User Interface after your registeration.\n", "");
}

int isInvalidPassword(char* password1, char*password2)
{
	if (strlen(password1) < 5 || strlen(password2) < 5)
	{
		printf("%40sError, Your password must more than 5 !\n", "");
		printf("%35s----------------------------------------\n", "");
		printf("%40sPlease try enter again for your register.\n", "");
		return 1;
	}
	if (strcmp(password1, password2) != 0)
	{
		error();
		printf("\n%35s<!> Your password is not Consistent <!>\n", "");
		printf("%35s----------------------------------------\n", "");
		printf("%40sPlease try enter again for your register.\n", "");
		return 1;
	}

	return 0;
}

int isInvalidID(UserInfo user, char* id)
{

	if (strlen(id) != 7)
	{
		printf("\n");
		error();
		printf("n%40sError, Your User ID must be 7 integer number !!\n\n", "");
		return 1;
	}
	for (unsigned int i = 0; i < strlen(id); i++)//ID cannot have alphabet
	{
		if (isalpha(id[i]) != 0)
		{
			printf("%40sInvalid, ID must not contain alpha !!\n %40sPlease try again.\n", "", "");
			return 1;
		}
	}
	if (strcmp(user.id, id) == 0)
	{
		printf("%40sYour ID is already been used.Please Try again.\n", "");
		return 1;
	}
	return 0;
}

int isInvalidPhoneNum(UserInfo user, char *phoneNum)
{
	if (strlen(phoneNum) < 10)//Phone Number must be more than 10
	{
		printf("%40sError !! Your Phone Number must more than 10 number value.\n", "");
		return 1;
	}
	for (unsigned int x = 0; x < strlen(phoneNum); x++)
	{
		if (isdigit(phoneNum[x]) == 0)
		{
			printf("%40sError, Phone number must not contain alphabet !!\n%40sPlease try again.\n", "", "");
			return 1;
		}
	}
	if (strlen(phoneNum) < 10)
	{
		printf("%40s The phone number must not less than 10 digits!\n", "");
		return 1;
	}
	if (strcmp(user.phoneNum, phoneNum) == 0)
	{
		printf("%40s The phoneNum is already be used.Please try again\n", "");
		return 1;
	}
	return 0;
}

int isInvalidName(char* username)
{
	if (strlen(username) > 39 || strlen(username) == 0)//name cannot more that 39
	{
		printf("\n");
		error();
		printf("\n%30sInvalid Message, User Name must not exceed 20 characters !!\n%30sPlease try again.\n", "", "");
		return 1;
	}
	for (unsigned int i = 0; i < strlen(username); i++)
	{
		if (isalpha(username[i]) == 0)//name cannot have digits and NULL
		{
			printf("\n");
			error();
			printf("\n%30sError, User Name must not contain digits !!\n%40sPlease try again.\n\n", "", "");
			return 1;
		}
	}

	return 0;
}

int isInvalidIC(UserInfo user, char * ic)
{
	if (strlen(ic) != 12)//IC must be 12 digit
	{
		printf("\n");
		error();
		printf("%40sError Message !! Your IC must in 12 number value.\n", "");
		return 1;
	}
	for (unsigned int j = 0; j < strlen(ic); j++)
	{
		if (isdigit(ic[j]) == 0)
		{
			printf("\n");
			error();
			printf("%40sError Message, IC must not contain alphabet !!\n%40sPlease try again.\n", "", "");//IC cannot have alphabet
			return 1;
		}
	}

	if (strcmp(user.IC, ic) == 0)
	{
		printf("%40sYour IC is already been used.Please Try again.\n", "");//IC cannot be repeat
		return 1;
	}
	return 0;
}

char* getUserName()
{
	printf("%26sPlease register with your real name to avoid inconvenience to you in the future\n", "");
	static char username[40];
	do {
		printf("\n%50sEnter your  Name\n", "");
		printf("%50s------------------\n", "");
		printf("%50s>>", "");
		rewind(stdin);
		scanf("%[^\n]", username);
	} while (isInvalidName(username));

	return username;
}

char* getUserID(UserInfo user)
{
	static char id[8];

	do
	{
		printf("\n%40sPlease enter your user ID (1906246)\n", "");
		printf("%40s-----------------------------------\n%35s>>", "", "");
		rewind(stdin);
		scanf("%s", id);// ID have limitation in 7 digit and cannot be repit
		user = SearchById(id);//function that search from binary file 
	} while (isInvalidID(user, id));

	printf("%26sPlease remember your ID because you will use it when doing your login function.\n", "");
	printf("%26s-------------------------------------------------------------------------------\n", "");
	return id;
}


char* getUserIC(UserInfo user)
{
	static char ic[13];

	do
	{
		printf("\n%40sEnter your IC (011234072345)\n", "");
		printf("%40s----------------------------\n%35s>>", "", "");
		rewind(stdin);
		scanf("%s", ic);
		user = SearchByIc(ic);
	} while (isInvalidIC(user, ic));
	return ic;
}

char* getUserGender()
{
	static char gender[2];
	printf("\n%40sEnter your gender.(M = Male/F = Female)\n%35s>>", "", "");
	rewind(stdin);
	scanf("%s", gender);
	while (strcmp(gender, "M") && strcmp(gender, "m") && strcmp(gender, "F") && strcmp(gender, "f") != 0)//Gender must only can be enter M,F only.
	{
		printf("\n%35sYour reply is invalid.\n%35sPlease try to key in again.\n", "", "");
		printf("\n%40sEnter your gender.(M = Male/F = Female)\n%35s>>", "", "");
		rewind(stdin);
		scanf("%s", gender);
	}
	return gender;

}

char*getUserphoneNum(UserInfo user)
{
	static char phoneNum[16];
	do
	{
		printf("\n%40sEnter your contact number. (01XXXXXXXX)\n%35s>>", "", "");
		rewind(stdin);
		scanf("%s", phoneNum);
		user = SearchByPhoneNum(phoneNum);
	} while (isInvalidPhoneNum(user, phoneNum));
	return phoneNum;
}

char*getUserPassword()
{
	static char password1[15];
	char password2[15];
	do {
		printf("\n%40sSelect your password.\n%35s>>", "", "");/*password can't no be have space and must have number*/
		hidepw(password1);
		printf("\n%40sEnter your password again\n%35s>>", "", "");
		hidepw(password2);
	} while (isInvalidPassword(password1, password2));
	printf("%25sPlease remember your password because you will use it when doing your log in function.\n", "");
	printf("%25s--------------------------------------------------------------------------------------\n", "");
	return password1;
}

void studentLogin(char* userType, char* userID, char* password)
{
	UserInfo user;
	char id[10];
	int valid;
	do {
		FILE*fptr = fopen("userInfo.bin", "rb");
		printf("\n%40sWelcome to Login In System.\n", "");
		printf("%40s---------------------------\n", "");
		printf("%42sUse your User Account\n", "");
		printf("%42s---------------------\n\n", "");
		printf("%40sEnter your userID (1906246)\n", "");
		printf("%40s---------------------------\n", "");
		printf("%40s>>", "");
		rewind(stdin);
		scanf("%s", id);


		user = SearchById(id);

		if (strcmp(user.id, id) == 0)
		{
			printf("%40sUser ID Confirmation completed!\n", "");
			printf("%40s-------------------------------\n\n", "");

			valid = checkPassword(user, password);//User password checking
			if (valid == 1)
			{
				*userType = 'T';
				strcpy(userID, id);
				return;
			}
		}
		else
		{
			wrongId();//wrong id function
		}

	} while (strcmp(user.id, id) == 0);
}


void errorID()
{
	int input, input1;
	printf("%30s---------------------------------------\n", "");
	printf("%30s|  1.  |Yes, I didn't have my account.|\n", "");
	printf("%30s|  2.  |No, let me try again.         |\n", "");
	printf("%30s---------------------------------------\n", "");
	printf("\n%30sIf you have any problem,you can press 5 to have a Beginner's Manual.\n", "");
	printf("%30sPlease make sure your choosing.\n", "");
	printf("%30s-------------------------------\n", "");
	printf("%30s>>", "");
	input = numSelect(1, 1, 5);
	switch (input)
	{
	case 1:
		printf("%30sDo you want to sign in with a new user account now ?\n\n", "");
		printf("%30s1. Yes.\n", "");
		printf("%30s2. No. [Back to the Main Menu]\n\n->", "");
		input1 = numSelect(1, 1, 4);
		switch (input1)
		{
		case 1:
			registerUser();
			break;

		case 2:
			main_menu();
			break;

		default:
			errorMessage();
			break;
		}

	case 2:
		passwordAnswer();
		break;

	case 3:
		printf("%46s>> Please pay more attention when you enter your Account Information <<\n", "");
		printf("%46s-----------------------------------------------------------------------\n\n", "");
		return;

	case 4:
		mamual();
		break;

	default:
		errorMessage();
		break;
	}
}

void logout()
{
	int input1, input2;

	printf("%40sAre you want to Exit ?\n", "");
	printf("%40s-------------------------\n", "");
	printf("%40s 1. Yes\n", "");
	printf("%40s 2. No\n\n%40s->>", "", "");
	input1 = numSelect(1, 1, 2);
	switch (input1)
	{
	case 1:
		printf("%40sAre you sure ?\n", "");
		printf("%40s--------------\n", "");
		printf("%40s 1. Yes\n", "");
		printf("%40s 2. No\n\n%40s->>", "", "");
		input2 = numSelect(1, 1, 2);
		switch (input2)
		{
		case 1:
			return;

		case 2:
			userMenu();
			break;

		default:
			errorMessage();
			break;
		}
	case 2:
		userMenu();
		break;

	default:
		errorMessage();
		break;
	}
}

void passwordAnswer()
{
	UserInfo user;
	char answerpassword[50];
	printf("%40sNow, Let start to help you to find your password.\n", "");
	printf("%40s-------------------------------------------------\n", "");
	printf("%40sQuestion ->>\n", "");
	printf("%40s------------\n", "");
	printf("%40sWhat is your The most memorable thing\n", "");
	printf("%40s--------------------------------------- \n\n", "");
	printf("%40sNow, Please enter your answer\n", "");
	printf("%40s-----------------------------\n", "");
	printf("%40s->>", "");
	rewind(stdin);
	scanf("%[^\n]", answerpassword);
	user = SearchByPasswordAnswer(answerpassword);
	if (strcmp(user.answerpassword, answerpassword) == 0)
	{
		printf("%40sAnswer Correct !!\n", "");
		printf("%40s-----------------\n", "");
		printf("%40sYour password is %s", "", user.password);
		printf("%30sPlease don't forget again.Maybe you can make a modify in your User Interface.\n", "");
		printf("%40sTo make it more easily to memorise.\n\n", "");
		printf("%40sNow, System back to Main Menu.\n", "");
		main_menu();
	}
	else
	{
		printf("%40sAnswer Incorrect !!\n", "");
		printf("%40s-------------------\n", "");
		printf("%40sPlease try again !!\n\n", "");
		passwordAnswer();
	}
}

void wrongPassword()
{
	int input;
	error();
	printf("%40sYour password is incorrect.\n", "");
	printf("%44sPlease try again.\n", "");
	printf("%44s-----------------\n", "");
	printf("%40sAre you forget your password ?\n", "");
	printf("%40s------------------------------\n", "");
	printf("%40s        1. Yes \n", "");
	printf("%40s        2. No (write the password again)\n", "");
	printf("%40s        3. No (Back to Main Menu)\n\n%45s>>", "", "");
	input = numSelect(1, 1, 3);
	switch (input)
	{
	case 1:
		passwordAnswer();
		break;

	case 2:
		break;

	case 3:
		printf("%35sIf you didn't have your user account, You can went to register function in Main Menu.\n", "");
		printf("%40sData Transfer.....\n\n", "");
		main_menu();
		break;

	default:
		errorMessage();
		break;
	}
}

void wrongId()
{
	int input;
	error();
	printf("%30sError ! Your User ID is invalid !\n", "");
	printf("%30sPlease try again to enter Your ID.\n\n", "");
	printf("%30s>>Are you forgrt ID or you didn't have your own user account ? <<\n", "");
	printf("%30s 1. Yes, I'm Forget my ID.\n", "");
	printf("%30s 2. No, I need to try again.\n", "");
	printf("%30s 3. I didn't have my own account.\n\n", "");
	printf("%40sYou can press 4 to see the Beginner's Manual.\n", "");
	printf("%40s---------------------------------------------\n", "");
	printf("%30s>>", "");
	input = numSelect(1, 1, 3);
	switch (input)
	{
	case 1:
		printf("%40sPlease check your ID in schoool intranet.\n", "");
		printf("%40sIF have any problem, You can go to our counter or email to us.\n\n", "");
		printf("%40sIf this will cause you any inconvenience, please forgive us.\n", "");
		printf("%40s------------------------------------------------------------\n\n", "");
		printf("%40sNow, System will bring you back to the Main Menu.\n", "");
		main_menu();
		break;

	case 2:
		return;

	case 3:
		printf("%30sYou can back to Main Menu to create your own account.\n", "");
		main_menu();
		break;

	case 4:
		mamual();
		break;

	default:
		errorMessage();

	}
}

int checkPassword(UserInfo user, char* userpassword)
{
	char password[30];
	do
	{
		printf("%40sEnter your password\n%40s>>", "", "");
		hidepw(password);

		user = SearchByPassword(password);

		if (strcmp(user.password, password) == 0)
		{
			printf("%40sLog in Successful !!\n", "");
			strcpy(userpassword, password);
			return 1;
		}
		else
		{
			wrongPassword();
		}
	} while (1);
}

void registerUser()//register function
{
	UserInfo user = { 0 };//struct
	char *name;
	char *id;
	char *ic;
	char *gender;
	char *phoneNum;
	char *password;

	titleRegister();//title register
	printf("%45s<!> Please Take Attandance !! <!>\n", "");
	printf("%45s---------------------------------\n", "");
	printf("%42sBefore that, let's declare one thing.\n", "");
	printf("%42s--------------------------------------\n\n", "");
	printf("%30sPlease follow the instructions of the system to register.\n", "");
	printf("%17sThis system will not be held responsible for any accidents or inconveniences caused to you.\n", "");
	printf("%17s-------------------------------------------------------------------------------------------\n\n", "");

	name = getUserName();

	id = getUserID(user);

	ic = getUserIC(user);

	gender = getUserGender();

	phoneNum = getUserphoneNum(user);

	password = getUserPassword();

	verificationCode();

	endyearFunction(&user);

	passwordAnswerChoose(&user);

	strcpy(user.gender, gender);
	strcpy(user.userName, name);
	strcpy(user.id, id);
	strcpy(user.IC, ic);
	strcpy(user.phoneNum, phoneNum);
	strcpy(user.password, password);

	displayUser(user);
	AddUser(user);
	system("pause");

	main_menu();
}



