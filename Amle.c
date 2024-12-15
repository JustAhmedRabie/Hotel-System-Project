﻿
#include "Amle.h"
#include "Hany.h"
#include "Menna.h"
#include "Rabie.h"
#include "Akram.h"

void RoomReservation()
{
    system("cls");
    printf("Reservation..\n");
    Reservation customer[2];
    // form room.txt
    int seaViewAvilable = 0; // room.txt
    int lakeViewAvilable = 3;
    int gardenViewAvilable = 1;

    /*// load data from file and check validity of them.

    strcpy(customer[0].customerName, "amle");
    customer[0].customerNational_Id = 12757927;
    Date date1 = {15, 2, 2026};
    customer[0].date = date1;
    strcpy(customer[0].customerEmail, "amlegomaa@gmail.com");
    customer[0].mobileNumber = 0122147445 */

    int i;
    int available = 1;
    srand(time(NULL));
    for (i = 0; i < 2; i++) // till end of file
    {
        printf("Please enter number from 1 to 3\n");
        printf("1 for Sea view \n");
        printf("2 for Lake view \n");
        printf("3 for Garden view \n");
        char roomCategoryChoice = getch();
        do
        {
            switch (roomCategoryChoice)
            {
            case '1':
            {
                if (seaViewAvilable == 0)
                {
                    printf("Sorry this category not available now , Please enter other.\n");
                    roomCategoryChoice = getch();
                    available = 0;
                }
                else
                {
                    printf("Done.\n");
                    available = 1;
                    seaViewAvilable--;
                    customer[i].reservationId = rand();
                    customer[i].roomNumber = rand() % 1000 + 1; // random room exicit in room.txt
                }
                break;
            }
            case '2':
            {
                if (lakeViewAvilable == 0)
                {
                    printf("Sorry this category not available now , Please enter other.\n");
                    roomCategoryChoice = getch();

                    available = 0;
                }
                else
                {
                    printf("Done.\n");
                    available = 1;
                    lakeViewAvilable--;
                    customer[i].reservationId = rand();
                    customer[i].roomNumber = rand() % 1000 + 1;
                }
                break;
            }
            case '3':
            {
                if (gardenViewAvilable == 0)
                {
                    printf("Sorry this category not available now , Please enter other.\n");
                    roomCategoryChoice = getch();
                    available = 0;
                }
                else
                {
                    printf("Done.\n");
                    available = 1;
                    gardenViewAvilable--;
                    customer[i].reservationId = rand();
                    customer[i].roomNumber = rand() % 1000 + 1;
                }
                break;
            }
            default:
                printf("Please enter valid category.\n");
                roomCategoryChoice = getch();
                available = 0;
                break;
            }
        } while (!available);
        strcpy(customer[i].roomStatus, "unconfirmed");
        printf("This is customer %d reservation Id : %d\n", i + 1, customer[i].reservationId);
        printf("This is customer %d room number : %d\n", i + 1, customer[i].roomNumber);
        printf("This is the room status of customer %d : %s\n", i + 1, customer[i].roomStatus);

    }
}