#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"
void LoadRooms(room roomsData[])
{
    FILE *roomsfile=fopen("rooms.txt","r");
    
        if(roomsfile==NULL){
        printf("Error!");
        getche();
        return;}
        int i=0;char x='a';
        while(!feof(roomsfile))
        {
        fscanf(roomsfile,"%d %s %d %s",roomsData[i].roomNumber,roomsData[i].category,roomsData[i].price,roomsData[i].status);
        x = fgetc(roomsfile);
        i++;}}
