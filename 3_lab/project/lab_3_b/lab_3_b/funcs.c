#ifndef APP_H
#include "app.h"
#endif

int delete(Container* pContainer) {
	if (pContainer == NULL || pContainer->pKey == NULL || pContainer->pTable == NULL)
		return 1;
	remove(pContainer->pTable->name);
	free(pContainer->pKey);
	free(pContainer->pTable);
	free(pContainer);
	return 0;
}

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
	status = tInsertItem(pContainer, key);
	if (status < 0)
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
	status = fGetInfo(pContainer->pTable, pKey_pId_pInfo);
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
	int status, *pInfo;
	char key[4] = "Key", info[5] = "Info";
	status = fGetAllInfo(pContainer->pTable, &pInfo);
	if (status != 0)
		return status;
	if (pContainer->pTable->keysCount == 0) {
		printf("\nTable %s is free!\n\n", pContainer->pTable->name);
		return 0;
	}
	printf("\nTable: %s\n", pContainer->pTable->name);
	printf("%7s * %7s * id\n", key, info);
	for (status = 0; status < pContainer->pTable->keysCount; status++)
		printf("%7d | %7d | %2d\n", pContainer->pKey[status], pInfo[status], status);
	printf("\n");
	free(pInfo);
	return 0;
}

int open(Container** ppContainer, char* pName) {
	int status;
	status = download(pName, ppContainer);
	return status;
}