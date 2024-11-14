#include <stdio.h>

int main(void)
{
    int a = 0;
    FILE* f = fopen("info/total_students", "wb");
    fwrite(&a, sizeof(int), 1, f);
    fclose(f);
}