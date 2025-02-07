﻿#ifndef STRUCTUERS_H
#define STRUCTUERS_H

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
    char customerName[30];
    char customerNational_Id[15];
    int numOfNights;
    Date date;
    char customerEmail[35];
    char mobileNumber[15];
    int terminator;
} Reservation;

#endif
