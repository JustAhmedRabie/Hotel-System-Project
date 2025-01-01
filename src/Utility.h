#ifndef UTILITY_H
#define UTILITY_H

#include "Includes.h"
#define SKIP_SEQ_PREFIX_1 0
#define SKIP_SEQ_PREFIX_2 224

int CmpRes(Reservation res1, Reservation res2);

void SortRes(Reservation resData[]);

void NameToUpper(char* str);

void NormAndCapital(char* str);

/// @brief returns a unique random int, USE SRAND(TIME(0)) BEFORE USING THE FUNCTION
/// @param min minimum number in range
/// @param max maximum number in range
/// @param nonDuplicates array for all the values that must not be repeated
/// @param n number of the values mustn't be repeated (length of the array)
/// @return
int GenerateRand(int min, int max, int nonDuplicates[], int n);

char *StrToLower(char *str);

void normalizeName(char* str);

int ExitChoice(char input[], int size);

#endif
