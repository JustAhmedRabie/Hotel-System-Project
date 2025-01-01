#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"

void LoadRooms(Room roomsData[])
{
    FILE* roomsfile = fopen("rooms.txt", "r");

    if (roomsfile == NULL)
    {
        printf(RED"Error! Rooms file not found!\n"RESET);
        getche();
        return;
    }
    int i = 0;
    char x = 'a';

    while (x != EOF)
    {
        fscanf(roomsfile, "%d %s %s %d", &roomsData[i].number, roomsData[i].status, roomsData[i].category,
               &roomsData[i].price);

        roomsData[i].terminator = 10;
        
        x = fgetc(roomsfile);
        i++;
    }
    roomsData[i].terminator = -1;

    fclose(roomsfile);
}

int is_vaild_name(const char* name)
{
    if (name[0] == '\0' || name[0] == '\n')
    {
        puts(RED "Invalid name!"RESET);
        return 0;
    }
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (strlen(name) < 4)
        {
            puts(RED "Invalid name!"RESET);

            return 0;
        }
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            printf(RED"Please enter letters only\n"RESET);
            return 0;
        }
    }
    return 1;
}

int is_vaild_mobil(const char* mobil)
{
    for (int i = 0; mobil[i] != '\0'; i++)
    {
        if (!isdigit(mobil[i]) && mobil[0] != '+')
        {
            printf(RED"Invalid phone number!\n"RESET);

            return 0;
        }
    }

    if (strlen(mobil) != 11)
    {
        if (mobil[0] == '+')
        {
            if (strlen(mobil+1) > 12 || strlen(mobil+1) < 11)
            {
                printf(RED"Invalid phone number!\n"RESET);
                return 0;
            }
            return 1;
        }
        printf(RED"Please enter 11 digits only\n"RESET);
        return 0;
    }
    return 1;
}

int is_valid_nationalid(const char* nationalid)
{
    if (strlen(nationalid) != 14)
    {
        puts(RED"ERROR! national ID must be 14 digits!\n"RESET);

        return 0;
    }
    for (int i = 0; i < 14; i++)
    {
        if (nationalid[i] < '0' || nationalid[i] > '9')

        {
            puts(RED"ID must contain only digits!\n"RESET);
            return 0;
        }
    }
    return 1;
}

int isValidEmail(const char* email)
{
    // check if the length of the email is less than 8

    if (strlen(email) < 8)
    {
        puts(RED"ERROR! Email length must be at least 8 characters!\n"RESET);
        return 0;
    }
    char* at = strchr(email, '@');
    char* dot = strchr(email, '.');
    char* special = NULL;

    int i = 0;
    while (email[i] != '\0')
    {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '@' && email[i] != '_')
        {
            puts(RED"ERROR! Email is Invalid!!\n"RESET);
            return 0;
        }
        i++;
    }

    // Check if there is exactly one '@' and it's not the first character
    if (at == NULL || at == email)
    {
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
        return 0;
    }

    // Check if there is a '.' after the '@'
    if (dot == NULL || (dot < at + 2) && (dot <= email+2) || dot == email + strlen(email) - 1)
    {
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
        return 0;
    }

    // Ensure there's no more than one '@'
    if (strchr(at + 1, '@') != NULL)
    {
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
        return 0;
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
    puts(RED"Error!,The number of nights is invalid.\n please enter number bet.1 and 30.\n"RESET);
    return 0;
}


void display_reservations_for_date()
{
    system("cls");
    puts(CYAN"Reservation report:"RESET);
    Reservation reservations[100];
    if (!reservationLoad(reservations))
    {
        puts(RED"You don't have any reservations!"RESET);

        getch();
        return;
    }
    int found = 0;

    // temporary reservation

    Reservation tempReservation;
    int valid = 0;
    //take checkin date


    if (GetDate(&tempReservation.date.days, &tempReservation.date.months, &tempReservation.date.years, 0) == -1)
        return;


    int i = 0;
    // terminator =-1 indicat to end of array
    int count = 0;
    while (reservations[i].terminator != -1)

    {
        Reservation current = reservations[i];
        //c0mpare dates of reservations
        if (CmpRes(current, tempReservation) == 0)
        {
            printf("Reservation %d:\n", count + 1);
            printf("Reservation ID:%ld\n", current.reservationId);
            printf("Room number:%d\n", current.room.number);
            printf("Room category:%s\n", current.room.category);
            printf("Reservation status:%s\n", current.reservationStatus);
            printf("Customer Name:%s\n", current.customerName);
            printf("National ID: %s \n", reservations[i].customerNational_Id);
            printf("Mobile Number: %s \n", reservations[i].mobileNumber);
            printf("Email :%-30s \n", reservations[i].customerEmail);
            printf("\n");
            found = 1;
            count++;
        }
        i++;
        //to check another reservation;
    }
    if (found)
    {
        if (count > 1)
        {
            printf(GREEN"Found %d reservations\n"RESET, count);
        }
        else if (count == 1)
        {
            printf(GREEN"Found %d reservation\n"RESET, count);
        }
    }
    else if (!found)
    {
        puts(RED"No reservation found for this date\n"RESET);
    }
    getch();
}
