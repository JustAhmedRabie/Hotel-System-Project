
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

void GetAvailableRoom(const char *category, Room *room)
{
    Room roomData[100];
    LoadRooms(roomData);

    room->number = 0;
    int i = 0;
    while (roomData[i].terminator != -1) {
        if (strcmp(category, roomData[i].category) == 0 && strcmp("available", StrToLower(roomData[i].status)) == 0) {
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
    reservationLoad(buffer);
    srand(0);

    int length = 0;
    while (buffer[length].terminator != -1)
    {
        nonDuplicates[length] = buffer[length].reservationId;
        length++;
    }
    return length;
}

void ChangeRoomStatus(int roomNumber,char *newStatus) {
    Room buffer[100];
    LoadRooms(buffer);
    int i = 0;
    while (buffer[i].terminator != -1) {
        if (buffer[i].number == roomNumber) {
            strcpy(buffer[i].status,newStatus);
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

    int length = 0;
    while (buffer[length].terminator != -1)
        length++;
    buffer[length].terminator = 0;

    buffer[length] = ReservationInfo;
    buffer[++length].terminator = -1;

    Update(buffer);
}

void GenerateReservationID(Reservation ReservationInfo)   //take the other data of user to collect all data
{
    int nonDuplicates[100];
    int length = GetNonDuplicatesId(nonDuplicates);
    int resId = 100000 + GenerateRand(10000, 99000, nonDuplicates, length);   //index + 1   index <-> len of nonDup

    ReservationInfo.reservationId = resId;
    strcpy(ReservationInfo.reservationStatus, "unconfirmed");

    puts("This is Your information");
    printf("Name: %s\n", ReservationInfo.customerName);
    printf("NationalId: %s\n", ReservationInfo.customerNational_Id);
    printf("Email: %s\n", ReservationInfo.customerEmail);
    printf("mobileNumber: %s\n", ReservationInfo.mobileNumber);
    printf("numOfNights: %d\n", ReservationInfo.numOfNights);
    printf("Date: %d %d %d\n", ReservationInfo.date.days, ReservationInfo.date.months, ReservationInfo.date.years);
    printf("reservationStatus: %s\n", ReservationInfo.reservationStatus);
    printf("ReservationID: %d\n", ReservationInfo.reservationId);
    printf("Room: %d\n", ReservationInfo.room.number);
    AddReservation(ReservationInfo);
}

void MakeReservation() {  //take data & add it to res file
    puts("Reservation...");
    Reservation ReservationInfo;

    int valid = 0;
    //take name
    do {
        puts("Please enter your Name.");
        fflush(stdin);
        gets(ReservationInfo.customerName);
        valid = is_vaild_name(ReservationInfo.customerName);
    }while (valid == 0);

    valid = 0;
    system("cls");
    //take national id
    do {
        puts("Please enter your National Id.");
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
    char buffer[100];
    do
    {
        puts("Please enter the Number of Nights.");
        scanf("%s", buffer);
        valid = valid_room_nights(buffer);
    } while (valid == 0);
    ReservationInfo.numOfNights = atoi(buffer);

    int first_time_flag = 1;
    do {
        if (first_time_flag == 0)
            puts("Sorry this Category not available");
        //system("cls");
        puts("Room category..");
        char choice_Category = UserRoomChoice();
        switch (choice_Category) {
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
    }while (ReservationInfo.room.number == 0);
    strcpy(ReservationInfo.room.status, "Reserved");

    GenerateReservationID(ReservationInfo);
    printf("Reservation Done\n");
    getch();

}

void CheckOut() {
    system("cls");
    puts("Check Out...");
    puts("Please enter your room number or Reservation Id.");
    int input;
    scanf("%d",&input);

    Reservation reservationData[100];
    reservationLoad(reservationData);
    int index = 0;  //need to save to call cancelReservation function
    int flag = 0;  //indicate that this process is available or not

    while (reservationData[index].terminator != -1) {
        if (reservationData[index].room.number == input || reservationData[index].reservationId == input) {
            if (strcmp(StrToLower(reservationData[index].reservationStatus),"confirmed") == 0) {
                flag = 1;
                break;
            }
        }
        index++;
    }

    if (flag == 0) {
        fflush(stdin);
        puts("Sorry Your input is Wrong or The reservations is Unconfirmed.");
        puts("Try again press 1.\n"
             "Exit press any character.");
        char choice = getch();
        if (choice == '1')
            CheckOut();
        else
            exit(0);
    }

    int roomNumber = reservationData[index].room.number;     // get if Data true or confirmed

    //calc Bill
    Room roomData[100];
    LoadRooms(roomData);
    int i = 0;
    int bill;

    while (roomData[i].terminator != -1) {  //calc bill
        if (roomData[i].number == roomNumber) {
            bill = roomData[i].price;
            break;
        }
        i++;
    }

    //check out done
    puts("The Check Out is Done.");
    printf("This is your Bill %d.\n",bill);
    ChangeRoomStatus(roomNumber,"Available"); //edit room status
    DeleteReservationEntry(reservationData,index);
}





