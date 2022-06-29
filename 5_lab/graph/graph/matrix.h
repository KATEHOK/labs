#pragma once

typedef struct Line {
	char pName[16];
	int* pWeight;
	//
	int prevId;
	int distance;
} Line;

typedef struct Matrix {
	int size;
	Line* pLine;
} Matrix;

/*
* �������������� �������.
* ������:
* NULL - ����� � ��������� ������;
* (Matrix*) ��������� �� �������.
*/
Matrix* initMatrix();

/*
* ������� �������:
* (Matrix*) pMatrix - ��������� �� �������.
*/
void deleteMatrix(Matrix* pMatrix);

/*
* ��������� ������ � ����� �������, ����������� ������� � ����������� ����:
* (Matrix*) pMatrix - ��������� �� �������;
* (char*) pName - ��� ��� ����� ������ (����������� ������ ��������).
* ������:
* 0 - �������;
* 1 - ����� � ��������� ������ (�� ��������);
* 2 - ������������ ���� (�� ��������);
* 3 - ����� � ��������� ������ (��������);
* 4 - ������� NULL;
*/
int addLine(Matrix* pMatrix, char pName[8]);

/*
* ������� ������ �� �������, ����������� ������� � ����������� ����:
* (Matrix*) pMatrix - ��������� �� �������;
* (char*) pName - ��� ��������� ������ (����������� ������ ��������).
* ������:
* 0 - �������;
* 1 - ������� �� �������;
* 2 - ����� ��� ������ � ������� (��������);
* 3 - ������� NULL.
*/
int deleteLine(Matrix* pMatrix, char pName[8]);

/*
* ��������� ������� ������ (��� ������� ��������� ��������):
* (Matrix*) pMatrix - ��������� �� �������;
* (char*) pSrc - ��� ������ (����������� ������ ��������);
* (char*) pDest - ��� ������� (����������� ������ ��������);
* (int) weight - ����������� ��������.
* ������:
* 0 - �������;
* 1 - ������(�) �� �������(�);
* 2 - ������� NULL.
*/
int addWeight(Matrix* pMatrix, char pSrc[8], char pDest[8], int weight);

/*
* �������� ������� ������:
* (Matrix*) pMatrix - ��������� �� �������;
* (char*) pSrc - ��� ������ (����������� ������ ��������);
* (char*) pDest - ��� ������� (����������� ������ ��������).
*/
void deleteWeight(Matrix* pMatrix, char pSrc[8], char pDest[8]);

/*
* ���� ������:
* (Matrix*) pMatrix - ��������� �� �������;
* (char*) pTarget - ��� ������� ������� (����������� ������ ��������).
* ������:
* >= 0 - ������ ������;
* -1 - ������ �� �������.
*/
int searchLine(Matrix* pMatrix, char pTarget[8]);

/*
* �������� �������:
* (Matrix*) pMatrix - ��������� �� �������.
* ������:
* 0 - �������;
* 1 - �������� NULL;
* 2 - ������� �����.
*/
int printMatrix(Matrix* pMatrix);

/*
* ������� ���������� �������
*/
Matrix* copyMatrix(Matrix* pMatrix);