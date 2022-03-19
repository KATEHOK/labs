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

int setFormula(char** ppFormula, int* pLen) {
    int status, i;
    char* pSupport;
    *pLen = 131;
    pSupport = (char*)malloc((*pLen) * sizeof(char));
    if (pSupport == NULL) {
        printf("|-> Memory request was declined!\n");
        return 1;
    }
    printf("Enter infix formula without spaces\n");
    status = scanf_s("%128s", pSupport + 1, (int)(((*pLen) - 1) * sizeof(char)));
    pSupport[0] = '(';
    pSupport[(*pLen) - 1] = '\0';
    i = 0;
    while (pSupport[i] != '\0')
        i++;
    if (i == (*pLen) - 1) {
        printf("|-> Wrong size of string!\n");
        free(pSupport);
        return 1;
    }
    pSupport[i] = ')';
    pSupport[i + 1] = '\0';
    i += 2;
    *ppFormula = (char*)malloc(i * sizeof(char));
    if (*ppFormula == NULL) {
        printf("|-> Memory request was declined!\n");
        free(pSupport);
        return 1;
    }
    strcpy_s(*ppFormula, i * sizeof(char), pSupport, ((*pLen) - 1) * sizeof(char));
    *pLen = i;
    free(pSupport);
    printf("Formula will be compiled = %s\n", *ppFormula);
    return 0;
}

int processOpenBracket(Stack* pMain, Stack* pBracket, Stack* pFragment, char* pData, int previous) {
    int status;
    char* pTrash;
    if (previous == 2) {
        status = stackPop(pFragment, &pTrash);
        if (status == 1) {
            printf("|-> Error with process open bracket!\n");
            return 1;
        }
        status = stackPush(pFragment, pData);
        if (status == 1) {
            printf("|-> Error with process open bracket!\n");
            return 1;
        }
    }
    else if (previous == 0) {
        status = stackPush(pFragment, pData);
        if (status == 1) {
            printf("|-> Error with process open bracket!\n");
            return 1;
        }
    }
    status = stackPush(pMain, pData);
    if (status > 0) {
        printf("|-> Error with process open bracket!\n");
        return 1;
    }
    status = stackPush(pBracket, pData);
    if (status > 0) {
        printf("|-> Error with process open bracket!\n");
        return 1;
    }
    return 0;
}

int processCloseBracket(Stack* pBracket, Stack* pFragment) {
    int status;
    char* pTrash;
    status = stackPop(pFragment, &pTrash);
    if (status == 1) {
        printf("|-> Error with process close bracket!\n");
        return 1;
    }
    status = stackPop(pBracket, &pTrash);
    if (status == 1) {
        printf("|-> Error with process close bracket!\n");
        return 1;
    }
    return 0;
}

int processPlusMinus(Stack* pMain, Stack* pSupport, Stack* pBracket, char* pData) {
    int status;
    char* pLastBracket, * pTmp;
    status = stackPush(pSupport, pData);
    if (status > 0) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    status = stackCopy(pBracket, &pLastBracket);
    if (status == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    status = stackPop(pMain, &pTmp);
    if (status == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    while (pTmp != pLastBracket) {
        status = stackPush(pSupport, pTmp);
        if (status > 0) {
            printf("|-> Error with process plus minus!\n");
            return 1;
        }
        status = stackPop(pMain, &pTmp);
        if (status == 1) {
            printf("|-> Error with process plus minus!\n");
            return 1;
        }
    }
    status = stackPush(pMain, pLastBracket);
    if (status > 0) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    status = stackPush(pMain, pData);
    if (status > 0) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    status = stackPop(pSupport, &pTmp);
    if (status == 1) {
        printf("|-> Error with process plus minus!\n");
        return 1;
    }
    while (pTmp != pData) {
        status = stackPush(pMain, pTmp);
        if (status > 0) {
            printf("|-> Error with process plus minus!\n");
            return 1;
        }
        status = stackPop(pSupport, &pTmp);
        if (status == 1) {
            printf("|-> Error with process plus minus!\n");
            return 1;
        }
    }
    return 0;
}

int processMulDiv(Stack* pMain, Stack* pSupport, Stack* pFragment, char* pData) {
    char* pLastFragment, * pTmp = NULL;
    int status;
    status = stackPop(pFragment, &pLastFragment);
    if (status == 1) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    status = stackPush(pSupport, pData);
    if (status > 0) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    while (pTmp != pLastFragment) {
        status = stackPop(pMain, &pTmp);
        if (status == 1) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
        status = stackPush(pSupport, pTmp);
        if (status > 0) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
    }
    status = stackPush(pMain, pData);
    if (status > 0) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    status = stackPop(pSupport, &pTmp);
    if (status == 1) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    while (pData != pTmp) {
        status = stackPush(pMain, pTmp);
        if (status > 0) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
        status = stackPop(pSupport, &pTmp);
        if (status == 1) {
            printf("|-> Error with process mul div!\n");
            return 1;
        }
    }
    status = stackPush(pFragment, pData);
    if (status > 0) {
        printf("|-> Error with process mul div!\n");
        return 1;
    }
    return 0;
}

int processParam(Stack* pMain, Stack* pFragment, char* pData, int previous) {
    int status;
    char* pTrash;
    status = stackPush(pMain, pData);
    if (status > 0) {
        printf("|-> Error with process parameter!\n");
        return 1;
    }
    if (previous == 0) {
        status = stackPush(pFragment, pData);
        if (status > 0) {
            printf("|-> Error with process parameter!\n");
            return 1;
        }
    }
    else if (previous == 2) {
        status = stackPop(pFragment, &pTrash);
        if (status == 1) {
            printf("|-> Error with process parameter!\n");
            return 1;
        }
        status = stackPush(pFragment, pData);
        if (status > 0) {
            printf("|-> Error with process parameter!\n");
            return 1;
        }
    }
    return 0;
}
