//
// Created by DigitalWorm on 04.03.2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "compile.h"
#include "stack.h"

int compile() {
    // инициализация переменных и указателей на стеки
    int i, feedback, stackType, stackSize, flashback = 0, stackLen = 128, stacksCount = 4;
    void *pvStack, *pvMainStack, *pvSupportStack, *pvBracketStack, *pvFragmentStack;
    char* pData, *pCopy;

    // выделяем память для хранения строки-формулы
    pData = (char*)malloc((stackLen + 2) * sizeof(char));
    if (pData == NULL) {
        printf("|-> Memory request was declined!\n");
        return 1;
    }
    *pData = '(';
    for (i = 0; i < stackLen + 2; i++)
        printf("%c", pData[i]);
    printf("\n");

    // запрашиваем ввод формулы
    printf("Enter formula without spaces (max length == %d symbols).\n", stackLen);
    scanf("%128s", pData + sizeof(char));
    // определяем реальную длину формулы
    i = 0;
    while (pData[i] != 0)
        i++;
    stackLen = i + 1;
    // переопределяем память
    pData = (char*)realloc(pData, sizeof(char) * (stackLen + 1));
    pData[stackLen - 1] = ')';
    pData[stackLen] = '\0';
    printf("%s --- %d\n", pData, stackLen);

    // инициализация стеков (в случае ошибок работает сборщик мусора)
    feedback = stackInit(&pvStack, stacksCount, &stackType, &stackLen);
    if (feedback == 1) {
        printf("|-> Stack init Error!\n");
        return 1;
    }
    // определяем размер стека в памяти
    if (stackType == 0)
        stackSize = sizeof(StackVector);
    else
        stackSize = sizeof(StackList);
    // для удобства пользования определяем указатели на специфические стеки
    pvMainStack = pvStack;
    pvSupportStack = stackSize + pvMainStack;
    pvBracketStack = stackSize + pvSupportStack;
    pvFragmentStack = stackSize + pvBracketStack;
    // стеки готовы к работе

    // перебираем формулу и вызываем соответствующие функции обработки
    pCopy = pData;
    for (i = 0; i < stackLen; i++) {
        if (*pCopy == '(') {
            feedback = processOpenBracket(pCopy, stackType, flashback, pvMainStack, pvBracketStack, pvFragmentStack);
            flashback = 0;
            if (feedback == 1) {
                printf("|-> Error with process something!\n");
                free(pData);
                stacksClean(&pvStack, stackType, stackSize, stacksCount);
                return 1;
            }
        } else if (*pCopy == ')') {
            feedback = processCloseBracket(stackType, pvBracketStack, pvFragmentStack);
            flashback = 1;
            if (feedback == 1) {
                printf("|-> Error with process something!\n");
                free(pData);
                stacksClean(&pvStack, stackType, stackSize, stacksCount);
                return 1;
            }
        } else if (*pCopy == '+' || *pCopy == '-') {
            feedback = processPlusMinus(pCopy, stackType, pvMainStack, pvSupportStack, pvBracketStack);
            flashback = 2;
            if (feedback == 1) {
                printf("|-> Error with process something!\n");
                free(pData);
                stacksClean(&pvStack, stackType, stackSize, stacksCount);
                return 1;
            }
        } else if (*pCopy == '*' || *pCopy == '/') {
            feedback = processMulDiv(pCopy, stackType, pvMainStack, pvSupportStack, pvFragmentStack);
            flashback = 3;
            if (feedback == 1) {
                printf("|-> Error with process something!\n");
                free(pData);
                stacksClean(&pvStack, stackType, stackSize, stacksCount);
                return 1;
            }
        } else if (*pCopy == ' ') {
            pCopy++;
            continue;
        } else {
            feedback = processLiteral(pCopy, stackType, flashback, pvMainStack, pvFragmentStack);
            if (feedback == 1) {
                printf("|-> Error with process something!\n");
                free(pData);
                stacksClean(&pvStack, stackType, stackSize, stacksCount);
                return 1;
            }
        }
        pCopy++;
    }

    printCompiled(stackType, stackLen, pvMainStack, pvSupportStack);

    // сбор мусора
    free(pData);
    stacksClean(&pvStack, stackType, stackSize, stacksCount);
    return 0;
}

