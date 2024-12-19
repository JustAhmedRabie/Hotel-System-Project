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
} date;

typedef struct
{
    int roomNumber;
    char status[20];
    char category[20];
    int price;
    int terminator;
}room;

typedef struct
{
    int reservationId;
    room room;
    char reservationStatus[20];
    char customerName[20];
    char customerNational_Id[15];
    int numOfNights;
    date date;
    char customerEmail[30];
    char mobileNumber[12];
    int terminator;
} reservation;

void RoomReservation();
char UserRoomChoice(int error);

#endif
