#pragma once
#define STACK_H


typedef struct {
	Release* pRelease;
} Stack;

int stackInit(Stack*,
#ifdef VECTOR
	int
#endif
);
int stackPush(Stack*, char*);
int stackCopy(Stack*, char**);
int stackPop(Stack*, char**);
void stackFree(Stack*);