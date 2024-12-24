#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"
#include <stdio.h>
#include <stdlib.h>
/*void LoadRoams( room *rooms) {
    int i=0 ;
    FILE *rooms_file = fopen("Rooms.txt", "r"); //getting the Rooms.txt
    if (rooms_file == NULL) {
        printf("Error opening file...might be lost!!");
        return ; } // handling if the file not found
    // Read rooms data
    while (fscanf(rooms_file, "%d %s %s %d", &rooms[i].roomNumber, rooms[i].status, rooms[i].category, &rooms[i].price) != EOF) {
        i++;
        if (i == 100) break; // stop after 100 rooms TODO: will replace with text files later and will be determine the threshold
    } // checking in every line , if

    fclose(rooms_file);
}*/ // an old loadrooms function , keep it in case of redundancy TODO: might delete it !


// Function to convert the name to lowercase and remove extra spaces
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_NAME_LEN 20 //just a threshold , TODO we will determine it later !!
#define MAX_RESERVATION_COUNT 100


// Function to convert the name to lowercase and remove extra spaces
void normalizeName(char* str)
{
    //ok
    char* src = str; // Pointer to traverse the input string
    char* dest = str; // Pointer to write the processed string
    int inSpace = 0; // To ensure that repeated spaces are not included

    // Skip leading spaces
    while (isspace(*src))
    {
        src++;
    }
    /* just handling the first and last excessive spaces , the inside spaces is the the
       user responsibility , only the excessive will be handled !!
     */
    // Traverse through the string
    while (*src)
    {
        if (isspace(*src))
        {
            // If it's a space and we're not already in a space sequence
            if (dest > str && !inSpace)
            {
                *dest++ = ' '; // Add a single space
                inSpace = 1; // Mark that we're in a space sequence , to skip the rest spaces !!
            }
        }
        else
        {
            // If it's a regular character, convert to lowercase
            *dest++ = tolower(*src);
            inSpace = 0; // Reset space marker
        }
        src++;
    }

    // Null-terminate the modified string
    *dest = '\0';

    // Remove trailing spaces
    while (dest > str && isspace(*(dest - 1)))
    {
        *(--dest) = '\0';
    }
}

// Function to query customer name from reservation list
int QueryCustomerbyName(Reservation* reserved, char* name, int* indices)
{
    int i = 0;
    int count = 0; // To count the number of reservations for the customer
    normalizeName(name);

    // Check all reserved entries for matching name
    while (reserved[i].terminator != -1)
    {
        if (strcmp(StrToLower(reserved[i].customerName), name) == 0)
        {
            indices[count++] = i; // Store index in indices array
        }
        i++;
    }

    return count; // Return the number of matching reservations
}


