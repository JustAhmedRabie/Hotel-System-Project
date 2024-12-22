#include "Rabie.h"
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
        x = fgetc(roomsfile);
        i++;
    }
    roomsData[i].terminator = -1;

    fclose(roomsfile);
}

int is_vaild_name(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
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

int valid_room_nights(int numOfNights)
{
    if(numOfNights>0 && numOfNights<=30)
    {
        return 1;
        //valid
    }
    return 0;
    printf("Error!!,The number of nights is invalid./n please enter number bet.1 and 30.\n");
}


void display_reservations_for_date(Reservation reservations[])
{
    int found=0;

    // temporary reservation

   Reservation tempRervation;
   tempRervation.date.days=21;
   tempRervation.date.months=12;
   tempRervation.date.years=2024;


    
    //to check every reservation in array
    
    int i=0;
    // terminator =-1 indicat to end of array
while (reservations[i].terminator!=-1)

    {
        Reservation current=reservations[i];
        //c0mpare dates of reservations
        if(CmpRes(current,tempRervation)==0)
        {
            printf("Reservation ID:%s\n",current.reservationId);
            printf("Custumer Name:%s\n",current.customerName);
            printf("Reservation Data:%d%d%d\n\n",current.date.days,current.date.months,current.date.years);
            found=1;
        }
        i++; 
        //to check another reservation;
    
    }
    if(!found)
    { 
        printf("No reservation found for the date 21-12-2024\n");

    }
    

}