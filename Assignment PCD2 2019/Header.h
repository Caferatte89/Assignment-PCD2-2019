#pragma once

// Self-defined sub-main function for each member.
void StaffInformation();
void Facility();
void UserInformation();
void Booking();
void FacilityUsage();

// For date usage.
typedef struct {
	int day, month, year;
} Date;

/* To display current date.
	"day" - return day
	"month" - return month
	"year" - return year
	else (invalid input) - return 0 */
int todayDate(char toDisplay[]);

// For user infomation usage.
typedef struct {
	char name[32], id[17];
	int choose1, choose2, chooset;
	char password[17];
	char gender[3], IC[16];
	char phoneNum[13];
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

// For password XOR usage?
#define XOR1 0b01100010
#define XOR2 0x01E

/* To check time input is valid or not.
	return 1 - valid
	return 0 - not valid */
int checkTimeValid(int time);

/* To check time input is valid or not. 
It also able to check whether if leap year day input is valid or not.
	return 1 - valid
	return 0 - not valid */
int checkDateValid(int day, int month, int year);

// 放各种define在这里。