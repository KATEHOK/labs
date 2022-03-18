//
// Created by DigitalWorm on 04.03.2022.
//

#include <stdio.h>
#include "funcs.h"

/*
 * Запрашивает у пользователя ввод числа.
 * Параметры:
 * (int*) pNum - указатель, куда записать число.
 * Вернёт:
 * 0 - записано число;
 * 1 - обнаружен конец файла.
 */
int getNum(int* pNum)
{
    int feedBack;
    do {
        *pNum = 0;
        feedBack = scanf_s("%d", pNum, sizeof(int));
        if (feedBack == 0) {
            // ввели не число
            scanf_s("%*c", 0);
            printf("It was NOT a NUMBER!\n");
        } else if (feedBack < 0) {
            // обнаружен конец файла
            scanf_s("%*c", 0);
            printf("|-> EOF detacted!\n\n");
            return 1;
        }
    } while (feedBack == 0);
    return 0;
}

int getInt(int* pNum)
{
    int feedback;
    printf("Enter integer number\n");
    feedback = getNum(pNum);
    return 0;
}

int getNat(int* pNum)
{
    int feedback;
    do {
        printf("Enter natural number\n");
        feedback = getNum(pNum);
        if (feedback == 1)
            return 1;
        if (*pNum < 0)
            printf("It was NOT a NATURAL number!\n");
    } while (*pNum < 1);
    printf("\n");
    return 0;
}