#pragma once

/*
* ������� ������ �������� � ����������� ��������
* ���������:
* (char*) pQuestion - ������ � ������������;
* (char**) ppArray - ������ ��������� ��������;
* (int) len - ����� �������.
* ������:
* -1 - ����� �����;
* 0 - �����;
* >0 - ��������.
*/
int console(char*, char**, int);

/*
* ����������� ���� ����� � ������, ��������� ����� ������� � �������
* ���������:
* (Table*) pTable - ��������� �� �������.
* ������:
* 0 - ������� (�� ��������� ���������� �����);
* 1 - ����� �����.
*/
//pTable --> oTable (offset), pKey --> oKey (offset)
int dInsertItem(Table*);

/*
* 
*/
//pTable --> oTable (offset), pKey --> oKey (offset)
int dDeleteItem(Table*);
