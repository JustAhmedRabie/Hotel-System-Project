#include "DataValidation.h"

int IsValidName(const char* name)
{
    if (name[0] == '\0' || name[0] == '\n')
    {
        puts(RED "Invalid name!"RESET);
        return 0;
    }
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (strlen(name) < 4)
        {
            puts(RED "Invalid name!"RESET);

            return 0;
        }
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            printf(RED"Please enter letters only\n"RESET);
            return 0;
        }
    }
    return 1;
}

int IsValidMobile(const char* mobil)
{
    for (int i = 0; mobil[i] != '\0'; i++)
    {
        if (!isdigit(mobil[i]) && mobil[0] != '+')
        {
            printf(RED"Invalid phone number!\n"RESET);

            return 0;
        }
    }

    if (strlen(mobil) != 11)
    {
        if (mobil[0] == '+')
        {
            if (strlen(mobil+1) > 13 || strlen(mobil+1) < 11)
            {
                printf(RED"Invalid phone number!\n"RESET);
                return 0;
            }
            return 1;
        }
        printf(RED"Please enter 11 digits only\n"RESET);
        return 0;
    }
    return 1;
}

int IsValidNationalId(const char* nationalid)
{
    if (strlen(nationalid) != 14)
    {
        puts(RED"ERROR! national ID must be 14 digits!\n"RESET);

        return 0;
    }
    for (int i = 0; i < 14; i++)
    {
        if (nationalid[i] < '0' || nationalid[i] > '9')

        {
            puts(RED"ID must contain only digits!\n"RESET);
            return 0;
        }
    }
    return 1;
}

int isValidEmail(const char* email)
{
    // check if the length of the email is less than 8

    if (strlen(email) < 8)
    {
        puts(RED"ERROR! Email length must be at least 8 characters!\n"RESET);
        return 0;
    }
    char* at = strchr(email, '@');
    char* dot = strchr(email, '.');
    char* special = NULL;

    int i = 0;
    while (email[i] != '\0')
    {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '@' && email[i] != '_')
        {
            puts(RED"ERROR! Email is Invalid!!\n"RESET);
            return 0;
        }
        i++;
    }

    // Check if there is exactly one '@' and it's not the first character
    if (at == NULL || at == email)
    {
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
        return 0;
    }

    // Check if there is a '.' after the '@'
    if (dot == NULL || (dot < at + 2) && (dot <= email+2) || dot == email + strlen(email) - 1)
    {
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
        return 0;
    }

    // Ensure there's no more than one '@'
    if (strchr(at + 1, '@') != NULL)
    {
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
        return 0;
    }

    return 1;
}

int IsValidNights(char* numOfNights)
{
    if (atoi(numOfNights) > 0 && atoi(numOfNights) <= 30)
    {
        return 1;
        // valid
    }
    puts(RED"Error!, The number of nights is invalid.\nplease enter number bet.1 and 30.\n"RESET);
    return 0;
}
