#ifndef RABIE_H
#define RABIE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "Amle.h"

typedef struct
{
    char username[20];
    char password[30];
}user;

typedef enum
{
    Available,
    Reserved
}roomStatus;

typedef struct
{
    int roomNumber;
    roomStatus status;
    roomCategory category;
    int price;
}room;

void LogIn();

/// @brief returns a unique random int, USE SRAND(TIME(0)) BEFORE USING THE FUNCTION
/// @param min minimum number in range
/// @param max maximum number in range
/// @param nonDuplicates array for all the values that must not be repeated
/// @param n number of the values mustn't be repeated (length of the array)
/// @return
int GenerateRand(int min, int max, int nonDuplicates[], int n);

#endif
