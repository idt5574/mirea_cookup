#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {
    max_fio_length = 128,
    max_path_length = 15
};

typedef struct tag_student
{
    char fio[max_fio_length];
    int id;
    short age;
    short year;
} STUDENT;

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

void add_student()
{
    STUDENT new_student;
    FILE* ts;
    FILE* ls;
    int total_students;
    char students[1024][128];
    int count = 0;
    char path[max_path_length];

    // Считываем из total_students количество объявленных студентов
    ts = fopen("info/total_students", "rb");
    fread(&total_students, sizeof(int), 1, ts);
    fclose(ts);

    // Открываем список студентов на считывание
    ls = fopen("info/student.list", "rb");

    // Считываем данные в массив students
    while (count < total_students && fread(&students[count], sizeof(students[count]), 1, ls) == 1)
        count++;
    
    system("cls");
    printf("Starting adding new student...\n");
    printf("Input FIO: ");
    scanf(" %[^\n]s", &new_student.fio);

    // Проверяем, существует ли уже студент с таким ФИО
    for(int i = 0; i < total_students; i++)
    {
        // Если существует - предупреждаем об этом пользователя
        if(strcmp(new_student.fio, students[i]) == 0)
        {
            int x;
            printf("Student with that FIO is already exits. \nIf you need change his data\nyou can use \"Change student info\" function!\nAbort the addition of a new student? \n(1 - Yes)\n");
            scanf("%d", &x);
            if(x == 1)
            {
                printf("Aborting...\n");
                delay(2);
                return;
            } else
                printf("Continued, new student will be added...\n");
        }
    }

    printf("Input age: ");
    scanf("%d", &new_student.age);

    printf("Input year of education: ");
    scanf("%d", &new_student.year);

    printf("ID of the new student: %d\n", total_students);

    // Задаём новому студенту следующий свободный айди
    new_student.id = total_students;
    strcpy(students[total_students++], new_student.fio);

    // Открываем total_students на ввод и сохраняем новое значение
    ts = fopen("info/total_students", "wb");
    fwrite(&total_students, sizeof(int), 1, ts);
    fclose(ts);

    // Открываем student.list на ввод и переносим массив students
    ls = fopen("info/student.list", "wb");
    fwrite(&students, sizeof(char[128]), total_students, ls);
    fclose(ls);

    // Создаем файл, где будет храниться информация о новом студенте
    sprintf(path, "info/%d", new_student.id);
    ls = fopen(path, "wb");
    fwrite(&new_student, sizeof(STUDENT), 1, ls);
    fclose(ls);

    printf("New student is successful created!\n");
    delay(2);
}

void check_student()
{
    STUDENT curent_student;
    int total_students;
    int check;
    int count = 0;
    FILE* ts;
    FILE* ls;
    char students[1024][128];
    char path[max_path_length];
    char curent_fio[128];

    // Считываем количество студентов
    ts = fopen("info/total_students", "rb");
    fread(&total_students, sizeof(int), 1, ts);
    fclose(ts);

    // Открываем список студентов на считывание
    ls = fopen("info/student.list", "rb");

    // Считываем данные в массив students
    while (count < total_students && fread(&students[count], sizeof(students[count]), 1, ls) == 1)
        count++;

    fclose(ls);

    // Спрашиваем пользователя, по какому полю он хочет найти студента
    system("cls");
    printf("Starting cheking student info...\n");
    printf("How you want to check? \n1) By FIO \n2) By ID\n");
    scanf(" %d", &check);

    if(check == 1) {
        // Ввод ФИО
        printf("Input FIO: ");
        scanf(" %[^\n]s", &curent_fio);

        // Поиск студента с введённым фио
        for(int i = 0; i < total_students; i++)
        {
            if(strcmp(curent_fio, students[i]) == 0)
            {
                // Создаём путь к файлу
                sprintf(path, "info/%d", i);
                // Открываем файл с информацией о студенте и переносим в переменную curent_student
                ls = fopen(path, "rb");
                fread(&curent_student, sizeof(STUDENT), 1, ls);
                fclose(ls);

                // Выводим информацию о студенте
                printf("Student info: \nID: %d\nFIO: %s \nAge: %d \nYear of education: %d\nInput anything to exit...\n", curent_student.id, curent_student.fio, curent_student.age, curent_student.year);
                scanf(" %s", &curent_fio);
                printf("Exiting...");
                delay(1);
                return;
            }
        }

        // Если студент с таким ФИО не найден, завершаем процесс
        printf("Student with this FIO does not exist!\nAborting process...");
        delay(2);
        return;
    } else if(check == 2)
    {
        // Запрашиваем на ввод ID студента
        int id;
        printf("Input ID: ");
        scanf(" %d", &id);

        // Проверям, существует ли студент с таким ID
        if(id > total_students)
        {
            printf("Student with this ID does not exist!\nAborting process...");
            delay(2);
            return;
        }

        // Создаём путь к файлу
        sprintf(path, "info/%d", id);
        // Открываем файл с информацией о студенте и переносим в переменную curent_student
        ls = fopen(path, "rb");
        fread(&curent_student, sizeof(STUDENT), 1, ls);
        fclose(ls);

        // Выводим информацию о студенте
        printf("Student info: \nID: %d\nFIO: %s \nAge: %d \nYear of education: %d\nInput anything to exit...\n", curent_student.id, curent_student.fio, curent_student.age, curent_student.year);
        scanf(" %s", &curent_fio);
        printf("Exiting...");
        delay(1);
        return;
    } else {
        printf("This command does not exist!\nAborting process...");
        delay(2);
        return;
    }
}

