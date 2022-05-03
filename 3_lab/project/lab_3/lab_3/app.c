#ifndef APP_H
#include "app.h"
#endif // !APP_H



int main() {
	int status;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");

	status = startConsole();
	if (status == 2) {
		printf("See You later!\n");
		system("pause");
		return 0;
	}

	TablesList* pTL = tablesListInit();

	while (1 == 1) {
		char** ppList[3] = {"New table", "Select table", "Exit"};
		printf("\n---Main menu---\n");
		status = console("What do You want to do?", ppList, 3);
		if (status == 3) {
			printf("\n");
			status = exitConsole(pTL);
			if (status == 0)
				return;
			printf("\n");
		} else if (status == 2) {
			Table* pTable = selectTableConsole(pTL);
			if (pTable == NULL)
				continue;
			status = processSelectedTable(pTable, pTL);
			if (status == 1) {
				printf("|-> Error!\n");
				break;
			}
		} else if (status == 1) {
			status = addTableConsole(pTL);
			if (status == 1)
				printf("New table was not added!\n");
			else
				printf("New table was added successfully!\n");
		} else {
			printf("|-> Structure of the list of tables was corrupted!\n");
			break;
		}
	}
	status = tablesListDelete(pTL);
	printf("See You later!\n");
	system("pause");
	return 0;
}