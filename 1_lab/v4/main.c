#include <stdio.h>
#include "structs.h"
#include "funcs.h"

int main() {
    int flag;
    Matrix matrix_1, matrix_2;
    // автограф
    printf("Developed by KATEHOK (https://github.com/KATEHOK)\nHello, World!\n\n");
    // "создаем" матрицы
    flag = createFirstMatrix(&matrix_1);
    if (flag == 1) {
        printf("|-> [Matrix 1] Creating Error!\nClosing the program...\n");
        return 1;
    }
    flag = createSecondMatrix(&matrix_1, &matrix_2);
    if (flag == 1) {
        printf("|-> [Matrix 1] Creating Error!\nClosing the program...\n");
    }
    // "красиво" печатаем матрицы
    printMatrix(&matrix_1, 1);
    printMatrix(&matrix_2, 2);
    // возвращаем память
    clean(&matrix_1, matrix_1.len);
    clean(&matrix_2, matrix_2.len);
    printf("\nClosing the program...");
    return 0;
}
