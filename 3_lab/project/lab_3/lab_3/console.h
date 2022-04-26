#pragma once
#ifndef APP_H
#include "app.h"
#endif // !APP_H

#define CONSOLE_H

/*
* �������� ��������� ������ �����
* ���������:
* (char**) ppList - ������ �����;
* (int) lenList - ����� �������.
*/
void printList(char**, int);

/*
* ����-������
* (char*) pQuestion - ������ � ������������;
* (char**) ppList - ������ �����-��������� ��������;
* (int) lenList - ����� �������.
* ������:
* > 0 - ����� (������ + 1) ���������� ������;
* 0 - ����� �����.
*/
int console(char*, char**, int);

/*
* ������� ���������� ������� ������ ������ ��� �� ����� �� ���������
* ������:
* 1 - ������� ������ ������;
* 2 - ����� �� ���������.
*/
int startConsole();

/*
* ����-������ �������������
* ���������:
* (char*) pQuestion - ������ � ������������.
* ������:
* 1 - ��������;
* 2 - �� ��������;
* 0 - ����� �����.
*/
int confirmConsole(char*);

/*
* ���� ������ �� ���������
* ���������:
* (TablesList*) pTL - ������ ������.
* ������:
* 0 - ����� � ������;
* 1 - �� ����� � ������.
*/
int exitConsole(TablesList*);

/*
* ���������� ������������ ������� ������� ��� ������
* ���������:
* (TablesList*) pTL - ��������� �� ������ ������.
* ������:
* > NULL - ��������� �� ��������� �������;
* NULL - �� ������� ������� ������� (������ ��� ������������ ���������).
*/
Table* selectTableConsole(TablesList*);

int processSelectedTable(Table*);

int addTableConsole(TablesList*);