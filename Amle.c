
#include "Amle.h"
#include "Hany.h"
#include "Menna.h"
#include "Rabie.h"
#include "Akram.h"


char UserRoomChoice()
{
    char roomCategoryChoice;
    while (1) {
        printf("1. for Sea view \n");
        printf("2. for Lake view \n");
        printf("3. for Garden view \n");
        printf("4. back to main menu \n");
        printf("5. Exit \n");
        printf("Please enter number from 1 to 5\n");
        roomCategoryChoice = getch();
        if (roomCategoryChoice >= '1' && roomCategoryChoice <= '5')
            break;
        printf("invalid input, Please choose number from 1 to 5\n");
    }
    return roomCategoryChoice;
}

void GetAvailableRoom(const char *category, Room *room) // return room number if valid else return 0
{
    Room roomData[100];
    LoadRooms(roomData);
    int i = 0;
    while (roomData[i].terminator != -1) {
        if (strcmp(category, roomData[i].category) == 0 && strcmp("Available", roomData[i].status) == 0)
            *room = roomData[i];
        i++;
    }
}

int GetNonDuplicatesId(int nonDuplicates[])
{
    Reservation buffer[100];
    reservationLoad(buffer);

    int index = 0;
    while (buffer[index].terminator != -1)
    {
        nonDuplicates[index] = buffer[index].reservationId;
        index++;
    }
    return index;
}

void ChangeRoomStatus(int roomNumber,char *status) {
    Room buffer[100];
    LoadRooms(buffer);
    int i = 0;
    while (buffer[i].terminator != -1) {
        if (buffer[i].number == roomNumber) {
            strcpy(buffer[i].status,status);
            break;
        }
        i++;
    }
    WriteEditedDataRoom(buffer);
}

void WriteEditedDataRoom(Room NewRoomData[100])
{
    int i ;
    FILE *file = fopen("rooms.text", "w");
    if (file == NULL) {
        printf("Cant open the file.");
        return;
    }
    for (i = 0; i < 100; i++) {   //TODO: loop until fixed size
        fprintf(file, "%d %s %s %d\n", NewRoomData[i].number,NewRoomData[i].status,NewRoomData[i].category,NewRoomData[i].price);
    }
    NewRoomData[i].terminator = -1;
    fclose(file);
}


void AddReservation(Reservation ReservationInfo) {  //
    Reservation buffer[100];
    reservationLoad(buffer);

    int index = 0;
    while (buffer[index].terminator != -1)
        index++;
    printf("DEBUG - AddReservation - before addition - index: %d\n", index);
    buffer[index].terminator = 0;

    ReservationInfo.terminator = -1;
    buffer[++index] = ReservationInfo;
    printf("DEBUG - AddReservation - after addition - index: %d\n", index);

    OverwriteRes(buffer);
}


void GenerateReservationID(Reservation ReservationInfo)   //take the other data of user to collect all data
{
    int nonDuplicates[100];
    int index = GetNonDuplicatesId(nonDuplicates);
    int resId = 100000 + GenerateRand(10000, 99000, nonDuplicates, index + 1);
    nonDuplicates[index + 2] = resId;
    ReservationInfo.reservationId = resId;
    strcpy(ReservationInfo.reservationStatus, "Unconfirmed");
    printf("***************** DEBUG GenerateReservationID *****************\n");
    printf("Room: %d, %s, %s, %d\n", ReservationInfo.room.number, ReservationInfo.room.status, ReservationInfo.room.category, ReservationInfo.room.price);
    printf("customerName: %s\n", ReservationInfo.customerName);
    printf("customerNationalId: %s\n", ReservationInfo.customerNational_Id);
    printf("customerEmail: %s\n", ReservationInfo.customerEmail);
    printf("mobileNumber: %s\n", ReservationInfo.mobileNumber);
    printf("numOfNights: %d\n", ReservationInfo.numOfNights);
    printf("Date: %d %d %d\n", ReservationInfo.date.days, ReservationInfo.date.months, ReservationInfo.date.years);
    printf("reservationStatus: %s\n", ReservationInfo.reservationStatus);
    printf("ReservationID: %d\n", ReservationInfo.reservationId);
    printf("***************** DEBUG GenerateReservationID *****************\n");
    getch();
    AddReservation(ReservationInfo);
}

