
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
    int seaViewAvailable = 0; // room.txt
    int lakeViewAvailable = 3;
    int gardenViewAvailable = 1;

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
        char roomCategoryChoice = UserRoomChoice(0); // you have to specify if there is an error or no in the argument, 1 for an error, 0 for no error
        do
        {
            switch (roomCategoryChoice)
            {
            case '1':
            {
                if (seaViewAvailable == 0)
                {
                    system("cls");
                    roomCategoryChoice = UserRoomChoice(1);
                    available = 0;
                }
                else
                {
                    system("cls");
                    printf("Done.\n");
                    available = 1;
                    seaViewAvailable--;
                    customer[i].reservationId = rand();
                    customer[i].roomNumber = rand() % 1000 + 1; // random room exicit in room.txt
                }
                break;
            }
            case '2':
            {
                if (lakeViewAvailable == 0)
                {
                    system("cls");
                    roomCategoryChoice = UserRoomChoice(1);

                    available = 0;
                }
                else
                {
                    system("cls");
                    printf("Done.\n");
                    available = 1;
                    lakeViewAvailable--;
                    customer[i].reservationId = rand();
                    customer[i].roomNumber = rand() % 1000 + 1;
                }
                break;
            }
            case '3':
            {
                if (gardenViewAvailable == 0)
                {
                    system("cls");
                    roomCategoryChoice = UserRoomChoice(1);
                    available = 0;
                }
                else
                {
                    system("cls");
                    printf("Done.\n");
                    available = 1;
                    gardenViewAvailable--;
                    customer[i].reservationId = rand();
                    customer[i].roomNumber = rand() % 1000 + 1;
                }
                break;
            }
            case '4':
                MainMenu();
                break;
            case '5':
                exit(0);
                break;
            default:
                system("cls");
                printf("Please enter valid category.\n");
                roomCategoryChoice = UserRoomChoice(0); // Already displayed a unique error message so I called the function with 0 argument
                available = 0;
                break;
            }
        } while (!available);
        system("cls");
        strcpy(customer[i].roomStatus, "unconfirmed");
        printf("This is customer %d reservation Id : %d\n", i + 1, customer[i].reservationId);
        printf("This is customer %d room number : %d\n", i + 1, customer[i].roomNumber);
        printf("This is the room status of customer %d : %s\n", i + 1, customer[i].roomStatus);
    }
}

char UserRoomChoice(int error)
{
    if (error)
        printf("Sorry this category is not available now , Please enter other.\n\n");

    printf("1. for Sea view \n");
    printf("2. for Lake view \n");
    printf("3. for Garden view \n");
    printf("4. back to main menu \n");
    printf("5. Exit \n");
    printf("Please enter number from 1 to 5\n");

    char roomCategoryChoice = getch();
    return roomCategoryChoice;
}