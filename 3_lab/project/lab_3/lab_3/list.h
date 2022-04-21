#pragma once
#ifndef APP_H
#include "app.h"
#endif // !APP_H

#define LIST_H

struct TablesItem {
	struct TablesItem* pPrev;
	struct TablesItem* pNext;
	Table* pTable;
};

typedef struct {
	struct TablesItem* pTop;
} TablesList;

/*
* �������������� ������ ������
* ������ (TablesList*):
* > NULL - �������;
* NULL - �� �������.
*/
TablesList* tablesListInit();

/*
* �������� ������������� �������
* ���������:
* (int) ms1 - ������ 1-�� ������������ ������;
* (int) ms2 - ������ 1-�� ������������ ������.
* ������ (Table*):
* > NULL - �������;
* NULL - �� �������.
*/
Table* createTable(int, int);

/*
* ���� ������� ������ ������
* ���������:
* (TablesList*) pTablesList - ��������� �� ������;
* (Table*) pTable - ��������� �� ������� �������.
* ������ (struct TablesItem*):
* > NULL - �������;
* NULL - �� �������.
*
*/
struct TablesItem* tablesListSearchItem(TablesList*, Table*);

/*
* ��������� ����� ������� � ������ ������
* ���������:
* (TablesList*) pTablesList - ��������� �� ������ ������;
* (Table*) pTable - ��������� �� ����������� �������.
* ������ (int):
* 0 - �������;
* 1 - �� ������� (pTable == NULL);
* 2 - �� ������� (������� ��� � ������);
* 3 - �� ������� (����� � ��������� ������).
*/
int tablesListAddItem(TablesList*, Table*);

/*
* ������� ������� �� ������ ������
* ���������:
* (TablesList*) pTablesList - ��������� �� ������ ������;
* (Table*) pTable - ��������� �� ��������� �������.
* ������ (int):
* 0 - �������;
* 1 - �� ������� (������� �� �������).
*/
int tablesListDeleteItem(TablesList*, Table*);

/*
* ������� ������ ������
* ���������:
* (TablesList*) pTablesList - ��������� �� ������ ������.
* ������ (int):
* 0 - �������;
* 1 - �� ������� (������� �������� ��������; ��������� ��������� ������).
*/
int tablesListDelete(TablesList*);