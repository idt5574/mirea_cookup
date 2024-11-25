#include <stdio.h>

int main() {
    int number = 1;             // Номер слова
    char word[] = "super long word";    // Слово, которое нужно вывести
    
    // Форматируем строку
    printf("║%d) %-15s║\n", number, word);

    return 0;
}
