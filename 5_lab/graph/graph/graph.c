#ifndef APP_H
#include "app.h"
#endif


// BASE

Graph* initGraph() {
	Graph* pGraph = (Graph*)malloc(sizeof(Graph));
	if (pGraph == NULL) return NULL;

	pGraph->pMatrix = initMatrix();
	if (pGraph->pMatrix == NULL) free(pGraph);

	return pGraph;
}

void deleteGraph(Graph* pGraph) {
	if (pGraph == NULL) return;
	deleteMatrix(pGraph->pMatrix);
	free(pGraph);
}

int addPoint(Graph* pGraph, char pName[8]) {
	if (pGraph == NULL || pName == NULL) return 4;
	return addLine(pGraph->pMatrix, pName);
}

int deletePoint(Graph* pGraph, char pName[8]) {
	if (pGraph == NULL || pName == NULL) return 3;
	return deleteLine(pGraph->pMatrix, pName);
}

int addArrow(Graph* pGraph, char pSrc[8], char pDest[8], int weight) {
	if (pGraph == NULL || pSrc == NULL || pDest == NULL) return 2;
	return addWeight(pGraph->pMatrix, pSrc, pDest, weight);
}

void deleteArrow(Graph* pGraph, char pSrc[8], char pDest[8]) {
	if (pGraph == NULL || pSrc == NULL || pDest == NULL) return;
	deleteWeight(pGraph->pMatrix, pSrc, pDest);
}

int printGraph(Graph* pGraph) {
	if (pGraph == NULL) return 1;
	return printMatrix(pGraph->pMatrix);
}

// ENDBASE

int searchWay(Graph* pGraph, char pSrc[8], char pDest[8]) {
	if (pGraph == NULL || pSrc == NULL || pDest == NULL || pGraph->pMatrix == NULL) return 1;

	int lineId = searchLine(pGraph->pMatrix, pSrc);
	if (lineId == -1 || searchLine(pGraph->pMatrix, pDest) == -1) return 2;

	Tree* pTree = initTree(pSrc);
	if (pTree == NULL) return 1;

	fillReachabilityTree(pGraph, pTree, lineId, pDest);

	if (searchTree(pTree, pDest) == NULL) {
		deleteTree(pTree);
		return 2;
	}
	
	printAsTree(pTree, 0);
	deleteTree(pTree);
	return 0;
}

void fillReachabilityTree(Graph* pGraph, Tree* pTree, int id, char pDest[8]) {
	for (int i = 0; i < pGraph->pMatrix->size; i++) {
		if (pGraph->pMatrix->pLine[id].pWeight[i] != 0) {

			if (strcmp(pGraph->pMatrix->pLine[i].pName, pDest) == 0)
				insertTree(pTree, pGraph->pMatrix->pLine[id].pName,
					pGraph->pMatrix->pLine[i].pName);

			if (searchTree(pTree, pGraph->pMatrix->pLine[i].pName) == NULL) {
				printf("inside\n");

				insertTree(pTree, pGraph->pMatrix->pLine[id].pName,
					pGraph->pMatrix->pLine[i].pName);

				fillReachabilityTree(pGraph, pTree, i, pDest);
			}
		}
	}
}

int findShortestWay(Graph* pGraph, char pSrc[8], char pDest[8]) {
	if (pGraph == NULL || pGraph->pMatrix == NULL) return 1;
	if (pGraph->pMatrix->size == 0) return 2;
	if (pGraph->pMatrix->pLine == NULL) return 1;
	// для удобства обращения
	Matrix* pMatrix = pGraph->pMatrix;
	Line* pLine = pMatrix->pLine;

	int srcId = searchLine(pMatrix, pSrc);
	int destId = searchLine(pMatrix, pDest);

	if (srcId == -1 || destId == -1) return 2;
	if (srcId == destId) {
		pLine[srcId].prevId = srcId;
		return 0;
	}
	
	// Шаг 1 "Инициализация"
	for (int i = 0; i < pMatrix->size; i++) {
		pLine[i].prevId = -1;

		if (strcmp(pLine[i].pName, pSrc) == 0) pLine[i].distance = 0;
		else pLine[i].distance = INT_MAX;
	}

	// Шаг 2 "Поиск кратчайших расстояний"
	for (int counter = 0; counter < pMatrix->size - 1; counter++)
		for (int i = 0; i < pMatrix->size; i++)
			for (int j = 0; j < pMatrix->size; j++) {
				if (pLine[i].pWeight[j] == 0) continue;

				if (pLine[i].distance != INT_MAX && pLine[i].pWeight[j] != 0 &&
					pLine[j].distance > pLine[i].distance + pLine[i].pWeight[j]) {

					pLine[j].distance = pLine[i].distance + pLine[i].pWeight[j];
					pLine[j].prevId = i;
				}
			}

	// Шаг 3 "Поиск отрицательных циклов"
	for (int i = 0; i < pMatrix->size; i++)
		for (int j = 0; j < pMatrix->size; j++)
			if (pLine[i].distance != INT_MAX && pLine[i].pWeight[j] != 0 &&
				pLine[j].distance > pLine[i].distance + pLine[i].pWeight[j]) return 3;

	// Шаг 4 "Проверка на достижимость"
	int curId = destId;
	for (int i = 0; i < pMatrix->size; i++) {
		curId = pLine[curId].prevId;
		if (curId == srcId) return 0;

		// Целевая вершина не достижима из начальной
		if (curId == -1) return 4;
	}

	// Целевая вершина не достижима из начальной
	return 4;
}

