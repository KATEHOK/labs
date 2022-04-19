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
		printf("Del: %d\n", tableDeleteItemBySingle(pTable, 32, 1));
		printByKS2(pTable);
		printByKS1(pTable);

		tableDelete(pTable);
		system("pause");
		printf("\n");
	}
	return 0;
}