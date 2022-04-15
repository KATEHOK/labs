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

		
		struct Item* pItem1 = (struct Item*)malloc(sizeof(struct Item));
		struct Item* pItem2 = (struct Item*)malloc(sizeof(struct Item));
		pItem1->pNext = NULL;
		pItem1->pPrev = NULL;
		pItem2->pNext = NULL;
		pItem2->pPrev = NULL;
		printf("add: %d\n", tableAdd(pTable, 0, 0, 1, 1, pItem1));
		printf("add: %d\n", tableAdd(pTable, 0, 0, 1, 1, pItem2));
		printByKS1(pTable);
		Table* pTable2 = searchRangeKS1(pTable, 0, 1);
		printByKS1(pTable2);
		tableDelete(pTable2);
		

		tableDelete(pTable);
		system("pause");
		printf("\n");
	}
	return 0;
}