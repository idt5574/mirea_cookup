#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d", &a);
    printf("%.1f", ((double) a * 3600.0) / 1000);

    return 0;
}