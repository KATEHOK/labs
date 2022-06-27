#pragma once

/*
* 
*    B
*   / \
*.........
*....R....
*.../ \...
*..B   B..
*./ \.....
*.........
* .../....
* .(B)....
* 
* +5th
*  
*/


typedef struct Info {
	char* pTxt;
	struct Info* pNext;
} Info;

typedef struct Node {
	unsigned int key;
	short color; //0 - black; 1 - red
	int infoCount;
	Info* pInfo;

	struct Node* pLeft;
	struct Node* pRight;
	struct Node* pParent;
} Node;

typedef struct Tree {
	Node* pRoot;
	Node* pEList;
} Tree;

/*
* �������������� ������.
* ������:
* NULL - ����� � ��������� ������;
* (Tree*) - ��������� �� ��������� ������.
*/
Tree* treeInit();

/*
* �������������� ���� ������, ������� - RED:
* (Tree*) pTree - ��������� �� ������;
* (int) key - ����;
* (char*) pInfo - ���������� (������).
* ������:
* NULL - ����� � ��������� ������;
* (Node*) - ��������� �� ��������� ����.
*/
Node* nodeInit(Tree* pTree, int key, Info* pInfo);

/*
* �������� ����������� �������� ���� ����� ������, ������� ������:
* (Tree*) pTree - ��������� �� ������.
*/
void treeDelete(Tree* pTree);

/*
* ���������� ������� ��� ���������� �������� ���� � ��� ������� ����:
* (Node*) pNode - ��������� �� ������� ����;
* (Node*) pEList - ��������� �� ����.
*/
void nodesDelete(Node* pNode, Node* pEList);

/*
* ������� ������ ����������:
* (Info*) pInfo - ��������� �� ������� ������, � �������� ���������� ��������.
*/
void infoListPrint(Info* pInfo);

/*
* ������� ������ ����������:
* (Info*) pInfo - ��������� �� ������� ������, � �������� ���������� ��������.
*/
void infoListDelete(Info* pInfo);

/*
* ���������� ������� ������ � �������� ���� � ���� �����, ���� ������� �� ������ ���������:
* (Node*) pNode - ��������� �� ����;
* (Node*) pEList - ��������� �� ����;
* (int) keyEnd - ������������ ����, ������� ����� ����������;
* (int) isKeyEndCorrect - ���� �� ����� ����, �������� ��� ������.
*/
void detour(Node* pNode, Node* pEList, int keyEnd, int isKeyEndCorrect);

/*
* ���������� ���� ���� �� ����� � ������:
* (Node*) pNode - ��������� �� ����;
* (Node*) pEList - ��������� �� ����;
* (int) key - ������� ����;
* (int) version - ������� ������ (���������� � 1)
* (Info**) ppInfo - ��������� �� ��������� �� ���������� (���� NULL, �� ���� �� ������������);
* ������:
* NULL - ���� �� ������;
* (Node*) - ��������� �� ��������� ����.
*/
Node* search(Node* pNode, Node* pEList, int key, int version, Info** ppInfo);

/*
* �� ��������� � ������ ������
* ���������� ����� ���� (������������� ����� - � ������):
* (Tree*) pTree - ��������� �� ������;
* (int) key - ����� ����;
* (char*) pTxt - ���������� (������), ������ �� ��� ����������.
* ������:
* NULL - ����� � ��������� ������ ��� ������ �����������;
* (Node*) - ��������� �� ��������� ����.
*/
Node* insertNotFirst(Tree* pTree, int key, char* pTxt);

/*
* ���� ������������ ������� ��� ������ �����:
* (Node*) pNode - ��������� �� ����;
* (Node*) pEList ��������� �� ����;
* (int) key - ����� ����;
* (int*) pLR - ���������, ���� �������� ����� ������� (-1 - ������������ ����, 0 - left, 1 - right).
* ������:
* (Node*) - ������� ���������.
*/
Node* searchFunnyFather(Node* pNode, Node* pEList, int key, int* pLR);

/*
* ��������� ������ ���� ������ � ������ ������:
* (Tree*) pTree - ��������� �� ������;
* (int) key - ����;
* (char*) pTxt - ���������� (������), ������ �� ��� ����������.
* ������:
* NULL - ����� � ��������� ������ ��� ������ ����������� ��������� strcpy;
* (Node*) - ��������� �� ����������� ����.
*/
Node* insertFirst(Tree* pTree, int key, char* pTxt);

/*
* �������������� ����� ������� ������ ����������:
* (char*) pTxt - ���������� (������), ������ �� ��� ����������;
* (Info*) pNext - ��������� �� ��������� ������� ������ (��� �������� ������� - NULL).
* ������:
* NULL - ����� � ��������� ������ ��� ������ �����������;
* (Info*) - ��������� �� ����� �������.
*/
Info* infoInit(char* pTxt, Info* pNext);

