#include "Utility.h"


int CmpRes(Reservation res1, Reservation res2)
{
    if (res1.date.years > res2.date.years)
    {
        return -1;
    }
    else if (res1.date.years < res2.date.years)
    {
        return 1;
    }
    
    if (res1.date.months > res2.date.months) return -1;
    
    else if (res1.date.months < res2.date.months) return 1;
    
    if (res1.date.days > res2.date.days) return -1;
    
    else if (res1.date.days < res2.date.days) return 1;

    return 0;
}

void SortRes(Reservation resData[])
{
    if (resData == NULL || resData[0].terminator == -1) return;

    int i = 0;

    while (resData[i + 1].terminator != -1)
    {
        int swap = 0;
        int j = 0;
        while (resData[j + 1].terminator != -1)
        {
            if (CmpRes(resData[j], resData[j + 1]) == 1)
            {
                Reservation resTemp = resData[j];
                resData[j] = resData[j + 1];
                resData[j + 1] = resTemp;
                swap = 1;
            }
            j++;
        }
        if (!swap) break;
        i++;
    }
}

void NameToUpper(char* str)
{
    int flag = 1;

    while (*str)
    {
        if (isspace(*str))
        {
            flag = 1;
        }
        else if (flag && isalpha(*str))
        {
            *str = toupper(*str);
            flag = 0;
        }
        else
        {
            *str = tolower(*str);
        }
        str++;
    }
}

void NormAndCapital(char* str)
{
    if (str == NULL) return;
    normalizeName(str);
    NameToUpper(str);
}

int GenerateRand(int min, int max, int nonDuplicates[], int n)
{
    if (n == 0) return (rand() % (max - min + 1) + min);
    if (n >= max - min + 1)
    {
        printf(RED"Error: All possible numbers have been generated!\n"RESET);
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
    }
    while (!isUnique);

    return newNumber;
}

char *StrToLower(char *str)
{
    char *p = malloc(strlen(str) + 1);
    char *result = p;
    while (*str)
    {
        *p = tolower(*str);
        p++;
        str++;
    }
    *p = '\0';
    return result;
}

void normalizeName(char* str)
{
    //ok
    char* src = str; // Pointer to traverse the input string
    char* dest = str; // Pointer to write the processed string
    int inSpace = 0; // To ensure that repeated spaces are not included

    // Skip leading spaces
    while (isspace(*src))
    {
        src++;
    }
    /* just handling the first and last excessive spaces , the inside spaces is the the
       user responsibility , only the excessive will be handled !!
     */
    // Traverse through the string
    while (*src)
    {
        if (isspace(*src))
        {
            // If it's a space and we're not already in a space sequence
            if (dest > str && !inSpace)
            {
                *dest++ = ' '; // Add a single space
                inSpace = 1; // Mark that we're in a space sequence , to skip the rest spaces !!
            }
        }
        else
        {
            // If it's a regular character, convert to lowercase
            *dest++ = tolower(*src);
            inSpace = 0; // Reset space marker
        }
        src++;
    }

    // Null-terminate the modified string
    *dest = '\0';

    // Remove trailing spaces
    while (dest > str && isspace(*(dest - 1)))
    {
        *(--dest) = '\0';
    }
}

int ExitChoice(char input[], int size)
{
    int i = 0;
    while (i < size + 1)
    {
        int c = getch();
        if (c == SKIP_SEQ_PREFIX_1 || c == SKIP_SEQ_PREFIX_2)
        {
            getch(); //to take actual code
            continue; //to skip i++
        }
        if (c == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i -= 1;
            }
            continue;
        }

        if (c == '\n' || c == '\r')
        {
            input[i] = '\0';
            printf("\n");
            return 1;
        }

        if (c == 27)
        {
            return -1;
        }
        input[i] = c;
        printf("%c", input[i]);
        i++;
    }
    printf("\n");
    return 0;
}