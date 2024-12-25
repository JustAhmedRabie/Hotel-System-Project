#ifndef AMLE_H
#define AMLE_H
#include <time.h>

typedef struct
{
    char username[20];
    char password[30];
    int terminator;
}user;


typedef struct
{
    int days;
    int months;
    int years;
} Date;

typedef struct
{
    int number;
    char status[20];
    char category[20];
    int price;
    int terminator;
}Room;

typedef struct
{
    int reservationId;
    Room room;
    char reservationStatus[20];
    char customerName[20];
    char customerNational_Id[15];
    int numOfNights;
    Date date;
    char customerEmail[30];
    char mobileNumber[12];
    int terminator;
} Reservation;

void MakeReservation(int reservID);
char UserRoomChoice();
void GetAvailableRoom(const char *category, Room *room);
void GenerateReservationID(Reservation ReservationInfo);
int GetNonDuplicatesId(int nonDuplicates[]);
void ChangeRoomStatus(int roomNumber,char *newStatus);
void WriteEditedDataRoom(Room NewRoomData[]);
void AddReservation(Reservation ReservationInfo);
void CheckOut();
void UserChoice(int choice);

#endif
