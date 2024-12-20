
#include "Amle.h"
#include "Hany.h"
#include "Menna.h"
#include "Rabie.h"
#include "Akram.h"



int GetCategorie() {
    char UserInput = UserRoomChoice();
    switch (UserInput) {
        case '1':
            return GetAvailableRoom("SeaView");
        case '2':
            return GetAvailableRoom("LakeView");
        case '3':
            return GetAvailableRoom("GardenView");
        case '4':
            MainMenu();
            return 0;
        break;
        case '5':
            return 0;
            // call exit function
    }
}
int GetAvailableRoom(char *category) // return room number if valid else return 0
{
    room roomData[100];
    LoadRooms(roomData);
    int i = 0;
    GetCategorie();
    while (roomData[i].terminator != -1) {
        if (strcmp(category, roomData[i].category) == 0 && strcmp("Available", roomData[i].status) == 0)
        {
            printf("Done.");
            return roomData[i].roomNumber;
        }
        i++;
    }
    return 0;
}
int GetNonDuplicatesId(int nonDuplicates[])
{
    reservation Data[100];
    reservationLoad(Data);
    int i = 0;
    int index = 0;
    while (Data[i].terminator != -1)
    {
        nonDuplicates[i] = Data[i].reservationId;
        i++;
        index++;
    }
    return index;
}
void WriteEditedDataRoom(room NewRoomData[100])
{
    int i ;
    FILE *file = fopen("rooms.text", "w");
    if (file == NULL) {
        printf("Cant open the file.");
        return;
    }
    else {
        for (i = 0; i < 100; i++) {   //loop until fixed size
            fprintf(file, "%d %s %s %d\n", NewRoomData[i].roomNumber,NewRoomData[i].status,NewRoomData[i].category,NewRoomData[i].price);
        }
        NewRoomData[i].terminator = -1;
        fclose(file);
    }
}
void ChangeRoomStatus(int roomNumber,char *status) {
    room roomData[100];
    LoadRooms(roomData);
    int i = 0;
    while (roomData[i].terminator != -1) {
        if (roomData[i].roomNumber == roomNumber) {
            strcpy(roomData[i].status,status);
            break;
        }
        i++;
    }
    WriteEditedDataRoom(roomData);
}
void GetReservationID()
{
    reservation Data[100];
    reservationLoad(Data);
    system("cls");
    printf("Reservation..\n");
    int roomNum = GetCategorie();
    if (roomNum == 0) {
        printf("Sorry This category not Available now.");
        UserRoomChoice();
    }
    else
    {
        int nonDuplicates[100];
        int index = GetNonDuplicatesId(nonDuplicates);
        int resId = 100000 + GenerateRand(10000, 99000, nonDuplicates, index - 1);
        nonDuplicates[index] = resId;
        ChangeRoomStatus(roomNum,"Reserved");
        // call menna function to append data & take resId ,roomnum
    }
    system("cls");
}
char UserRoomChoice()
{
    char roomCategoryChoice;
    while (1) {
        printf("1. for Sea view \n");
        printf("2. for Lake view \n");
        printf("3. for Garden view \n");
        printf("4. back to main menu \n");
        printf("5. Exit \n");
        printf("Please enter number from 1 to 5\n");
        roomCategoryChoice = getch();
        if (roomCategoryChoice >= '1' && roomCategoryChoice <= '5')
            break;
        else
            printf("invalid input, Please choose number from 1 to 5\n");
    }
    return roomCategoryChoice;
}



