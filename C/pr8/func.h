#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

typedef struct tag_coords
{
    int x, y;
} COORDINATES;

typedef struct tag_item
{
    char name[15];
    int name_len;
    int id;
}ITEM;

typedef struct tag_character
{
    COORDINATES crd;
    ITEM* inventory[5];
    int count_of_items;
} CHARACTER;

typedef struct tag_object
{
    char name[15];
    char action[15];
    char use_msg[25];
    void (*interact_function);
    bool is_used;
    COORDINATES interact_coordinates[4];
} OBJECT;

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

int check_coordinates(COORDINATES* ar, int len, COORDINATES arg)
{
    for(int i = 0; i < len; i++)
        if(ar[i].x == arg.x && ar[i].y == arg.y)
            return 1;
    return 0;
}

int check_obj_coordinates(OBJECT* ar_of_objects[], int len, COORDINATES arg)
{
    for(int i = 0; i < len; i++)
        for(int j = 0; j < 4; j++)
            if(ar_of_objects[i]->interact_coordinates[j].x == arg.x && ar_of_objects[i]->interact_coordinates[j].y == arg.y)
                return i;
    
    return -1;
}

void add_item(CHARACTER* character, char* name, int name_len, int id)
{
    ITEM* new_item = malloc(sizeof(ITEM));
    if (new_item == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strcpy(new_item->name, name);
    new_item->name_len = name_len;
    new_item->id = id;

    character->inventory[character->count_of_items] = new_item;
    character->count_of_items++;
}

void output_map(char* ui[], char* map[], CHARACTER person)
{
    for (int i = 0; i < 10; i++) 
            strncpy(ui[i], map[i], 16);
    
    ui[person.crd.y][person.crd.x] = 'i';

    return;
}

void output_hints(char* ui[], COORDINATES crd, bool* output_condition)
{
    COORDINATES w_block[10] = {{3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {6, 7}, {10, 2}};
    COORDINATES a_block[9] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {7, 6}};
    COORDINATES s_block[9] = {{3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {6, 5}};
    COORDINATES d_block[10] = {{10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7}, {10, 8}, {5, 6}, {9, 1}};
    COORDINATES obj_interact[2] = {{9, 1}, {10, 2}};

    char str[9] = "    ch   ";

    if(output_condition[0] && !output_condition[3] && !output_condition[6])
    {
        if (check_coordinates(w_block, 10, crd) != 1) str[0] = 'w';
        if (check_coordinates(a_block, 9, crd) != 1) str[1] = 'a';
        if (check_coordinates(s_block, 9, crd) != 1) str[2] = 's';
        if (check_coordinates(d_block, 10, crd) != 1) str[3] = 'd';
    }

    if(!output_condition[6]) str[6] = 'e';

    if(output_condition[3])
    {
        if (output_condition[4]) str[0] = 'w';
        if (output_condition[5]) str[2] = 's';
    }

    if(output_condition[6])
    {
        if (output_condition[7]) str[1] = 'a';
        if (output_condition[8]) str[3] = 'd';
    }

    if (check_coordinates(obj_interact, 2, crd) == 1) str[7] = 'f';

    strncpy(ui[10], str, 8); 
    return;
}

void output_coordinates(char* ui[], COORDINATES arg)
{
    char op[12]; 
    sprintf(op, "x: %d; y: %d\0", arg.x, arg.y);
    strncpy(ui[11], op, 12);
    return;
}

void output_inventory(char* ui[], CHARACTER person, int icl)
{
    const char *initial_inventory[9] = {
        "╔=================╗\0", 
        "║    INVENTORY    ║\0", 
        "╠=================╣\0", 
        "║                 ║\0",
        "║                 ║\0", 
        "║                 ║\0", 
        "║                 ║\0", 
        "║                 ║\0",
        "╚=================╝\0"
    };

    int written_items = 0;

    for(int i = 0; i < 3; i++)
        strncat(ui[i], initial_inventory[i], 25);
    
    for(int i = 0; i < 6; i++)
    {
        if(written_items < person.count_of_items)
        {
            char* str = malloc(25);
            if(i == icl)
                sprintf(str, "║>  %-14s║\0", person.inventory[i]->name);
            else
                sprintf(str, "║%d) %-14s║\0", i + 1, person.inventory[i]->name);
            
            strncat(ui[i + 3], str, 25);
            written_items++;
            free(str);
        } else{
            strncat(ui[i + 3], initial_inventory[i + 3], 25);
        }
    }

    return;
}

void output_obj_menu(char* ui[], CHARACTER character, int mcl, OBJECT obj)
{
    char* msg = malloc(27);

    if(mcl == 0){
        sprintf(msg, "You see the %s. %s it?\0", obj.name, obj.action);
        strncpy(ui[13], msg, 27);
        strncpy(ui[14], ">Yes | No\0", 10);
    } else if(mcl == 1){
        sprintf(msg, "You see the %s. %s it?\0", obj.name, obj.action);
        strncpy(ui[13], msg, 27);
        strncpy(ui[14], " Yes | No<\0", 11);
    } else if(mcl == 2)
    {
        strncpy(ui[13], obj.use_msg, 27);
    } else if(mcl == 3)
    {
        sprintf(msg, "You already used %s!\0", obj.name);
        strncpy(ui[13], msg, 27);
    }

    free(msg);

    return;
}

void show_ui(char* map[], CHARACTER person, bool* output_condition, int icl, OBJECT* obj, int mcl)
{
    system("cls");
    char *UI[16];
    for (int i = 0; i < 16; i++){
        UI[i] = calloc(32, sizeof(char));
        if (UI[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    if(output_condition[0])
        output_map(UI, map, person);
    
    if(output_condition[1])
        output_hints(UI, person.crd, output_condition);

    if(output_condition[2])
        output_coordinates(UI, person.crd);

    if(output_condition[3])
        output_inventory(UI, person, icl);
    
    if(output_condition[6])
        output_obj_menu(UI, person, mcl, *obj);


    for(int i = 0; i < 16; i++)
    {
        printf("%s\n", UI[i]);
    }

    for (int i = 0; i < 16; i++) {
        if (UI[i] != NULL)
            free(UI[i]);
    }
    
    return;
}

void move_on_obj_menu(char* map[], CHARACTER* character, bool* output_condition, OBJECT* obj)
{
    char c;
    char* str;
    int menu_cursor_location = 0;

    output_condition[8] = true;
    show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);

    while(1)
    {
        if(kbhit()) {
            c = getch();
        }

        if(c == 'd')
        {
            c = '\0';
            if(menu_cursor_location == 0)
            {
                output_condition[8] = false;
                output_condition[7] = true;
                menu_cursor_location++;

                show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);
            }
            continue;
        } else if(c == 'a')
        {
            c = '\0';
            if(menu_cursor_location == 1)
            {
                output_condition[8] = true;
                output_condition[7] = false;
                menu_cursor_location--;

                show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);
            }
            continue;
        } else if(c == 'f')
        {
            c = '\0';

            if(menu_cursor_location == 0)
            {
                output_condition[8] = false;
                output_condition[7] = false;

                if(!obj->is_used)
                {
                    obj->is_used = true;
                    menu_cursor_location = 2;
                    add_item(character, "Staff\0", 7, 3);
                    show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);
                    output_condition[6] = false;
                    delay(2);
                    show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);
                    return;
                } else
                {
                    menu_cursor_location = 3;
                    show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);
                    output_condition[6] = false;
                    delay(2);
                    show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);
                    return;
                }
            } else
            {
                output_condition[8] = false;
                output_condition[7] = false;
                output_condition[6] = false;
                show_ui(map, *character, output_condition, 0, NULL, 0);
                return;
            }

            continue;
        } else if(c == 'h')
        {
            c = '\0';
            if(output_condition[1])
                output_condition[1] = false;
            else output_condition[1] = true;

            show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);
            continue;
        } else if(c == 'c')
        {
            c = '\0';
            if(output_condition[2])
                output_condition[2] = false;
            else output_condition[2] = true;

            show_ui(map, *character, output_condition, 0, obj, menu_cursor_location);

            continue;
        }
    }
}

