#ifndef APP_H
#include "app.h"
#endif // !APP_H


int tableInit(Table* pTable) {
	int maxSize1 = 0, maxSize2 = 0, status, i;
	struct KeySpace2* pTemp;
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
	pTemp = pTable->pKS2;
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
	free(pTable->pKS1);
	for (i = 0; i < pTable->maxSize2; i++) {
		pKS2 = pTable->pKS2 + i;
		if (pKS2->pNext != NULL) {
			while (pKS2->pNext != NULL) {
				pKS2 = pKS2->pNext;
				//TODO очистка информации из pData
				printf("%p\n", pKS2);
				system("pause");
				free(pKS2->pData);
				free(pKS2->pPrev);
			}
			free(pKS2);
		}
	}
	free(pTable->pKS2);
}

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
	if (pTable->countKeys1 == 0) {
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

int insertKS2(Table* pTable, int key, Item* pData) {
	int lastRelease, hash, status;
	struct KeySpace2* pNew, *pLast;
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
	pTable->countKeys2++;
	printf("{%d} %p\n", key, pNew);
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
			/*printf("\n");
			for (int i = 0; i < pTable->maxSize2; i++) {
				struct KeySpace2* pKS = pTable->pKS2 + i;
				printf("{%d} ", i);
				while (pKS->pNext) {
					pKS = pKS->pNext;
					printf("(%d.%d) ", pKS->key, pKS->release);
				}
				printf("| ");
				while (pKS->pPrev) {
					pKS = pKS->pPrev;
					printf("(%d.%d) ", pKS->key, pKS->release);
				}
				printf("\n");
			}
			printf("\n");*/
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