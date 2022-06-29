#ifndef APP_H
#include "app.h"
#endif

Matrix* initMatrix() {
	Matrix* pMatrix = (Matrix*)malloc(sizeof(Matrix));
	if (pMatrix == NULL) return NULL;

	pMatrix->size = 0;
	pMatrix->pLine = NULL;
	return pMatrix;
}

void deleteMatrix(Matrix* pMatrix) {
	for (int i = 0; i < pMatrix->size; i++) free(pMatrix->pLine[i].pWeight);
	free(pMatrix->pLine);
	free(pMatrix);
}

int addLine(Matrix* pMatrix, char pName[8]) {
	Line* pLine;
	int* pWeight;
	int i;

	if (pMatrix == NULL || pName == NULL) return 4;

	if (searchLine(pMatrix, pName) >= 0) return 2;

	pMatrix->size++;
	pLine = (Line*)realloc(pMatrix->pLine, pMatrix->size * sizeof(Line));
	if (pLine == NULL) {
		pMatrix->size--;
		return 1;
	}
	
	pMatrix->pLine = pLine;

	for (i = 0; i < pMatrix->size - 1; i++) {
		pWeight = (int*)realloc(pMatrix->pLine[i].pWeight, pMatrix->size * sizeof(int));
		if (pWeight == NULL) return 3;

		pWeight[pMatrix->size - 1] = 0;
		pMatrix->pLine[i].pWeight = pWeight;
	}

	pWeight = (int*)calloc(pMatrix->size, sizeof(int));
	if (pWeight == NULL) return 3;

	pMatrix->pLine[pMatrix->size - 1].pWeight = pWeight;
	i = strcpy_s(pMatrix->pLine[pMatrix->size - 1].pName, 8 * sizeof(char), pName);

	return 0;
}

int deleteLine(Matrix* pMatrix, char pName[8]) {
	int targetId = 0, i, j;
	int* pWeight = NULL;
	Line* pLine = NULL;

	if (pMatrix == NULL || pName == NULL) return 3;
	targetId = searchLine(pMatrix, pName);
	if (targetId == -1) return 1;

	if (pMatrix->size == 1) {
		free(pMatrix->pLine[0].pWeight);
		free(pMatrix->pLine);
		pMatrix->pLine = NULL;
		pMatrix->size = 0;
		return 0;
	}

	free(pMatrix->pLine[targetId].pWeight);

	for (i = 0; i < pMatrix->size - 1; i++) {

		if (i >= targetId) pMatrix->pLine[i] = pMatrix->pLine[i + 1];

		for (j = 0; j < pMatrix->size - 1; j++)
			if (j >= targetId) pMatrix->pLine[i].pWeight[j] = pMatrix->pLine[i].pWeight[j + 1];

		if (pMatrix->size == 1) free(pMatrix->pLine[i].pWeight);
		else pWeight = (int*)realloc(pMatrix->pLine[i].pWeight, (pMatrix->size - 1) * sizeof(int));

		if (pWeight == NULL && pMatrix->size - 1 > 0) return 2;
		if (pMatrix->size > 1) pMatrix->pLine[i].pWeight = pWeight;
	}

	if (pMatrix->size == 1) free(pMatrix->pLine);
	else pLine = (Line*)realloc(pMatrix->pLine, (pMatrix->size - 1) * sizeof(Line));
	if (pLine == NULL) return 2;

	if (pMatrix->size > 1) pMatrix->pLine = pLine;
	pMatrix->size--;
	return 0;
}

int addWeight(Matrix* pMatrix, char pSrc[8], char pDest[8], int weight) {
	int srcId = 0, destId = 0;
	if (pMatrix == NULL || pSrc == NULL || pDest == NULL) return 2;

	srcId = searchLine(pMatrix, pSrc);
	destId = searchLine(pMatrix, pDest);
	if (srcId == -1 || destId == -1) return 1;

	pMatrix->pLine[srcId].pWeight[destId] = weight;
	return 0;
}

void deleteWeight(Matrix* pMatrix, char pSrc[8], char pDest[8]) {
	int srcId = 0, destId = 0;
	if (pMatrix == NULL || pSrc == NULL || pDest == NULL) return;

	srcId = searchLine(pMatrix, pSrc);
	destId = searchLine(pMatrix, pDest);
	if (srcId == -1 || destId == -1) return;

	pMatrix->pLine[srcId].pWeight[destId] = 0;
}

int searchLine(Matrix* pMatrix, char pTarget[8]) {
	for (int i = 0; i < pMatrix->size; i++) if (strcmp(pTarget, pMatrix->pLine[i].pName) == 0) return i;
	return -1;
}

int printMatrix(Matrix* pMatrix) {
	if (pMatrix == NULL) return 1;
	if (pMatrix->size == 0) return 2;

	printf("\n");
	for (int i = 0; i < 8; i++) printf(" ");
	for (int i = 0; i < pMatrix->size; i++) printf("|%8s", pMatrix->pLine[i].pName);
	printf("\n");

	for (int i = 0; i < pMatrix->size; i++) {
		printf("%8s", pMatrix->pLine[i].pName);

		for (int j = 0; j < pMatrix->size; j++) printf("|%8d", pMatrix->pLine[i].pWeight[j]);
		printf("\n");
	}

	printf("\n");
	return 0;
}

Matrix* copyMatrix(Matrix* pMatrix) {
	if (pMatrix == NULL || (pMatrix->pLine == NULL && pMatrix->size != 0)) return NULL;

	Matrix* pCopy = (Matrix*)malloc(sizeof(Matrix));
	if (pCopy == NULL) return NULL;

	pCopy->size = pMatrix->size;
	pCopy->pLine = (Line*)malloc(pCopy->size * sizeof(Line));
	if (pCopy->pLine == NULL && pCopy->size != 0) {
		free(pCopy);
		return NULL;
	}

	for (int i = 0; i < pCopy->size; i++) {
		pCopy->pLine[i].pWeight = (int*)malloc(pCopy->size * sizeof(int));
		if (pCopy->pLine[i].pWeight == NULL) {
			free(pCopy->pLine);
			free(pCopy);
			return NULL;
		}

		strcpy_s(pCopy->pLine[i].pName, 8 * sizeof(char), pMatrix->pLine[i].pName);
		for (int j = 0; j < pCopy->size; j++) pCopy->pLine[i].pWeight[j] = pMatrix->pLine[i].pWeight[j];
	}

	return pCopy;
}