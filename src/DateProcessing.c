#include "DateProcessing.h"

int fday = 1;
int fyear = 2024;
int fmon = 1;
int limit;

Reservation today;
Reservation selection;

const char* month[] = {
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};


void CheckDayLimit(int* limit)
{
    if (fmon == 1 || fmon == 3 || fmon == 5 || fmon == 7 || fmon == 8 || fmon == 10 || fmon == 12)
    {
        *limit = 31;
    }
    else
    {
        *limit = 30;
        if (fmon == 2)
        {
            *limit = 28;
            if (fyear % 4 == 0)
            {
                *limit = 29;
            }
        }
    }
}

int Days()
{
    system("cls");
    puts(CYAN"Choose check-in date:"RESET);
    printf("\033[7;33m%d\033[0m/%s/%d", fday, month[fmon - 1], fyear);
    int ch;

    int i = fday;
    while (1)
    {
        ch = GetCode();
        if (ch == 13 || ch == 27)
        {
            return 0;
        }

        if (ch == 333)
        {
            fday = i;
            Months();
            return 0;
        }
        else if (ch == 331)
        {
            fday = i;
            Years();
            return 0;
        }
        else
        {
            CheckDayLimit(&limit);

            if (ch == 328)
            {
                if (i < limit)
                {
                    system("cls");
                    i++;
                    fday = i;
                    AdjustLimit();
                    i = fday;
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("\033[7;33m%d\033[0m/%s/%d", fday, month[fmon - 1], fyear);
                }
                else
                {
                    i = 1;
                    fday = i;
                    if (fmon >= 12)
                    {
                        fyear++;
                    }
                    fmon++;
                    AdjustLimit();
                    i = fday;
                    system("cls");
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("\033[7;33m%d\033[0m/%s/%d", fday, month[fmon - 1], fyear);
                }
            }
            if (ch == 336)
            {
                if (i <= 1)
                {
                    i--;
                    fday = i;
                    if (fmon <= 1)
                    {
                        fyear--;
                    }
                    fmon--;
                    AdjustLimit();
                    i = fday;
                    system("cls");
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("\033[7;33m%d\033[0m/%s/%d", fday, month[fmon - 1], fyear);
                }
                else
                {
                    system("cls");
                    i--;
                    fday = i;
                    AdjustLimit();
                    i = fday;
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("\033[7;33m%d\033[0m/%s/%d", fday, month[fmon - 1], fyear);
                }
            }
        }
    }
    return i;
}

void AdjustLimit(void)
{
    Reservation upperBound = today;
    upperBound.date.years += 5;

    selection.date.days = fday;
    selection.date.months = fmon;
    selection.date.years = fyear;
    if (fmon == 1 && fday < 1) fday = 31;
    if (fmon == 0 && fday < 1){ fday = 31; fmon = 12;}
    if (fday < 1 && CmpRes(selection, today) == 1) fday = 1;
    
    selection.date.days = fday;
    selection.date.months = fmon;
    selection.date.years = fyear;
    if (CmpRes(selection, today) == 1)
    {
        fday = today.date.days;
        fmon = today.date.months;
        fyear = today.date.years;
    }
    if (CmpRes(selection, upperBound) == -1)
    {
        fday = upperBound.date.days;
        fmon = upperBound.date.months;
        fyear = upperBound.date.years;
    }
    
    if (fmon < 1) fmon = 12;
    if (fmon > 12) fmon = 1;
    if (fyear < today.date.years) fyear = today.date.years;
    if (fyear > today.date.years + 5) fyear = today.date.years+5;
    CheckDayLimit(&limit);
    if (fday < 1) fday = limit;
    
    if (limit < fday)
        fday = limit;

    selection.date.days = fday;
    selection.date.months = fmon;
    selection.date.years = fyear;

    if (CmpRes(selection, today) == 1)
    {
        fday = today.date.days;
        fmon = today.date.months;
        fyear = today.date.years;
    }
    if (CmpRes(selection, upperBound) == -1)
    {
        fday = upperBound.date.days;
        fmon = upperBound.date.months;
        fyear = upperBound.date.years;
    }
}

