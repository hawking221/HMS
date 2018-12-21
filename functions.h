#pragma once
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define CAP 110

/* variables */
enum state { Vacant, Occupied };

extern char name[CAP][50];
extern char cms[CAP][8];
extern char contact[CAP][13];
extern int year[CAP];

extern int room[CAP];
extern int bed[45][3];
extern char dept[CAP][10];
extern int appliances[45];
extern int fines[CAP];

extern char alldepts[11][8];

extern char WLname[CAP][50];
extern char WLcms[CAP][8];
extern char WLcontact[CAP][13];
extern char WLdept[CAP][10];
extern int WLyear[CAP];


/* Custom Purpose Functions */
int RoomPos(int, char); //translate room number to array position in room[]
int searchByCMS(char a[]); //returns array position of given CMS ID
void error(char text[]); //displays a given error message in a specific font color and design

/* Main Menu Functions*/
int searchByRoom();
int modifyDetails();
int checkWaiting();
int checkVacancy();
int displayReport();
int checkFines();

/* Sub Menu Functions */
int changeRooms(int ID);



/* Definitions */


int searchByRoom() {
	

	int input = 0;

ASKROOM:
	printf("\n\ENTER ROOM NUMBER: "); scanf("%d", &input);

	if (!(input >= 101 && input <= 115) && !(input >= 201 && input <= 215) && !(input >= 301 && input <= 315)) {
		error("INVALID ROOM NUMBER");
		goto ASKROOM;
	}

	/* Prints details of all students in given room */
	printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
	for (int i = 0; i < CAP; i++) {
		if (room[i] == input) {
			printf("%s		%s		%s		%s		%d		%d\n", name[i], cms[i], contact[i], dept[i], room[i], year[i]);
		}
	}
	printf("\n\nNumber of Appliances in the room: %d \n", appliances[RoomPos(input, 'r')]);
	
	/* MENU 1 */
MENU: 
	printf("\n\tMENU: \n");
	printf("\t => To Check another room, press 1 \n");
	printf("\t => To Return to main menu, press 2 \n");

	printf("\nEnter your command: "); scanf("%d", &input);

	switch (input) {
	case 1:
		searchByRoom();
		break;
	case 2: 
		return 0;
		break;
	default:
		goto MENU;
	}

}

int modifyDetails() {
	char input[20] = { '0' };
	int input2 = 0;
	int student;

ASKCMS:
	printf("\nENTER CMS ID: "); scanf("%s", input);
	

	student = searchByCMS(input);

	if (student == 1000) {
		printf("\n");
		error("CMS ID NOT FOUND");
		printf("\n");
		goto ASKCMS;
	}

	printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
	printf("%s		%s		%s		%s		%d		%d\n", name[student], cms[student], contact[student], dept[student], room[student], year[student]);

MENU:
	printf("\n\tMENU: \n");
	printf("\t => To Modify contact number, press 1 \n");
	printf("\t => To Modify department, press 2 \n");
	printf("\t => To Change rooms, press 3 \n");
	printf("\t => To Remove this student, press 4 \n");
	printf("\t => To Return to main menu, press 5 \n");

	printf("\nEnter your command: "); scanf("%d", &input2);
	
	if (input2 == 1) {
		printf("ENTER NEW CONTACT NUMBER: ");  scanf("%s", input);
		strcpy(contact[student], input);
		printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
		printf("%s		%s		%s		%s		%d		%d\n", name[student], cms[student], contact[student], dept[student], room[student], year[student]);
		
	}
	else if (input2 == 2) {
		printf("ENTER NEW DEPARTMENT: "); scanf("%s", input);
		strcpy(dept[student], input);
		printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
		printf("%s		%s		%s		%s		%d		%d\n", name[student], cms[student], contact[student], dept[student], room[student], year[student]);
	}
	else if (input2 == 3) {
		changeRooms(student);
		return 0;
		
	}
	else if (input2 == 4) {

		strcpy(name[student], "-");
		strcpy(cms[student], "-");
		strcpy(contact[student], "-");
		strcpy(dept[student], "-");
		year[student] = 0;
		for (int y = 0; y < 3; y++) {
			if (bed[RoomPos(room[student], 'r')][y] == Occupied) {
				bed[RoomPos(room[student], 'r')][y] = Vacant;
				break;
			}
		}
		room[student] = 0;
		
		printf("\nStudent has been removed!\n\n");
	}
	else if (input2 == 5) {
		return 0;
	}
	else {
		goto MENU;
	}

MENU2:
	printf("\n\tMENU: \n");
	printf("\t => To Choose another student, press 1 \n");
	printf("\t => To Return to main menu, press 2 \n");

	printf("\nEnter your command: "); scanf("%d", &input2);

	switch (input2) {
	case 1:
		goto ASKCMS;
	case 2:
		return 0;
	}

}

