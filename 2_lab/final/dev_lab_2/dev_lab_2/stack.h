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

/*
* ��������� � ���� ���� ��������.
* ���������:
* (Stack*) pStack - ��������� �� ����;
* (char*) pData - ��������� �� ������.
* ������:
* 0 - ������;
* 1 - ��������� (������������ �����-�������);
* 2 - ��������� (������ ������ �����-������).
*/
int stackPush(Stack*, char*);

/*
* �������� �� ����� ���� ��������.
* ���������:
* (Stack*) pStack - ��������� �� ����;
* (char**) ppData - ��������� �� ��������� �� ������.
* ������:
* 0 - ������;
* 1 - ��������� (���� ����).
*/
int stackCopy(Stack*, char**);

/*
* �������� � ������� �� ����� ���� ��������.
* ���������:
* (Stack*) pStack - ��������� �� ����;
* (char**) ppData - ��������� �� ��������� �� ������.
* ������:
* 0 - ������;
* 1 - ��������� (���� ����).
*/
int stackPop(Stack*, char**);

/*
* ����������� ������, ���������� ��� ����.
* ���������:
* (Stack*) pStack - ��������� �� ����.
*/
void stackFree(Stack*);