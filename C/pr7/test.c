#include <stdio.h>

int main(void)
{
    int a = 0;
    char st_list[1024][128];
    int pos[1024] = {-1};

    FILE* f = fopen("info/total_students", "wb");
    fwrite(&a, sizeof(int), 1, f);
    fclose(f);

    f = fopen("info/count_null_positions", "wb");
    fwrite(&a, sizeof(int), 1, f);
    fclose(f);

    f = fopen("info/null_positions", "wb");
    fwrite(&pos, sizeof(int), 1, f);
    fclose(f);

    f = fopen("info/student.list", "wb");
    fwrite(&st_list, sizeof(int), 1, f);
    fclose(f);
}