#ifndef APP_H
#include "app.h"
#endif


int init(Container** ppContainer, char* pName, int maxKeyCount) {
	int status, tmp = 0;
	status = tInit(ppContainer, pName, maxKeyCount);
	if (status == 1)
		return 1;
	status = upload(*ppContainer, &tmp);
	if (status != 0) {
		status = tDelete(*ppContainer);
		if (status == 1)
			return 3;
		return 2;
	}
	return 0;
}

int insertItem(Container* pContainer, int key, int info) {
	int status;
	status = tInsertItem(pContainer, key, info);
	if (status != 0)
		return abs(status);
	status = fInsertItem(pContainer->pTable, key, status, info);
	if (status == 1) {
		status = tDeleteItem(pContainer, key);
		if (status < 0)
			return 5;
		return 4;
	}
	return 0;
}

int deleteItem(Container* pContainer, int key) {
	int status;
	status = tDeleteItem(pContainer, key);
	if (status < 0)
		return abs(status);
	status = fDeleteItem(pContainer->pTable, status);
	if (status != 0)
		return 3;
	return 0;
}

int copyRange(Container* pSource, Container** ppDestination, int minKey, int maxKey, char* pName) {
	int minId, status;
	minId = tCopyRange(pSource, ppDestination, minKey, maxKey, pName);
	if (minId < 0)
		return abs(minId);
	status = fCopyRange(pSource->pTable, (*ppDestination)->pTable, minId);
	if (status != 0) {
		if (tDelete(*ppDestination) != 0)
			return 6;
		return status + 2;
	}
	return 0;
}

int getInfo(Container* pContainer, int* pKey_pId_pInfo) {
	int status;
	status = tSearchItem(pContainer, pKey_pId_pInfo);
	if (status != 0)
		return status;
	status = fGetInfo(pContainer, pKey_pId_pInfo);
	if (status != 0)
		return 3;
	return 0;
}

int printItem(Container* pContainer, int key_info) {
	int status, key = key_info;
	status = getInfo(pContainer, &key_info);
	if (status == 0)
		printf("\nTable: %s\nKey: %d\nInfo: %d\n\n", pContainer->pTable->name, key, key_info);
	return status;
}

int print(Container* pContainer) {
	int* pInfo, status, id;
	status = fGetAllInfo(pContainer->pTable, &pInfo);
	if (status != 0)
		return status;
	if (pContainer->pTable->keysCount > 0)
		printf("\n* Table: %s\n*   key   *   info   *\n", pContainer->pTable->name);
	else
		printf("\nTable: %s - is free!\n", pContainer->pTable->name);
	for (id = 0; id < pContainer->pTable->keysCount; id++)
		printf("* %7d * %8d *\n", pContainer->pKey[id], pInfo[id]);
	printf("\n");
	free(pInfo);
	return 0;
}