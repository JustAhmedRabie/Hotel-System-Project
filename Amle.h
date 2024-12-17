#ifndef AMLE_H
#define AMLE_H
#include <time.h>
#include "Rabie.h"

typedef struct
{
    int days;
    int months;
    int years;
} Date;

typedef enum
{
    SeaView,
    LakeView,
    GardenView,
}roomCategory;

typedef struct
{
    int reservationId;
    int roomNumber;
    char roomStatus[15];
    roomCategory roomCategory;
    char customerName[20];
    long customerNational_Id;
    int numOfNights;
    Date date;
    char customerEmail[20];
    char mobileNumber[12];
} Reservation;

void RoomReservation();
char UserRoomChoice(int error);

#endif
