#ifndef RABIE_H
#define RABIE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "Amle.h"

void LogIn();
void LoadUsers(user usersData[]);

/// @brief returns a unique random int, USE SRAND(TIME(0)) BEFORE USING THE FUNCTION
/// @param min minimum number in range
/// @param max maximum number in range
/// @param nonDuplicates array for all the values that must not be repeated
/// @param n number of the values mustn't be repeated (length of the array)
/// @return
int GenerateRand(int min, int max, int nonDuplicates[], int n);
int Save(int error);
void CancelReservation(int error);
void OverwriteRes(Reservation resData[]);
void DeleteReservationEntry(Reservation resData[100], int i);

#endif
