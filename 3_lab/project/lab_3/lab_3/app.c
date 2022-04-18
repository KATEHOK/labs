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

		/*
		printf("add: %d\n", tableAdd(pTable, 517, 32, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 557, 32, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 507, 32, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 57, 32, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 87, 67, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 5656, 67, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 2, 67, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 8, 67, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 32, 67, 0, 0, makeNewItem(NULL)));
		printf("add: %d\n", tableAdd(pTable, 56, 67, 0, 0, makeNewItem(NULL)));
		printByKS2(pTable);
		printByKS1(pTable);
		Table* pSearched1 = tableSearchItemBySingle(pTable, 87, 1);
		Table* pSearched2 = tableSearchItemBySingle(pTable, 67, 2);
		Table* pSearched3 = tableSearchItemBySingle(pTable, 0, 1);
		printf("tables\n");
		printByKS2(pSearched1);
		printByKS2(pSearched2);
		printByKS2(pSearched3);
		tableDelete(pSearched1);
		tableDelete(pSearched2);
		tableDelete(pSearched3);*/

		tableDelete(pTable);
		system("pause");
		printf("\n");
	}
	return 0;
}