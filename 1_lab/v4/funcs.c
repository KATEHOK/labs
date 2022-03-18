// Created by DigitalWorm on 22.02.2022.
// Changed by DigitalWorm on 23.02.2022.

#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"

/*
 * Запрашивает у пользователя ввод числа.
 * Параметры:
 * (int*) pNum - указатель, куда записать число;
 * (int) numType - тип запрашиваемого числа:
 * 0 - натуральное;
 * 1 - целое.
 * Вернёт:
 * 0 - записано необходимое число;
 * 1 - обнаружен конец файла.
 */
int getNum(int* pNum, int numType)
{
    int feedBack;
    do {
        *pNum = 0;
        if (numType == 0)
            printf("Print Natural number (from 0 to 2147483647)\n");
        else if (numType == 1)
            printf("Print Integer number (from -2147483648 to 2147483647\n");
        else {
            printf("|-> UNKNOWN VALUE of parameter 'numType'\n");
            return 1;
        }
        feedBack = scanf_s("%d", pNum, sizeof(int));
        if (feedBack == 0) {
            // ввели не число
            scanf_s("%*c", 0);
            printf("It was NOT a NUMBER!\n\n");
        } else if (feedBack < 0) {
            // обнаружен конец файла
            scanf_s("%*c", 0);
            printf("|-> EOF detacted!\n\n");
            return 1;
        } else if (numType == 0 && *pNum <= 0) {
            // введено не натуральное число
            printf("It was NOT a NATURAL number!\n\n");
            feedBack = 0;
        }
    } while (feedBack == 0);
    return 0;
}

/*
 * Устанавливает длину.
 * Параметры:
 * (int*)  - указатель, куда будет записано значение:
 * (int)  - тип, чья длина запрашивается:
 * 0 - длина матрицы (количество строк);
 * 1 - длина строки (количество элементов).
 * Вернёт:
 * 0 - если запись произведена успешно;
 * 1 - если запись не была произведена.
 */
int setLen(int* pLen, int lenType)
{
    int flag;
    if (lenType == 0)
        printf("Print count of lines\n");
    else if (lenType == 1)
        printf("Print length of the line\n");
    flag = getNum(pLen, 0);
    if (flag == 1) {
        printf("|-> [Matrix 1] Error in setting length of the ");
        if (lenType == 0)
            printf("matrix!\n");
        else
            printf("line!\n");
    }
    return flag;
}

/*
 * Запрашивает память для массива указателей на строки.
 * Параметры:
 * (Matrix*) pMatrix - указатель на матрицу.
 * Вернет:
 * 0 - если память была выделена;
 * 1 - если память не была выделена.
 */
int askMemoryMatrix(Matrix* pMatrix)
{
    pMatrix->matrix = (Line*)malloc(pMatrix->len * sizeof(Line));
    if (pMatrix->matrix == NULL) {
        printf("|-> Giving memory for matrix Error!\n");
        return 1;
    }
    return 0;
}

/*
 * Запрашивает память для массива целых чисел.
 * Параметры:
 * (Line*) pLine - указатель на строку.
 * Вернет:
 * 0 - если память была выделена;
 * 1 - если память не была выделена.
 */
int askMemoryLine(Line* pLine)
{
    pLine->lin = (int*)malloc(pLine->len * sizeof(int));
    if (pLine->lin == NULL) {
        printf("|-> Giving memory for line Error!\n");
        return 1;
    }
    return 0;
}

/*
 * Устанавливает значение элемента.
 * Параметры:
 * (int*) pItem - указатель на элемент матрицы.
 * Вернет:
 * 0 - если установка прошла успешно;
 * 1 - если значение не было установлено успешно.
 */
int setItem(int* pItem)
{
    int flag;
    flag = getNum(pItem, 1);
    if (flag == 1)
        printf("|-> Setting item Error!\n");
    return flag;
}

/*
 * Освобождает память, выделенную под матрицу.
 * Параметры:
 * (Matrix*) pMatrix - указатель на матрицу;
 * (int) i - индекс последней строки + 1.
 */
void clean(Matrix* pMatrix, int i)
{
    int x;
    for (x = 0; x < i; x++) {
        free(pMatrix->matrix[x].lin);
    }
    free(pMatrix->matrix);
}

/*
 * Определяет, является ли число палиндромом.
 * Параметры:
 * (int) num - число.
 * Вернёт:
 * 0 - если число является палиндромом;
 * 1 - если число не является палиндромом.
 */
int isPalindrome(int num)
{
    int reverse = 0, tmp;
    if (num < 0)
        tmp = -num;
    else
        tmp = num;
    while (tmp > 0) {
        reverse *= 10;
        reverse += tmp % 10;
        tmp /= 10;
    }
    if (num < 0)
        reverse = -reverse;
    if (reverse == num)
        return 0;
    return 1;
}

/*
 * Заполняем матрицу №1.
 * Параметры:
 * (Matrix*) pMatrix - указатель на матрицу.
 * Вернет:
 * 0 - если заполнение произошло успешно;
 * 1 - если заполнение не произошло успешно (очистит память);
 */
