#pragma once

// Self-defined sub-main function for each member.
int main(char loginacc[]);
void StaffInformationMod(char loginacc[]);
void FacilityMod(char staffOrNot);
void UserInformationMod();
void BookingMod(char userType, char userID[], char password[]);
void FacilityUsageMod(char type, char id[]);

void studentLogin(char* userType, char* userID, char* password);
char staffLogin(char* userType, char* userID, char* userpassword);

// For date usage.
typedef struct {
	int day, month, year;
} Date;

/* To display current date
	"day" - return day.
	"month" - return month
	"year" - return year
	else (invalid input) - return 0 */
int todayDate(char toDisplay[]);

// For user infomation usage.
/*typedef struct {
	char name[32], id[17];
	int choose1, choose2, chooset;
	char password[17];
	char gender[3], IC[16];
	char phoneNum[13];
} UserInfo;*/

typedef struct {
	char userName[50];
	char id[8];
	char choosequestion[50];
	char password[17];
	char gender[2];
	char IC[16];
	char phoneNum[13];
	char answerpassword[30];
	Date date;
	char userType;
} UserInfo;

// For staff information usage.
typedef struct {
	char staffID[7];
	char job[17];
	UserInfo info;
} StaffInfo;

// For student information usage.
typedef struct {
	char studentID[12], classroom[4];
	int yearstu, semstu;
	UserInfo info;
} StudentInfo;

/* For checking whether the file is exist/empty or not.
   return -1 - not exist
   return  0 - empty
   return  1 - exist */
int checkFile(char fileName[]);

/* To check time input is valid or not.
	return 1 - valid
	return 0 - not valid */
int checkTimeValid(int time);

/* To check time input is valid or not. 
It also able to check whether if leap year day input is valid or not.
	return 1 - valid
	return 0 - not valid */
int checkDateValid(int day, int month, int year);

/* To check whether the year is leap year or not.
	return 1 - leap year
	return 0 - common year */
int checkLeap(int year);

// To let user only choose selection by pressing up-and-down key.
char confirmSelect(char X, char Y);
int numSelect(int start, int min, int max);

// 放各种define在这里。