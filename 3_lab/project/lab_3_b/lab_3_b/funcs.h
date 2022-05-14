#pragma once

/*
* �������������� � ���������� � ���� ����� �������
* ���������:
* (Container**) ppContainer - ��������� �� ���������, ���� �������� ��������� ��������� �������;
* (char*) pName - ��� ����� ������� (������ �������� <= 16, ��������� - '\0')
* (int) maxKeyCount - ����������� ��������� ���������� ��������� �������.
* ������:
* 0 - ������� ������ ������������� � ������ � ����;
* 1 - ����� � ��������� ������ ��� ���������;
* 2 - ����� � �������� ������� � ����;
* 3 - ���������� + �� ������� ������� ��������� ��������� (������� �������� ���������).
*/
int init(Container**, char*, int);

/*
* ������� ��������� ������� � ���� � ��������
* ���������:
* (Container*) pContainer - ��������� �� ��������� ��������� �������.
* ������:
* 0 - �������� ������ �������;
* 1 - �������� ��������� ���������.
*/
int delete(Container*);

/*
* ��������� ������� � ������� (� ��������� � � ����)
* ���������:
* (Container*) pContainer - ��������� �� ��������� ��������� �������;
* (int) key - ����;
* (int) info - ����������.
* ������:
* 0 - �������;
* 1 - �������� ��������� ���������;
* 2 - �� ������� (������������ ������);
* 3 - �� ������� (������������);
* 4 - �� ������� ������� ����;
* 5 - ���������� + �� ������� ������� �� ��������� ������� (�������� ��������� ���������).
*/
int insertItem(Container*, int, int);

/*
* ������� ���� �� ��������� � �� �����
* ���������:
* (Container*) pContainer - ��������� �� ��������� ��������� �������;
* (int) key - �������� �����.
* ������:
* 0 - ���� ������� ������;
* 1 - �������� ��������� ���������;
* 2 - ���� �� ������;
* 3 - �� ������� ������� ����, ��� ���� �� ��������� ���� ��� ������ (����� ����� ��������������)
*/
int deleteItem(Container*, int);

/*
* ���� � ����� ��������� � ������� ��������� ��������� ������� � ��������� ������� � ����
* ���������:
* (Container*) pSource - ��������� �� ����������������� �������;
* (Container**) ppDestination - ��������� �� ��������� ���� �������� ��������� ������� �������;
* (int) minKey - ������ ������� ���������;
* (int) maxKey - ������� ������� ���������;
* (char*) pName - ��� ����� ������� (������-������ �������� �� 16 ��, ��������� - '\0').
* ������:
* 0 - �������� �������-��������� ������ �������;
* 1 - �������� ��������� ���������;
* 2 - �� ������� ���������������� ��������� ��������� ������� (����� � ��������� ������);
* 3 - ������ �������� ��������� �����;
* 4 - ������ �������� �������� �����;
* 5 - ������ ��������� ������ ��� ������;
* 6 - ������ 3-6 + ������ �������� ��������� ������� ������� (�������������� ��������� � �����).
*/
int copyRange(Container*, Container**, int, int, char*);

/*
* �������� ���������� ��������
* ���������:
* (Container*) pContainer - ��������� �� ��������� �������;
* (int*) pKey_pId_pInfo - ��������� �� ���� �������� � � �� �� ����� - �� �����, ���� �������� � ����.
* ������:
* 0 - ���� �����������;
* 1 - �������� ��������� ���������;
* 2 - ���� �� ������;
* 3 - ������ �������� �����.
*/
int getInfo(Container*, int*);

/*
* ������������� �������
* ���������:
* (Container*) pContainer - ��������� �� ��������� �������;
* (int) key_info - ���� ��������, � ����� ������ - ����.
* ������:
* 0 - ���� �����������;
* 1 - �������� ��������� ���������;
* 2 - ���� �� ������;
* 3 - ������ �������� �����.
*/
int printItem(Container*, int);

/*
* ������������� ������� ��� ���������� � ���, ��� ������� �����
* (Container*) pContainer - ��������� �� ��������� �������.
* ������:
* 0 - ������� ����������� �������;
* 1 - ������ �������� �����;
* 2 - ����� � ��������� ������ ��� ������.
*/
int print(Container*);

/*
* ��������� �������� ������� � ������������ ������ �� �����
* (Container**) - ��������� �� ���������, ���� �������� ��������� �������;
* (char*) pName - ��� ������� (��� �� � �������� �����, ����� �� 15 ��������).
* ������:
* 0 - ������� ��������� �������;
* 1 - �� ������� ������� ���� � ����� ������;
* 2 - ����� � ��������� ������;
* 3 - ���� ����.
*/
int open(Container**, char*);