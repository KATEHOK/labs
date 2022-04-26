#ifndef APP_H
#include "app.h"
#endif // !APP_H


void printList(char** ppList, int lenList) {
	int i;
	for (i = 0; i < lenList; i++)
		printf("%d) %s\n", i + 1, ppList[i]);
}

int console(char* pQuestion, char** ppList, int lenList) {
	int status, answer = lenList + 1;
	while (answer > lenList) {
		printf("%s\nEnter number of point:\n", pQuestion);
		printList(ppList, lenList);
		status = getNat(&answer);
		if (status == 1)
			return 0;
		if (answer > lenList)
			printf("'%d' is invalid point! Please retry!\n\n", answer);
	}
	return answer;
}

int startConsole() {
	char** ppList[2] = {"Init list of tables", "Exit"};
	printf("\n---Start menu---\n");
	return console("What do You want to do?", ppList, 2);
}

int confirmConsole(char* pQuestion) {
	char** ppList[2] = {"Yes", "No"};
	return console(pQuestion, ppList, 2);
}

int exitConsole(TablesList* pTL) {
	int status;
	printf("\n---Exit menu---\n");
	status = confirmConsole("Do You want to exit?");
	if (status == 1) {
		printf("See You later!\n");
		tablesListDelete(pTL);
		return 0;
	}
	return 1;
}

Table* selectTableConsole(TablesList* pTL) {
	struct TablesItem* pTablesItem = NULL;
	int status, answer = -1;
	printf("\n---Select menu---\n");
	while (answer < 0) {
		tablesListPrint(pTL);
		printf("Enter index of table or '-1' to exit\n");
		status = getInt(&answer);
		if (status == 1 || answer == -1)
			return NULL;
		if (answer < -1) {
			printf("'%d' is invalid index! Please retry!\n\n", answer);
			continue;
		}
		pTablesItem = tablesListSearchItem(pTL, NULL, answer);
		if (pTablesItem == NULL) {
			printf("'%d' is invalid index! Please retry!\n\n", answer);
			answer = -1;
		}
	}
	return pTablesItem->pTable;
}

int processSelectedTable(Table* pTable) {
	printf("\n---Table process menu---\n");
	printf("Processing...\n");
	return 0;
}

int addTableConsole(TablesList* pTL) {
	int status;
	printf("\n---New table menu---\n");
	status = tablesListAddItem(pTL, createTable(0, 0));
	return status;
}