int Months()
{
    int ch;

    int mon = fmon;


    system("cls");
    puts(CYAN"Choose check-in date:"RESET);
    printf("%d/\033[7;33m%s\033[0m/%d", fday, month[fmon - 1], fyear);
    while (1)
    {
        ch = GetCode();
        if (ch == 13 || ch == 27)
        {
            return 0;
        }
        if (ch == 331)
        {
            fmon = mon;
            Days();
            return 0;
        }
        else if (ch == 333)
        {
            fmon = mon;
            Years();
            return 0;
        }
        else
        {
            if (ch == 328 && mon < 12)
            {
                system("cls");
                mon++;
                fmon = mon;
                AdjustLimit();
                mon = fmon;
                puts(CYAN"Choose check-in date:"RESET);
                printf("%d/\033[7;33m%s\033[0m/%d", fday, month[fmon - 1], fyear);
            }
            else if (ch == 328 && mon == 12)
            {
                system("cls");
                mon = 1;
                fmon = mon;
                fyear++;
                AdjustLimit();
                mon = fmon;
                puts(CYAN"Choose check-in date:"RESET);
                printf("%d/\033[7;33m%s\033[0m/%d", fday, month[fmon - 1], fyear);
            }

            if (ch == 336 && mon > 1)
            {
                system("cls");
                mon--;
                fmon = mon;
                AdjustLimit();
                mon = fmon;
                puts(CYAN"Choose check-in date:"RESET);
                printf("%d/\033[7;33m%s\033[0m/%d", fday, month[fmon - 1], fyear);
            }
            else if (ch == 336 && mon == 1)
            {
                system("cls");
                mon = 12;
                fmon = mon;
                fyear--;
                AdjustLimit();
                mon = fmon;
                puts(CYAN"Choose check-in date:"RESET);
                printf("%d/\033[7;33m%s\033[0m/%d", fday, month[fmon - 1], fyear);
            }
            else if ((ch == 336 || ch == 328) && (mon > 12 || mon < 0))
            {
                mon = 1;
                fmon = mon;
            }
        }
    }
}

int Years()
{
    system("cls");
    puts(CYAN"Choose check-in date:"RESET);
    printf("%d/%s/\033[7;33m%d\033[0m", fday, month[fmon - 1], fyear);
    int ch;

    int i = fyear;
    while (1)
    {
        ch = GetCode();
        if (ch == 13 || ch == 27)
        {
            return 0;
        }
        if (ch == 331)
        {
            fyear = i;
            Months();
            return 0;
        }
        else if (ch == 333)
        {
            fyear = i;
            Days();
            return 0;
        }
        else
        {
            if (ch == 328)
            {
                time_t date;

                struct tm* timeinfo;

                date = time(NULL);
                timeinfo = localtime(&date);

                int curYear = timeinfo->tm_year + 1900;
                int yearLim = curYear + 5;
                
                if (i >= yearLim)
                {
                    system("cls");
                    i = yearLim;
                    fyear = i;
                    AdjustLimit();
                    i = fyear;
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("%d/%s/\033[7;33m%d\033[0m", fday, month[fmon - 1], fyear);
                }
                else
                {
                    system("cls");
                    i++;
                    fyear = i;
                    AdjustLimit();
                    i = fyear;
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("%d/%s/\033[7;33m%d\033[0m", fday, month[fmon - 1], fyear);
                }
            }
            if (ch == 336)
            {
                int curYear = today.date.years;
                
                if (i <= curYear)
                {
                    system("cls");
                    i = curYear;
                    fyear = i;
                    AdjustLimit();
                    i = fyear;
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("%d/%s/\033[7;33m%d\033[0m", fday, month[fmon - 1], fyear);
                }
                else
                {
                    system("cls");
                    i--;
                    fyear = i;
                    AdjustLimit();
                    i = fyear;
                    puts(CYAN"Choose check-in date:"RESET);
                    printf("%d/%s/\033[7;33m%d\033[0m", fday, month[fmon - 1], fyear);
                }
            }
        }
    }
}

int GetCode(void)
{
    int ch = getch();

    if (ch == 27)
    {
        time_t date;

        struct tm *timeinfo;

        date = time(NULL);
        timeinfo = localtime(&date);

        fday = timeinfo->tm_mday;
        fmon = timeinfo->tm_mon + 1;
        fyear = timeinfo->tm_year + 1900;
        printf("\033[?25h\033[0 q"); //re-enables the caret
        system("cls");
        MainMenu();
        return 0;
    }

    if (ch == 0 || ch == 224)
        ch = 256 + getch();


    return ch;
}

int GetDate(int* day, int* month, int* year, int limit)
{
    time_t date;

    struct tm *timeinfo;

    date = time(NULL);
    timeinfo = localtime(&date);

    fday = timeinfo->tm_mday;
    fmon = timeinfo->tm_mon + 1;
    fyear = timeinfo->tm_year + 1900;

    if (limit)
    {
        today.date.days = fday;
        today.date.months = fmon;
        today.date.years = fyear;
    }
    else
    {
        today.date.days = 1;
        today.date.months = 1;
        today.date.years = fyear-2;
    }

    printf("\033[?25l"); //disables the caret
    Days();

    *day = fday;
    *month = fmon;
    *year = fyear;

    fday = timeinfo->tm_mday;
    fmon = timeinfo->tm_mon + 1;
    fyear = timeinfo->tm_year + 1900;

    printf("\033[?25h\033[0 q"); //re-enables the caret
    system("cls");
}