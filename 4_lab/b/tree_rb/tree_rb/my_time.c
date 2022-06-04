#ifndef APP_H
#include "app.h"
#endif


int* genNumsArray(int count) {
	srand(time(NULL));
	int i;
	int* pNums = (int*)malloc(count * sizeof(int));
	if (pNums == NULL) return NULL;

	for (i = 0; i < count; i++) rand_s(pNums + i);

	return pNums;
}

char** genStrsArray(int count) {
	int i;
	char defaultStr[8] = "default\0";
	char** ppStr = (char**)malloc(count * sizeof(char*));
	if (ppStr == NULL) return NULL;
	for (i = 0; i < count; i++) {
		ppStr[i] = (char*)malloc(8 * sizeof(char));
		if (ppStr[i] == NULL) {
			for (i = i - 1; i >= 0; i--) free(ppStr[i]);
			free(ppStr);
			return NULL;
		}
		strcpy_s(ppStr[i], 8, defaultStr);
	}
	return ppStr;
}

int printIntoFile(char* pFileName, int size, clock_t time) {
	FILE* pFile;
	int trash, status = fopen_s(&pFile, pFileName, "a");
	if (status != 0) return 1;

	status = fprintf(pFile, "%d %d\n", size, time);
	trash = fclose(pFile);

	if (status <= 0) return 1;
	return 0;
}

void checkTime(char* pPath) {
	int i, j, status, counter, firstPoint = 1, step = 1, pointsCount = 1;
	int* pKeys;
	clock_t timeStart, timeFinish, timeRange;
	char** ppInfo;
	Tree* pTree;
	remove(pPath);

	printf("\nEnter first point\n");
	status = getNat(&firstPoint);
	if (status == 1) return;

	printf("\nEnter step\n");
	status = getNat(&step);
	if (status == 1) return;

	printf("\nEnter count of points\n");
	status = getNat(&pointsCount);
	if (status == 1) return;

	pTree = dInit();
	if (pTree == NULL) return;

	pKeys = genNumsArray(firstPoint + step * (pointsCount - 1));
	if (pKeys == NULL) {
		treeDelete(pTree);
		printf("Error with generate\n");
		return;
	}

	ppInfo = genStrsArray(firstPoint + step * (pointsCount - 1));
	if (ppInfo == NULL) {
		free(pKeys);
		treeDelete(pTree);
		printf("Error with generate\n");
		return;
	}

	for (counter = 0; counter < firstPoint; counter++) {
		if (insert(pTree, pKeys[counter], ppInfo[counter]) == NULL) {
			free(pKeys);
			treeDelete(pTree);
			for (counter = counter; counter < firstPoint + step * (pointsCount - 1); counter++)
				free(ppInfo[counter]);
			free(ppInfo);
			printf("Error with insert\n");
			return;
		}
	}

	timeStart = clock();
	//вызов поиска
	for (j = 0; j < firstPoint + step * (pointsCount - 1); j++)
		search(pTree->pRoot, pKeys[j], ppInfo[j]);
	timeFinish = clock();
	timeRange = timeFinish - timeStart;
	//запись данных в файл GFG.txt
	status = printIntoFile(pPath, firstPoint, timeRange);
	if (status != 0) printf("Point: '%d' was not printed\n", firstPoint);

	for (i = 0; i < pointsCount - 1; i++) {
		for (counter = firstPoint + i * step; counter < firstPoint + (i + 1) * step; counter++) {
			if (insert(pTree, pKeys[counter], ppInfo[counter]) == NULL) {
				free(pKeys);
				treeDelete(pTree);
				for (counter = counter; counter < firstPoint + step * (pointsCount - 1); counter++)
					free(ppInfo[counter]);
				free(ppInfo);
				printf("Insert error!\n");
				return;
			}
		}

		timeStart = clock();
		//вызов поиска
		for (j = 0; j < firstPoint + step * (pointsCount - 1); j++)
			search(pTree->pRoot, pKeys[j], ppInfo[i]);
		timeFinish = clock();
		timeRange = timeFinish - timeStart;
		//запись данных в файл GFG.txt
		status = printIntoFile(pPath, firstPoint + (i + 1) * step, timeRange);
		if (status != 0) printf("Point: '%d' was not printed\n", firstPoint + (i + 1));
	}

	printf("Success!\n");
	free(pKeys);
	free(ppInfo);
	treeDelete(pTree);
}
