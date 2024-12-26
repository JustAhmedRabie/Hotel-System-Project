#ifndef MENNA_H
#define MENNA_H

void LoadRooms(Room roomsData[]);
int is_vaild_name(const char *name);
int is_vaild_mobil(const char*mobil);
int is_vaild_Date(Date date );
int isValidEmail(const char *email);
int is_valid_nationalid(const char* nationalid);
int valid_room_nights(char* numOfNights);
void display_reservations_for_date();

#endif
