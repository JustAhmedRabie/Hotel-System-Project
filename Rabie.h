#ifndef RABIE_H
#define RABIE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include<windows.h>
#include "Amle.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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
void OverwriteRoom(Room roomData[]);
void Update(Reservation resData[]);
int CmpRes(Reservation res1, Reservation res2);
void SortRes(Reservation resData[]);
void NameToUpper(char *str);
void NormAndCapital(char *str);
void TrackRoom();
void RoomReservation(Reservation resData[]);
void ReservationRoom(Room* roomData);
void EditReservation();
void StandBy(char* str);
int GetDate(int* day, int* month, int* year, int limit);
int GetCode(void);
int Years();
int Months();
int Days();
void CheckDayLimit(int* limit);
void AdjustLimit(void);
#endif