void printShortestWay(Graph* pGraph, int srcId, int destId, int curId) {
	int prevId = pGraph->pMatrix->pLine[curId].prevId;
	if (curId != srcId) printShortestWay(pGraph, srcId, destId, prevId);

	printf("[%s]", pGraph->pMatrix->pLine[curId].pName);
	if (curId != destId) printf("->");
}

int sortGraph(Graph* pGraph) {
	int status = checkCycle(pGraph);
	if (status != 0) return status;
	
	Matrix* pOld = pGraph->pMatrix;
	Matrix* pNew = initMatrix();
	if (pNew == NULL) return 2;

	Matrix* pOldStatic = copyMatrix(pOld);
	pGraph->pMatrix = pOldStatic;


	/*deleteMatrix(pNew);
	deleteMatrix(pOld);
	return 2;*/


	pGraph->pMatrix = pOldStatic;
	if (pGraph->pMatrix == NULL) {
		deleteMatrix(pNew);
		pGraph->pMatrix = pOld;
		return 2;
	}

	int i, j;
	for (int counter = pOld->size; counter > 0; counter--) {
		// выбираем конечную вершину
		for (i = 0; i < pOld->size; i++) {
			status = 0;
			// выбираем начальную вершину
			for (j = 0; j < pOld->size; j++)
				if (pOld->pLine[j].pWeight[i] != 0) {
					status = 1;
					break;
				}

			if (status == 1) continue;

			//нашли исток, индекс = i

			status = addLine(pNew, pOld->pLine[i].pName);
			if (status != 0) {
				deleteMatrix(pNew);
				deleteMatrix(pOld);
				return 2; // исходная матрица сохранена
			}

			status = deleteLine(pOld, pOld->pLine[i].pName);
			if (status != 0) {
				deleteMatrix(pNew);
				deleteMatrix(pOld);
				return 2; // исходная матрица сохранена
			}

			break;
		}
	}
	deleteMatrix(pOld);

	/*printf("\n%d %d\n", pNew->size, pOldStatic->size);
	deleteMatrix(pNew);
	return 2;*/

	//printf("Free points\n");

	// pNew имеет все исходные вершины, но не имеет ребер. Восстановим ребра.

	for (i = 0; i < pOldStatic->size; i++)
		for (j = 0; j < pOldStatic->size; j++) {
			if (pOldStatic->pLine[i].pWeight[j] == 0) continue;

			status = addWeight(pNew, pOldStatic->pLine[i].pName,
								pOldStatic->pLine[j].pName, pOldStatic->pLine[i].pWeight[j]);

			if (status != 0) {
				deleteMatrix(pNew);
				pGraph->pMatrix = pOldStatic;
				return 2; // исходная матрица сохранена
			}
		}

	deleteMatrix(pOldStatic);
	pGraph->pMatrix = pNew;
	return 0;
}

int checkCycle(Graph* pGraph) {
	// 0 - all right
	// 1 - memory error
	// 2 - не критическая ошибка
	// 3 - существует цикл
	return 0;

	Tree** ppTree = (Tree**)malloc(pGraph->pMatrix->size * sizeof(Tree*));
	if (ppTree == NULL) return 2;

	for (int i = 0; i < pGraph->pMatrix->size; i++) {
		ppTree[i] = initTree(pGraph->pMatrix->pLine[i].pName);
		if (ppTree[i] == NULL) {
			for (int j = 0; j < i; j++) deleteTree(ppTree[j]);
			free(ppTree);
			return 2;
		}

		
	}
	
	return 0;
}
