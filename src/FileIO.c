#include "FileIO.h"


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
    LoadReservations(resData);

    int i = 0;
    int j = 0;
    while (roomData[i].terminator != -1)
    {
        strcpy(roomData[i].status, "Available");
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
                strcpy(roomData[j].status, "Reserved");
            }
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
        puts(RED"Error! ROOMS FILE NOT FOUND"RESET);
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

void DeleteReservationEntry(Reservation resData[], int i)
{
    while (resData[i].terminator != -1)
    {
        resData[i] = resData[i + 1];
        i++;
    }
    resData[i].terminator = 10;
    // Assign the terminator value to anything but -1, because there will be two consecutive -1
    Update(resData);
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

void LoadUsers(user usersData[])
{
    FILE* userFile = fopen("users.txt", "r");
    if (userFile == NULL)
    {
        printf(RED"Error! USERS FILE NOT FOUND"RESET);
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

int LoadReservations(Reservation reservData[])
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

        reservData[i].terminator = 1;
        x = fgetc(reservationFile);
        i++;
    }
    reservData[i].terminator = -1;

    fclose(reservationFile);
    RoomReservation(reservData);
    return 1;
}

void LoadRooms(Room roomsData[])
{
    FILE* roomsfile = fopen("rooms.txt", "r");

    if (roomsfile == NULL)
    {
        printf(RED"Error! Rooms file not found!\n"RESET);
        getche();
        return;
    }
    int i = 0;
    char x = 'a';

    while (x != EOF)
    {
        fscanf(roomsfile, "%d %s %s %d", &roomsData[i].number, roomsData[i].status, roomsData[i].category,
               &roomsData[i].price);

        roomsData[i].terminator = 10;
        
        x = fgetc(roomsfile);
        i++;
    }
    roomsData[i].terminator = -1;

    fclose(roomsfile);
}