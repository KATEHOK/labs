//
// Created by DigitalWorm on 04.03.2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"
#include "stack.h"

/*
 * Устанавливает тип используемой структуры.
 * Параметры:
 * (int*) pType - указатель на число.
 * Вернет:
 * 0 - значение успешно установлено;
 * 1 - значение не было успешно установлено.
 */
int setLogicType(int* pType)
{
    int feedback;
    do {
        printf("\nLet's set type of logic structure\n0 - vector, 1 - list\n");
        feedback = getInt(pType);
        if (feedback == 1) {
            printf("|-> Error with input naturel number!\n");
            return 1;
        }
        if (*pType > 1 || *pType < 0)
            printf("Wrong type of logic structure!\n");
    } while(*pType > 1 || *pType < 0);
    return 0;
}

/*
 * Инициализирует стеки.
 * В случае ошибок собирает мусор.
 * Параметры:
 * (void**) ppvStack - указатель на "массив" стеков;
 * (int) count - количество стеков;
 * (int*) pType - указатель на тип стека:
 * 0 - стек-вектор;
 * 1 - стек-список.
 * Вернет:
 * 0 - если стеки были проинициализированы;
 * 1 - если стеки не были проинициализированы
 */
int stackInit(void** ppvStack, int count, int* pType, int* pStackLen)
{
    int size, feedback, i, j;
    void* copy;

    feedback = setLogicType(pType);
    if (feedback == 1) {
        printf("|-> Error with setting type of logic structure\n");
        return 1;
    }

    if (*pType == 0) {
        size = sizeof(StackVector);
        if (*pStackLen < 1) {
            printf("Set length of stack\n");
            feedback = getNat(pStackLen);
            if (feedback == 1) {
                printf("|-> Error with setting length of stack!\n");
                return 1;
            }
        }
    }
    else {
        size = sizeof(StackList);
    }
    *ppvStack = NULL;
    *ppvStack = malloc(size * count);
    if (*ppvStack == NULL) {
        printf("|-> Memory request was declined!\n");
        return 1;
    }

    copy = *ppvStack;
    for (i = 0; i < count; i++) {
        if (*pType == 0) {
            ((StackVector*)copy)->top = 0;
            ((StackVector*)copy)->len = *pStackLen;
            ((StackVector*)copy)->ppData = (char**)malloc(sizeof(char*) * ((StackVector*)copy)->len);
//            printf("Malloc %p\n", ((StackVector*)*ppvStack)->ppData);
            if (((StackVector*)copy)->ppData == NULL) {
                printf("|-> Memory request was declined!\n");
                copy = *ppvStack;
                for (j = 0; j < i; j++) {
                    free(((StackVector*)copy)->ppData);
                    copy += size;
                }
                free(*ppvStack);
                return 1;
            }
        } else {
            ((StackList*)copy)->pTop = NULL;
        }
        copy += size;
    }
    return 0;
}

/*
 * Добавляет указатель на элемент в стек-вектор.
 * Параметры:
 * (void**) ppvStack - указатель на "массив" стеков;
 * (char*) pNew - указатель на новый элемент.
 * Вернет:
 * 0 - если элемент успешно добавлен;
 * 1 - если элемент не добавлен успешно.
 */
int stackVectorPush(void** ppvStack, char* pNew)
{
    if (((StackVector*)*ppvStack)->top == ((StackVector*)*ppvStack)->len) {
        printf("|-> Stack overflow Error!\n");
        return 1;
    }
    ((StackVector*)*ppvStack)->ppData[((StackVector*)*ppvStack)->top] = pNew;
    ((StackVector*)*ppvStack)->top++;
    return 0;
}

/*
 * Добавляет в стек-список новый элемент.
 * Ошибки не вызывают утечку памяти.
 * Параметры:
 * (void**) ppvStack - указатель на указатель на стек;
 * (char*) pNew - указатель на новый элемент.
 * Вернет:
 * 0 - если элемент создан успешно;
 * 1 - если элемент не удалось создать.
 */
int stackListPush(void** ppvStack, char* pNew)
{
    ListItem tmp;
    tmp.pPrevious = (void*)(((StackList*)*ppvStack)->pTop);
    ((StackList*)*ppvStack)->pTop = (ListItem*)malloc(sizeof(ListItem));
    if (((StackList*)*ppvStack)->pTop == NULL) {
        printf("|-> Memory request was declined!\n");
        ((StackList*)*ppvStack)->pTop = (ListItem*)(tmp.pPrevious);
        return 1;
    }
    *(((StackList*)*ppvStack)->pTop) = tmp;
    ((StackList*)*ppvStack)->pTop->pData = pNew;
    return 0;
}

/*
 * Вызывает функцию добавления нового элемента.
 * Параметры:
 * (void**) ppvStack - указатель на указатель на стек;
 * (int) type - тип стека (0 или 1);
 * (char*) pNew - указатель на новый элемент.
 * Вернет:
 * 0 - новый элемент добавлен;
 * 1 - новый элемент не был добавлен.
 */
int stackPush(void** ppvStack, int type, char* pNew)
{
    int feedback;
    if (type == 0)
        feedback = stackVectorPush(ppvStack, pNew);
    else
        feedback = stackListPush(ppvStack, pNew);
    if (feedback == 1) {
        printf("|-> Error with pushing!\n");
        return 1;
    }
    return 0;
}

/*
 * Считывает указатель на символ из верхнего элемента,
 * убивает верхний элемент, собирает мусор.
 * Параметры:
 * (void**) ppvStack - указатель на указатель на стек;
 * (int) type - тип стека (0 или 1);
 * (char**) ppData - указатель  на указатель на символ.
 * Вернет:
 * 0 - если считывание прошло успешно;
 * 1 - если считывание не прошло успешно.
 */
int stackPop(void** ppvStack, int type, char** ppData)
{
    ListItem* tmp;
    if (type == 0) {
        if (((StackVector*)*ppvStack)->top == 0) {
            printf("|-> Error popping! Stack is free!\n");
            return 1;
        }
        ((StackVector*)*ppvStack)->top--;
        *ppData = ((StackVector*)*ppvStack)->ppData[((StackVector*)*ppvStack)->top];
    } else {
        if (((StackList*)*ppvStack)->pTop == NULL) {
            printf("|-> Error popping! Stack is free!\n");
            return 1;
        }
        *ppData = ((StackList*)*ppvStack)->pTop->pData;
        tmp = ((StackList*)*ppvStack)->pTop;
        ((StackList*)*ppvStack)->pTop = (ListItem*)(tmp->pPrevious);
        free(tmp);
    }
    return 0;
}

/*
 * Перебирает стек и очищает память.
 * Параметры:
 * (void**) ppvStack - указатель на указатель на стек;
 * (int) type - тип стека (0 или 1).
 */
void stackClean(void** ppvStack, int type) {
    ListItem* tmp;
    if (type == 0)
        free(((StackVector*)*ppvStack)->ppData);
    else {
        while (((StackList*)*ppvStack)->pTop != NULL) {
            tmp = ((StackList*)*ppvStack)->pTop;
            ((StackList*)*ppvStack)->pTop = (ListItem*)(tmp->pPrevious);
            free(tmp);
        }
    }
}

/*
 * Перебирает "массив" стеков для очистки памяти.
 * Параметры:
 * (void**) ppvStack - указатель на "массив" стеков;
 * (int) type - тип стека (0 или 1);
 * (int) size - размер стека;
 * (int) count - количество стеков.
 */
void stacksClean(void** ppvStack, int type, int size, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        stackClean(ppvStack, type);
        *ppvStack += size;
    }
    free(*ppvStack - size * count);
}