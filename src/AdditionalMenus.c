#include "AdditionalMenus.h"

void ReservationReport()
{
    system("cls");
    puts(CYAN"Reservation report:"RESET);
    Reservation reservations[100];
    if (!LoadReservations(reservations))
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

void MainMenu()
{
    char choice;
    int i = 0;

    do
    {
        system("cls");
        if (i)
            puts(RED "ERROR, Invalid Input!\n" RESET);

        {
            // Main Menu Prompts
            printf(GREEN "*******************************\n" RESET);
            printf(GREEN "*      Heliopolise Hotel      *\n" RESET);
            printf(GREEN "*******************************\n" RESET);
            printf("\n");
            printf(CYAN " * Main menu * \n" RESET);
            printf("1. Reservation\n");
            printf("2. Check in \n");
            printf("3. Check out\n");
            printf("4. Cancel reservation \n");
            printf("5. Check room availability \n");
            printf("6. View customer details\n");
            printf("7. Query\n");
            printf("8. Reservation report \n");
            printf("9. Edit Reservation \n");
            printf("0. Exit\n");
            printf("Please enter your choice (0 - 9) : ");
        }
        choice = getch();
        if (choice >= '0' && choice <= '9')
            break;
        i++;
    } while (1);

    MenuChoiceProcess(choice);
}

void MenuChoiceProcess(char choice)
{
    switch (choice)
    {
    case '1':
        system("cls");
        puts(CYAN"Reservation:"RESET);
        MakeReservation(0);
        break;
    case '2':
        system("cls");
        CheckIn();
        break;
    case '3':
        system("cls");
        CheckOut();
        break;
    case '4':
        system("cls");
        CancelReservation(0);
        break;
    case '5':
        system("cls");
        TrackRoom();
        break;
    case '6':
        system("cls");
        ViewCustomerDetails();
        break;
    case '7':
        system("cls");
        Query();
        break;
    case '8':
        system("cls");
        ReservationReport();
        break;
    case '9':
        system("cls");
        EditReservation();
        break;
    case '0':
        system("cls");
        puts("Exiting...");
        exit(0);
        break;
    default:
        puts("Invalid choice!\n");
    }

    MainMenu();
}

void LogIn()
{
    char password[30];
    char username[20];
    user users[10];

    LoadUsers(users);

    int i = 0;
    int isValid = 0;
    char choice;
    do
    {
        system("cls");
        if (i)
            puts(RED"ERROR, Invalid Input!\n"RESET);

        printf("1. Log In\n");
        printf("2. Exit \n");

        choice = getch();

        if (choice == '1')
            break;
        else if (choice == '2')
            exit(0);

        i++;
    }
    while (1);

    i = 0;

    do
    {
        system("cls");
        if (i)
            puts(RED"ERROR, Invalid Input!\n"RESET);
        puts("Please enter your username:");
        gets(username);
        puts("Please enter your password:");
        i = 0;

        do
        {
            char ch = getch();
            if (ch == 13) // ASCII enter code
            {
                password[i] = '\0';
                break;
            }

            // If Backspace is pressed, remove last character
            if (ch == 8) // ASCII value for Backspace key
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b"); // Erase previous character and move cursor back
                }
            }
            else
            {
                password[i] = ch;
                printf("*");
                i++;
            }
        }
        while (1);

        for (i = 0; users[i].terminator != -1; i++)
        {
            if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password))
            {
                isValid = 1;
                break;
            }
        }
        i++; // Just to know if it's not the first time the user enters his information
    }
    while (!isValid);
    i--;

    MainMenu();
}

int Save(int error)
{
    if (error)
    {
        system("cls");
        puts(RED"ERROR, please enter a valid input!"RESET);
    }

    puts(YELLOW"Do you want to save the changes you did?"RESET);
    puts(YELLOW"type: Y/N"RESET);
    puts(YELLOW"type: E to exit, M to navigate to main menu"RESET);

    fflush(stdin);
    char x = getch();
    if (tolower(x) == 'y')
    {
        puts(CYAN"Your changes was saved successfully!, press any key to continue..."RESET);
        getch();
        system("cls");
        return 1;
    }
    else if (tolower(x) == 'n')
    {
        puts(YELLOW"Your changes wasn't saved, press any key to continue..."RESET);
        getch();
        system("cls");
        return 0;
    }
    else if (tolower(x) == 'm')
    {
        MainMenu();
        return 0;
    }
    else if (tolower(x) == 'e')
    {
        exit(0);
        return 0;
    }
    else
    {
        x = Save(1);
        return x;
    }
}

void StandBy(char* str)
{
    if (str == NULL) return;


    printf("\033[?25l"); //disables the caret
    system("cls");
    printf(GREEN);
    printf("%s", str);

    for (int i = 0; i <= 8; i++)
    {
        fflush(stdin);
        printf(".");
        Sleep(400);
    }
    printf("\n");
    printf(RESET);
    fflush(stdin);
    printf("\033[?25h\033[0 q"); //re-enables the caret
    system("cls");
}