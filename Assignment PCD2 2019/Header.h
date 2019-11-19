#pragma once

// Self-defined function.
void StaffInformation();
void Facility();
void UserInformation();
void Booking();
void FacilityUsage();

// For date usage.
typedef struct {
	int day, month, year;
} Date;

// For user infomation usage.
typedef struct {
	char name[32];
	char gender[3], IC[16];
	char phoneNum[13];
} UserInfo;

// For staff information usage.
typedef struct {
	char staffID[7];
	UserInfo info;
} StaffInfo;

// For student information usage.
typedef struct {
	char studentID[12];
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

// 放各种define在这里。