int checkWaiting() {
	int input = 0;
	int vacancySuccess = 0;
	int vacantRoom;
	int vacantArrayPos;

	printf("\nName		        CMS ID		Contact			Department	    Year\n");
	for (int i = 0; i < CAP; i++) {
		if (WLyear[i] != 0) {
			printf("%s\t\t%s		%s		%s		      %d\n", WLname[i], WLcms[i], WLcontact[i], WLdept[i], WLyear[i]);
		}
	}
MENU:
	printf("\n\n\tMENU: \n");
	printf("\t => To Allot a room to the next person, press 1 \n");
	printf("\t => To Return to main menu, press 2 \n");
	printf("\nEnter your command: "); scanf("%d", &input);

	if (input == 1) {
		
		/* checking for first vacant room */
		for (int k = 0; k < 45; k++) {
			for (int l = 0; l < 3; l++) {
				if (bed[k][l] == Vacant) {
					vacantRoom = RoomPos(k, 'p');
					printf("The student has been moved to Room Number %d\n", vacantRoom);
					bed[k][l] = Occupied;
					vacancySuccess = 1;
					break;
				}
			}
			if (vacancySuccess == 1)
			break;
		}

		if (vacancySuccess == 0) {
			printf("\n");
			error("NO VACANCY IN HOSTEL");
			printf("\n");
			goto MENU;
		}
		vacancySuccess = 0; //reset for next usage
		
		
		/* check for next vacant array position */
		for (int i = 0; i < CAP; i++) {
			if (room[i] == 0) {
				vacantArrayPos = i;
				break;
			}
		}

		/* copy details from waiting list to hostel list */
		strcpy(name[vacantArrayPos], WLname[0]);
		strcpy(cms[vacantArrayPos], WLcms[0]);
		strcpy(contact[vacantArrayPos], WLcontact[0]);
		strcpy(dept[vacantArrayPos], WLdept[0]);
		room[vacantArrayPos] = vacantRoom;
		year[vacantArrayPos] = WLyear[0];

		/* removing top entry in waiting list as he has been alotted a room */
		for (int c = -1; c < CAP - 1; c++) {
			strcpy(WLname[c], WLname[c+1]);
			strcpy(WLcms[c], WLcms[c+1]);
			strcpy(WLcontact[c], WLcontact[c+1]);
			strcpy(WLdept[c], WLdept[c+1]);
			WLyear[c] = WLyear[c+1];
		}
		

		/* Done, now back to menu */
		goto MENU;
	}


	else if (input == 2) {
		return 0;
	}

	else {
		goto MENU;
	}


}

int checkVacancy() {
	int input = 0;
	char input2[10] = "00";

	printf("\n\nThe rooms that are vacant are: \n");
	for (int i = 0; i < 45; i++) {
		for (int j = 0; j < 3; j++) {
			if (bed[i][j] == Vacant) {
				printf("Room #%d, Bed #%d \n", RoomPos(i, 'p'), j+1);
			}
		}
	}

MENU:
	printf("\n\tMENU: \n");
	printf("\t => To Shift a student to a room, press 1 \n");
	printf("\t => To Return to main menu, press 2 \n");

	printf("\nEnter your command: "); scanf("%d", &input);

	switch (input) {
	case 1:
		printf("ENTER CMS ID: "); scanf(" %s", input2);
		if (searchByCMS(input2) == 1000) {
			error("CMS ID NOT FOUND");
			goto MENU;
		}
		printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
		printf("%s		%s		%s		%s		%d		%d\n", name[searchByCMS(input2)], cms[searchByCMS(input2)], contact[searchByCMS(input2)], dept[searchByCMS(input2)], room[searchByCMS(input2)], year[searchByCMS(input2)]);
		changeRooms(searchByCMS(input2));
		return 0; 
		break;
	case 2:
		return 0;
	default:
		goto MENU;
	}
}

