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

    // Открываем students.list на ввод и переносим массив students
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

        printf("Student with this FIO does not exist!\nAborting process...");
        delay(2);
        return;
    } else if(check == 2)
    {
        int id;
        printf("Input ID: ");
        scanf(" %d", &id);

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