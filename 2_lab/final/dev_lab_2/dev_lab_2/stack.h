#pragma once
#define STACK_H


typedef struct {
	Release* pRelease;
} Stack;

/*
* �������������� ����.
* ���������:
* (Stack*) pStack - ���������  �� ����;
* (int) len - ����� ������� (���� ������������ ����-������).
* ������:
* 0 - �������;
* 1 - ���������.
*/
int stackInit(Stack*, int);


int stackPush(Stack*, char*);


int stackCopy(Stack*, char**);


int stackPop(Stack*, char**);

/*
* ����������� ������, ���������� ��� ����.
* ���������:
* (Stack*) pStack - ��������� �� ����.
*/
void stackFree(Stack*);