#pragma once


/*
* ����������� � ������������� �����.
* ���������:
* (int*) pNum - ���������, ���� ���������� �����.
* ������:
* 0 - �������;
* 1 - ���������;
*/
int getNum(int*);

/*
* ����������� � ������������� ����������� �����.
* ���������:
* (int*) pNum - ���������, ���� ���������� �����.
* ������:
* 0 - �������;
* 1 - ���������;
*/
int getNat(int*);

/*
* ����������� � ������������� ����� �����.
* ���������:
* (int*) pNum - ���������, ���� ���������� �����.
* ������:
* 0 - �������;
* 1 - ���������;
*/
int getInt(int*);

/*
* �������������� ������ �����.
* ���������:
* (Stack*) pMain - ��������� �� ������� ����;
* (Stack*) pSupport - ��������� �� ���� ���������� ����������;
* (Stack*) pBracket - ��������� �� ���� ������;
* (Stack*) pFragment - ��������� �� ���� ����������;
* (int*) pLen - ��������� �� ����� ������� (���� ������������ ����-������).
* ������:
* 0 - �������;
* 1 - ���������.
*/
int stacksInit(Stack*, Stack*, Stack*, Stack*, int*);

/*
* ����������� ������, ���������� ��� ������ �����.
* ���������:
* (Stack*) pMain - ��������� �� ������� ����;
* (Stack*) pSupport - ��������� �� ���� ���������� ����������;
* (Stack*) pBracket - ��������� �� ���� ������;
* (Stack*) pFragment - ��������� �� ���� ����������.
*/
void stacksFree(Stack*, Stack*, Stack*, Stack*);

/*
* ����������� � ������������� �������, ���������� ����� �����-�������.
* ���������:
* (char**) ppFormula - ��������� �� ������ (�� ������);
* (int*) pLen - ��������� �� ����� �������.
* ������:
* 0 - �������;
* 1 - ���������.
*/
int setFormula(char**, int*);

/*
* ������������ �������� ������.
* ���������:
* (Stack*) pMain - ��������� �� �������� ����;
* (Stack*) pBracket - ��������� �� ���� ������;
* (Stack*) pFragment - ��������� �� ���� ����������;
* (char*) pData - ��������� �� �������������� ������;
* (int) previous - ��� ���������� �������� (0, 1, 2, 3, 4).
* ������:
* 0 - �������;
* 1 - ���������.
*/
int processOpenBracket(Stack*, Stack*, Stack*, char*, int);

/*
* ������������ �������� ������.
* ���������:
* (Stack*) pBracket - ��������� �� ���� ������
* (Stack*) pFragment - ��������� �� ���� ����������.
* ������:
* 0 - �������;
* 1 - ���������.
*/
int processCloseBracket(Stack*, Stack*);

/*
* ������������ �������� �������� � ���������.
* (Stack*) pMain - ��������� �� �������� ����;
* (Stack*) pSupport - ��������� �� ���� ���������� ����������;
* (Stack*) pBracket - ��������� �� ���� ������;
* (char*) pData - ��������� �� �������������� ������.
* ������:
* 0 - �������;
* 1 - ���������.
*/
int processPlusMinus(Stack*, Stack*, Stack*, char*);

/*
* ������������ �������� ��������� � �������.
* (Stack*) pMain - ��������� �� �������� ����;
* (Stack*) pSupport - ��������� �� ���� ���������� ����������;
* (Stack*) pFragment - ��������� �� ���� ����������;
* (char*) pData - ��������� �� �������������� ������.
* ������:
* 0 - �������;
* 1 - ���������.
*/
int processMulDiv(Stack*, Stack*, Stack*, char*);

/*
* ������������ ����������.
* ���������:
* (Stack*) pMain - ��������� �� �������� ����;
* (Stack*) pFragment - ��������� �� ���� ����������;
* (char*) pData - ��������� �� �������������� ������;
* (int) previous - ��� ���������� �������� (0, 1, 2, 3, 4).
* ������:
* 0 - �������;
* 1 - ���������.
*/
int processParam(Stack*, Stack*, char*, int);

/*
* �������� ���������������� �������.
* (Stack*) pMain - ��������� �� �������� ����;
* (Stack*) pSupport - ��������� �� ���� ���������� ����������;
* (int) len - ����� ������� (�������).
* ������:
* 0 - �������;
* 1 - ���������.
*/
int printCompiled(Stack*, Stack*, int);