int fillFirstMatrix(Matrix* pMatrix)
{
    int flag, i, j;
    printf("\n[Matrix 1]\n");
    for (i = 0; i < pMatrix->len; i++) {
        printf("[Line %d]\n", i + 1);
        flag = setLen(&pMatrix->matrix[i].len, 1);
        if (flag == 1) {
            printf("[Matrix 1][Line %] Input Error! Incorrect count of items!\n", i + 1);
            free(pMatrix->matrix);
            return 1;
        }

        flag = askMemoryLine(pMatrix->matrix + i);
        if (flag == 1) {
            printf("[Matrix 1][Line %d] Memory Error!\n", i + 1);
            clean(pMatrix, i);
            return 1;
        }

        for (j = 0; j < pMatrix->matrix[i].len; j++) {
            flag = setItem(&pMatrix->matrix[i].lin[j]);
            if (flag == 1) {
                printf("[Matrix 1][Line %d][Item %d] Input Error!\n", i + 1, j + 1);
                clean(pMatrix, i);
                return 1;
            }
        }
    }
    return 0;
}

/*
 * Заполняет матрицу №2.
 * Параметры:
 * (Matrix*) pMatrix_1 - указатель на матрицу №1;
 * (Matrix*) pMatrix_2 - указатель на матрицу №2.
 * Вернет:
 * 0 - если заполнение произошло успешно;
 * 1 - если заполнение не произошло успешно (очистит память).
 */
int fillSecondMatrix(Matrix* pMatrix_1, Matrix* pMatrix_2)
{
    int flag, i, j, realLen;
    for (i = 0; i < pMatrix_1->len; i++) {
        pMatrix_2->matrix[i].len = pMatrix_1->matrix[i].len;
        flag = askMemoryLine(&(pMatrix_2->matrix[i]));
        if (flag == 1) {
            printf("[Matrix 2] Giving memory Error!");
            clean(pMatrix_1, pMatrix_1->len);
            clean(pMatrix_2, i);
            return 1;
        }

        realLen = 0;

        for (j = 0; j < pMatrix_1->matrix[i].len; j++) {
            if (0 == isPalindrome(pMatrix_1->matrix[i].lin[j])) {
                pMatrix_2->matrix[i].lin[realLen] = pMatrix_1->matrix[i].lin[j];
                realLen++;
            }
        }

        pMatrix_2->matrix[i].lin = (int*)realloc(pMatrix_2->matrix[i].lin, realLen * sizeof(int));
        pMatrix_2->matrix[i].len = realLen;
    }
    return 0;
}

/*
 * Создает первую матрицу.
 * Параметры:
 * (Matrix*) pMatrix_1 - указатель на матрицу №1.
 * Вернет:
 * 0 - если матрица была создана успешно;
 * 1 - если матрица не была создана успешно.
 */
int createFirstMatrix(Matrix* pMatrix)
{
    int flag;

    flag = setLen(&pMatrix->len, 0);
    if (flag == 1) {
        printf("|-> [Matrix 1] Input Error! Incorrect count of lines!\n");
        return 1;
    }

    flag = askMemoryMatrix(pMatrix);
    if (flag == 1) {
        printf("|-> [Matrix 1] Memory Error!\n");
        return 1;
    }

    flag = fillFirstMatrix(pMatrix);
    if (flag == 1) {
        printf("|-> [Matrix 1] Filling Error!\n");
        return 1;
    }

    return 0;
}

/*
 * Создает вторую матрицу.
 * Параметры:
 * (Matrix*) pMatrix_1 - указатель на матрицу №1;
 * (Matrix*) pMatrix_2 - указатель на матрицу №2.
 * Вернет:
 * 0 - если матрица была создана успешно;
 * 1 - если матрица не была создана успешно.
 */
int createSecondMatrix(Matrix* pMatrix_1, Matrix* pMatrix_2)
{
    int flag;

    pMatrix_2->len = pMatrix_1->len;
    flag = askMemoryMatrix(pMatrix_2);
    if (flag == 1) {
        printf("|-> [Matrix 2] Memory Error!\n");
        free(pMatrix_1);
        return 1;
    }

    flag = fillSecondMatrix(pMatrix_1, pMatrix_2);
    if (flag == 1) {
        printf("|-> [Matrix 2] Filling Error!\n");
        return 1;
    }

    return 0;
}

/*
 * Печатает матрицу.
 * Параметры:
 * (Matrix*) pMatrix - указатель на матрицу;
 * (int) mNum - номер матрицы.
 */
void printMatrix(Matrix* pMatrix, int mNum)
{
    int i, j;
    Line* pLine = pMatrix->matrix;
    int* pItem;
    printf("\nMATRIX  #%d\n", mNum);
    for (i = 0; i < pMatrix->len; i++) {
        printf("[Line %d] ", i + 1);
        pItem = pLine->lin;
        for (j = 0; j < pLine->len; j++) {
            printf("%11d ", *pItem);
            pItem++;
        }
        pLine++;
        printf("\n");
    }
    /*
    for (i = 0; i < pMatrix->len; i++) {
        printf("[Line %d] ", i + 1);
        for (j = 0; j < pMatrix->matrix[i].len; j++) {
            printf("%11d ", pMatrix->matrix[i].lin[j]);
        }
        printf("\n");
    }
    */
    printf("THE END #%d\n", mNum);
}