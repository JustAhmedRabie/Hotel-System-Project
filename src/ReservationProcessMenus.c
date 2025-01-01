#include "ReservationProcessMenus.h"

void CancelReservation(int error)
{
    system("cls");
    puts(CYAN"Cancel Reservation:"RESET);
    Reservation resData[100];
    if (!LoadReservations(resData))
    {
        puts(RED"You don't have any reservations yet"RESET);
        getch();
        return;
    }

    if (error)
    {
        puts(RED"ERROR, please enter a valid input!"RESET);
    }
    puts("Please enter the reservation ID or the Room number you want to cancel:");
    puts("enter -1 to get to main menu, -2 to exit");
    int input;
    int i = 0;
    fflush(stdin);
    scanf("%d", &input);
    fflush(stdin);
    if (input == -1) MainMenu();
    else if (input == -2) exit(0);

    while (resData[i].terminator != -1)
    {
        if (input == resData[i].reservationId || input == resData[i].room.number)
        {
            break;
        }

        i++;
    }
    if (resData[i].terminator == -1)
    {
        CancelReservation(1);
        return;
    }
    if (strcmp("unconfirmed", StrToLower(resData[i].reservationStatus)))
    {
        puts(RED"Error! Either the reservation is checked in or checked out!"RESET);
        getch();
        CancelReservation(0);
        return;
    }
    if (Save(0))
    {
        DeleteReservationEntry(resData, i);
    }
}

void EditReservation()
{
    Reservation reservData[100];
    Reservation reservBackup[100];
    LoadReservations(reservBackup);
    system("cls");
    puts(CYAN"Editing reservation"RESET);
    if (!LoadReservations(reservData))
    {
        puts(RED"You don't have any reservations yet"RESET);
        getch();
        return;
    }
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
        else if (input == -2) exit(0);

        int i = 0;
        while (reservData[i].terminator != -1)
        {
            if (input == reservData[i].reservationId || input == reservData[i].room.number)
            {
                if (strcmp(StrToLower(reservData[i].reservationStatus), "confirmed") == 0)
                {
                    puts(RED"This reservation is already checked in!"RESET);
                    getch();
                    break;
                }
                flag = 1;

                system("cls");
                puts(CYAN"Please enter you new data:"RESET);
                long ID = reservData[i].reservationId;
                DeleteReservationEntry(reservData, i);
                int complete = MakeReservation(ID);

                if (complete == -1)
                {
                    Update(reservBackup);
                    return;
                }
                if (Save(0))
                {
                    puts(GREEN"Reservation edited successfully!"RESET);
                    getch();
                }
                else
                {
                    Update(reservBackup);
                }

                break;
            }
            i++;
        }
        int isFound = !(reservData[i].terminator == -1);

        if (!isFound) puts(RED"The input is invalid!"RESET);
        if (!flag) continue;
        else break;
    }
    while (1);
}

char UserRoomChoice()
{
    char roomCategoryChoice;
    while (1)
    {
        printf("1. for Sea view \n");
        printf("2. for Lake view \n");
        printf("3. for Garden view \n");
        printf("4. back to main menu \n");
        printf("5. Exit \n");
        printf("Please enter number from 1 to 5\n");
        roomCategoryChoice = getch();
        if (roomCategoryChoice >= '1' && roomCategoryChoice <= '5')
            break;
        system("cls");
        printf(RED "invalid input, Please choose number from 1 to 5\n" RESET);
    }
    return roomCategoryChoice;
}

void GetAvailableRoom(const char* category, Room* room)
{
    Room roomData[100];
    LoadRooms(roomData);

    room->number = 0;
    int i = 0;
    while (roomData[i].terminator != -1)
    {
        if (strcmp(category, roomData[i].category) == 0 && strcmp("available", StrToLower(roomData[i].status)) == 0)
        {
            //printf("DEBUG - Found available room\n");
            *room = roomData[i];
            return;
        }
        i++;
    }
}

int GetNonDuplicatesId(int nonDuplicates[])
{
    Reservation buffer[100];
    srand(time(NULL));
    if (!LoadReservations(buffer))
    {
        return 0;
    }

    int length = 0;
    while (buffer[length].terminator != -1)
    {
        nonDuplicates[length] = buffer[length].reservationId;
        length++;
    }
    return length;
}

void AddReservation(Reservation ReservationInfo)
{
    //
    Reservation buffer[100];
    if (!LoadReservations(buffer))
    {
        buffer[0] = ReservationInfo;
        buffer[1].terminator = -1;
        Update(buffer);
        return;
    }
    int length = 0;
    while (buffer[length].terminator != -1)
        length++;

    buffer[length] = ReservationInfo;
    buffer[length].terminator = 10;

    buffer[length + 1].terminator = -1;

    Update(buffer);
}

