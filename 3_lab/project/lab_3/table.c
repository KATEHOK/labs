#ifndef APP_H
#include "app.h"
#endif // !APP_H


int tableInit(Table* pTable) {
	int maxSize1 = 0, maxSize2 = 0, status;
	pTable->countKeys1 = 0;
	pTable->countKeys2 = 0;
	if (maxSize1 == 0) {
		status = setMaxSizeKS(&maxSize1, 1);
		if (status == 1)
			return 1;
	}
	if (maxSize2 == 0) {
		status = setMaxSizeKS(&maxSize2, 2);
		if (status == 1)
			return 1;
	}
	pTable->maxSize1 = maxSize1;
	pTable->maxSize2 = maxSize2;
	pTable->pKS1 = (struct KeySpace1*)malloc(maxSize1 * sizeof(struct KeySpace1));
	if (pTable->pKS1 == NULL) {
		printf("|-> Memory request Error!\n");
		return 1;
	}
	pTable->pKS2 = (struct KeySpace2*)malloc(maxSize2 * sizeof(struct KeySpace2));
	if (pTable->pKS2 == NULL) {
		printf("|-> Memory request Error!\n");
		free(pTable->pKS1);
		return 1;
	}
	printf("maxsize1 = %d; maxsize2 = %d\n", maxSize1, maxSize2);
	return 0;
}
void tableDelete(Table*);

int tableAdd(Table*, int, int, char*);
Item* tableSearchItemByComposite(Table*, int, int);
void tableDeleteItemByComposite(Table*, int, int);
Item* tableSearchItemBySingle(Table*, int);
void tableDeleteItemBySingle(Table*, int);
int tablePrint(Table*);

int setMaxSizeKS(int* pData, int KSNumber) {
	int status = 0;
	printf("Enter max count of keys in the %d keys-space\n", KSNumber);
	status = getNat(pData);
	if (status == 1)
		printf("|-> setMaxSizeKS(%d) Error!\n", KSNumber);
	return status;
}

int searchKS1(Table* pTable, int key) {
	int minId = 0, maxId = pTable->countKeys1 - 1, curId;
	while (minId <= maxId) {
		//printf("min = %d; max = %d\n", minId, maxId);
		curId = (minId + maxId) / 2;
		if (key == pTable->pKS1[curId].key)
			return curId;
		else if (key < pTable->pKS1[curId].key)
			maxId = curId - 1;
		else
			minId = curId + 1;
	}
	return -1;
}

int deleteKS1(Table* pTable, int key) {
	int keyId, i;
	// отсутствие ключа
	keyId = searchKS1(pTable, key);
	if (keyId == -1)
		return 1;
	for (i = keyId + 1; i < pTable->countKeys1; i++)
		pTable->pKS1[i - 1] = pTable->pKS1[i];
	pTable->countKeys1--;
	return 0;
}

int insertKS1(Table* pTable, int key, Item* pData) {
	int i;
	// переполнение
	if (pTable->countKeys1 == pTable->maxSize1)
		return 1;
	// дублирование ключей
	i = searchKS1(pTable, key);
	if (i > -1)
		return 2;
	//printf("After errors\n");
	if (pTable->countKeys1 == 0) {
		printf("countKeys1 == 0\n");
		pTable->pKS1[0].key = key;
		pTable->pKS1[0].pData = pData;
	} else {
		for (i = pTable->countKeys1 - 1; i >= 0; i--) {
			if (pTable->pKS1[i].key <= key) {
				pTable->pKS1[i + 1].key = key;
				pTable->pKS1[i + 1].pData = pData;
				break;
			} else
				pTable->pKS1[i + 1] = pTable->pKS1[i];
			if (i == 0) {
				pTable->pKS1->key = key;
				pTable->pKS1->pData = pData;
			}
		}
	}
	pTable->countKeys1++;
	return 0;
}