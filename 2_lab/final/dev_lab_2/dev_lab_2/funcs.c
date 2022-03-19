#ifndef A_H
#include "a.h"
#endif


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
}

int getInt(int* pNum) {
    int status;
    printf("Enter integer number\n");
    status = getNum(pNum);
    if (status == 1)
        return 1;
    return 0;
}

int stacksInit(Stack* pMain, Stack* pSupport, Stack* pBracket, Stack* pFragment, int* pLen) {
    int status;

#ifdef VECTOR
    printf("Enter length of vector\n");
    status = getNat(pLen);
    if (status == 1) {
        printf("|-> Length of vector was NOT set!\n");
        return 0;
    }
#else
    * pLen = 128;
#endif

    status = stackInit(pMain, *pLen);
    if (status == 1) {
        printf("|-> stackMain was NOT inited!\n");
        return 1;
    }
    status = stackInit(pSupport, *pLen);
    if (status == 1) {
        printf("|-> stackSupport was NOT inited!\n");
        stackFree(pMain);
        return 1;
    }
    status = stackInit(pBracket, *pLen);
    if (status == 1) {
        printf("|-> stackBracket was NOT inited!\n");
        stackFree(pMain);
        stackFree(pSupport);
        return 1;
    }
    status = stackInit(pFragment, *pLen);
    if (status == 1) {
        printf("|-> stackFragment was NOT inited!\n");
        stackFree(pMain);
        stackFree(pSupport);
        stackFree(pBracket);
        return 1;
    }
    return 0;
}

void stacksFree(Stack* pMain, Stack* pSupport, Stack* pBracket, Stack* pFragment) {
    stackFree(pMain);
    stackFree(pSupport);
    stackFree(pBracket);
    stackFree(pFragment);
}
