#include "Rabie.h"
#include "Hany.h"
#include "Akram.h"
#include "Amle.h"
#include "Menna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int printMainMenu () {
    int choice;
    printf("*******************************\n");
    printf("*      Heliopolise Hotel      *\n");
    printf("*******************************\n");
    printf("-the main menu : \n");
    printf("1. reservation\n");
    printf("2. check in \n");
    printf("3. cancel reservatoin \n");
    printf("4. check room availability \n");
    printf("5. view customer details\n");
    printf("6. Query\n");
    printf("7. reservation report \n");
    printf("8. Exit \n");
    printf("please enter your choice (1 - 7) : ");
    scanf("%d", &choice);
return choice;
}