void del_student()
{
    FILE* ts;
    FILE* stlist;
    int total_students;
    char students_list[1024][max_fio_length];
    char FIO[max_fio_length];
    int id, chooser, count = 0;
    char path[max_path_length];

    // Открываем total_students на считывание и переносим значение в переменную total_students
    ts = fopen("info/total_students", "rb");
    fread(&total_students, sizeof(int), 1, ts);
    fclose(ts);

    // Открываем student.list на считывание и переносим значения в массив строк students_list
    stlist = fopen("info/student.list", "rb");

    while (count < total_students && fread(&students_list[count], sizeof(students_list[count]), 1, stlist) == 1)
        count++;
    
    // Очищаем консоль и спрашиваем пользователя по какому параметру нужно удалить пользователя
    system("cls");
    
    // printf("DEBUG: \ntotal_students = %d \nstudents_list: ", total_students);
    // for(int i = 0; i < total_students; i++)
    //     printf("%s\n", students_list[i]);
    // printf("DEBUG ENDED!\n");   

    printf("By which parameter you want to delete? \n1) FIO \n2) ID\n");
    scanf(" %d", &chooser);

    if(chooser == 1)
    {
        // Просим пользователя ввести ФИО
        printf("Input FIO: ");
        scanf(" %[^\n]s", &FIO);

        // Ищем студента с заданным ФИО
        for(int i = 0; i < total_students; i++)
            if(strcmp(students_list[i], FIO) == 0)
            {
                // Если найден, спрашиваем, действительно пользователь хочет его удалить
                printf("Student finded!\nYou really want to delete him?\n(1 - Yes)\n");
                scanf(" %d", &chooser);
                
                if(chooser == 1)
                {
                    // Удаляем файл, хранящий информацию о студенте
                    sprintf(path, "info/%d", i);
                    remove(path);

                    // Удаляем упоминание о студенте из списка
                    for(int j = i; j < total_students; j++)
                        strcpy(students_list[i], students_list[i + 1]);
                    
                    // Уменьшаем количество студентов на 1
                    total_students--;
                    
                    // Сохраняем в файлах total_students и student.list новые значения
                    ts = fopen("info/total_students", "wb");
                    fwrite(&total_students, sizeof(int), 1, ts);
                    fclose(ts);

                    stlist = fopen("info/student.list", "wb");
                    fwrite(&students_list, sizeof(char[128]), total_students, stlist);
                    fclose(stlist);
                    
                    // Сообщаем пользователю об успешном удалении и завершаем процесс
                    printf("Student successful deleted! \nExiting...");
                    delay(2);
                    return;
                } else 
                {
                    printf("Aborting process...\n");
                    delay(2);
                    return;
                }
            }
        printf("Student with this FIO doesn't exits!\nExiting...");
        delay(2);
        return;
    }  else if(chooser == 2)
    {
        // Запрашиваем ID
        printf("Input ID: ");
        scanf(" %d", &id);

        if(id >= total_students)
        {
            printf("Student with this ID doesn't exits!\nAborting process...");
            delay(2);
            return;
        }

        // Удаляем файл студента
        sprintf(path, "info/%d", id);
        remove(path);

        for(int i = id; i < total_students; i++)
            strcpy(students_list[i], students_list[i + 1]);
        
        total_students--;

        // Сохраняем в файлах total_students и student.list новые значения
        ts = fopen("info/total_students", "wb");
        fwrite(&total_students, sizeof(int), 1, ts);
        fclose(ts);

        stlist = fopen("info/student.list", "wb");
        fwrite(&students_list, sizeof(char[128]), total_students, stlist);
        fclose(stlist);
                    
        // Сообщаем пользователю об успешном удалении и завершаем процесс
        printf("Student successful deleted! \nExiting...");
        delay(2);
        return;
    } else {
        printf("Unknown command! \nAborting process...\n");
        delay(2);
        return;
    }
}

