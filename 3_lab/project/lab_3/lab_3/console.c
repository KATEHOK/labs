#ifndef APP_H
#include "app.h"
#endif // !APP_H

TablesList* tablesListInit() {
	TablesList* pTables = (TablesList*)malloc(sizeof(TablesList));
	pTables->pTop = NULL;
	return pTables;
}

struct TablesItem* tablesListSearchItem(TablesList* pTablesList, Table* pTable) {
	struct TablesItem* pCur = pTablesList->pTop;
	if (pCur == NULL)
		return NULL;
	if (pCur->pTable == pTable)
		return pCur;
	while (pCur->pNext != NULL) {
		pCur = pCur->pNext;
		if (pCur->pTable == pTable)
			return pCur;
	}
	return NULL;
}

Table* createTable(int ms1, int ms2) {
	Table* pTable;
	int status = tableInit(&pTable, ms1, ms2);
	if (status == 0)
		return pTable;
	return NULL;
}

int tablesListAddItem(TablesList* pTablesList, Table* pTable) {
	struct TablesItem* pRes;
	if (pTable == NULL)
		return 1;
	pRes = tablesListSearchItem(pTablesList, pTable);
	if (pRes != NULL)
		return 2;
	pRes = (struct TablesItem*)malloc(sizeof(struct TablesItem));
	if (pRes == NULL)
		return 3;
	pRes->pNext = pTablesList->pTop;
	pRes->pPrev = NULL;
	pRes->pTable = pTable;
	pTablesList->pTop = pRes;
	if (pRes->pNext != NULL)
		pRes->pNext->pPrev = pRes;
	return 0;
}

int tablesListDeleteItem(TablesList* pTablesList, Table* pTable) {
	struct TablesItem* pItem;
	pItem = tablesListSearchItem(pTablesList, pTable);
	if (pItem == NULL)
		return 1;
	if (pItem == pTablesList->pTop)
		pTablesList->pTop = pItem->pNext;
	if (pItem->pPrev != NULL)
		pItem->pPrev->pNext = pItem->pNext;
	if (pItem->pNext != NULL)
		pItem->pNext->pPrev = pItem->pPrev;
	tableDelete(pTable);
	free(pItem);
	return 0;
}

int tablesListDelete(TablesList* pTablesList) {
	int status;
	while (pTablesList->pTop != NULL) {
		status = tablesListDeleteItem(pTablesList, pTablesList->pTop->pTable);
		if (status > 0)
			return 1;
	}
	free(pTablesList);
	return 0;
}
