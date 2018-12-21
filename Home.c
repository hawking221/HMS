#include <stdio.h>
#include "functions.h"
#include <windows.h>
#include <stdlib.h>


#define CAP 110 //capacity

/*
	This hostel has 45 rooms. There are 25 biseaters, and 20 triseaters. The capacity is thus 110 students.
	There are 3 floors. Each floor has 15 rooms.
	Rooms 101 to 115 and 201 to 210 are biseaters.
	Rooms 211 to 215 and 301 to 315 are triseaters.

	The program runs best on the solution configuration "Release"

*/

/* Functions in this file */
int saveChanges();

/* Storage */
char alldepts[11][8] = { "IESE", "NICE", "SEECS", "SMME", "SNS", "SCME", "NBS", "S3H", "ASAB", "SADA", "IGIS" };

/* Fields of Data for Waiting List*/
char WLname[CAP][50];
char WLcms[CAP][8];
char WLcontact[CAP][13];
char WLdept[CAP][10];
int WLyear[CAP];

/* Fields of Data for Students currently residing */
char name[CAP][50];
char cms[CAP][8];
char contact[CAP][13];
int year[CAP];

int room[CAP];
int bed[45][3];

char dept[CAP][10];
int appliances[45];
int fines[CAP];

/* Misc */
int start = 0;