void QueryCustomer()
{
    Reservation reserved[MAX_RESERVATION_COUNT];
    reservationLoad(reserved); // Load reservations data

    system("cls");

    int indices[MAX_RESERVATION_COUNT]; // Array to store indices of matching reservations
    int numOfReservations = 0; // To store the number of reservations found

    // Loop to allow retrying the search if customer is not found
    while (numOfReservations == 0)
    {
        char Name[MAX_NAME_LEN] = ""; // to reset the name

        // Prompt user for customer name
        printf("Enter the Customer Name, after filling the name press [Enter]: ");
        fgets(Name, MAX_NAME_LEN, stdin);

        // Manually remove the newline character if present
        if (Name[strlen(Name) - 1] == '\n')
        {
            Name[strlen(Name) - 1] = '\0'; // Remove the newline character
        }

        // Querying the customer information
        printf("Querying The Customer Information...\n");

        numOfReservations = QueryCustomerbyName(reserved, Name, indices);
        // Get the number of reservations and store indices

        if (numOfReservations > 0)
        {
            printf("-> Personal Information :\n");
            // Display personal information here
            printf(
                "===================================================================================================================\n");
            printf("%-20s%-15s%-30s%s\n", "Name", "Id", "Email", "Phone Number");
            printf(
                "===================================================================================================================\n");
            printf("%-20s%-15s%-30s%s\n", reserved[indices[0]].customerName,
                   reserved[indices[0]].customerNational_Id,
                   reserved[indices[0]].customerEmail,
                   reserved[indices[0]].mobileNumber);
            // Barrier
            printf(
                "********************************************************************************************************************\n");
            puts("To Proceed To Reservation : Press any button");
            getch(); // a place holder to keep the screen open, will be removed
            printf(
                "********************************************************************************************************************\n");
            printf("-> Reservation Information :\n");
            // Display reservation information here
            // Print table header with proper spacing
            printf(
                "===================================================================================================================\n");
            printf("%-20s%-15s%-25s%-25s%s\n",
                   "Reservation ID",
                   "Room",
                   "Number of Nights",
                   "Date of Reservation",
                   "Reservation Status");
            printf(
                "===================================================================================================================\n");

            // Loop through all reservations for this customer
            for (int j = 0; j < numOfReservations; j++)
            {
                int index = indices[j]; // Get the index of each reservation
                printf("%-20d%-15d%-25d%02d-%02d-%04d%26s\n",
                       reserved[index].reservationId,
                       reserved[index].room.number,
                       reserved[index].numOfNights,
                       reserved[index].date.days,
                       reserved[index].date.months,
                       reserved[index].date.years,
                       reserved[index].reservationStatus);
            }
            // Barrier
            printf(
                "********************************************************************************************************************\n");
            puts("To Proceed ,  Press any button");
            getch(); // a place holder to keep the screen open, will be removed
            printf(
                "********************************************************************************************************************\n");
        }
        else
        {
            printf("Customer not found \n");
            printf("-> Try Again? Press any button\n");
            printf("-> Quit to Query menu? Press 0\n");
            printf("-> Your choice ?");

            char option = getch();
            if (option == '0')
            {
                return; // Exit the function if the user chooses to quit
            }
        }
    }
}

// ROOMS SECTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int QueryStatusbyGet(Room* roomsData, char* Option, int* indices)
{
    int i = 0;
    int count = 0; // To count the number of reservations for the customer

    // Check all entries for matching Availability/Reservation
    while (roomsData[i].terminator != -1)
    {
        if (strcmp(StrToLower(roomsData[i].status), Option) == 0)
        {
            indices[count++] = i; // Store index in indices array
        }
        i++;
    }

    return count; // Return the number of matching reservations
}

void QueryRoomStatus_A()
{
    Room roomsData[MAX_RESERVATION_COUNT];
    LoadRooms(roomsData);
    int indices_A[MAX_RESERVATION_COUNT]; // Array to store indices of matching reservations
    //char Option [MAX_NAME_LEN] ="Available" ;
    // Querying the customer information
    printf("Querying The Customer Information...\n");
    // Get the number of reservations and store indices
    int num_Ava = QueryStatusbyGet(roomsData, "available", indices_A); //getting the number of available
    if (num_Ava > 0)
    {
        // and the index of each available !!
        printf("-> Available Rooms:\n");
        // Just the format
        printf("+==========+======================+===========\n");
        printf("| %-8s | %-20s | %-8s |\n", "Room ID", "Category", "Price");
        printf("+==========+======================+===========\n");
        for (int i = 0; i < num_Ava; i++)
        {
            //Loop to print
            int index = indices_A[i];
            printf("| %-8d | %-20s | %-8d |\n", roomsData[index].number,
                   roomsData[index].category,
                   roomsData[index].price);
        }
        printf(
            "********************************************************************************************************************\n");
        puts("To Proceed ,  Press any button");
        getch(); // a place holder to keep the screen open, will be removed
        printf(
            "********************************************************************************************************************\n");
    }
    else
    {
        printf("No Rooms available !\n");
        puts("To Proceed ,  Press any button");
        getch();
    }
}