void MakeReservation() {  //take data & add it to res file
    puts("Reservation.");

    Reservation ReservationInfo;
    int valid;
    //take name
    do {
        puts("Please enter your Name.\n");
        scanf("%s",ReservationInfo.customerName);
        valid = is_vaild_name(ReservationInfo.customerName);
    }while (valid == 0);

    valid = 0;
    system("cls");
    //take national id
    do {
        puts("Please enter your National Id.\n");
        scanf("%s",ReservationInfo.customerNational_Id);
        valid = is_valid_nationalid(ReservationInfo.customerNational_Id);
    }while (valid == 0);

    valid = 0;
    system("cls");
    //take email
    do {
        puts("Please enter your Email.");
        scanf("%s",ReservationInfo.customerEmail);
        valid = is_vaild_Email(ReservationInfo.customerEmail);
    }while (valid == 0);

    valid = 0;
    system("cls");
    //take mobile number
    do {
        puts("Please enter your Mobile Number.");
        scanf("%s",ReservationInfo.mobileNumber);
        valid = is_vaild_mobil(ReservationInfo.mobileNumber);
    }while (valid == 0);

    valid = 0;
    system("cls");
    //take checkin date
    do {
        puts("Please enter the Check In date.");
        scanf("%d %d %d",&ReservationInfo.date.days,&ReservationInfo.date.months,&ReservationInfo.date.years);
        valid = is_vaild_Date(ReservationInfo.date);
    }while (valid == 0);

    valid = 0;
    system("cls");
    //take num of nights
    // TODO: Ask Menna to imlement is_vaild_number_nights()
    ReservationInfo.numOfNights = 3;    // TODO: remove this when implementation is ready
    /*do {
        puts("Please enter the Number of Nights.\n");
        scanf("%d",ReservationInfo.numOfNights);
        valid = is_vaild_number_nights(CustomerInfo.numOfNights);
    }while (valid == 0);*/

    int first_time_flag = 1;
    do {
        if (first_time_flag == 0)
            puts("Sorry this Category not available");

        puts("Please enter the Room category.\n");
        char choice = UserRoomChoice();
        switch (choice) {
            case '1':
                GetAvailableRoom("SeaView", &ReservationInfo.room);
                break;
            case '2':
                GetAvailableRoom("LakeView", &ReservationInfo.room);
                break;
            case '3':
                GetAvailableRoom("LakeView", &ReservationInfo.room);
                break;
            case '4':
                MainMenu();
                return;
            case '5':
                //TODO: call exit
                return;
        }
        first_time_flag = 0;
    }while (ReservationInfo.room.number == 0);
    strcpy(ReservationInfo.room.status, "Reserved");

    printf("Reservation Information ready\n");
    printf("***************** DEBUG MakeReservation *****************\n");
    printf("Room: %d, %s, %s, %d\n", ReservationInfo.room.number, ReservationInfo.room.status, ReservationInfo.room.category, ReservationInfo.room.price);
    printf("customerName: %s\n", ReservationInfo.customerName);
    printf("customerNationalId: %s\n", ReservationInfo.customerNational_Id);
    printf("customerEmail: %s\n", ReservationInfo.customerEmail);
    printf("mobileNumber: %s\n", ReservationInfo.mobileNumber);
    printf("numOfNights: %d\n", ReservationInfo.numOfNights);
    printf("Date: %d %d %d\n", ReservationInfo.date.days, ReservationInfo.date.months, ReservationInfo.date.years);
    printf("***************** DEBUG MakeReservation *****************\n");
    getch();
    GenerateReservationID(ReservationInfo);
    printf("reservation Done\n");
    getch();
}


void CheckOut() {
    printf("Check Out.");
    printf("Please enter your room number.");
    int roomnumber ;
    scanf("%d",&roomnumber);

    int bill = 0;
    int i = 0;

    Room roomData[100];
    LoadRooms(roomData);

    while (roomData[i].terminator != -1) {  //calc bill
        if (roomData[i].number == roomnumber) {
            bill = roomData[i].price;
            break;
        }
    }
    if (bill == 0) {
        //sign that room number dosenot exist
        printf("invalid room number."
               "1.Checkout"
               "2.exit");
        char choice = getch();
        if (choice == '1')
            CheckOut();
        else if (choice == '2') {
            // call exit function
            return;
        }
        else {
            printf("invalid choice.");
            CheckOut();
        }
    }
    else {
        Reservation Data[100];
        reservationLoad(Data);

        i = 0;
        int flag = 0;
        while (Data[i].terminator != -1) {
            if (Data[i].room.number == roomnumber)
                if (strcmp(Data[i].reservationStatus,"Confirmed") == 0) {
                    flag = 1;
                    break;
                }
            i++;
        }

        if (flag == 0) {
            printf("Sorry This service is not available.");
            return;
        }

        printf("This is your check out %d.",bill);

        ChangeRoomStatus(roomnumber,"Available"); //edit room status

        //call cancel reservation


    }





    }





