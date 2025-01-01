#ifndef FILEIO_H
#define FILEIO_H

#include "Includes.h"

void RoomReservation(Reservation resData[]);

void OverwriteRes(Reservation resData[]);

void ReservationRoom(Room* roomData);

void OverwriteRoom(Room roomData[]);

void DeleteReservationEntry(Reservation resData[], int i);

void Update(Reservation resData[]);

void LoadUsers(user usersData[]);

int LoadReservations(Reservation reservData[]);

void LoadRooms(Room roomsData[]);

#endif 