void QueryRoomStatus_R()
{
    Room roomsData[MAX_RESERVATION_COUNT];
    LoadRooms(roomsData);
    int indices_R[MAX_RESERVATION_COUNT]; // Array to store indices of matching reservations
    //char Option [MAX_NAME_LEN] ="Available" ;
    // Querying the customer information
    printf("Querying The Customer Information...\n");
    // Get the number of reservations and store indices
    int num_Res = QueryStatusbyGet(roomsData, "reserved", indices_R); //getting the number of available
    if (num_Res > 0)
    {
        // and the index of each available !!
        printf("-> Reserved Rooms:\n");
        // Just the format
        printf("+==========+======================+===========\n");
        printf("| %-8s | %-20s | %-8s |\n", "Room ID", "Category", "Price");
        printf("+==========+======================+===========\n");
        for (int i = 0; i < num_Res; i++)
        {
            //Loop to print
            int index = indices_R[i];
            printf("| %-8d | %-20s | %-8d |\n", roomsData[index].number,
                   roomsData[index].category,
                   roomsData[index].price);
        }
        printf(
            "********************************************************************************************************************\n");
        puts("To Proceed ,  Press any button");
        getch(); // a place holder to keep the screen open, will be removed
        printf(
            "********************************************************************************************************************\n");
    }
    else
    {
        printf("No Rooms available !\n");
        puts("To Proceed ,  Press any button");
        getch();
    }
}

int QueryRoom_Status_ChoiceProcess(char choice)
{
    switch (choice)
    {
    case '1':
        QueryRoomStatus_A();
        return 1;
    case '2':
        QueryRoomStatus_R();
        return 2;
    case '3':
        return 3;
    default:
        return 0;
    }
}

void QueryRoomStatus()
{
    // handling status query menu
    system("cls");
    int i = 0;
    do
    {
        system("cls");
        if (i)
            puts("Invalid Input!\n");

        {
            // Query Rooms Status Menu Prompts
            printf("*******************************\n");
            printf("Which Category you want to work on  ? ?\n");
            printf("1. Available\n");
            printf("2. Reserved\n");
            printf("3. Exit Room Status Query\n");
            printf("*******************************\n");
            printf("Please enter your choice (1 - 3) : ");
        }
        char choice = getch();
        if (choice >= '1' && choice <= '3')
            if (QueryRoom_Status_ChoiceProcess(choice) == 3)
            {
                // if 3 then exit to the caller of query
                system("cls");
                puts("Exiting...");
                break;
            }
            else continue; /* if 1 or 2 which resemble Number or Status querying ...
                              return to the query menu if user needs more querying assistance !!*/

        i++; // originally 0 , if there is wrong in inputs , will display error message !!
    }
    while (1) ;
}

/*BY NUMBER section*******************************************************************/
int QueryRoomNumber_guest_get(Reservation* res, int roomnum, int* indices)
{
    int i = 0;
    int count = 0; // To count the number of reservations for the Room and its associated

    // Check all entries for matching room id
    while (res[i].terminator != -1)
    {
        if (res[i].room.number == roomnum)
        {
            indices[count++] = i; // Store index in indices array
        }
        i++;
    }

    return count; // Return the number of matching reservations
}

int QueryRoomNumber_get(Room* roomsData, int inputNumber)
{
    int i = 0; // index for the while statement search

    // Check all reserved entries for matching number :
    while (roomsData[i].terminator != -1)
    {
        if (roomsData[i].number == inputNumber)
        {
            return i;
        }
        i++;
    }
    return -1; // Return -1 if customer not found
}

