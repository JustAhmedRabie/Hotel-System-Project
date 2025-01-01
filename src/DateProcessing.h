#ifndef DATEPROCESSING_H
#define DATEPROCESSING_H

#include "Includes.h"

void CheckDayLimit(int* limit);

int Days();

void AdjustLimit(void);

int Months();

int Years();

int GetCode(void);

int GetDate(int* day, int* month, int* year, int limit);

#endif 
