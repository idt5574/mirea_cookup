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
typedef struct tag_object OBJECT;

void add_item(CHARACTER* character, char* name, int name_len, int id);
void move_on_map(char* map[], CHARACTER* character, bool* output_condition, OBJECT* ar_of_obj[]);
void free_inventory(CHARACTER* character);

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    char c = '\0';
    int inv_cursor_location = 0;

    bool output_condition[9] = {true, true, true, false, true, true, false, false, false};
    /* Conditions: 
        0 - map
        1 - hints
        2 - coordinates
        3 - inventory
        4 - move up in inventory
        5 - move down in inventory
        6 - object menu
        7 - move left in obj menu
        8 - move right in obj menu
    */
    
    // Define the new character position
    CHARACTER new_character = {.crd.x = 5, .crd.y = 5, {}, 0};

    add_item(&new_character, "Sword\0", 7, 0);
    add_item(&new_character, "Axe\0", 5, 1);
    add_item(&new_character, "Pickaxe\0", 9, 2);

    OBJECT new_object_1 = {"object", "Use", "You used the object!\0", NULL, 0, {{10, 2}, {9, 1}, {-1, -1}, {-1, -1}}};

    OBJECT* ar_of_objs[1] = {&new_object_1};

    //Use pointers to strings for each row (allocate memory)
    char *map[10] = {
        malloc(13), malloc(13), malloc(13), malloc(13), malloc(13),
        malloc(13), malloc(13), malloc(13), malloc(13), malloc(13)
    };

    const char *initial_map[] = {
        "╔========╗\0", "║       ?║\0", "║        ║\0", "║        ║\0",
        "║        ║\0", "║        ║\0", "║   #    ║\0", "║        ║\0",
        "║        ║\0", "╚========╝\0"
    };

    // Copy init_map to map
    for (int i = 0; i < 10; i++) {
        strncpy(map[i], initial_map[i], 16);
    }

    move_on_map(map, &new_character, output_condition, ar_of_objs);
    free_inventory(&new_character);
    return 0;
}
