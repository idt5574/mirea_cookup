#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include "func.h"

typedef struct tag_character CHARACTER;
typedef struct tag_coords COORDINATES;
typedef struct tag_item ITEM;

int check_coordinates(COORDINATES*, int, COORDINATES);
void show_ui(char* map[], CHARACTER person, bool* condition, int* icl);

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    char c = '\0';
    int inv_cursor_location = 0;

    bool output_condition[4] = {true, true, true, false};
    bool is_inventory_open = false;
    
    // Define the new character position
    CHARACTER new_character = {.crd.x = 5, .crd.y = 5, {}, 0};
    ITEM new_item = {"item\0", 0};
    new_character.inventory[0] = &new_item;
    new_character.count_of_items++;
    
    COORDINATES border_w[9] = {{3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {6, 7}};
    COORDINATES border_a[9] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {7, 6}};
    COORDINATES border_s[9] = {{3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {6, 5}};
    COORDINATES border_d[9] = {{10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7}, {10, 8}, {5, 6}};

    // Use pointers to strings for each row (allocate memory)
    char *map[10] = {
        malloc(13), malloc(13), malloc(13), malloc(13), malloc(13),
        malloc(13), malloc(13), malloc(13), malloc(13), malloc(13)
    };

    const char *initial_map[] = {
        "╔========╗\0", "║        ║\0", "║        ║\0", "║        ║\0",
        "║        ║\0", "║        ║\0", "║   #    ║\0", "║        ║\0",
        "║        ║\0", "╚========╝\0"
    };

    for (int i = 0; i < 10; i++) {
        strncpy(map[i], initial_map[i], 16);
    }

    // for (int i = 0; i < 10; i++) {
    // printf("MAP[%d]: %s\n", i, map[i]);
    // }

    // Print the modified map
    show_ui(map, new_character, output_condition, &inv_cursor_location);

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
            show_ui(map, new_character, output_condition, &inv_cursor_location);
            c = '\0'; 
        } else if(c == 'a')
        {
            if(check_coordinates(border_a, 9, new_character.crd) == 1)
            {
                c = '\0';
                continue;
            }

            new_character.crd.x -= 1;
            show_ui(map, new_character, output_condition, &inv_cursor_location);
            c = '\0';
        } else if(c == 's')
        {
            if(check_coordinates(border_s, 9, new_character.crd) == 1)
            {
                c = '\0';
                continue;
            }

            new_character.crd.y += 1;
            show_ui(map, new_character, output_condition, &inv_cursor_location);
            c = '\0'; 
        } else if(c == 'd')
        {
            if(check_coordinates(border_d, 9, new_character.crd) == 1)
            {
                c = '\0';
                continue;
            }

            new_character.crd.x += 1;
            show_ui(map, new_character, output_condition, &inv_cursor_location);
            c = '\0'; 
        } else if(c == 'h')
        {
            if(output_condition[1])
                output_condition[1] = false;
            else output_condition[1] = true;

            show_ui(map, new_character, output_condition, &inv_cursor_location);
            c = '\0'; 
        } else if(c == 'c')
        {
            if(output_condition[2])
                output_condition[2] = false;
            else output_condition[2] = true;

            show_ui(map, new_character, output_condition, &inv_cursor_location);
            c = '\0'; 
        } else if(c == 'e')
        {
            if(output_condition[3])
                output_condition[3] = false;
            else output_condition[3] = true;

            show_ui(map, new_character, output_condition, &inv_cursor_location);
            c = '\0'; 
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
