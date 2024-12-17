#ifndef AMLE_H
#define AMLE_H
#include <time.h>
#include "Rabie.h"

typedef struct
{
    char username[20];
    char password[30];
}user;


typedef struct
{
    int days;
    int months;
    int years;
} Date;

typedef struct
{
    int roomNumber;
    char status[20];
    char category[20];
    int price;
}room;

typedef struct
{
    int reservationId;
    room room;
    char customerName[20];
    long customerNational_Id;
    int numOfNights;
    Date date;
    char customerEmail[20];
    char mobileNumber[12];
} reservation;

void RoomReservation();
char UserRoomChoice(int error);

#endif
