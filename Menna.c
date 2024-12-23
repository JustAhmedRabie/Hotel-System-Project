﻿#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"
void LoadRooms(Room roomsData[])
{
    FILE *roomsfile = fopen("rooms.txt", "r");

    if (roomsfile == NULL)
    {
        printf("Error!");
        getche();
        return;
    }
    int i = 0;
    char x = 'a';

    while (x != EOF)
    {
        
        fscanf(roomsfile, "%d %s %s %d", &roomsData[i].number, roomsData[i].status, roomsData[i].category, &roomsData[i].price);
        if (strcmp(StrToLower(roomsData[i].category),"seaview") == 0) roomsData[i].price = 1600;
        if (strcmp(StrToLower(roomsData[i].category),"lakeview") == 0) roomsData[i].price = 1800;
        if (strcmp(StrToLower(roomsData[i].category),"gardenview") == 0) roomsData[i].price = 2000;
        x = fgetc(roomsfile);
        i++;
    }
    roomsData[i].terminator = -1;

    fclose(roomsfile);
}

int is_vaild_name(const char *name)
{
    if (name[0] == '\0' || name[0] == '\n')
    {
        puts("Invalid name!");
        return 0;
    }
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (strlen(name) < 4)
        {
            puts("Invalid name!");
            return 0;
        }
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            printf("Please enter letters only\n");
            return 0;
        }
    }
    return 1;
}

int is_vaild_mobil(const char *mobil)
{
    for (int i = 0; mobil[i] != '\0'; i++)
    {

        if (!isdigit(mobil[i]))
        {
            printf("Please enter digits only\n");
            return 0;
        }
    }
    if (strlen(mobil) != 11) return 0;
    return 1;
}

int is_vaild_Date(Date date)
{
    if (date.years != 2024 && date.years != 2025)
    {
        printf("ERROR, Date is invalid!!\n");
        return 0;
    }
    // check year of reservation

    if (date.months < 1 || date.months > 12)
    {
        printf("ERROR, Date is invalid!!\n");
        return 0;
    }
    // check month

    // check no of days dpend on which month
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date.years % 4 == 0)
    {
        days_in_month[1] = 29;
    }

    if (date.days < 1 || date.days > days_in_month[date.months - 1])
    {
        printf("ERROR, Date is invalid!!\n");
        return 0;
    }
    return 1;
}

int is_vaild_Email(const char *email)
{
    int at_found = 0, dot_found = 0;
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            at_found = 1;
        }
        if (email[i] == '.' && at_found)
        {
            dot_found = 1;
        }

    }
    return dot_found && at_found;
}

int is_valid_nationalid(const char *nationalid)
{
    if (strlen(nationalid) != 14)
    {
        printf("ERROR! national ID must be 14 digits!!\n");
        return 0;
    }
    for (int i = 0; i < 14; i++)
    {
        if (nationalid[i] < '0' || nationalid[i] > '9')

        {
            printf("ID must contain only digits!!\n");
            return 0;
        }
    }
    return 1;
}

int valid_room_nights(char* numOfNights)
{
    if (atoi(numOfNights) > 0 && atoi(numOfNights) <= 30)
    {
        return 1;
        // valid
    }
    printf("Error!!,The number of nights is invalid.\n please enter number bet.1 and 30.\n");
    return 0;
}


void display_reservations_for_date()
{
    Reservation reservations[100];
    if (!reservationLoad(reservations))
    {
        puts("You don't have any reservations!");
        getch();
        return;
    }
    int found=0;

    // temporary reservation

    Reservation tempReservation;
    int valid = 0;
    system("cls");
    //take checkin date
    do
    {
        puts("Please enter the Check In date.");
        scanf("%d %d %d", &tempReservation.date.days, &tempReservation.date.months, &tempReservation.date.years);
        valid = is_vaild_Date(tempReservation.date);
    }
    while (valid == 0);


    int i=0;
    // terminator =-1 indicat to end of array
    int count=0;
while (reservations[i].terminator!=-1)

    {
        Reservation current=reservations[i];
        //c0mpare dates of reservations
        if(CmpRes(current,tempReservation)==0)
        {
            printf("Reservation %d: ", count+1);
            printf("Reservation ID:%ld\n",current.reservationId);
            printf("Room number:%d\n",current.room.number);
            printf("Room category:%s\n",current.room.category);
            printf("Customer Name:%s\n",current.customerName);
            printf("National ID: %s \n",reservations[i].customerNational_Id);
            printf("Mobile Number: %s \n",reservations[i].mobileNumber);
            printf("Email :%-30s \n",reservations[i].customerEmail);
            printf("\n");
            found=1;
            count++;
        }
        i++; 
        //to check another reservation;
    
    }
  if (found)
  {
      printf("found %d reservations", count);
  }
  else if (!found)
      {
        printf("No reservation found for this date\n");
    }
    getch();
    

}