void QueryRoomNumber()
{
    Room roomsdata[MAX_NAME_LEN];
    LoadRooms(roomsdata);
    Reservation reservations[MAX_RESERVATION_COUNT];
    reservationLoad(reservations);
    int inputNumber=0;  // here i fixed a buffer bug :)
    int res_indices[MAX_RESERVATION_COUNT];
    system("cls");
    fflush(stdin);
    printf("Enter the Room Number : ");
    scanf("%d", &inputNumber);
    printf("Querying The Room Information...\n");
    int index = QueryRoomNumber_get(roomsdata, inputNumber);
    // now to print the results ...
    //room number info
    if (index != -1)
    {
        printf("-> Room Information\n");
        printf("+==========+======================+==========+===================+\n");
        printf("| %-8s | %-20s | %-8s | %-17s |\n", "Room ID", "Category", "Price", "Status");
        printf("+==========+======================+==========+===================+\n");
        printf("| %-8d | %-20s | %-8d | %-17s |\n", roomsdata[index].number
               , roomsdata[index].category
               , roomsdata[index].price
               , roomsdata[index].status);
        printf("+==========+======================+==========+===================+\n");

        // if Room is Reserved .. get the guest associated

        if (strcmp(StrToLower(roomsdata[index].status), "reserved") == 0)
        {
            int room_r_data = QueryRoomNumber_guest_get(reservations, inputNumber, res_indices);
            // number of reserved times
            if (room_r_data > 0)
            {
                printf("-> Guest-Associated-with-Room Information\n");
                printf(
                    "===================================================================================================================================================================\n");
                printf("%-20s%-15s%-15s%-30s%-15s%-25s%-25s%s\n",
                       "Reservation ID",
                       "Guest",
                       "National ID",
                       "Email",
                       "PhoneNumber",
                       "Number of Nights",
                       "Date of Reservation",
                       "Reservation Status");
                printf(
                    "===================================================================================================================================================================\n");
                // Loop through all reservations for this customer
                for (int j = 0; j < room_r_data; j++)
                {
                    int index_R_Data = res_indices[j]; // Get the index of each reservation
                    printf("%-20d%-15s%-15s%-30s%-15s%-25d%02d-%02d-%04d%26s\n",
                           reservations[index_R_Data].reservationId,
                           reservations[index_R_Data].customerName,
                           reservations[index_R_Data].customerNational_Id,
                           reservations[index_R_Data].customerEmail,
                           reservations[index_R_Data].mobileNumber,
                           reservations[index_R_Data].numOfNights,
                           reservations[index_R_Data].date.days,
                           reservations[index_R_Data].date.months,
                           reservations[index_R_Data].date.years,
                           reservations[index_R_Data].reservationStatus);
                }
                // Barrier
                printf(
                    "********************************************************************************************************************************************************************\n");
            }
            else
            {
                printf("Error in Data !\n->Room Status is RESERVED but there is no such ID in reservations !!\n");
            }
        }
        else
        {
            printf("No Associated Reservations With this Room !! \n");
        }
        // in any case whilst found reservation or not , error in data .... will return to proceeding checkpoint
        puts("To Proceed , Press any button");
        getch();
    }
    // if room is not found in the first place
    else
    {
        printf("Room not found \n");
        printf("-> Try Again? Press any button\n");
        printf("-> Quit to Query menu? Press 0\n");
        printf("-> Your choice ?");

        char option = getch();
        printf("%c", '\n');
        if (option == '0')
        {
            return; // Exit the function if the user chooses to quit
        }
    }
}

/*Room Menu Seection*/
int QueryRoom_ChoiceProcess(char choice)
{
    switch (choice)
    {
    case '1':
        QueryRoomNumber();
        return 1;
    case '2':
        QueryRoomStatus();
        return 2;
    case '3':
        return 3;
    default:
        return 0;
    }
}

void QueryRoom()
{
    /*room roomsData[MAX_RESERVATION_COUNT] ;
    LoadRooms(roomsData) ; */
    system("cls");
    int i = 0;
    do
    {
        system("cls");
        if (i)
            puts("Invalid Input!\n");

        {
            // Query Rooms Menu Prompts
            printf("*******************************\n");
            printf("By what you want to use to query on Rooms ?\n");
            printf("1. Using Number\n");
            printf("2. Using Status\n");
            printf("3. Exit Room Query\n");
            printf("*******************************\n");
            printf("Please enter your choice (1 - 3) : ");
        }
        char choice = getch();
        if (choice >= '1' && choice <= '3')
            if (QueryRoom_ChoiceProcess(choice) == 3)
            {
                // if 3 then exit to the caller of query
                system("cls");
                puts("Exiting...");
                break;
            }
            else continue; /* if 1 or 2 which resemble Number or Status querying ...
                              return to the query menu if user needs more querying assistance !!*/

        i++; // originally 0 , if there is wrong in inputs , will display error message !!
    }
    while (1) ;
}


// MENU SECTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int QueryChoiceProcess(char choice)
{
    //ok
    switch (choice)
    {
    case '1':
        QueryCustomer();
        return 1;
    case '2':
        QueryRoom();
        return 2;
    case '3':
        return 3;
    default:
        return 0;
    }
}