/*
 * Печатает скомпиллированную формулу.
 * Параметры:
 * (int) stackType - тип стека (0 или 1);
 * (int) len - длина введенной строки;
 * (void*) pvMainStack - указатель на основной стек;
 * (void*) pvSupportStack - указатель на вспомогательный стек.
 */
void printCompiled(int stackType, int len, void* pvMainStack, void* pvSupportStack)
{
    char* pTmp;
    char bufer[len];
    int feedback, i = 0;
    feedback = stackPop(&pvMainStack, stackType, &pTmp);
    while (feedback == 0) {
        feedback = stackPush(&pvSupportStack, stackType, pTmp);
        feedback = stackPop(&pvMainStack, stackType, &pTmp);
    }
    feedback = 0;
    while (feedback == 0) {
        feedback = stackPop(&pvSupportStack, stackType, &pTmp);
        if (feedback == 0 && *pTmp != '(' && *pTmp != ')') {
            bufer[i] = *pTmp;
            i++;
        }
    }
    bufer[i] = '\0';
    printf("Compiled: %s\n", bufer);
}

/*
 * Обрабатывает открытую скобку.
 * (char*) pData - указатель на новый символ;
 * (int) stackType - тип стека (0 или 1);
 * (int) flashback - код предыдущей операции (0, 1, 2 или 3);
 * (void*) pvMainStack - указатель на основной стек;
 * (void*) pvBracketStack - указатель на стек скобок;
 * (void*) pvFragmentStack - указатель на стек фрагментов.
 * Вернет:
 * 0 - если символ обработан успешно;
 * 1 - если символ не был успешно обработан.
 */
int processOpenBracket(char* pData, int stackType, int flashback, void* pvMainStack, void* pvBracketStack, void* pvFragmentStack)
{
    int feedback;
    char* pTrash;
    if (flashback == 2) {
        feedback = stackPop(&pvFragmentStack, stackType, &pTrash);
        if (feedback == 1) {
            printf("|-> Error with process open bracket!\n");
            return 1;
        }
        feedback = stackPush(&pvFragmentStack, stackType, pData);
        if (feedback == 1) {
            printf("|-> Error with process open bracket!\n");
            return 1;
        }
    } else if (flashback == 0) {
        feedback = stackPush(&pvFragmentStack, stackType, pData);
        if (feedback == 1) {
            printf("|-> Error with process open bracket!\n");
            return 1;
        }
    }
    feedback = stackPush(&pvMainStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process open bracket!\n");
        return 1;
    }
    feedback = stackPush(&pvBracketStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process open bracket!\n");
        return 1;
    }
    return 0;
}

/*
 * Обрабатывает закрытую скобку.
 * (int) stackType - тип стека (0 или 1);
 * (void*) pvBracketStack - указатель на стек скобок;
 * (void*) pvFragmentStack - указатель на стек фрагментов.
 * Вернет:
 * 0 - если символ обработан успешно;
 * 1 - если символ не был успешно обработан.
 */
int processCloseBracket(int stackType, void* pvBracketStack, void* pvFragmentStack)
{
    int feedback;
    char* pTrash;
    feedback = stackPop(&pvFragmentStack, stackType, &pTrash);
    if (feedback == 1) {
        printf("|-> Error with process close bracket!\n");
        return 1;
    }
    feedback = stackPop(&pvBracketStack, stackType, &pTrash);
    if (feedback == 1) {
        printf("|-> Error with process close bracket!\n");
        return 1;
    }
    return 0;
}

/*
 * Обрабатывает опирации сложения и вычитания.
 * (char*) pData - указатель на новый символ;
 * (int) stackType - тип стека (0 или 1);
 * (void*) pvMainStack - указатель на основной стек;
 * (void*) pvSupportStack - указатель на вспомогательный стек.
 * (void*) pvBracketStack - указатель на стек скобок.
 * Вернет:
 * 0 - если символ обработан успешно;
 * 1 - если символ не был успешно обработан.
 */
