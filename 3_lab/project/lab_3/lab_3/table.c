#ifndef APP_H
#include "app.h"
#endif // !APP_H


int tableInit(Table** ppTable, int maxSize1, int maxSize2) {
	int status, i;
	struct KeySpace2* pTemp;
	*ppTable = (Table*)malloc(sizeof(Table));
	if (*ppTable == NULL)
		return 2;
	(*ppTable)->countKeys1 = 0;
	(*ppTable)->countKeys2 = 0;
	(*ppTable)->maxKey1 = 0;
	(*ppTable)->maxKey2 = 0;
	if (maxSize1 == 0) {
		status = setMaxSizeKS(&maxSize1, 1);
		if (status == 1) {
			free(*ppTable);
			return 1;
		}
	}
	if (maxSize2 == 0) {
		status = setMaxSizeKS(&maxSize2, 2);
		if (status == 1) {
			free(*ppTable);
			return 1;
		}
	}
	(*ppTable)->maxSize1 = maxSize1;
	(*ppTable)->maxSize2 = maxSize2;
	(*ppTable)->pKS1 = (struct KeySpace1*)malloc(maxSize1 * sizeof(struct KeySpace1));
	if ((*ppTable)->pKS1 == NULL) {
		free(*ppTable);
		return 2;
	}
	(*ppTable)->pKS2 = (struct KeySpace2*)malloc(maxSize2 * sizeof(struct KeySpace2));
	if ((*ppTable)->pKS2 == NULL) {
		free((*ppTable)->pKS1);
		free(*ppTable);
		return 2;
	}
	pTemp = (*ppTable)->pKS2;
	for (i = 0; i < maxSize2; i++) {
		pTemp->pNext = NULL;
		pTemp->pPrev = NULL;
		pTemp->pData = NULL;
		pTemp->key = i;
		pTemp->release = -1;
		pTemp++;
	}
	return 0;
}

void tableDelete(Table* pTable) {
	int i;
	struct KeySpace2* pKS2;
	if (pTable != NULL) {
		free(pTable->pKS1);
		for (i = 0; i < pTable->maxSize2; i++) {
			pKS2 = pTable->pKS2 + i;
			if (pKS2->pNext != NULL) {
				do {
					pKS2 = pKS2->pNext;
					//TODO очистка информации из
					deleteItemFromList(pKS2->pData);
					if (pKS2->pPrev != pTable->pKS2 + i)
						free(pKS2->pPrev);
				} while (pKS2->pNext != NULL);
				if (pKS2 != pTable->pKS2 + i)
					free(pKS2);
			}
		}
		free(pTable->pKS2);
		free(pTable);
	}
}

int tableAdd(Table* pTable, int key1, int key2, int isKey1True, int isKey2True, struct Item* pData) {
	int status;
	status = insertKS1(pTable, key1, pData, isKey1True);
	if (status > 0)
		return status;
	status = insertKS2(pTable, key2, pData, isKey2True);
	if (status == 1)
		return 3;
	return 0;
}

struct Item* tableSearchItemByComposite(Table* pTable, int key1, int key2) {
	int status, key1Id;
	struct Item* pItem;
	key1Id = searchKS1(pTable, key1);
	if (key1 == -1)
		return NULL;
	pItem = pTable->pKS1[key1Id].pData;
	printf("%p\n", pItem);
	if (key2 != pItem->key2)
		return NULL;
	return pItem;
}

int tableDeleteItemByComposite(Table* pTable, int key1, int key2) {
	int status;
	struct Item* pItem = tableSearchItemByComposite(pTable, key1, key2);
	if (pItem == NULL)
		return 1;
	status = deleteKS1(pTable, pItem->key1);
	if (status == 1)
		return 2;
	status = deleteKS2(pTable, pItem->key2, pItem->p2->release, 0);
	if (status <= 0) {
		status = insertKS1(pTable, pItem->key1, pItem, 0);
		if (status > 0)
			return 4;
		return 3;
	}
	deleteItemFromList(pItem);
	return 0;
}

struct Item* tableSearchItemBySingle(Table*, int);
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