void Query()
{
    // ok
    int i = 0;
    do
    {
        system("cls");
        if (i)
            puts("Invalid Input!\n");

        {
            // Query Menu Prompts
            printf("*******************************\n");
            printf("What do you want to query about ?\n");
            printf("1. Customer\n");
            printf("2. Room \n");
            printf("3. Exit\n");
            printf("*******************************\n");
            printf("Please enter your choice (1 - 3) : ");
        }
        char choice = getch();
        if (choice >= '1' && choice <= '3')
            if (QueryChoiceProcess(choice) == 3)
            {
                // if 3 then exit to the caller of query
                system("cls");
                puts("Exiting...");
                break;
            }
            else continue; /* if 1 or 2 which resemble customer or room querying ...
                              return to the query menu if user needs more querying assistance !!*/

        i++; // originally 0 , if there is wrong in inputs , will display error message !!
    }
    while (1) ;
}

// end of query function
int V_Details_Res_ID_get(Reservation* reservationId, int Res_ID)
{
    // SEARCH AnD GET THE UNIQUE RESERVATION ID
    int i = 0; // index for the while statement search

    // Check all reserved entries for matching number :
    while (reservationId[i].terminator != -1)
    {
        if (reservationId[i].reservationId == Res_ID)
        {
            return i;
        }
        i++;
    }
    return -1; // Return -1 if customer not found
}

void V_Details_Res_ID()
{
    fflush(stdin);
    // handling the menu of reservation id retails
    Reservation res[MAX_RESERVATION_COUNT];
    reservationLoad(res); // Load reservations data
    int inputID = 0;
    system("cls");
    printf("Reservation ID : \n");
    scanf("%d", &inputID);
    int index = V_Details_Res_ID_get(res, inputID);
    printf("Querying The Reservations Information...\n");
    if (index != -1)
    {
        printf(
            "===================================================================================================================================================================\n");
        printf("%-20s%-15s%-15s%-30s%-15s%-25s%-25s%s\n",
               "Reservation ID",
               "Guest",
               "National ID",
               "Email",
               "PhoneNumber",
               "Number of Nights",
               "Date of Reservation",
               "Reservation Status");
        printf(
            "===================================================================================================================================================================\n");
        printf("%-20d%-15s%-15s%-30s%-15s%-25d%02d-%02d-%04d%26s\n",
               res[index].reservationId,
               res[index].customerName,
               res[index].customerNational_Id,
               res[index].customerEmail,
               res[index].mobileNumber,
               res[index].numOfNights,
               res[index].date.days,
               res[index].date.months,
               res[index].date.years,
               res[index].reservationStatus);
        // Barrier
        printf(
            "********************************************************************************************************************************************************************\n");
        printf("To Proceed , Press any button \n");
        getch();
    }

    else
    {
        printf("No Reservation with that ID! Might be Error in data or just a missing entry\n");
        printf("Or Might Your Entered input is Wrong .... Consider Checking again \n");
        printf("To Proceed , Press any button \n");
        getch();
    }
    //the end , will return to the caller
}

int V_DetailsChoiceProcess(char choice)
{
    switch (choice)
    {
    case '1':
        V_Details_Res_ID();
        return 1;
    case '2':
        QueryRoomNumber();
        return 2;
    case '3':
        return 3;
    default:
        return 0;
    }
}

void ViewCustomerDetails()
{
    system("cls");
    int i = 0;
    do
    {
        system("cls");
        if (i)
            puts("Invalid Input!\n");

        {
            // Query Menu Prompts
            printf("*******************************\n");
            printf("By What you want to view Details ?\n");
            printf("1. Reservation ID\n");
            printf("2. Room Number \n");
            printf("3. Exit\n");
            printf("*******************************\n");
            printf("Please enter your choice (1 - 3) : ");
        }
        char choice = getch();
        if (choice >= '1' && choice <= '3')
            if (V_DetailsChoiceProcess(choice) == 3)
            {
                // if 3 then exit to the caller of query
                system("cls");
                puts("Exiting...");
                break;
            }
            else continue; /* if 1 or 2 which resemble customer or room querying ...
                              return to the query menu if user needs more querying assistance !!*/

        i++; // originally 0 , if there is wrong in inputs , will display error message !!
    }
    while (1) ;
}
