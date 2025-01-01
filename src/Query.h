#ifndef QUERY_H
#define QUERY_H

#include "Includes.h"

int QueryCustomerbyName(Reservation* reserved, char* name, int* indices);

void QueryCustomer();

int QueryStatusbyGet(Room* roomsData, char* Option, int* indices);

void QueryRoomStatus_A();

void QueryRoomStatus_R();

int QueryRoom_Status_ChoiceProcess(char choice);

void QueryRoomStatus();

int QueryRoomNumber_guest_get(Reservation* res, int roomnum, int* indices);

int QueryRoomNumber_get(Room* roomsData, int inputNumber);

void QueryRoomNumber();

int QueryRoom_ChoiceProcess(char choice);

void QueryRoom();

int QueryChoiceProcess(char choice);

void Query();

int V_Details_Res_ID_get(Reservation* reservationId, int Res_ID);

void V_Details_Res_ID();

int V_DetailsChoiceProcess(char choice);

void ViewCustomerDetails();

void TrackRoom();

#endif 
