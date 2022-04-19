#ifndef APP_H
#include "app.h"
#endif // !APP_H



int main() {
	int status;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");

	while (1 == 1) {
		TablesList* pTL = tablesListInit();

		/*Table* pTable = createTable(16, 4);
		status = tablesListAddItem(pTL, pTable);
		pTable = createTable(16, 4);
		status = tablesListAddItem(pTL, pTable);
		pTable = createTable(16, 4);
		status = tablesListAddItem(pTL, pTable);
		pTable = createTable(16, 4);
		status = tablesListAddItem(pTL, pTable);
		struct TablesItem* pItem = pTL->pTop;
		//printf("pItem: %p\n", pItem);
		while (pItem != NULL) {
			tablePrint(pItem->pTable, 1);
			//printf("pTable: %p ? ", pItem->pTable);
			//printf("pTable: %p\n", (tablesListSearchItem(pTL, pItem->pTable))->pTable);
			pItem = pItem->pNext;
		}
		printf("Del: %d\n", tablesListDelete(pTL));*/

		status = tablesListDelete(pTL);
		system("pause");
		printf("\n");
	}
	return 0;
}