int processPlusMinus(char* pData, int stackType, void* pvMainStack, void* pvSupportStack, void* pvBracketStack)
{
    int feedback;
    char* pBracket, *pTmp;
    feedback = stackPush(&pvSupportStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    feedback = stackPop(&pvBracketStack, stackType, &pBracket);
    if (feedback == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    feedback = stackPush(&pvBracketStack, stackType, pBracket);
    if (feedback == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    feedback = stackPop(&pvMainStack, stackType, &pTmp);
    if (feedback == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    while (pTmp != pBracket) {
        feedback = stackPush(&pvSupportStack, stackType, pTmp);
        if (feedback == 1) {
            printf("|-> Error with process plus minus!\n");
            return 1;
        }
        feedback = stackPop(&pvMainStack, stackType, &pTmp);
        if (feedback == 1) {
            printf("|-> Error with process plus minus!\n");
            return 1;
        }
    }
    feedback = stackPush(&pvMainStack, stackType, pBracket);
    if (feedback == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    feedback = stackPush(&pvMainStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    feedback = stackPop(&pvSupportStack, stackType, &pTmp);
    if (feedback == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    while (pTmp != pData) {
        feedback = stackPush(&pvMainStack, stackType, pTmp);
        if (feedback == 1) {
            printf("|-> Error with process plus minus!\n");
            return 1;
        }
        feedback = stackPop(&pvSupportStack, stackType, &pTmp);
        if (feedback == 1) {
            printf("|-> Error with process plus minus! 264\n");
            return 1;
        }
    }
    return 0;
}

/*
 * Обрабатывает опирации умножения и деления.
 * (char*) pData - указатель на новый символ;
 * (int) stackType - тип стека (0 или 1);
 * (void*) pvMainStack - указатель на основной стек;
 * (void*) pvSupportStack - указатель на вспомогательный стек.
 * (void*) pvFragmentStack - указатель на стек фрагментов.
 * Вернет:
 * 0 - если символ обработан успешно;
 * 1 - если символ не был успешно обработан.
 */
int processMulDiv(char* pData, int stackType, void* pvMainStack, void* pvSupportStack, void* pvFragmentStack)
{
    char* pFragment, *pTmp = NULL;
    int feedback;
    feedback = stackPop(&pvFragmentStack, stackType, &pFragment);
    if (feedback == 1) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    feedback = stackPush(&pvSupportStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    while (pTmp != pFragment) {
        feedback = stackPop(&pvMainStack, stackType, &pTmp);
        if (feedback == 1) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
        feedback = stackPush(&pvSupportStack, stackType, pTmp);
        if (feedback == 1) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
    }
    feedback = stackPush(&pvMainStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    feedback = stackPop(&pvSupportStack, stackType, &pTmp);
    if (feedback == 1) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    while(pData != pTmp) {
        feedback = stackPush(&pvMainStack, stackType, pTmp);
        if (feedback == 1) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
        feedback = stackPop(&pvSupportStack, stackType, &pTmp);
        if (feedback == 1) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
    }
    feedback = stackPush(&pvFragmentStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    return 0;
}

/*
 * Обрабатывает переменную.
 * (char*) pData - указатель на новый символ;
 * (int) stackType - тип стека (0 или 1);
 * (int) flashback - код предыдущей операции (0, 1, 2 или 3);
 * (void*) pvMainStack - указатель на основной стек;
 * (void*) pvFragmentStack - указатель на стек фрагментов.
 * Вернет:
 * 0 - если символ обработан успешно;
 * 1 - если символ не был успешно обработан.
 */
int processLiteral(char* pData, int stackType, int flashback, void* pvMainStack, void* pvFragmentStack)
{
    int feedback;
    char* pFragment;
    feedback = stackPush(&pvMainStack, stackType, pData);
    if (feedback == 1) {
        printf("|-> Error with process literal!\n");
        return 1;
    }
    if (flashback == 0) {
        feedback = stackPush(&pvFragmentStack, stackType, pData);
        if (feedback == 1) {
            printf("|-> Error with process literal!\n");
            return 1;
        }
    } else if (flashback == 2) {
        feedback = stackPop(&pvFragmentStack, stackType, &pFragment);
        if (feedback == 1) {
            printf("|-> Error with process literal!\n");
            return 1;
        }
        feedback = stackPush(&pvFragmentStack, stackType, pData);
        if (feedback == 1) {
            printf("|-> Error with process literal!\n");
            return 1;
        }
    }
    return 0;
}




