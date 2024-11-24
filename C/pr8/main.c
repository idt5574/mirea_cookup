#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include "func.h"

typedef struct tag_character CHARACTER;
typedef struct tag_coords COORDINATES;

void output_map(char* map[], CHARACTER person);
int check_coordinates(COORDINATES*, int, COORDINATES);
void show_ui(char* map[], CHARACTER person, bool is_map_show, bool is_commands_show);

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    char c = '\0';
    
    // Define the new character position
    CHARACTER new_character = {.crd.x = 5, .crd.y = 5};
    
    COORDINATES border_w[9] = {{3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {6, 7}};
    COORDINATES border_a[9] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {7, 6}};
    COORDINATES border_s[9] = {{3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {6, 5}};
    COORDINATES border_d[9] = {{10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7}, {10, 8}, {5, 6}};

    // Use pointers to strings for each row (allocate memory)
    char *map[10] = {
        malloc(12), malloc(12), malloc(12), malloc(12), malloc(12),
        malloc(12), malloc(12), malloc(12), malloc(12), malloc(12)
    };
    
    // Initialize the map with the box characters
    strcpy(map[0], "╔════════╗\n");
    strcpy(map[1], "║        ║\n");
    strcpy(map[2], "║        ║\n");
    strcpy(map[3], "║        ║\n");
    strcpy(map[4], "║        ║\n");
    strcpy(map[5], "║        ║\n");
    strcpy(map[6], "║   #    ║\n");
    strcpy(map[7], "║        ║\n");
    strcpy(map[8], "║        ║\n");
    strcpy(map[9], "╚════════╝\n");
    
    // Print the modified map
    show_ui(map, new_character, true, true);

    while (1) { 
        if (kbhit()) { 
            c = getch(); 
        }

        if (c == 'w') {
            if(check_coordinates(border_w, 9, new_character.crd) == 1)
            {
                c = '\0';
                continue;
            }

            new_character.crd.y -= 1;
            show_ui(map, new_character, true, true);
            c = '\0'; 
            printf("x: %d; y: %d", new_character.crd.x, new_character.crd.y);
        } else if(c == 'a')
        {
            if(check_coordinates(border_a, 9, new_character.crd) == 1)
            {
                c = '\0';
                continue;
            }

            new_character.crd.x -= 1;
            show_ui(map, new_character, true, true);
            c = '\0';
            printf("x: %d; y: %d", new_character.crd.x, new_character.crd.y);
        } else if(c == 's')
        {
            if(check_coordinates(border_s, 9, new_character.crd) == 1)
            {
                c = '\0';
                continue;
            }

            new_character.crd.y += 1;
            show_ui(map, new_character, true, true);
            c = '\0'; 
            printf("x: %d; y: %d", new_character.crd.x, new_character.crd.y);
        } else if(c == 'd')
        {
            if(check_coordinates(border_d, 9, new_character.crd) == 1)
            {
                c = '\0';
                continue;
            }

            new_character.crd.x += 1;
            show_ui(map, new_character, true, true);
            c = '\0'; 
            printf("x: %d; y: %d", new_character.crd.x, new_character.crd.y);
        } else if(c == '`')
            break;
    }
    c = '\0'; 

    // Free allocated memory
    for (int i = 0; i < 10; i++) {
        free(map[i]);
    }

    return 0;
}
