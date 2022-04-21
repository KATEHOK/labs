#ifndef APP_H
#include "app.h"
#endif // !APP_H

TablesList* tablesListInit() {
	TablesList* pTables = (TablesList*)malloc(sizeof(TablesList));
	pTables->pTop = NULL;
	return pTables;
}

struct TablesItem* tablesListSearchItem(TablesList* pTablesList, Table* pTable, int id) {
	struct TablesItem* pCur = pTablesList->pTop;
	if (pCur == NULL)
		return NULL;
	if (pCur->pTable == pTable || pCur->id == id)
		return pCur;
	while (pCur->pNext != NULL) {
		pCur = pCur->pNext;
		if (pCur->pTable == pTable || pCur->id == id)
			return pCur;
	}
	return NULL;
}

Table* createTable(int ms1, int ms2) {
	Table* pTable;
	int id = 0;
	int status = tableInit(&pTable, ms1, ms2);
	if (status == 0)
		return pTable;
	return NULL;
}

int tablesListAddItem(TablesList* pTablesList, Table* pTable) {
	struct TablesItem* pRes;
	if (pTable == NULL)
		return 1;
	pRes = tablesListSearchItem(pTablesList, pTable, -1);
	if (pRes != NULL)
		return 2;
	pRes = (struct TablesItem*)malloc(sizeof(struct TablesItem));
	if (pRes == NULL)
		return 3;
	if (pTablesList->pTop == NULL)
		pRes->id = 0;
	else
		pRes->id = pTablesList->pTop->id + 1;
	pRes->pNext = pTablesList->pTop;
	pRes->pPrev = NULL;
	pRes->pTable = pTable;
	pTablesList->pTop = pRes;
	if (pRes->pNext != NULL)
		pRes->pNext->pPrev = pRes;
	return 0;
}

int tablesListDeleteItem(TablesList* pTablesList, Table* pTable, int id) {
	struct TablesItem* pItem;
	pItem = tablesListSearchItem(pTablesList, pTable, id);
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
		status = tablesListDeleteItem(pTablesList, pTablesList->pTop->pTable, -1);
		if (status > 0)
			return 1;
	}
	free(pTablesList);
	return 0;
}

void tablesListPrint(TablesList* pTablesList) {
	struct TablesItem* pItem = pTablesList->pTop;
	printf("\nTables:\n");
	while (pItem != NULL) {
		printf("#%d\n", pItem->id);
		pItem = pItem->pNext;
	}
	printf("\n");
}
