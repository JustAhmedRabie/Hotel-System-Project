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
    }
    while (1);

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
        }
        while (1);

        for (i = 0; i < 3; i++)
        {
            if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password))
            {
                isValid = 1;
                break;
            }
        }
        i++; // Just to know if it's not the first time the user enters his information
    }
    while (!isValid);
    i--;

    MainMenu();
}

int GenerateRand(int min, int max, int nonDuplicates[], int n)
{
    if (n == 0) return (rand() % (max - min + 1) + min);
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
    }
    while (!isUnique);

    return newNumber;
}

void LoadUsers(user usersData[])
{
    FILE* userFile = fopen("users.txt", "r");
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

    printf("\n");
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

int DeleteReservationEntry(Reservation resData[100], int i)
{
    while (resData[i].terminator != -1)
    {
        resData[i] = resData[i + 1];
        i++;
    }
    resData[i].terminator = 10;
    // Assign the terminator value to anything but -1, because there will be two consecutive -1

    int confirmation = Save(0);
    if (confirmation)
    {
        Update(resData);
        return 1;
    }
    else return 0;
}

void Update(Reservation resData[])
{
    Room roomData[100];
    OverwriteRes(resData);
    LoadRooms(roomData);
    for (int i = 0; roomData[i].terminator != -1; i++)
    {
        roomData[i].number;
        roomData[i].status;
        roomData[i].category;
        roomData[i].price;
    }
    OverwriteRoom(roomData);
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
        return;
    }
    if (strcmp("unconfirmed", StrToLower(resData[i].reservationStatus)))
    {
        puts("Error! Either the reservation is checked in or checked out!");
        getch();
        CancelReservation(0);
        return;
    }
    DeleteReservationEntry(resData, i);
}

void OverwriteRes(Reservation resData[])
{
    FILE* reservationFile = fopen("reservations.txt", "w");

    if (reservationFile == NULL)
    {
        puts("Error");
        getch();
        return;
    }

    SortRes(resData);

    int i = 0;
    while (resData[i].terminator != -1)
    {
        NormAndCapital(resData[i].customerName);
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

void ReservationRoom(Room* roomData) //this function
{
    Reservation resData[100];
    reservationLoad(resData);

    int i = 0;
    int j = 0;
    while (roomData[i].terminator != -1)
    {
        strcpy(roomData[i].status, "available");
        i++;
    }

    i = 0;
    while (resData[i].terminator != -1)
    {
        j = 0;
        while (roomData[j].terminator != -1)
        {
            if (roomData[j].number == resData[i].room.number)
            {
                strcpy(roomData[j].status, "reserved");
            }
            if (strcmp(StrToLower(roomData[j].category), "seaview") == 0) roomData[j].price = 1600;
            if (strcmp(StrToLower(roomData[j].category), "lakeview") == 0) roomData[j].price = 1800;
            if (strcmp(StrToLower(roomData[j].category), "gardenview") == 0) roomData[j].price = 2000;
            j++;
        }
        i++;
    }
}

void OverwriteRoom(Room roomData[])
{
    FILE* roomFile = fopen("rooms.txt", "w");

    if (roomFile == NULL)
    {
        puts("Error");
        getch();
        return;
    }

    ReservationRoom(roomData);
    int i = 0;
    while (roomData[i].terminator != -1)
    {
        fprintf(roomFile,
                "%d %s %s %d", // The format for the room text file
                roomData[i].number,
                roomData[i].status,
                roomData[i].category,
                roomData[i].price);

        if (roomData[i + 1].terminator == -1)
        {
            break;
        }

        fprintf(roomFile, "%c", '\n');
        i++;
    }
    fclose(roomFile);
}

int CmpRes(Reservation res1, Reservation res2)
{
    if (res1.date.years > res2.date.years)
    {
        return -1;
    }
    else if (res1.date.years < res2.date.years)
    {
        return 1;
    }
    if (res1.date.months > res2.date.months) return -1;
    else if (res1.date.months < res2.date.months) return 1;
    if (res1.date.days > res2.date.days) return -1;
    else if (res1.date.days < res2.date.days) return 1;

    return 0;
}

void SortRes(Reservation resData[])
{
    int i = 0;

    while (resData[i + 1].terminator != -1)
    {
        int swap = 0;
        int j = 0;
        while (resData[j + 1].terminator != -1)
        {
            if (CmpRes(resData[j], resData[j + 1]) == 1)
            {
                Reservation resTemp = resData[j];
                resData[j] = resData[j + 1];
                resData[j + 1] = resTemp;
                swap = 1;
            }
            j++;
        }
        if (!swap) break;
        i++;
    }
}

void NameToUpper(char* str)
{
    int flag = 1;

    while (*str)
    {
        if (isspace(*str))
        {
            flag = 1;
        }
        else if (flag && isalpha(*str))
        {
            *str = toupper(*str);
            flag = 0;
        }
        else
        {
            *str = tolower(*str);
        }
        str++;
    }
}

void NormAndCapital(char* str)
{
    if (str == NULL) return;
    normalizeName(str);
    NameToUpper(str);
}

void TrackRoom()
{
    Room roomData[100];
    LoadRooms(roomData);

    int i = 0;
    printf("+==========+======================+==========+===================+\n");
    printf("| %-8s | %-20s | %-8s | %-17s |\n", "Room ID", "Category", "Price", "Status");
    printf("+==========+======================+==========+===================+\n");
    while (roomData[i].terminator != -1)
    {
        printf("| %-8d | %-20s | %-8d | %-17s |\n", roomData[i].number
               , roomData[i].category
               , roomData[i].price
               , roomData[i].status);
        printf("+==========+======================+==========+===================+\n");

        i++;
    }

    puts("Press any key to continue:");
    getch();
}

void RoomReservation(Reservation resData[])
{
    Room roomData[100];
    LoadRooms(roomData);
    int i = 0;
    int j = 0;
    while (resData[i].terminator != -1)
    {
        j = 0;
        while (roomData[j].terminator != -1)
        {
            if (roomData[j].number == resData[i].room.number)
            {
                resData[i].room.price = roomData[j].price;
                strcpy(resData[i].room.category, roomData[j].category);
            }
            j++;
        }
        i++;
    }
}