void change_student()
{
    FILE* ts;
    FILE* sl;
    FILE* sd;
    STUDENT cur_student;
    char student_list[1024][max_fio_length];
    char cur_fio[max_fio_length];
    int id, total_students, chooser, count = 0;
    char path[max_path_length];

    // Из файла достаем total_students
    ts = fopen("info/total_students", "rb");
    fread(&total_students, sizeof(int), 1, ts);
    fclose(ts);

    // Достаём данные для student_list
    sl = fopen("info/student.list", "rb");
    while (count < total_students && fread(&student_list[count], sizeof(student_list[count]), 1, sl) == 1)
        count++;
    fclose(sl);
    
    system("cls");
    printf("By which parameter you want to change info? \n1) FIO \n2) ID \n");
    scanf(" %d", &chooser);

    if(chooser == 1)
    {
        printf("Input FIO: ");
        scanf(" %[^\n]s", &cur_fio);

        for(int i = 0; i < total_students; i++)
        if(strcmp(cur_fio, student_list[i]) == 0)
        {
            printf("Student finded! \nWhat do you want you change? \n1) FIO \n2) Age \n 3) Year \n");
            scanf(" %d", &chooser);

            // Создаем путь и считываем данные о студенте
            sprintf(path, "info/%d", i);
            sd = fopen(path, "rb");
            fread(&cur_student, sizeof(STUDENT), 1, sd);
            fclose(sd);

            if(chooser == 1) {
                char new_fio[max_fio_length];

                printf("Input NEW FIO: ");
                scanf(" %[^\n]s", &new_fio);

                // Меняем везде инфу о нём
                strcpy(student_list[i], new_fio);
                strcpy(cur_student.fio, new_fio);
                
                // Записываем новую информацию в файлы
                sl = fopen("info/student.list", "wb");
                fwrite(&student_list, sizeof(char[128]), total_students, sl);
                fclose(sl);

                sd = fopen(path, "wb");
                fwrite(&cur_student, sizeof(STUDENT), 1, sd);
                fclose(sd);
            } else if(chooser == 2)
            {
                int new_age;
                printf("Input NEW age: ");
                scanf(" %d", &new_age);
                cur_student.age = new_age;

                // Создаем путь и считываем данные о студенте
                sd = fopen(path, "wb");
                fwrite(&cur_student, sizeof(STUDENT), 1, sd);
                fclose(sd);
            } else if(chooser == 3)
            {
                printf("Input NEW year of education: ");
                scanf(" %d", &cur_student.year);

                // Создаем путь и считываем данные о студенте
                sd = fopen(path, "wb");
                fwrite(&cur_student, sizeof(STUDENT), 1, sd);
                fclose(sd);
            } else {
                printf("Unknown command! \nAborting process...");
                delay(2);
                return;
            }
        }
    } else if(chooser == 2)
    {
        printf("Input ID: ");
        scanf(" %d", &id);

        if(id >= total_students)
        {
            printf("Student with this ID doesn't exits! \nAborting process...");
            delay(2);
            return;
        }

        printf("Student finded! \nWhat do you want you change? \n1) FIO \n2) Age \n3) Year \n");
            scanf(" %d", &chooser);

            // Создаем путь и считываем данные о студенте
            sprintf(path, "info/%d", id);
            sd = fopen(path, "rb");
            fread(&cur_student, sizeof(STUDENT), 1, sd);
            fclose(sd);

            if(chooser == 1) {
            char new_fio[max_fio_length];

            printf("Input NEW FIO: ");
            scanf(" %[^\n]s", &new_fio);

            // Меняем везде инфу о нём
            strcpy(student_list[id], new_fio);
            strcpy(cur_student.fio, new_fio);
            
            // Записываем новую информацию в файлы
            sl = fopen("info/student.list", "wb");
            fwrite(&student_list, sizeof(char[128]), total_students, sl);
            fclose(sl);

            sd = fopen(path, "wb");
            fwrite(&cur_student, sizeof(STUDENT), 1, sd);
            fclose(sd);
        } else if(chooser == 2)
        {
            printf("Input NEW age: ");
            scanf(" %d", &cur_student.age);

            // Создаем путь и считываем данные о студенте
            sd = fopen(path, "wb");
            fwrite(&cur_student, sizeof(STUDENT), 1, sd);
            fclose(sd);
        } else if(chooser == 3)
        {
            printf("Input NEW year of education: ");
            scanf(" %d", &cur_student.year);

            // Создаем путь и считываем данные о студенте
            sd = fopen(path, "wb");
            fwrite(&cur_student, sizeof(STUDENT), 1, sd);
            fclose(sd);
        } else {
            printf("Unknown command! \nAborting process...");
            delay(2);
            return;
        }
    } else {
        printf("Unknown command! \nAborting process");
        delay(2);
        return;
    }
}

void show_all_students()
{
    char student_list[1024][128];
    int total_students, count = 0;
    FILE* ts;
    FILE* sl;

    // Из файла достаем total_students
    ts = fopen("info/total_students", "rb");
    fread(&total_students, sizeof(int), 1, ts);
    fclose(ts);

    // Достаём данные для student_list
    sl = fopen("info/student.list", "rb");
    while (count < total_students && fread(&student_list[count], sizeof(student_list[count]), 1, sl) == 1)
        count++;
    fclose(sl);
    
    system("cls");
    for(int i = 0; i < total_students; i++)
        printf("%d) %s\n", i, student_list[i]);

    printf("End. Input any to exit.\n");
    scanf(" %s", &student_list[0]);
    return;
}
