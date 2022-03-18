#pragma once
#define STACK_H


typedef struct {
	Release* pRelease;
} Stack;

int stackInit(Stack*);
int stackFree(Stack*);
int stackPush(Stack*, char*);
int stackCopy(Stack*, char**);
int stackPop(Stack*, char**);
