#ifndef RESERVATIONPROCESSMENUS_H
#define RESERVATIONPROCESSMENUS_H

#include "Includes.h"

void CancelReservation(int error);

void EditReservation();

char UserRoomChoice();

void GetAvailableRoom(const char* category, Room* room);

int GetNonDuplicatesId(int nonDuplicates[]);

void AddReservation(Reservation ReservationInfo);

void GenerateReservationID(Reservation ReservationInfo);

int MakeReservation(int reservID);

#endif