int displayReport() {
	int input = 0;
	char input2[20] = "00";
	int c = 0; //count variable to count numbers
	int student;

	int rent;
MENU:
	printf("\n\tMENU: \n");
	printf("\t => To Output a list of all student data, press 1 \n");
	printf("\t => To Show a distribution report, press 2 \n");
	printf("\t => To Print fee invoice, press 3 \n");
	printf("\nEnter your command: "); scanf("%d", &input);

	if (input == 1) {
		printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
		for (int i = 0; i < CAP; i++) {
			if (room[i] != 0) {
				printf("%s\t\t%s		%s		%s		%d		%d\n", name[i], cms[i], contact[i], dept[i], room[i], year[i]);
			}
		}
	}
	else if (input == 2) {
		printf("\n\nBY:\n\n");
		printf("\t Batch: \n");
		printf("		Freshmen: ");
		for (int i = 0; i < CAP; i++) {
			if (year[i] == 1) c++;
		}
		printf("%d\n", c); 
		c = 0;
		printf("		Sophmores: ");
		for (int i = 0; i < CAP; i++) {
			if (year[i] == 2) c++;
		}
		printf("%d\n", c); 
		c = 0;
		printf("		Juniors: ");
		for (int i = 0; i < CAP; i++) {
			if (year[i] == 3) c++;
		}
		printf("%d\n", c); 
		c = 0;
		printf("		Seniors: ");
		for (int i = 0; i < CAP; i++) {
			if (year[i] == 4) c++;
		}
		printf("%d\n", c);
		c = 0;

		printf("\n\n\t Department: \n");
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < CAP; j++) {
				if (strcmp(alldepts[i], dept[j]) == 0) c++;
			}
			printf("		%s: %d \n", alldepts[i], c);
			c = 0;
			
		}
	

	}
	else if (input == 3) {
		/* The base rent is 40000 per year for biseaters and 30000 per year for triseaters
		There is an additional flat rate of 5000 for mess.
		Each appliance nets an extra 5000 per year */
	ASKCMS:
		printf("\nENTER CMS ID: "); scanf("%s", input2);

		student = searchByCMS(input2);

		if (student == 1000) {
			printf("\n");
			error("CMS ID NOT FOUND");
			printf("\n");
			goto ASKCMS;
		}



		/* Design structure for bill */
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD saved_attributes;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		saved_attributes = consoleInfo.wAttributes;

		SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		
		
		/* Actual Bill */

		
		
		printf("\t\t\t           FEE INVOICE                 \n");
		printf("\t\t\t|Name             %20s|\n", name[student]);
		printf("\t\t\t|CMS ID           %20s|\n", cms[student]);
		printf("\t\t\t|Department       %20s|\n", dept[student]);
		printf("\t\t\t|Room No.         %20d|\n", room[student]);
		printf("\t\t\t                DETAIL                 \n");
		/* calculating rent - start */
		if ((room[student] >= 101 && room[student] <= 115) || (room[student] >= 201 && room[student] <= 210)) {
			rent = 40000; //rent for a biseater
		}
		else {
			rent = 30000; //rent for a triseater
		}
		/* calculating rent - end */
		printf("\t\t\t|Rent                 Rs. %12d|\n", rent);
		printf("\t\t\t|Mess                 Rs. %12d|\n", 5000);
		printf("\t\t\t|Appliance Charges    Rs. %12d|\n", appliances[RoomPos(room[student], 'r')] * 5000);
		printf("\t\t\t|_____________________________________|\n");
		printf("\t\t\t|Total Bill           Rs. %12d|\n", rent + 5000 + appliances[RoomPos(room[student], 'r')] * 5000);


		SetConsoleTextAttribute(hConsole, saved_attributes);
	}
	else {
		goto MENU;
	}

MENU2:
	printf("\n\tMENU: \n");
	printf("\t => To Choose another report, press 1 \n");
	printf("\t => To Return to main menu, press 2 \n");
	printf("\nEnter your command: "); scanf("%d", &input);

	switch (input) {
	case 1:
		goto MENU;
	case 2:
		return 0;
	default:
		goto MENU2;
	}
}

