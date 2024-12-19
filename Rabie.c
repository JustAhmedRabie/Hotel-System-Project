#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Rabie.h"
#include "Menna.h"

void LogIn()
{
    char password[30];
    char username[20];
    user users[3];

    LoadUsers(users);

    int i = 0;
    int isValid = 0;
    char choice;
    do
    {
        system("cls");
        if (i)
            puts("ERROR, Invalid Input!\n");

        printf("1. Log In\n");
        printf("2. Exit \n");

        choice = getch();

        if (choice == '1')
            break;
        else if (choice == '2')
            exit(0);

        i++;
    } while (1);

    i = 0;

    do
    {
        system("cls");
        if (i)
            puts("ERROR, Invalid Input!\n");
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
        } while (1);

        for (i = 0; i < 3; i++)
        {
            if (!strcmp(users[i].username, username) && !strcmp(users[i].password, password))
            {
                isValid = 1;
                break;
            }
        }
        i++; // Just to know if it's not the first time the user enters his information
    } while (!isValid);
    i--;

    MainMenu();
}

int GenerateRand(int min, int max, int nonDuplicates[], int n)
{
    if (n >= max - min + 1)
    {
        printf("Error: All possible numbers have been generated!\n");
        return -1; // Return an error if all unique numbers have been generated
    }
    int newNumber;
    int isUnique;

    do
    {
        newNumber = (rand() % (max - min + 1)) + min;
        isUnique = 1;

        // Check if the number has already been generated
        for (int i = 0; i < n; i++)
        {
            if (nonDuplicates[i] == newNumber)
            {
                isUnique = 0;
                break;
            }
        }
    } while (!isUnique);

    return newNumber;
}

void LoadUsers(user usersData[])
{
    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL)
    {
        printf("Error!");
        getche();
        return;
    }

    char x = 'a';
    int i = 0;

    while (x != EOF)
    {

        fscanf(userFile, "%s %s", usersData[i].username, usersData[i].password);
        x = fgetc(userFile);
        i++;
    }
    usersData[i].terminator = -1;


    fclose(userFile);
}