void move_on_inventory(char* map[], CHARACTER* character, bool* output_condition)
{
    char c;
    int icl = 0;

    output_condition[4] = false;

    if(character->count_of_items < 2)
        output_condition[5] = false;

    show_ui(map, *character, output_condition, icl, NULL, 0);

    while(1)
    {
        if (kbhit()) { 
            c = getch(); 
        }

        if(c == 'w')
        {
            c = '\0';
            if(icl > 0)
            {
                icl--;

                if(icl == 0)
                    output_condition[4] = false;
                
                if(!output_condition[5])
                    output_condition[5] = true;

                show_ui(map, *character, output_condition, icl, NULL, 0);
            }
            continue;
        } else if(c == 's') 
        {
            c = '\0';
            if(icl < character->count_of_items - 1)
            {
                icl++;

                if(icl == character->count_of_items - 1)
                    output_condition[5] = false;

                if(!output_condition[4])
                    output_condition[4] = true;

                show_ui(map, *character, output_condition, icl, NULL, 0);
            }
            continue;
        } else if(c == 'h')
        {
            c = '\0';
            if(output_condition[1])
                output_condition[1] = false;
            else output_condition[1] = true;

            show_ui(map, *character, output_condition, icl, NULL, 0);
        } else if(c == 'c')
        {
            c = '\0';
            if(output_condition[2])
                output_condition[2] = false;
            else output_condition[2] = true;

            show_ui(map, *character, output_condition, icl, NULL, 0);

            continue;
        } else if(c == 'e')
        {
            c = '\0';
            output_condition[3] = false;
            output_condition[4] = true;
            output_condition[5] = true;
            return;
        }
    }
}

