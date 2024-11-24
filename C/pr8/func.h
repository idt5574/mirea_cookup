#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

typedef struct tag_coords
{
    int x, y;
} COORDINATES;

typedef struct tag_character
{
    COORDINATES crd;
} CHARACTER;

int check_coordinates(COORDINATES* ar, int len, COORDINATES arg)
{
    for(int i = 0; i < len; i++)
        if(ar[i].x == arg.x && ar[i].y == arg.y)
            return 1;
    return 0;
}

void output_map(char* map[], CHARACTER person)
{
    system("cls");
    for (int i = 0; i < 10; i++) {
        if(i == person.crd.y)
        {
            for(int j = 0; j < 11; j++)
            {
                if(j != person.crd.x)
                    printf("%c", map[i][j]);
                else
                    printf("i");
            }
            printf("║\n");
        } else
            printf("%s", map[i]);
    }
}

void output_commands(COORDINATES crd)
{
    COORDINATES w_block[9] = {{3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {6, 7}};
    COORDINATES a_block[9] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {7, 6}};
    COORDINATES s_block[9] = {{3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {6, 5}};
    COORDINATES d_block[9] = {{10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7}, {10, 8}, {5, 6}};

    char w;
    char a;
    char s;
    char d;

    if(check_coordinates(w_block, 9, crd) != 1)
        w = 'w';
    else w = ' ';

    if(check_coordinates(a_block, 9, crd) != 1)
        a = 'a';
    else a = ' ';

    if(check_coordinates(s_block, 9, crd) != 1)
        s = 's';
    else s = ' ';

    if(check_coordinates(d_block, 9, crd) != 1)
        d = 'd';
    else d = ' ';

    printf("%c%c%c%c\n", w, a, s, d);    
    return;
}

void show_ui(char* map[], CHARACTER person, bool is_map_show, bool is_commands_show)
{
    if(is_commands_show)
        output_map(map, person);
    
    if(is_commands_show)
        output_commands(person.crd);

    return;
}