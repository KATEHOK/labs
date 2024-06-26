#pragma once

typedef struct Graph {
	Matrix* pMatrix;
} Graph;


// BASE

/*
* �������������� ����, ������������� - �������� ���������.
* ������:
* NULL - ����� � ��������� ������;
* (Graph*) - ��������� �� ����� ����.
*/
Graph* initGraph();

/*
* ������� ����:
* (Graph*) pGraph - ��������� �� ����.
*/
void deleteGraph(Graph* pGraph);

/*
* ��������� � ���� ����� �������:
* (Graph*) pGraph - ��������� �� ����;
* (char*) pName - ��� ������� (����������� ������ ��������).
* ������:
* 0 - �������;
* 1 - ����� � ��������� ������ (�� ��������);
* 2 - ������������ ���� (�� ��������);
* 3 - ����� � ��������� ������ (��������);
* 4 - ������� NULL.
*/
int addPoint(Graph* pGraph, char pName[8]);

/*
* ������� ������� �����:
* (Graph*) pGraph - ��������� �� ����;
* (char*) pName - ��� ��������� ������ (����������� ������ ��������).
* ������:
* 0 - �������;
* 1 - ������� �� �������;
* 2 - ����� ��� ������ � ������� (��������);
* 3 - ������� NULL;
*/
int deletePoint(Graph* pGraph, char pName[8]);

/*
* ��������� ���� (��� ������� ��������� ���):
* (Graph*) pGraph - ��������� �� ����;
* (char*) pSrc - ��� ��������� ������� (����������� ������ ��������);
* (char*) pDest - ��� �������� ������� (����������� ������ ��������);
* (int) weight - ����������� �������� ����.
* ������:
* 0 - �������;
* 1 - ������(�) �� �������(�);
* 2 - ������� NULL.
*/
int addArrow(Graph* pGraph, char pSrc[8], char pDest[8], int weight);

/*
* ������� ����:
* (Graph*) pGraph - ��������� �� ����;
* (char*) pSrc - ��� ��������� ������� (����������� ������ ��������);
* (char*) pDest - ��� �������� ������� (����������� ������ ��������).
*/
void deleteArrow(Graph* pGraph, char pSrc[8], char pDest[8]);

/*
* �������� ������� ��������� �����:
* (Graph*) pGraph - ��������� �� ����.
* ������:
* 0 - �������;
* 1 - �������� NULL;
* 2 - � ����� ��� ������.
*/
int printGraph(Graph* pGraph);

// ENDBASE

/*
* ������ ������ ������������ ��� �������� �������:
* (Graph*) pGraph - ��������� �� ����;
* (char*) pSrc - ��� ��������� ������� (����������� ������ ��������);
* (char*) pDest - ��� �������� ������� (����������� ������ ��������).
* ������:
* 0 - �������;
* 1 - ����� � ��������� ������ (���� �� ���������);
* 2 - �������(�) �� �������(�).
*/
int searchWay(Graph* pGraph, char pSrc[8], char pDest[8]);

/*
* ��������� ������ ������������ �� �������� �������:
* (Graph*) pGraph - ��������� �� ����;
* (Tree*) pTree - ��������� �� ������ ������������;
* (int) id - id ������� �������;
* (char*) pDest - ��� �������� ������� (����������� ������ ��������).
*/
void fillReachabilityTree(Graph* pGraph, Tree* pTree, int id, char pDest[8]);

/*
* �������� ������ ����������� ���� BellmanFord:
* (Graph*) pGraph - ��������� �� ����;
* (char*) pSrc - ��� ��������� ������� (����������� ������ ��������);
* (char*) pDest - ��� ������� ������� (����������� ������ ��������).
* ������:
* 0 - ���������� ���� ������;
* 1 - ����������� ������;
* 2 - �������(�) �� �������(�);
* 3 - ���������� ������������� ����;
* 4 - ������� ������� �� ��������� �� ���������.
*/
int findShortestWay(Graph* pGraph, char pSrc[8], char pDest[8]);

/*
* ���������� �������� ���������� ����:
* (Graph*) pGraph - ��������� �� ����;
* (int) srcId - ������ ��������� �������;
* (int) destId - ������ ������� �������;
* (int) curId - ������ ������� �������.
*/
void printShortestWay(Graph* pGraph, int srcId, int destId, int curId);

/*
* �������������� ����������:
* (Graph*) pGraph - ��������� �� ����.
* ������:
* 0 - �����;
* 1 - ����������� ������;
* 2 - �� ����������� ������;
* 3 - ���� �� ���������.
*/
int sortGraph(Graph* pGraph);

/*
* ���������� ������� �����:
* (Graph*) pGraph - ��������� �� ����.
* ������:
* 0 - ���� ������������;
* 1 - ����������� ������;
* 3 - ���������� ����.
*/
int checkCycle(Graph* pGraph);

/**/
int fillTree(Tree* pTree, int idParent);