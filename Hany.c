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
        MakeReservation();
        break;
    case '2':
        system("cls");
        CheckIn();
        break;
    case '3':
        system("cls");
        CancelReservation(0);
        break;
    case '4':
        system("cls");
        TrackRoom();
        break;
    case '5':
        system("cls");
        ViewCustomerDetails();
        break;
    case '6':
        system("cls");
        Query();
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

    MainMenu();
}
void reservationLoad(Reservation reservData[100])
{
    FILE *reservationFile=fopen("reservations.txt","r");
    
    if (reservationFile==NULL)
    {
        puts("Error");  //please ... make it more meaningfull :)
        getch();
        return;
    }
    
    int i=0;
    char x = 'a';
    
    while (x!=EOF)
    {
        fscanf(reservationFile,
        "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", //The format for the reservations text file
        &reservData[i].reservationId,
        &reservData[i].room.number,
        reservData[i].reservationStatus,
        reservData[i].customerName,
        reservData[i].customerNational_Id,
        &reservData[i].numOfNights,
        &reservData[i].date.days,
        &reservData[i].date.months,
        &reservData[i].date.years,
        reservData[i].customerEmail,
        reservData[i].mobileNumber);
        

        x = fgetc(reservationFile);
        i++;
    }
    reservData[i].terminator = -1;

    fclose(reservationFile);
    RoomReservation(reservData);
}

char* StrToLower(char* str)
{
    char* p = malloc(strlen(str) + 1);
    char* result = p;
    while (*str)
    {
        *p = tolower(*str);
        p++;
        str++;
    }
    *p = '\0';
    return result;
}

void CheckIn()
{
    system("cls");
    Reservation reservData[100];
    reservationLoad(reservData);

    time_t date;

    struct tm* timeinfo;
    
    date = time(NULL);
    timeinfo = localtime(&date);

    Reservation tempReservation;
    tempReservation.date.days = timeinfo->tm_mday;
    tempReservation.date.months = timeinfo->tm_mon + 1;
    tempReservation.date.years = timeinfo->tm_year + 1900;
    
    long input;

    do
    {
        system("cls");
        int flag = 0;
        puts("Enter the reservation ID or room number");
        puts("Type 0 to go back to the main menu, -1 to exit");
        scanf("%ld",&input);
        if (input == 0)
        {
            MainMenu();
            return;
        }
        else if (input == -1) exit(0);
        
        int i=0;
        while (reservData[i].terminator != -1)
        {
            if (input == reservData[i].reservationId || input == reservData[i].room.number)
            {
                if (strcmp(StrToLower(reservData[i].reservationStatus), "confirmed") == 0)
                {
                    puts("This reservation is already checked in!");
                    getch();
                    break;
                }

                if (CmpRes(tempReservation, reservData[i]) == 1)
                {
                    puts("The reservation date is not due yet!");
                    getch();
                    break;
                }
                flag = 1;
                if (Save(0))
                {
                    system("cls");
                    strcpy(reservData[i].reservationStatus, "Confirmed");
                    OverwriteRes(reservData);
                    puts ("reservation confirmed!");
                    puts ("That's your information:");
                    printf("Name: %s\n", reservData[i].customerName);
                    printf("NationalId: %s\n", reservData[i].customerNational_Id);
                    printf("Email: %s\n", reservData[i].customerEmail);
                    printf("mobileNumber: %s\n", reservData[i].mobileNumber);
                    printf("numOfNights: %d\n", reservData[i].numOfNights);
                    printf("Date: %d-%d-%d\n", reservData[i].date.days, reservData[i].date.months, reservData[i].date.years);
                    printf("reservationStatus: %s\n", reservData[i].reservationStatus);
                    printf("ReservationID: %d\n", reservData[i].reservationId);
                    printf("Room: %d\n", reservData[i].room.number);
                    puts("press any key to continue");
                    getch();
                }
                break;
            }
            i++;
        }
        int isFound = !(reservData[i].terminator == -1);

        if (!flag) continue;
        if (!isFound) puts("The input is invalid!");
        else break;
    }
    while (1);
}