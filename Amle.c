#include "Amle.h"
#include "Hany.h"
#include "Menna.h"
#include "Rabie.h"
#include "Akram.h"

#define SKIP_SEQ_PREFIX_1 0
#define SKIP_SEQ_PREFIX_2 224

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
    if (!reservationLoad(buffer))
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
    if (!reservationLoad(buffer))
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

int ExitChoice(char input[], int size)
{
    int i = 0;
    while (i < size + 1)
    {
        int c = getch();
        if (c == SKIP_SEQ_PREFIX_1 || c == SKIP_SEQ_PREFIX_2)
        {
            getch(); //to take actual code
            continue; //to skip i++
        }
        if (c == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i -= 1;
            }
            continue;
        }

        if (c == '\n' || c == '\r')
        {
            input[i] = '\0';
            printf("\n");
            return 1;
        }

        if (c == 27)
        {
            return -1;
        }
        input[i] = c;
        printf("%c", input[i]);
        i++;
    }
    printf("\n");
    return 0;
}

void MakeReservation(int reservID)
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
            MainMenu();
            return;
        }
        fflush(stdin);
        NormAndCapital(ReservationInfo.customerName);
        valid = is_vaild_name(ReservationInfo.customerName);
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
            MainMenu();
            return;
        }
        valid = is_valid_nationalid(ReservationInfo.customerNational_Id);
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
            MainMenu();
            return;
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
        ret = ExitChoice(ReservationInfo.mobileNumber, 11);
        if (ret == -1)
        {
            system("cls");
            MainMenu();
            return;
        }
        valid = is_vaild_mobil(ReservationInfo.mobileNumber);
    }
    while (valid == 0);

    valid = 0;
    system("cls");
    //take checkin date

    do
    {
        if (GetDate(&ReservationInfo.date.days, &ReservationInfo.date.months, &ReservationInfo.date.years) == -1)
            return;

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
            MainMenu();
            return;
        }
        valid = valid_room_nights(n_nights);
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
            MainMenu();
            return;
        case '5':
            exit(0);
        }
        first_time_flag = 0;
    }
    while (ReservationInfo.room.number == 0);


    strcpy(ReservationInfo.room.status, "Reserved");
    ReservationInfo.reservationId = reservID;
    GenerateReservationID(ReservationInfo);
}

void CheckOut()
{
    system("cls");
    puts(CYAN"Check-Out:"RESET);

    Reservation reservationData[100];

    if (!reservationLoad(reservationData))
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
