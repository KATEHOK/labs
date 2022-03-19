#pragma once
#define STACK_H


typedef struct {
	Release* pRelease;
} Stack;

/*
* Инициализирует стек.
* Параметры:
* (Stack*) pStack - указатель  на стек;
* (int) len - длина вектора (если используется стек-вектор).
* Вернет:
* 0 - успешно;
* 1 - неуспешно.
*/
int stackInit(Stack*, int);


int stackPush(Stack*, char*);


int stackCopy(Stack*, char**);


int stackPop(Stack*, char**);

/*
* Освобождает память, выделенную под стек.
* Параметры:
* (Stack*) pStack - указатель на стек.
*/
void stackFree(Stack*);