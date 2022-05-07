#ifndef APP_H
#include "app.h"
#endif

int createFormatFile(char* pFilename, int maxKeysCount) {
	int err;
	FILE* pFile;
	Table table = {{'\0'}, 0, maxKeysCount};
	err = fopen_s(&pFile, pFilename, "w");
	if (err != 0)
		return 1;
	fclose(pFile);
	return 0;
}

int upload(Container* pContainer, int* pInfo) {
	int err, id;
	long offset = sizeof(Table);
	FileItem fileItem = {0, 0};
	FILE* pFile;
	if (pContainer == NULL || pContainer->pTable == NULL ||
		pContainer->pKey == NULL || pInfo == NULL)
		return 1;
	err = fopen_s(&pFile, pContainer->pTable->name, "w");
	if (err != 0)
		return 2;
	rewind(pFile);
	fwrite(pContainer->pTable, sizeof(Table), 1, pFile);
	for (id = 0; id < pContainer->pTable->keysCount; id++) {
		fileItem.key = pContainer->pKey[id];
		fileItem.info = pInfo[id];
		fseek(pFile, offset, SEEK_SET);
		fwrite(&fileItem, sizeof(FileItem), 1, pFile);
		offset += sizeof(FileItem);
	}
	fclose(pFile);
	return 0;
}

int download(char* pName, Table** ppTable, int** ppKey) {
	int err, i;
	long offset;
	FILE* pFile;
	FileItem fileItem;
	err = fopen_s(&pFile, pName, "r");
	if (err != 0 )
		return 1;
	rewind(pFile);
	*ppTable = (Table*)malloc(sizeof(Table));
	if (*ppTable == NULL) {
		fclose(pFile);
		return 2;
	}
	if (!feof(pFile))
		fread(*ppTable, sizeof(Table), 1, pFile);
	else {
		fclose(pFile);
		free(*ppTable);
		return 3;
	}
	*ppKey = (int*)malloc((*ppTable)->maxKeysCount * sizeof(int));
	if (*ppKey == NULL) {
		fclose(pFile);
		free(*ppTable);
		return 2;
	}
	offset = sizeof(Table);
	for (i = 0; i < (*ppTable)->keysCount; i++) {
		fseek(pFile, offset, SEEK_SET);
		fread(&fileItem, sizeof(FileItem), 1, pFile);
		(*ppKey)[i] = fileItem.key;
		offset += sizeof(FileItem);
	}
	fclose(pFile);
	return 0;
}

int fInsertItem(Table* pTable, int key, int id, int info) {
	long offsetCounter,	offset = sizeof(Table) + id * sizeof(FileItem);
	FILE* pFile;
	int err;
	FileItem fileItem;
	err = fopen_s(&pFile, pTable->name, "r+b");
	if (err != 0)
		return 1;
	for (offsetCounter = sizeof(Table) + (pTable->keysCount - 1) * sizeof(FileItem);
		offsetCounter > offset; offsetCounter -= sizeof(FileItem)) {
		fseek(pFile, offsetCounter - sizeof(FileItem), SEEK_SET);
		fread(&fileItem, sizeof(FileItem), 1, pFile);
		fseek(pFile, offsetCounter, SEEK_SET);
		fwrite(&fileItem, sizeof(FileItem), 1, pFile);
	}
	fileItem.info = info;
	fileItem.key = key;
	fseek(pFile, offsetCounter, SEEK_SET);
	fwrite(&fileItem, sizeof(FileItem), 1, pFile);
	rewind(pFile);
	fwrite(pTable, sizeof(Table), 1, pFile);
	fclose(pFile);
	return 0;
}

int fDeleteItem(Table* pTable, int id) {
	long offsetCounter, offsetMax = sizeof(Table) + (pTable->keysCount - 1) * sizeof(FileItem);
	FILE* pFile;
	int err;
	FileItem fileItem;
	err = fopen_s(&pFile, pTable->name, "r+b");
	if (err != 0)
		return 1;
	for (offsetCounter = sizeof(Table) + id * sizeof(FileItem);
		offsetCounter < offsetMax; offsetCounter += sizeof(FileItem)) {
		fseek(pFile, offsetCounter + sizeof(FileItem), SEEK_SET);
		fread(&fileItem, sizeof(FileItem), 1, pFile);
		fseek(pFile, offsetCounter, SEEK_SET);
		fwrite(&fileItem, sizeof(FileItem), 1, pFile);
	}
	rewind(pFile);
	fwrite(pTable, sizeof(Table), 1, pFile);
	fclose(pFile);
	return 0;
}

int fCopyRange(Table* pTableSource, Table* pTableDestination, int idFrom) {
	FILE* pSource, *pDestination;
	FileItem* pFileItem;
	int err, itemsCount = pTableDestination->keysCount;
	err = fopen_s(&pSource, pTableSource->name, "r");
	if (err != 0)
		return 1;
	err = fopen_s(&pDestination, pTableSource->name, "w");
	if (err != 0) {
		fclose(pSource);
		return 2;
	}
	pFileItem = (FileItem*)malloc(sizeof(FileItem) * itemsCount);
	if (pFileItem == NULL) {
		fclose(pSource);
		fclose(pDestination);
		remove(pTableDestination->name);
		return 3;
	}
	rewind(pDestination);
	fwrite(pTableDestination, sizeof(Table), 1, pDestination);
	fseek(pSource, sizeof(Table) + idFrom * sizeof(FileItem), SEEK_SET);
	fseek(pDestination, sizeof(Table), SEEK_SET);
	fread(pFileItem, itemsCount * sizeof(FileItem), 1, pSource);
	fwrite(pFileItem, itemsCount * sizeof(FileItem), 1, pDestination);
	fclose(pSource);
	fclose(pDestination);
	return 0;
}

int fGetInfo(Table* pTable, int* pId_pAns) {
	FILE* pFile;
	FileItem fileItem;
	int err;
	err = fopen_s(&pFile, pTable->name, "r");
	if (err != 0)
		return 1;
	fseek(pFile, sizeof(Table) + (*pId_pAns) * sizeof(FileItem), SEEK_SET);
	fread(&fileItem, sizeof(FileItem), 1, pFile);
	*pId_pAns = fileItem.info;
	fclose(pFile);
	return 0;
}

int fGetAllInfo(Table* pTable, int** ppInfo) {
	FILE* pFile;
	FileItem fileItem;
	long offset;
	int i, err = fopen_s(&pFile, pTable->name, "r");
	if (err != 0)
		return 1;
	*ppInfo = (int*)malloc(sizeof(int) * pTable->keysCount);
	if (*ppInfo == NULL) {
		fclose(pFile);
		return 2;
	}
	offset = sizeof(Table);
	for (i = 0; i < pTable->keysCount; i++) {
		fseek(pFile, offset, SEEK_SET);
		fread(&fileItem, sizeof(FileItem), 1, pFile);
		offset += sizeof(FileItem);
		(*ppInfo)[i] = fileItem.info;
	}
	fclose(pFile);
	return 0;
}