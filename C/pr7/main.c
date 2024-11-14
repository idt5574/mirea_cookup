#include <stdio.h>

enum {
    max_fio_length = 128,
    _fio = 1,
    _id = 2,
    _age = 3, 
    _year = 4
};

typedef struct tag_student
{
    char fio[max_fio_length];
    int id;
    short age;
    short year;
} STUDENT;

int main(void)
{


    return 0;
}