#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"

void LogIn()
{
    char password[30];
    char username[20];
    user users[3];

    { //just some placeholder data, TODO: will replace with text files later
        strcpy(users[0].username, "ahmed.x");
        strcpy(users[1].username, "mohamed.y");
        strcpy(users[2].username, "mahmoud.z");

        strcpy(users[0].password, "ahmed123");
        strcpy(users[1].password, "mohamed123");
        strcpy(users[2].password, "mahmoud123");
    }

    
    int i = 0;
    int isValid = 0;
    
    do
    {
        system("cls");
        if (i) puts("ERROR, Invalid Input!\n");
        puts("Please enter your username:");
        gets(username);
        puts("Please enter your password:");
        i = 0;
        
        do
        {
            char ch = getch();
            if (ch == 13) //ASCII enter code
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
                    printf("\b \b");  // Erase previous character and move cursor back
                }
            }
            else
            {
                password[i] = ch;
                printf("*");
                i++;
            }
        }while (1);    
            
        
        for (i = 0; i < 3; i++)
        {
            if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password))
            {
                isValid = 1; break;
            }
        }
        i++; //Just to know if it's not the first time the user enters his information
    }
    while (!isValid);
    i--;
    
    //MainMenu(users[i]);
}
