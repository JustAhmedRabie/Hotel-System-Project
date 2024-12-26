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
            puts(RED "ERROR, Invalid Input!\n" RESET);

        {
            // Main Menu Prompts
            printf(GREEN "*******************************\n" RESET);
            printf(GREEN "*      Heliopolise Hotel      *\n" RESET);
            printf(GREEN "*******************************\n" RESET);
            printf("\n");
            printf(CYAN " * Main menu * \n" RESET);
            printf("1. Reservation\n");
            printf("2. Check in \n");
            printf("3. Check out\n");
            printf("4. Cancel reservation \n");
            printf("5. Check room availability \n");
            printf("6. View customer details\n");
            printf("7. Query\n");
            printf("8. Reservation report \n");
            printf("9. Edit Reservation \n");
            printf("0. Exit\n");
            printf("Please enter your choice (0 - 9) : ");
        }
        choice = getch();
        if (choice >= '0' && choice <= '9')
            break;
        i++;
    } while (1);

    MenuChoiceProcess(choice);
}

void MenuChoiceProcess(char choice)
{
    switch (choice)
    {
    case '1':
        system("cls");
        puts(CYAN"Reservation:"RESET);
        MakeReservation(0);
        break;
    case '2':
        system("cls");
        CheckIn();
        break;
    case '3':
        system("cls");
        CheckOut();
        break;
    case '4':
        system("cls");
        CancelReservation(0);
        break;
    case '5':
        system("cls");
        TrackRoom();
        break;
    case '6':
        system("cls");
        ViewCustomerDetails();
        break;
    case '7':
        system("cls");
        Query();
        break;
    case '8':
        system("cls");
        display_reservations_for_date();
        break;
    case '9':
        system("cls");
        EditReservation();
        break;
    case '0':
        system("cls");
        puts("Exiting...");
        exit(0);
        break;
    default:
        puts("Invalid choice!\n");
    }

    MainMenu();
}

int reservationLoad(Reservation reservData[100])
{
    FILE *reservationFile = fopen("reservations.txt", "r");

    if (reservationFile == NULL)
    {
        FILE *createdFile = fopen("reservations.txt", "w");
        fclose(createdFile);
        reservData[0].terminator = -1;
        return 0;
    }
    char x = fgetc(reservationFile);

    int i = 0;
    if (x == EOF)
    {
        FILE *createdFile = fopen("reservations.txt", "w");
        fclose(createdFile);
        reservData[0].terminator = -1;
        return 0;
    }

    fseek(reservationFile, 0, SEEK_SET);
    x = 'a';

    while (x != EOF)
    {
        fscanf(reservationFile,
               "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", // The format for the reservations text file
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

        reservData[i].terminator = 10;
        x = fgetc(reservationFile);
        i++;
    }
    reservData[i].terminator = -1;

    fclose(reservationFile);
    RoomReservation(reservData);
    return 1;
}

char *StrToLower(char *str)
{
    char *p = malloc(strlen(str) + 1);
    char *result = p;
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
    if (!reservationLoad(reservData))
    {
        puts(RED "You don't have any reservations yet" RESET);
        getch();
        return;
    }

    time_t date;

    struct tm *timeinfo;

    date = time(NULL);
    timeinfo = localtime(&date);

    Reservation tempReservation;
    tempReservation.date.days = timeinfo->tm_mday;
    tempReservation.date.months = timeinfo->tm_mon + 1;
    tempReservation.date.years = timeinfo->tm_year + 1900;
    puts(CYAN "Check-in: " RESET);
    long input;

    do
    {
        int flag = 0;
        puts("Enter the reservation ID or room number");
        puts("Type -1 to go back to the main menu, -2 to exit");
        fflush(stdin);
        scanf("%ld", &input);
        fflush(stdin);
        system("cls");
        if (input == -1)
        {
            MainMenu();
            return;
        }
        else if (input == -2)
            exit(0);

        int i = 0;
        while (reservData[i].terminator != -1)
        {
            if (input == reservData[i].reservationId || input == reservData[i].room.number)
            {
                if (strcmp(StrToLower(reservData[i].reservationStatus), "confirmed") == 0)
                {
                    puts(RED "This reservation is already checked in!" RESET);
                    getch();
                    break;
                }

                if (CmpRes(tempReservation, reservData[i]) == 1)
                {
                    puts(RED "The reservation date is not due yet!" RESET);
                    getch();
                    break;
                }
                flag = 1;
                if (Save(0))
                {
                    system("cls");
                    strcpy(reservData[i].reservationStatus, "confirmed");
                    OverwriteRes(reservData);
                    puts(GREEN "reservation confirmed and checked in successfully!" RESET);
                    puts(YELLOW "That's your information:" RESET);
                    printf("Name: %s\n", reservData[i].customerName);
                    printf("NationalId: %s\n", reservData[i].customerNational_Id);
                    printf("Email: %s\n", reservData[i].customerEmail);
                    printf("mobileNumber: %s\n", reservData[i].mobileNumber);
                    printf("numOfNights: %d\n", reservData[i].numOfNights);
                    printf("Date: %d-%d-%d\n", reservData[i].date.days, reservData[i].date.months,
                           reservData[i].date.years);
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

        if (!isFound)
            puts(RED "The input is invalid!" RESET);
        if (!flag)
            continue;
        else
            break;
    } while (1);
}
