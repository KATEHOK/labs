//
// Created by DigitalWorm on 04.03.2022.
//

#ifndef V2_STACK_H
#define V2_STACK_H

typedef struct {
    int len;
    int top;
    char** ppData;
} StackVector;

typedef struct {
    void* pPrevious;
    char* pData;
} ListItem;
typedef struct {
    ListItem* pTop;
} StackList;

int stackInit(void**, int, int*, int*);
int setLogicType(int*);
int stackPush(void**, int, char*);
int stackVectorPush(void**, char*);
int stackListPush(void**, char*);
int stackPop(void**, int, char**);
void stackClean(void**, int);
void stacksClean(void**, int, int, int);

#endif //V2_STACK_H
