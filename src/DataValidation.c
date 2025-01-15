#include "DataValidation.h"
#include <regex.h>

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
    const char* regex_pattern =
        "^[a-zA-Z0-9][._]?[a-zA-Z0-9]+([-._][a-zA-Z0-9]+(_?[a-zA-Z0-9]+)*)*@[a-zA-Z0-9]+([-.][a-zA-Z0-9]+)*\\.[a-zA-Z]{2,4}$";

    regex_t regex;
    int ret = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (ret)
    {
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
        return 0;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    
    regfree(&regex);

    if (ret)
        puts(RED"ERROR! Email is Invalid!!\n"RESET);
    
    return ret == 0;
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
