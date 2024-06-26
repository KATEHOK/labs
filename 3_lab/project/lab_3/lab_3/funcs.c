﻿#ifndef APP_H
#include "app.h"
#endif // !APP_H


int getNum(int* pNum)
{
    int status;
    do {
        *pNum = 0;
        status = scanf_s("%d", pNum, sizeof(int));
        if (status == 0) {
            // ввели не число
            scanf_s("%*c", 0);
            printf("It was NOT a NUMBER!\n");
        }
        else if (status < 0) {
            // обнаружен конец файла
            scanf_s("%*c", 0);
            printf("|-> EOF detacted!\n");
            return 1;
        }
    } while (status == 0);
    return 0;
}

int getNat(int* pNum) {
    int status;
    do {
        printf("Enter natural number\n");
        status = getNum(pNum);
        if (status == 1)
            return 1;
        if (*pNum < 1)
            printf("It was NOT a NATURAL number!\n");
    } while (*pNum < 1);
    return 0;
}

int getInt(int* pNum) {
    int status;
    printf("Enter integer number\n");
    status = getNum(pNum);
    return status;
}