#ifndef AMLE_H
#define AMLE_H
#include  <time.h>
#include  "Rabie.h"

typedef struct
{
    int days;
    int months;
    int years;
} Date;

typedef struct
{
    int reservationId;
    int roomNumber;
    char roomStatus[15];
    int roomCategory;
    char customerName[20];
    long customerNational_Id;
    int numOfNights;
    Date date;
    char customerEmail[20];
    long mobileNumber;
} Reservation;

void RoomReservation();



#endif
