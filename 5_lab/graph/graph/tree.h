#pragma once

typedef struct Tree {
	struct Tree** ppChildren;
	char pName[8];
	int childrenCount;
} Tree;


/*
* �������������� ������ ������� � ������:
* (char*) pName - ��� ������� (����������� ������ ��������).
* ������:
* NULL - ����� � ��������� ������, �������� NULL ��� ������ �����������;
* (Tree*) - ��������� �� ����� �������.
*/
Tree* initTree(char pName[8]);

/*
* ������� ���������:
* (Tree*) pTree - ��������� �� ������;
* (char*) pName - ��� ������� (����������� ������ ��������).
*/
void deleteSubTree(Tree* pTree, char pName[8]);

/*
* ���������� ������� ��� ������:
* (Tree*) pTree - ��������� �� ������.
*/
void deleteTree(Tree* pTree);

/*
* ���������� ���� ���� �� �����:
* (Tree*) pTree - ��������� �� ���������, � ������� �������������� �����;
* (char*) pName - ��� ���� (����������� ������ ��������).
* ������:
* NULL - ���� �� ������;
* (Tree*) - ��������� �� ��������� ����.
*/
Tree* searchTree(Tree* pTree, char pName[8]);

/*
* ��������� ����� ���� � �������� ������, ���� ��������� �����������:
* (Tree*) pTree - ��������� �� ������;
* (char*) pParent - ��� �������� (����������� ������ ��������);
* (char*) pNew - ��� ������������ ���� (����������� ������ ��������).
* ������:
* NULL - ���-�� ����� �� ���;
* (Tree*) - ��������� �� ����������� ����.
*/
Tree* insertTree(Tree* pTree, char pParent[8], char pNew[8]);

/*
* �������� ������ � ���� ������:
* (Tree*) pTree - ��������� �� ���������;
* (int) offset - ������ ��� �������� ����.
*/
void printAsTree(Tree* pTree, int offset);