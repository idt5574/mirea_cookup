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

void output_map(char* ui[], char* map[], CHARACTER person)
{
    for (int i = 0; i < 10; i++) 
            strncpy(ui[i], map[i], 16);
    
    ui[person.crd.y][person.crd.x] = 'i';

    return;
}

void output_hints(char* ui[], COORDINATES crd)
{
    COORDINATES w_block[9] = {{3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {6, 7}};
    COORDINATES a_block[9] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {7, 6}};
    COORDINATES s_block[9] = {{3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {6, 5}};
    COORDINATES d_block[9] = {{10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7}, {10, 8}, {5, 6}};

    char str[7] = "    ch "; // Инициализация пустой строки с местом для `\0`

    // Проверяем блокировку и обновляем строку
    if (check_coordinates(w_block, 9, crd) != 1) str[0] = 'w';
    if (check_coordinates(a_block, 9, crd) != 1) str[1] = 'a';
    if (check_coordinates(s_block, 9, crd) != 1) str[2] = 's';
    if (check_coordinates(d_block, 9, crd) != 1) str[3] = 'd';

    strncpy(ui[10], str, 7); 
    return;
}

void output_coordinates(char* ui[], COORDINATES arg)
{
    char op[12]; 
    sprintf(op, "x: %d; y: %d\0", arg.x, arg.y);
    strncpy(ui[11], op, 12);
    return;
}

void show_ui(char* map[], CHARACTER person, bool* condition)
{
    system("cls");
    char *UI[12];
    for (int i = 0; i < 12; i++){
        UI[i] = calloc(12, sizeof(char));
        if (UI[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    if(condition[0])
        output_map(UI, map, person);
    
    if(condition[1])
        output_hints(UI, person.crd);

    if(condition[2])
        output_coordinates(UI, person.crd);
    

    for(int i = 0; i < 12; i++)
    {
        printf("%s\n", UI[i]);
    }

    for (int i = 0; i < 12; i++) {
        if (UI[i] != NULL)
            free(UI[i]);
    }
    
    return;
}