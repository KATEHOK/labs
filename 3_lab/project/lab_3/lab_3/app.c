#ifndef APP_H
#include "app.h"
#endif // !APP_H



int main() {
	int status;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");

	while (1 == 1) {
		Table* pTable;
		status = tableInit(&pTable, 0, 0);
		printf("Init: %d\n", status);
		if (status > 0) {
			system("pause");
			return 0;
		}

		/*struct Item* pItem2 = (struct Item*)malloc(sizeof(struct Item));
		pItem2->pNext = NULL;
		pItem2->pPrev = NULL;
		printf("add: %d\n", tableAdd(pTable, 0, 0, 1, 1, pItem1));
		printf("add: %d\n", tableAdd(pTable, 0, 0, 1, 1, pItem2));
		printByKS1(pTable);
		Table* pTable2 = searchRangeKS1(pTable, 0, 1);
		printByKS1(pTable2);
		tableDelete(pTable2);
		*/
		/*
		struct Item* pItem1 = (struct Item*)malloc(sizeof(struct Item));
		pItem1->pNext = NULL;
		pItem1->pPrev = NULL;
		printf("add: %d\n", tableAdd(pTable, 89, 34, 0, 0, pItem1));
		printByKS1(pTable);

		struct Item* pItem = tableSearchItemByComposite(pTable, 89, 34);
		printf("%d %d\n", pItem->key1, pItem->key2);
		*/

		printf("add 1: %d\n", tableAdd(pTable, 98, 45, 0, 0, makeNewItem(NULL)));
		printf("add 2: %d\n", tableAdd(pTable, 58, 49, 0, 0, makeNewItem(NULL)));
		printByKS1(pTable);
		status = tableDeleteItemByComposite(pTable, 58, 49);
		printf("del: %d\n", status);
		printByKS1(pTable);


		tableDelete(pTable);
		system("pause");
		printf("\n");
	}
	return 0;
}