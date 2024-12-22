#ifndef AKRAM_H
#define AKRAM_H
//void LoadRoams(room *rooms); //a redundant function ... use it if you want
void normalizeName(char *str) ; //standard input
int QueryCustomerbyName(Reservation* reserved, char* name, int* indices) ; //getting the name
void QueryCustomer() ; // handle the output
//ROOMS SECTION
void QueryRoom() ;
int QueryRoom_ChoiceProcess(char choice) ;
/*By Status*/
void QueryRoomStatus() ;
void QueryRoomStatus_A() ;
void QueryRoomStatus_R() ;
int  QueryStatusbyGet(Room * roomsData, char* Option, int* indices) ;
int QueryRoom_Status_ChoiceProcess(char choice) ;
/*By NUMBER section*/
void QueryRoomNumber() ;
int  QueryRoomNumber_get(Room* roomsData, int inputNumber ) ;
//MENU SECTION
int QueryChoiceProcess(char choice) ;
void Query() ; // just call it , the others are auxiliary

// VIEW Details Section ...
void ViewCustomerDetails() ;
int V_DetailsChoiceProcess(char choice) ;
void V_Details_Res_ID() ;
int V_Details_Res_ID_get (Reservation * reservationId , int Res_ID) ;

#endif