void GenerateReservationID(Reservation ReservationInfo) //take the other data of user to collect all data
{
    int resId;
    int flag = 1;

    if (ReservationInfo.reservationId == 0)
    {
        int nonDuplicates[100];
        int length = GetNonDuplicatesId(nonDuplicates);
        resId = 100000 + GenerateRand(10000, 99000, nonDuplicates, length); //index + 1   index <-> len of nonDup
        ReservationInfo.reservationId = resId;
        flag = 0;
    }

    strcpy(ReservationInfo.reservationStatus, "unconfirmed");

    system("cls");
    StandBy("Processing your reservation");
    puts("This is Your information");
    printf("Name: %s\n", ReservationInfo.customerName);
    printf("National ID: %s\n", ReservationInfo.customerNational_Id);
    printf("Email: %s\n", ReservationInfo.customerEmail);
    printf("Mobile Number: %s\n", ReservationInfo.mobileNumber);
    printf("Num Of Nights: %d\n", ReservationInfo.numOfNights);
    printf("Date: %d-%d-%d\n", ReservationInfo.date.days, ReservationInfo.date.months, ReservationInfo.date.years);
    printf("Reservation Status: %s\n", ReservationInfo.reservationStatus);
    printf("Reservation ID: %d\n", ReservationInfo.reservationId);
    printf("Room: %d\n", ReservationInfo.room.number);
    printf("\n");

    if (!flag)
    {
        if (Save(0))
        {
            AddReservation(ReservationInfo);
        }
        else return;
    }
    else
    {
        AddReservation(ReservationInfo);
    }
}

int MakeReservation(int reservID)
{
    //take data & add it to res file
    Reservation ReservationInfo;
    int valid = 0;
    int ret;
    puts("press ESC for main menu");
    //take name
    do
    {
        puts("Please enter your Name.");
        fflush(stdin);
        ret = ExitChoice(ReservationInfo.customerName, 29);
        if (ret == -1)
        {
            system("cls");
            return -1;
        }
        fflush(stdin);
        NormAndCapital(ReservationInfo.customerName);
        valid = IsValidName(ReservationInfo.customerName);
    }
    while (valid == 0);

    valid = 0;
    system("cls");
    //take national id
    do
    {
        puts("Please enter your National Id.");
        ret = ExitChoice(ReservationInfo.customerNational_Id, 14);
        if (ret == -1)
        {
            system("cls");
            return -1;
        }
        valid = IsValidNationalId(ReservationInfo.customerNational_Id);
    }
    while (valid == 0);

    valid = 0;
    system("cls");
    //take email
    do
    {
        puts("Please enter your Email.");
        ret = ExitChoice(ReservationInfo.customerEmail, 29);
        if (ret == -1)
        {
            system("cls");
            return -1;
        }
        valid = isValidEmail(ReservationInfo.customerEmail);
    }
    while (valid == 0);

    valid = 0;
    system("cls");
    //take mobile number
    do
    {
        puts("Please enter your Mobile Number.");
        ret = ExitChoice(ReservationInfo.mobileNumber, 13);
        if (ret == -1)
        {
            system("cls");
            return -1;
        }
        valid = IsValidMobile(ReservationInfo.mobileNumber);
    }
    while (valid == 0);

    valid = 0;
    system("cls");
    //take checkin date

    do
    {
        if (GetDate(&ReservationInfo.date.days, &ReservationInfo.date.months, &ReservationInfo.date.years, 1) == -1)
            return -1;

        time_t date;

        struct tm* timeinfo;

        date = time(NULL);
        timeinfo = localtime(&date);

        Reservation tempReservation;
        tempReservation.date.days = timeinfo->tm_mday;
        tempReservation.date.months = timeinfo->tm_mon + 1;
        tempReservation.date.years = timeinfo->tm_year + 1900;

        if (CmpRes(tempReservation, ReservationInfo) == -1)
        {
            fflush(stdin);
            system("cls");
            puts(RED"Invalid Date!"RESET);
            getch();
        }
        else valid = 1;
    }
    while (valid == 0);

    valid = 0;
    system("cls");
    char n_nights[3];
    do
    {
        puts("Please enter the Number of Nights.");
        ret = ExitChoice(n_nights, 2);
        if (ret == -1)
        {
            system("cls");
            return -1;
        }
        valid = IsValidNights(n_nights);
    }
    while (valid == 0);
    ReservationInfo.numOfNights = atoi(n_nights);

    system("cls");
    int first_time_flag = 1;
    do
    {
        system("cls");
        if (first_time_flag == 0)
            puts(RED "Sorry this Category not available" RESET);

        puts(CYAN"Room category.."RESET);
        char choice_Category = UserRoomChoice();
        switch (choice_Category)
        {
        case '1':
            GetAvailableRoom("SeaView", &ReservationInfo.room);
            break;
        case '2':
            GetAvailableRoom("LakeView", &ReservationInfo.room);
            break;
        case '3':
            GetAvailableRoom("GardenView", &ReservationInfo.room);
            break;
        case '4':
            return -1;
        case '5':
            exit(0);
        }
        first_time_flag = 0;
    }
    while (ReservationInfo.room.number == 0);


    strcpy(ReservationInfo.room.status, "Reserved");
    ReservationInfo.reservationId = reservID;
    GenerateReservationID(ReservationInfo);
    return 1;
}