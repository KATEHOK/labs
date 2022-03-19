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