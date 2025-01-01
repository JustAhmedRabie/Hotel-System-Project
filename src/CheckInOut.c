#include "CheckInOut.h"


void CheckIn()
{
    system("cls");
    Reservation reservData[100];
    if (!LoadReservations(reservData))
    {
        puts(RED "You don't have any reservations yet" RESET);
        getch();
        return;
    }

    time_t date;

    struct tm *timeinfo;

    date = time(NULL);
    timeinfo = localtime(&date);

    Reservation tempReservation;
    tempReservation.date.days = timeinfo->tm_mday;
    tempReservation.date.months = timeinfo->tm_mon + 1;
    tempReservation.date.years = timeinfo->tm_year + 1900;
    puts(CYAN "Check-in: " RESET);
    long input;

    do
    {
        int flag = 0;
        puts("Enter the reservation ID or room number");
        puts("Type -1 to go back to the main menu, -2 to exit");
        fflush(stdin);
        scanf("%ld", &input);
        fflush(stdin);
        system("cls");
        if (input == -1)
        {
            MainMenu();
            return;
        }
        else if (input == -2)
            exit(0);

        int i = 0;
        while (reservData[i].terminator != -1)
        {
            if (input == reservData[i].reservationId || input == reservData[i].room.number)
            {
                if (strcmp(StrToLower(reservData[i].reservationStatus), "confirmed") == 0)
                {
                    puts(RED "This reservation is already checked in!" RESET);
                    getch();
                    break;
                }

                if (CmpRes(tempReservation, reservData[i]) == 1)
                {
                    puts(RED "The reservation date is not due yet!" RESET);
                    getch();
                    break;
                }
                flag = 1;
                if (Save(0))
                {
                    system("cls");
                    strcpy(reservData[i].reservationStatus, "confirmed");
                    OverwriteRes(reservData);
                    puts(GREEN "Reservation confirmed and checked in successfully!" RESET);
                    puts(YELLOW "That's your information:" RESET);
                    printf("Name: %s\n", reservData[i].customerName);
                    printf("National ID: %s\n", reservData[i].customerNational_Id);
                    printf("Email: %s\n", reservData[i].customerEmail);
                    printf("Mobile Number: %s\n", reservData[i].mobileNumber);
                    printf("Num Of Nights: %d\n", reservData[i].numOfNights);
                    printf("Date: %d-%d-%d\n", reservData[i].date.days, reservData[i].date.months,
                           reservData[i].date.years);
                    printf("Reservation Status: %s\n", reservData[i].reservationStatus);
                    printf("Reservation ID: %d\n", reservData[i].reservationId);
                    printf("Room: %d\n", reservData[i].room.number);
                    puts("press any key to continue");
                    getch();
                }
                break;
            }
            i++;
        }
        int isFound = !(reservData[i].terminator == -1);

        if (!isFound)
            puts(RED "The input is invalid!" RESET);
        if (!flag)
            continue;
        else
            break;
    } while (1);
}

void CheckOut()
{
    system("cls");
    puts(CYAN"Check-Out:"RESET);

    Reservation reservationData[100];

    if (!LoadReservations(reservationData))
    {
        puts(RED "You don't have any reservations yet" RESET);
        getch();
        return;
    }
    puts("Please enter your room number or Reservation Id.");
    int input;

    fflush(stdin);
    scanf("%d", &input);
    fflush(stdin);
    int index = 0; //need to save to call cancelReservation function
    int flag = 0; //indicate that this process is available or not

    while (reservationData[index].terminator != -1)
    {
        if (reservationData[index].room.number == input || reservationData[index].reservationId == input)
        {
            if (strcmp(StrToLower(reservationData[index].reservationStatus), "confirmed") == 0)
            {
                flag = 1;
                break;
            }
        }
        index++;
    }

    if (flag == 0)
    {
        fflush(stdin);
        puts(RED"Sorry Your input is Wrong or The reservations is Unconfirmed." RESET);
        puts("To try again press any key.\n"
            "For main menu press M");
        puts("To exit press E");
        char choice = getch();

        if (tolower(choice) == 'm')
        {
            MainMenu();
            return;
        }
        else if (tolower(choice) == 'e')
            exit(0);
        else
        {
            CheckOut();
            return;
        }
    }

    int nights = reservationData[index].numOfNights;
    int roomNumber = reservationData[index].room.number; // get if Data true or confirmed

    //calc Bill
    Room roomData[100];
    LoadRooms(roomData);
    int i = 0;
    int bill;

    while (roomData[i].terminator != -1)
    {
        //calc bill
        if (roomData[i].number == roomNumber)
        {
            bill = roomData[i].price;
            bill *= nights;
            break;
        }
        i++;
    }
    //check out done
    if (Save(0))
    {
        DeleteReservationEntry(reservationData, index);
        puts(GREEN "The Check Out is Done." RESET);
        printf("Number of Nights: %d\n", nights);
        printf("Price of the night: %d\n", roomData[i].price);
        printf("This is your total Bill: " "\x1b[30m" "\x1b[107m" "%d$" "\x1b[40m" RESET ".\n", bill);
        getch();
    }
}