int insertKS1(Table* pTable, int key, struct Item* pData, int isKeyTrue) {
	int i;
	// переполнение
	if (pTable->countKeys1 == pTable->maxSize1)
		return 1;
	if (isKeyTrue == 1)
		key = pTable->maxKey1 + 1;
	// дублирование ключей
	i = searchKS1(pTable, key);
	if (i > -1)
		return 2;
	if (pTable->countKeys1 == 0) {
		pTable->pKS1[0].key = key;
		pTable->pKS1[0].pData = pData;
		pData->key1 = key;
		pData->id1 = 0;
		pData->p1 = pTable->pKS1;
	} else {
		for (i = pTable->countKeys1 - 1; i >= 0; i--) {
			if (pTable->pKS1[i].key <= key) {
				pTable->pKS1[i + 1].key = key;
				pTable->pKS1[i + 1].pData = pData;
				pData->key1 = key;
				pData->id1 = i + 1;
				pData->p1 = pTable->pKS1 + i + 1;
				break;
			} else
				pTable->pKS1[i + 1] = pTable->pKS1[i];
			if (i == 0) {
				pTable->pKS1->key = key;
				pTable->pKS1->pData = pData;
				pData->key1 = key;
				pData->id1 = 0;
				pData->p1 = pTable->pKS1;
			}
		}
	}
	if (pTable->countKeys1 == 0 || key > pTable->maxKey1)
		pTable->maxKey1 = key;
	pTable->countKeys1++;
	return 0;
}

int getHash(int key, int size) {
	return abs((key * 2147483647) % size);
}

int searchKS2(struct KeySpace2** ppRes, Table* pTable, int key, int release) {
	struct KeySpace2 *pKS = pTable->pKS2 + getHash(key, pTable->maxSize2);
	int counter = 0;
	if (pKS->pNext == NULL)
		return 0;
	while (pKS->pNext) {
		pKS = pKS->pNext;
		if (pKS->key == key) {
			if (release == -2) {
				*ppRes = pKS;
				return 1;
			} else if (release == -1) {
				ppRes[counter] = pKS;
				counter++;
			} else if (pKS->release == release) {
				*ppRes = pKS;
				return 1;
			}
		}
	}
	return counter;
}

int insertKS2(Table* pTable, int key, struct Item* pData, int isKeyTrue) {
	int lastRelease, hash, status;
	struct KeySpace2* pNew, *pLast;
	if (isKeyTrue == 1)
		key = pTable->maxKey2 + 1;
	status = searchKS2(&pLast, pTable, key, -2);
	if (status == 0)
		lastRelease = -1;
	else
		lastRelease = pLast->release;
	pNew = (struct KeySpace2*)malloc(sizeof(struct KeySpace2));
	if (pNew == NULL)
		return 1;
	hash = getHash(key, pTable->maxSize2);
	pNew->key = key;
	pNew->release = lastRelease + 1;
	pNew->pData = pData;
	pNew->pNext = (pTable->pKS2 + hash)->pNext;
	pNew->pPrev = pTable->pKS2 + hash;
	if ((pTable->pKS2 + hash)->pNext != NULL)
		(pTable->pKS2 + hash)->pNext->pPrev = pNew;
	(pTable->pKS2 + hash)->pNext = pNew;
	pNew->pData->id2 = hash;
	pNew->pData->key2 = key;
	pNew->pData->p2 = pNew;
	if (pTable->countKeys2 == 0 || key > pTable->maxKey2)
		pTable->maxKey2 = key;
	pTable->countKeys2++;
	return 0;
}

int deleteKS2(Table* pTable, int key, int release, int doNotTouch) {
	int len, deleted, i;
	struct KeySpace2 *pTemp, **ppSynonims = NULL;
	ppSynonims = (struct KeySpace2**)malloc(sizeof(struct KeySpace2*) * pTable->countKeys2);
	if (ppSynonims == NULL)
		return -1;
	len = searchKS2(ppSynonims, pTable, key, release);
	deleted = 0;
	for (i = 0; i < len; i++) {
		if (doNotTouch > 0)
			doNotTouch--;
		else {
			pTemp = ppSynonims[i];
			ppSynonims[i]->pPrev->pNext = ppSynonims[i]->pNext;
			if (ppSynonims[i]->pNext != NULL)
				ppSynonims[i]->pNext->pPrev = ppSynonims[i]->pPrev;
			free(pTemp);
			deleted++;
		}
	}
	pTable->countKeys2 -= deleted;
	free(ppSynonims);
	return deleted;
}

