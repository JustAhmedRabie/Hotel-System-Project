#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MainMenu()
{
    char choice;
    int i = 0;

    do
    {
        system("cls");
        if (i)
            puts("ERROR, Invalid Input!\n");

        { // Main Menu Prompts
            printf("*******************************\n");
            printf("*      Heliopolise Hotel      *\n");
            printf("*******************************\n");
            printf("-the main menu : \n");
            printf("1. Reservation\n");
            printf("2. Check in \n");
            printf("3. Cancel reservation \n");
            printf("4. Check room availability \n");
            printf("5. View customer details\n");
            printf("6. Query\n");
            printf("7. Reservation report \n");
            printf("8. Exit \n");
            printf("Please enter your choice (1 - 8) : ");
        }
        choice = getch();
        if (choice >= '1' && choice <= '8')
            break;
        i++;
    } while (1);

    MenuChoiceProcess(choice);
    getch(); // TODO: remove later, it was just to prevent the console from termination
}

void MenuChoiceProcess(char choice)
{
    switch (choice)
    {
    case '1':
        system("cls");
        // Amle will call Reservation function
        RoomReservation();
        break;
    case '2':
        system("cls");
        puts("Checking in...");
        break;
    case '3':
        system("cls");
        puts("Canceling reservation...");
        break;
    case '4':
        system("cls");
        puts("Checking room availability...");
        break;
    case '5':
        system("cls");
        puts("Viewing customer details...");
        break;
    case '6':
        system("cls");
        puts("Querying...");
        break;
    case '7':
        system("cls");
        puts("Reporting your reservation...");
        break;
    case '8':
        system("cls");
        puts("Exiting...");
        exit(0);
        break;
    default:
        puts("Invalid choice!\n");
    }
}
/*void reservationLoad(reservation reservData[100]) {
    system("cls");
    FILE *reservationFile=fopen("reservation,txt","r");
    for (int i=0;i<100;i++){
        fscanf(reservationFile,"%d",&reservData[i].reservationId);
        fscanf(reservationFile,"%d",&reservData[i].roomNumber);
        fscanf(reservationFile,"%s",reservData[i].reservationStatus);
        fscanf(reservationFile,"%s",reservData[i].category);
        fscanf(reservationFile,"%s",reservData[i].customerName);
        fscanf(reservationFile,"%ld",&reservData[i].customerNational_Id);
        fscanf(reservationFile,"%d",&reservData[i].numOfNights);
        fscanf(reservationFile,"%d",&reservData[i].date.days);
        fscanf(reservationFile,"%d",&reservData[i].date.months);
        fscanf(reservationFile,"%d",&reservData[i].date.years);
        fscanf(reservationFile,"%s",reservData[i].customerEmail);
        fscanf(reservationFile,"%s",reservData[i].mobileNumber);
    }
}*/