int changeRooms(int ID) {

	int input = 0;
	char input2[10] = "00";
	int ID2; //ID of person to swap rooms with
	int temp; //temporary placeholder for swapping
	int changeSuccess = 0; //determine if room change is a success

MENU:
	printf("\n\tMENU: \n");
	printf("\t => To Move into a vacant spot, press 1\n");
	printf("\t => To Swap rooms, press 2\n");
	printf("\t => To Return to main menu, press 3\n");
	printf("\nEnter your command: "); scanf("%d", &input);

	if (input == 1) {
		printf("\nENTER THE ROOM NUMBER YOU WANT TO OCCUPY: "); scanf("%d", &input);
		
		changeSuccess = 0; //reset
		for (int i = 0; i < 3; i++) {
			if (bed[RoomPos(input, 'r')][i] == Vacant) {
				/* Room Changes */
				for (int i = 0; i < 3; i++) {
					if (bed[RoomPos(room[ID], 'r')][i] == Occupied) {
						bed[RoomPos(room[ID], 'r')][i] = Vacant;
						break;
					}
				}

				room[ID] = input;
				
				for (int i = 0; i < 3; i++) {
					if (bed[RoomPos(room[ID], 'r')][i] == Vacant) {
						bed[RoomPos(room[ID], 'r')][i] = Occupied;
						break;
					}
				}


				changeSuccess = 1; //return success
				
				printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
				printf("%s		%s		%s		%s		%d		%d\n", name[ID], cms[ID], contact[ID], dept[ID], room[ID], year[ID]);

				break;
			}
			
			
			

			
		}


		if (changeSuccess == 0) {
			/* Return Error because the room is not vacant */
			error("SORRY THE ROOM IS NOT VACANT OR IS INVALID");
			goto MENU;
		}
		

		
	}

	else if (input == 2) {
	SWAPMENU:
		printf("ENTER CMS ID OF STUDENT YOU WISH TO SWAP WITH: "); scanf("%s", input2);
		ID2 = searchByCMS(input2);

		if (ID2 == 1000) {
			printf("\n");
			error("CMS ID NOT FOUND");
			printf("\n");
			goto SWAPMENU;
		}

		/* Swap */
		temp = room[ID];
		room[ID] = room[ID2];
		room[ID2] = temp;

		printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
		printf("%s		%s		%s		%s		%d		%d\n", name[ID], cms[ID], contact[ID], dept[ID], room[ID], year[ID]);
		printf("%s		%s		%s		%s		%d		%d\n", name[ID2], cms[ID2], contact[ID2], dept[ID2], room[ID2], year[ID2]);
	}
	else if (input == 3) {
		return 0;
	}
	else {
		goto MENU;
	}
	
MENU2:
	printf("\n\tMENU: \n");
	printf("\t => To Change rooms again, press 1\n");
	printf("\t => To Return to main menu, press 2");
	printf("\nEnter your command: "); scanf("%d", &input);

	switch (input) {
	case 1:
		goto MENU;
	case 2:
		return 0;
	default:
		goto MENU2;
	}

}

int RoomPos(int x, char y) {

	/* p if the integer paramter is an array position to convert to a room number */
	/* r if the integer parameter is a room number */

	if (y == 'r') {
		if (x >= 101 && x <= 115) {
			return x - 101;
		}
		else if (x >= 201 && x <= 215) {
			return x - 186;
		}
		else if (x >= 301 && x <= 315) {
			return x - 271;
		}
	}

	if (y == 'p') {
		if (x >= 0 && x <= 14) {
			return x + 101;
		}
		else if (x >= 15 && x <= 29) {
			return x + 186;
		}
		else if (x >= 30 && x <= 44) {
			return x + 271;
		}
	}
}

int searchByCMS(char a[]) {
	int i;
	for (i = 0; i < CAP; i++) {
		if (strcmp(a, cms[i]) == 0) {
			return i;
		}
	}
	if (i >= CAP) {
		return 1000; //error
	}

}

void error(char text[]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	printf("\t\t\t\t\t\t%s", text);
	SetConsoleTextAttribute(hConsole, saved_attributes);

}

int checkFines() {
	int student;
	int input;
	char input2[10];
	int input3 = 0;

ASKCMS:
	printf("\nENTER CMS ID: "); scanf("%s", input2);


	student = searchByCMS(input2);

	if (student == 1000) {
		printf("\n");
		error("CMS ID NOT FOUND");
		printf("\n");
		goto ASKCMS;
	}

	printf("\nName		        CMS ID		Contact			Department	Room		Year\n");
	printf("%s		%s		%s		%s		%d		%d\n", name[student], cms[student], contact[student], dept[student], room[student], year[student]);
MENU:
	printf("\n\tMENU: \n");
	printf("\t => To View fines on this student, press 1\n");
	printf("\t => To Edit fines on this student, press 2\n");
	printf("\t => To Return to main menu, press 3\n");
	printf("\nEnter your command: "); scanf("%d", &input);

	switch (input) {
	case 1:
		printf("\n\nThere is a fine of Rs. %d on their account. \n", fines[student]);
		goto MENU;
		break;
	case 2:
		printf("ENTER NEW FINE: "); scanf("%d", &input3);
		fines[student] = input3;
		printf("\n\nThe fine has been updated. \n");
		break;
	case 3:
		return 0;
		break;
	default:
		goto MENU;
	}
}