Table* searchRangeKS1(Table* pTable, int minKey, int maxKey) {
	Table* pResTable;
	struct Item* pChild;
	int status, key, keyId;
	status = tableInit(&pResTable, pTable->maxSize1, pTable->maxSize2);
	if (status == 1) {
		free(pResTable);
		return NULL;
	}
	if (minKey > maxKey) {
		key = minKey;
		minKey = maxKey;
		maxKey = key;
	}
	for (key = minKey; key <= maxKey; key++) {
		keyId = searchKS1(pTable, key);
		if (keyId == -1)
			continue;
		// вставка элемента
		pChild = makeChild(pTable->pKS1[keyId].pData);
		if (pChild == NULL) {
			tableDelete(pResTable);
			return NULL;
		}
		status = tableAdd(pResTable, key, pTable->pKS1[keyId].pData->key2, 0, 0, pChild);
		if (status > 0) {
			deleteItemFromList(pChild);
			tableDelete(pResTable);
			return NULL;
		}
	}
	return pResTable;
}

void printByKS1(Table* pTable) {
	int i;
	printf("\n");
	if (pTable != NULL) {
		for (i = 0; i < pTable->countKeys1; i++) {
			printf("(%2d) k1 %2d, k2 %2d, r %1d\n", i, pTable->pKS1[i].pData->key1,
				pTable->pKS1[i].pData->key2, pTable->pKS1[i].pData->p2->release);
		}
		if (pTable->countKeys1 == 0)
			printf("Table is empty!\n");	}
	else
		printf("Table is not exist!\n");
	printf("\n");
}

struct Item* makeChild(struct Item* pPrev) {
	struct Item* pChild;
	pChild = (struct Item*)malloc(sizeof(struct Item));
	if (pChild == NULL)
		return NULL;
	pChild->pPrev = pPrev;
	pChild->pNext = NULL;
	while (pPrev->pNext != NULL)
		pPrev = pPrev->pNext;
	pPrev->pNext = pChild;
	return pChild;
}

void deleteItemFromList(struct Item* pCurrent) {
	if (pCurrent->pPrev)
		pCurrent->pPrev->pNext = pCurrent->pNext;
	if (pCurrent->pNext)
		pCurrent->pNext->pPrev = pCurrent->pPrev;
	free(pCurrent);
}

struct Item* makeNewItem(char* pInfo) {
	struct Item* pItem = (struct Item*)malloc(sizeof(struct Item));
	if (pItem == NULL)
		return NULL;
	pItem->id1 = -1;
	pItem->id2 = -1;
	pItem->p1 = NULL;
	pItem->p2 = NULL;
	pItem->pNext = NULL;
	pItem->pPrev = NULL;
	pItem->pInfo = pInfo;
	return pItem;
}

Table* searchByKeyOrRelease(Table* pTable, int key, int release) {
	struct KeySpace2** ppCells;
	Table* pNewTable;
	int status, count, i = 0;
	status = tableInit(&pNewTable, pTable->maxSize1, pTable->maxSize2);
	if (status > 0)
		return NULL;
	ppCells = (struct KeySpace2**)malloc(pTable->countKeys2 * sizeof(struct KeySpace2*));
	if (ppCells == NULL) {
		tableDelete(pNewTable);
		return NULL;
	}
	count = searchKS2(ppCells, pTable, key, release);
	for (i = 0; i < count; i++) {
		status = tableAdd(pNewTable, ppCells[i]->pData->key1,
			ppCells[i]->key, 0, 0, makeChild(ppCells[i]->pData));
		if (status > 0) {
			tableDelete(pNewTable);
			free(ppCells);
			return NULL;
		}
	}
	free(ppCells);
	return pNewTable;
}

int tableClean(Table* pTable, int release) {}