int main() {

	/* Design */
	system("color 3F");
	system("title Hostel Management System");

	/* Variables */
	int input = 0;
	FILE *myfile; //pointer variable for file address

	if (start == 0) {
	
	/* import names */
	myfile = fopen("names.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(name[i], 50, myfile); //reads line i+1 and stores into i-th position of the array
		name[i][strlen(name[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);

	/* import CMS ID */
	myfile = fopen("cms.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(cms[i], 8, myfile); //reads line i+1 and stores into i-th position of the array
		cms[i][strlen(cms[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);

	/* import contact */
	myfile = fopen("contact.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(contact[i], 13, myfile); //reads line i+1 and stores into i-th position of the array
		contact[i][strlen(contact[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);

	/* import departments */
	myfile = fopen("dept.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(dept[i], 10, myfile); //reads line i+1 and stores into i-th position of the array
		dept[i][strlen(dept[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);

	/* import appliances */
	myfile = fopen("appliances.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fscanf(myfile, "%d", &appliances[i]); //reads line i+1 and stores into i-th position of the array
	}
	fclose(myfile);

	/* import room numbers */
	myfile = fopen("room.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fscanf(myfile, "%d", &room[i]); //reads line i+1 and stores into i-th position of the array
	}
	fclose(myfile);

	/* import years */
	myfile = fopen("year.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fscanf(myfile, "%d", &year[i]); //reads line i+1 and stores into i-th position of the array
	}
	fclose(myfile);

	/* import bed states */
	myfile = fopen("bed.txt", "r");
	for (int i = 0; i < 45; i++) {
		for (int j = 0; j < 3; j++) {
			fscanf(myfile, "%d", &bed[i][j]); //reads line i+1 and stores into i-th position of the array
		}
	}
	fclose(myfile);

	/* import fines */
	myfile = fopen("fines.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fscanf(myfile, "%d", &fines[i]); //reads line i+1 and stores into i-th position of the array
	}
	fclose(myfile);
	
	/* import waiting list names */
	myfile = fopen("WLnames.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(WLname[i], 50, myfile); //reads line i+1 and stores into i-th position of the array
		WLname[i][strlen(WLname[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);
	
	/* import waiting list CMS ids*/
	myfile = fopen("WLcms.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(WLcms[i], 50, myfile); //reads line i+1 and stores into i-th position of the array
		WLcms[i][strlen(WLcms[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);

	/* import waiting list contacts */
	myfile = fopen("WLcontact.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(WLcontact[i], 50, myfile); //reads line i+1 and stores into i-th position of the array
		WLcontact[i][strlen(WLcontact[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);

	/* import waiting list departments */
	myfile = fopen("WLdept.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fgets(WLdept[i], 50, myfile); //reads line i+1 and stores into i-th position of the array
		WLdept[i][strlen(WLdept[i]) - 1] = '\0'; //removes unwanted new line marker at the end
	}
	fclose(myfile);

	/* import waiting list years */
	myfile = fopen("WLyear.txt", "r");
	for (int i = 0; i < CAP; i++) {
		fscanf(myfile, "%d", &WLyear[i]); //reads line i+1 and stores into i-th position of the array
	}
	fclose(myfile);

	/* Welcome */
	
		printf("\t\t\t\t\t************************************* \n");
		printf("\t\t\t\t\t*                                   *\n");
		printf("\t\t\t\t\t*    ____________________________   *\n");
		printf("\t\t\t\t\t*                                   *\n");		
		printf("\t\t\t\t\t*    Welcome to Aurangzeb Hostels   *\n");
		printf("\t\t\t\t\t*    ____________________________   *\n");
		printf("\t\t\t\t\t*                                   *\n");
		printf("\t\t\t\t\t*                                   *\n");
		printf("\t\t\t\t\t************************************* \n\n");

		start = 1; //the above code will never be run again if main() is ever called after this
	}

	/* MAIN MENU */

MENU:		
	printf("\n\n\tMAIN MENU: \n");
	printf("\t => To List details of students in a particular room, press 1 \n");
	printf("\t => To Modify/Remove details of a student, press 2 \n");
	printf("\t => To Check waiting list, press 3 \n");
	printf("\t => To Check for vacancies, press 4 \n");
	printf("\t => To Display a report, press 5 \n");
	printf("\t => To View/Edit fines, press 6 \n");
	printf("\t => To Save changes, press 7 \n");
	printf("\t => To Exit program, press 8 \n");
	printf("\nEnter your command: "); scanf("%d", &input);
	
	switch (input) {
	case 1: 
		searchByRoom();
		break;
	case 2: 
		modifyDetails();
		break;
	case 3: 
		checkWaiting();
		break;
	case 4:
		checkVacancy();
		break;
	case 5:
		displayReport();
		break;
	case 6:
		checkFines();
		break;
	case 7:
		saveChanges();
		break;
	case 8:
		exit(0);
	}
	goto MENU;

	
	



	getch();
}

int saveChanges() {
	FILE *myfile;

	/* exporting names */
	myfile = fopen("names.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", name[i]);
	}
	fclose(myfile);

	/* exporting department */
	myfile = fopen("dept.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", dept[i]);
	}
	fclose(myfile);

	/* exporting CMS */
	myfile = fopen("cms.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", cms[i]);
	}
	fclose(myfile);

	/* exporting contacts */
	myfile = fopen("contact.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", contact[i]);
	}
	fclose(myfile);

	/* exporting room numbers */
	myfile = fopen("room.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%d\n", room[i]);
	}
	fclose(myfile);

	/* exporting years */
	myfile = fopen("year.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%d\n", year[i]);
	}
	fclose(myfile);

	/* exporting beds */
	myfile = fopen("bed.txt", "w");
	for (int i = 0; i < 45; i++) {
		for (int j = 0; j < 3; j++) {
			fprintf(myfile, "%d\n", bed[i][j]);
		}
	}
	fclose(myfile);

	/* exporting fines */
	myfile = fopen("fines.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%d\n", fines[i]);
	}
	fclose(myfile);

	/* exporting Waiting list names */
	myfile = fopen("WLnames.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", WLname[i]);
	}
	fclose(myfile);

	/* exporting Waiting list CMS */
	myfile = fopen("WLcms.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", WLcms[i]);
	}
	fclose(myfile);

	/* exporting Waiting list department */
	myfile = fopen("WLdept.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", WLdept[i]);
	}
	fclose(myfile);

	/* exporting Waiting list contacts */
	myfile = fopen("WLcontact.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%s\n", WLcontact[i]);
	}
	fclose(myfile);

	/* exporting Waiting list year */
	myfile = fopen("WLyear.txt", "w");
	for (int i = 0; i < CAP; i++) {
		fprintf(myfile, "%d\n", WLyear[i]);
	}
	fclose(myfile);

	printf("\n\nYour changes have been saved!\n");

	return 0;
}

