#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"

void delay(int);
void add_student();
void check_student();

typedef enum {
    check = 1,
    add = 2,
    del = 3,
    chg = 4,
    qt = 5
} CHOOSE;

int main(void)
{
    while (1)
    {
        system("cls");
        printf("MENU:\n1) Check student info \n2) Add new student \n3) Delete student \n4) Change student info \n5) Quit\n");
        CHOOSE chooser;
        scanf(" %d", &chooser);

        switch (chooser)
        {
        case check:
            check_student();
            break;

        case add:
            add_student();
            break;

        case del:
            
            break;

        case chg:
            /* code */
            break;
        
        case qt:
            system("cls");
            printf("Bye!\n");
            delay(1);
            return 0;

        default:
            system("cls");
            printf("This command is doesn't exist!\n\n");
            delay(2);
            break;
        }
    }

    return 0;
}
