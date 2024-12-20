#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Rabie.h"
#include "Menna.h"

void LogIn()
{
    char password[30];
    char username[20];
    user users[3];

    LoadUsers(users);

    int i = 0;
    int isValid = 0;
    char choice;
    do
    {
        system("cls");
        if (i)
            puts("ERROR, Invalid Input!\n");

        printf("1. Log In\n");
        printf("2. Exit \n");

        choice = getch();

        if (choice == '1')
            break;
        else if (choice == '2')
            exit(0);

        i++;
    } while (1);

    i = 0;

    do
    {
        system("cls");
        if (i)
            puts("ERROR, Invalid Input!\n");
        puts("Please enter your username:");
        gets(username);
        puts("Please enter your password:");
        i = 0;

        do
        {
            char ch = getch();
            if (ch == 13) // ASCII enter code
            {
                password[i] = '\0';
                break;
            }

            // If Backspace is pressed, remove last character
            if (ch == 8) // ASCII value for Backspace key
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b"); // Erase previous character and move cursor back
                }
            }
            else
            {
                password[i] = ch;
                printf("*");
                i++;
            }
        } while (1);

        for (i = 0; i < 3; i++)
        {
            if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password))
            {
                isValid = 1;
                break;
            }
        }
        i++; // Just to know if it's not the first time the user enters his information
    } while (!isValid);
    i--;

    MainMenu();
}

int GenerateRand(int min, int max, int nonDuplicates[], int n)
{
    if (n >= max - min + 1)
    {
        printf("Error: All possible numbers have been generated!\n");
        return -1; // Return an error if all unique numbers have been generated
    }
    int newNumber;
    int isUnique;

    do
    {
        newNumber = (rand() % (max - min + 1)) + min;
        isUnique = 1;

        // Check if the number has already been generated
        for (int i = 0; i < n; i++)
        {
            if (nonDuplicates[i] == newNumber)
            {
                isUnique = 0;
                break;
            }
        }
    } while (!isUnique);

    return newNumber;
}

void LoadUsers(user usersData[])
{
    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL)
    {
        printf("Error!");
        getche();
        return;
    }

    char x = 'a';
    int i = 0;

    while (x != EOF)
    {

        fscanf(userFile, "%s %s", usersData[i].username, usersData[i].password);
        x = fgetc(userFile);
        i++;
    }
    usersData[i].terminator = -1;

    fclose(userFile);
}

int Save(int error)
{
    if (error)
    {
        system("cls");
        puts("ERROR, please enter a valid input!");
    }

    puts("Do you want to save the changes you did?");
    puts("type: Y/N");
    puts("type: E to exit, M to navigate to main menu");

    char x = getch();
    if (tolower(x) == 'y')
    {
        puts("Your changes was saved successfully!, press any key to continue...");
        getch();
        system("cls");
        return 1;
    }
    else if (tolower(x) == 'n')
    {
        puts("Your changes wasn't saved, press any key to continue...");
        getch();
        system("cls");
        return 0;
    }
    else if (tolower(x) == 'm') MainMenu();
    else if (tolower(x) == 'e') exit(0); 
    else
        x = Save(1);

    return x;
}

void DeleteReservationEntry(Reservation resData[100], int i)
{
    while (resData[i].terminator != -1)
    {
        resData[i] = resData[i + 1];
        i++;
    }
    resData[i].terminator = 10; // Assign the terminator value to anything but -1, because there will be two consecutive -1

    int confirmation = Save(0);
    if (confirmation)
    {
        OverwriteRes(resData);
    }
}

void CancelReservation(int error)
{

    Reservation resData[100];
    reservationLoad(resData);

    system("cls");
    if (error)
    {
        puts("ERROR, please enter a valid input!");
    }
    puts("Please enter the reservation ID or the Room number you want to cancel:");
    puts("enter 0 to get to main menu, -1 to exit");
    int input;
    int i = 0;
    scanf("%d", &input);
    if (input == 0) MainMenu();
    else if (input == -1) exit(0); 

    while (resData[i].terminator != -1)
    {
        if (input == resData[i].reservationId || input == resData[i].room.number)
        {
            break;
        }

        i++;
    }
    if (resData[i].terminator == -1)
    {
        CancelReservation(1);
    }
    puts(StrToLower(resData[i].reservationStatus));
    if (strcmp("unconfirmed",StrToLower(resData[i].reservationStatus)))
    {
        puts("Error! Either the reservation is checked in or checked out!");
        getch();
        CancelReservation(0);
    }
    DeleteReservationEntry(resData, i);
}

void OverwriteRes(Reservation resData[])
{
    FILE *reservationFile = fopen("reservations.txt", "w");

    if (reservationFile == NULL)
    {
        puts("Error");
        getch();
        return;
    }

    int i = 0;
    while (resData[i].terminator != -1)
    {
        fprintf(reservationFile,
                "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s", // The format for the reservations text file
                resData[i].reservationId,
                resData[i].room.number,
                resData[i].reservationStatus,
                resData[i].customerName,
                resData[i].customerNational_Id,
                resData[i].numOfNights,
                resData[i].date.days,
                resData[i].date.months,
                resData[i].date.years,
                resData[i].customerEmail,
                resData[i].mobileNumber);

        if (resData[i + 1].terminator == -1)
        {
            break;
        }

        fprintf(reservationFile, "%c", '\n');
        i++;
    }
    fclose(reservationFile);
}