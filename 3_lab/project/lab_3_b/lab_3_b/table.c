#ifndef APP_H
#include "app.h"
#endif

int tInit(Container** ppContainer, char* pName, int maxKeysCount) {
	*ppContainer = (Container*)malloc(sizeof(Container));
	if (*ppContainer == NULL)
		return 1;
	(*ppContainer)->pTable = (Table*)malloc(sizeof(Table));
	if ((*ppContainer)->pTable == NULL) {
		free(*ppContainer);
		return 1;
	}
	(*ppContainer)->pKey = (int*)malloc(sizeof(int) * maxKeysCount);
	if ((*ppContainer)->pKey == NULL) {
		free((*ppContainer)->pTable);
		free(*ppContainer);
		return 1;
	}
	strcpy_s((*ppContainer)->pTable->name, 16 * sizeof(char), pName);
	(*ppContainer)->pTable->keysCount = 0;
	(*ppContainer)->pTable->maxKeysCount = maxKeysCount;
	return 0;
}

int tDelete(Container* pContainer) {
	if (pContainer == NULL || pContainer->pKey == NULL || pContainer->pTable == NULL)
		return 1;
	free(pContainer->pTable);
	free(pContainer->pKey);
	free(pContainer);
	return 0;
}

int tSearchItem(Container* pContainer, int* pKey_pId) {
	int maxId = pContainer->pTable->keysCount - 1, minId = 0, middle;
	if (pContainer == NULL || pContainer->pKey == NULL || pContainer->pTable == NULL)
		return 1;
	if (pContainer->pTable->keysCount == 0)
		return 2;
	if (pContainer->pKey[0] == *pKey_pId) {
		*pKey_pId = 0;
		return 0;
	}
	while (maxId >= minId) {
		middle = (maxId + minId) / 2;
		if (pContainer->pKey[middle] > *pKey_pId)
			maxId = middle - 1;
		else if (pContainer->pKey[middle] < *pKey_pId)
			minId = middle + 1;
		else {
			*pKey_pId = middle;
			return 0;
		}
	}
	//printf("kc = %d\n", pContainer->pTable->keysCount);
	return 2;
}

int tInsertItem(Container* pContainer, int key) {
	int status, id = key;
	status = tSearchItem(pContainer, &id);
	if (status == 1)
		return -1;
	if (status == 0)
		return -2;
	if (pContainer->pTable->keysCount == pContainer->pTable->maxKeysCount)
		return -3;
	id = pContainer->pTable->keysCount - 1;
	if (pContainer->pKey[id] > key)
		while (id >= 0 && pContainer->pKey[id] > key) {
			pContainer->pKey[id + 1] = pContainer->pKey[id];
			id--;
		}
	id++;
	pContainer->pKey[id] = key;
	pContainer->pTable->keysCount++;
	//printf("id = %d, kc = %d\n", id, pContainer->pTable->keysCount);
	return id;
}

int tDeleteItem(Container* pContainer, int key) {
	int id, status = tSearchItem(pContainer, &key);
	if (status != 0)
		return -status;
	for (id = key; id < pContainer->pTable->keysCount - 1; id++)
		pContainer->pKey[id] = pContainer->pKey[id + 1];
	pContainer->pTable->keysCount--;
	//printf("id = %d, kc = %d\n", key, pContainer->pTable->keysCount);
	return key;
}

int tCopyRange(Container* pSource, Container** ppDestination, int minKey, int maxKey, char* pName) {
	int status, id, i, minId = 0;
	if (pSource == NULL || pSource->pKey == NULL || pSource->pTable == NULL)
		return -1;
	if (minKey > maxKey) {
		status = minKey;
		minKey = maxKey;
		maxKey = status;
	}
	status = tInit(ppDestination, pName, pSource->pTable->maxKeysCount);
	if (status == 1)
		return -2;
	i = 0;
	for (id = 0; id < pSource->pTable->keysCount; id++) {
		if (pSource->pKey[id] >= minKey && pSource->pKey[id] <= maxKey) {
			if (i == 0)
				minId = id;
			(*ppDestination)->pKey[i] = pSource->pKey[id];
			(*ppDestination)->pTable->keysCount++;
			i++;
		}
	}
	return minId;
}