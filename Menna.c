#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"
void LoadRooms(room roomsData[])
{
    FILE *roomsfile=fopen("rooms.txt","r");
    
    if(roomsfile==NULL)
    {
        printf("Error!");
        getche();
        return;
    }
    int i = 0;
    char x ='a';
    
    while(x!= EOF)
    {
        fscanf(roomsfile,"%d %s %s %d",&roomsData[i].roomNumber,roomsData[i].status,roomsData[i].category,&roomsData[i].price);
        x = fgetc(roomsfile);
        i++;
    }

    fclose(roomsfile);
}