/*
* �������� ��������������� ������� �������:
* (Tree*) pTree - ��������� �� ������;
* (int) key - ����;
* (char*) pInfo - ���������� (������), ������ �� ��� ����������.
* ������:
* NULL - ����� � ��������� ������ ��� ������ �����������;
* (Node*) - ��������� �� ����������� ����.
*/
Node* insert(Tree* pTree, int key, char* pTxt);

/*
* ����� ������� ������ ���� (������ ������� �������):
* url = '5 ������-������ �������.pdf' (33);
* (Tree*) pTree - ��������� �� ������;
* (Node*) pNode - ��������� �� ���� '�'.
*/
void rotateLeft(Tree* pTree, Node* pA);

/*
* ������ ������� ������ ���� (�� ������� �������):
* url = '5 ������-������ �������.pdf' (36);
* (Tree*) pTree - ��������� �� ������;
* (Node*) pNode - ��������� �� ���� 'B'.
*/
void rotateRight(Tree* pTree, Node* pB);

/*
* ���������� �������� ��� ����� ��������:
* (Tree*) pTree - ��������� �� ������;
* (Node*) pFirst - ��������� �� ������ ����;
* (Node*) pSecond - ��������� �� ������ ����.
*/
void rotateLeftLeft(Tree* pTree, Node* pFirst, Node* pSecond);

/*
* ���������� �������� ��� ������ ��������:
* (Tree*) pTree - ��������� �� ������;
* (Node*) pFirst - ��������� �� ������ ����;
* (Node*) pSecond - ��������� �� ������ ����.
*/
void rotateRightRight(Tree* pTree, Node* pFirst, Node* pSecond);

/*
* ���������� �������� ��� ��������:
* (Tree*) pTree - ��������� �� ������;
* (Node*) pLeft - ��������� �� ���� ��� ������ ��������;
* (Node*) pRight - ��������� �� ���� ��� ������� ��������.
*/
void rotateLeftRight(Tree* pTree, Node* pLeft, Node* pRight);

/*
* ���������� �������� ��� ��������:
* (Tree*) pTree - ��������� �� ������;
* (Node*) pRight - ��������� �� ���� ��� ������� ��������;
* (Node*) pLeft - ��������� �� ���� ��� ������ ��������.
*/
void rotateRightLeft(Tree* pTree, Node* pRight, Node* pLeft);

/*
* ����������� ������ ����� ������� ������������� ����� (�� ���������� ����� ������ �������):
* (Tree*) pTree - ��������� �� ������;
* (Node*) pNode - ��������� �� ����������� (��������������) �������.
*/
void insertFix(Tree* pTree, Node* pNode);

/*
* ��������� ������� ���� �� �����:
* (Tree*) pTree - ��������� �� ������;
* (int) key - ������� ����.
* ������:
* 0 - �������;
* 1 - ���� �� ������.
*/
int nodeDelete(Tree* pTree, int key);

/*
* fix-pv-in-right.png
*/
void deleteFixRight(Tree* pTree, Node* pParent);

/*
* fix-pv-in-right.png // ���������
*/
void deleteFixLeft(Tree* pTree, Node* pParent);

/*
* ������������ ������ �������.
* ����� - ������. ������ �������� �� 1 ������ �����������.
* ������ �������� �� ������ ����.
* ������� - ������.
*/
void fixHigher(Tree* pTree, Node* pCurrent, Node* pParent);

/*
* ���������� ���� ���� � ������������ ������:
* (Node*) pNode - ��������� �� ���������, � ������� �������������� �����.
* ������:
* NULL - ���� pNode == NULL;
* (Node*) - ��������� �� ������� ����.
*/
Node* searchMax(Node* pNode, Node* pEList);

/*
* ���������� ���� ���� � ����������� ������:
* (Node*) pNode - ��������� �� ���������, � ������� �������������� �����.
* ������:
* NULL - ���� pNode == NULL;
* (Node*) - ��������� �� ������� ����.
*/
Node* searchMin(Node* pNode, Node* pEList);

/*
* ���� ���� � ������ ������, ����������� ��������:
* (Node*) pNode - ��������� �� ���������, � ������� ����� ����������� �����;
* (Node*) pEList - ��������� �� ����;
* (int) key - �������� ����;
* (Node*) pMemory - ��������� "������ �����".
* ������:
* NULL - ������� NULL ��� pEList ������ pNode;
* (Node*) - ��������� �� ������� ����.
*/
Node* searchSpecial(Node* pNode, Node* pEList, int key, Node* pMemory);

/*
* ��������� �� ���������� ����� ������ �� ������:
* (char*) pPath - ���� �� �����.
* ������:
* NULL - �� ������� (�� �������� ������ ��� �� ������ ����);
* (Tree*) -��������� �� ����� ������.
*/
Tree* download(char* pPath);

/*
* ���������� �������� ������ "� ���� ������":
* (Node*) pNode - ����, � �������� ������ ������;
* (int) offset - ���������� �������� ����� ������� ����� (������� 0).
*/
void printAsTree(Node* pNode, Node* pEList, int offset);