void move_on_map(char* map[], CHARACTER* character, bool* output_condition, OBJECT* ar_of_obj[])
{
    char c;

    COORDINATES border_w[10] = {{3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {6, 7}, {10, 2}};
    COORDINATES border_a[9] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {7, 6}};
    COORDINATES border_s[9] = {{3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {8, 8}, {9, 8}, {10, 8}, {6, 5}};
    COORDINATES border_d[10] = {{10, 1}, {10, 2}, {10, 3}, {10, 4}, {10, 5}, {10, 6}, {10, 7}, {10, 8}, {5, 6}, {9, 1}};
    COORDINATES obj_interact[2] = {{9, 1}, {10, 2}};

    show_ui(map, *character, output_condition, 0, NULL, 0);

    // 
    while (1) { 
        if (kbhit()) { 
            c = getch(); 
        }

        if (c == 'w') {
            c = '\0';
            if(check_coordinates(border_w, 10, character->crd) == 1)
                continue;


            character->crd.y -= 1;
            show_ui(map, *character, output_condition, 0, NULL, 0);

            continue;
        } else if(c == 'a')
        {
            c = '\0';
            if(check_coordinates(border_a, 9, character->crd) == 1)
                continue;
            
            character->crd.x -= 1;
            show_ui(map, *character, output_condition, 0, NULL, 0);

            continue;
        } else if(c == 's')
        {
            c = '\0';
            if(check_coordinates(border_s, 9, character->crd) == 1)
                continue;


            character->crd.y += 1;
            show_ui(map, *character, output_condition, 0, NULL, 0); 

            continue;
        } else if(c == 'd')
        {
            c = '\0';
            if(check_coordinates(border_d, 10, character->crd) == 1)
                continue;
            

            character->crd.x += 1;
            show_ui(map, *character, output_condition, 0, NULL, 0);

            continue;
        } else if(c == 'h')
        {
            c = '\0';
            if(output_condition[1])
                output_condition[1] = false;
            else output_condition[1] = true;

            show_ui(map, *character, output_condition, 0, NULL, 0);

            continue;
        } else if(c == 'c')
        {
            c = '\0';
            if(output_condition[2])
                output_condition[2] = false;
            else output_condition[2] = true;

            show_ui(map, *character, output_condition, 0, NULL, 0);

            continue;
        } else if(c == 'e')
        {
            c = '\0';
            output_condition[3] = true;
            
            move_on_inventory(map, character, output_condition);
            show_ui(map, *character, output_condition, 0, NULL, 0);
            output_condition[3] = false;

            continue;
        } else if(c == 'f') 
        {
            c = '\0';
            int obj_index = check_obj_coordinates(ar_of_obj, 1, character->crd);

            if(obj_index != -1)
            {
                output_condition[6] = true;
                move_on_obj_menu(map, character, output_condition, ar_of_obj[obj_index]);
            }

            continue;
        } else if(c == '`')
        {
            break;
        }
    }
}

void free_inventory(CHARACTER* character) {
    for (int i = 0; i < character->count_of_items; i++) {
        free(character->inventory[i]);
    }
    character->count_of_items = 0;
}
