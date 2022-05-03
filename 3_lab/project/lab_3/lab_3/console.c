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

int printConsole() {
	int ks;
	char** ppList[3] = {"The first keyspace", "The second keyspace", "Both keyspaces"};
	ks = console("What keyspace do you want to print on?", ppList, 3);
	return ks;
}

int processSelectedTable(Table* pTable, TablesList* pTL) {
	int *pInfo, answer, key1, key2, status = 0;
	struct Item* pItem, **ppItem;
	Table* pNewTable;
	char** ppList[11] = {
		"Add element",
		"Search element by composite",
		"Delete element by composite",
		"Search element(s) by single",
		"Delete element(s) by single",
		"Print table",
		"Make table-range",
		"Make table-including one/all release(s)",
		"Reorganise table",
		"Delete table",
		"Exit"
	};
	printf("\n---Table process menu---\n");

	while (status == 0) {
		answer = console("What do You want to do?", ppList, 11);
		switch (answer) {
		case 1:
			printf("Enter key 1\n");
			answer = getInt(&key1);
			if (answer == 1)
				return 1;
			printf("Enter key 2\n");
			answer = getInt(&key2);
			if (answer == 1)
				return 1;
			pInfo = (int*)malloc(sizeof(int));
			if (pInfo == NULL) {
				printf("|-> Memory request was declined!\n");
				return 1;
			}
			printf("Enter info\n");
			answer = getInt(pInfo);
			answer = tableAdd(pTable, key1, key2, 0, 0, makeNewItem(pInfo));
			switch (answer) {
			case 1:
				printf("|-> Oversize!\n");
				break;
			case 2:
				printf("|-> Key is already exist!\n");
				break;
			case 3:
				printf("|-> Memory request was declined!\n");
				return 1;
				break;
			default:
				printf("Item was added\n");
				break;
			}
			break;
		case 2:
			printf("Enter the first key\n");
			answer = getInt(&key1);
			if (answer == 1)
				return 1;
			printf("Enter the second key\n");
			answer = getInt(&key2);
			if (answer == 1)
				return 1;
			pItem = tableSearchItemByComposite(pTable, key1, key2);
			if (pItem == NULL)
				printf("The item is not exist!\n");
			else {
				printf("-----\nKey 1: %d\nKey 2: %d; release: %d\nInfo: %d\n-----\n",
					pItem->key1, pItem->key2, pItem->p2->release, *(pItem->pInfo));
			}
			break;
		case 3:
			printf("Enter the first key\n");
			answer = getInt(&key1);
			if (answer == 1)
				return 1;
			printf("Enter the second key\n");
			answer = getInt(&key2);
			if (answer == 1)
				return 1;
			answer = tableDeleteItemByComposite(pTable, key1, key2);
			if (answer > 0)
				printf("|-> Item was not deleted! ");
			if (answer == 1)
				printf("Item is not exist\n");
			else if (answer == 3) {
				printf("Table was corrupted!\n");
				return 1;
			}
			else if (answer > 0)
				printf("Table was not corrupted!\n");
			else
				printf("Item was deleted!\n");
			break;
		case 4:
			printf("Enter the key\n");
			answer = getInt(&key1);
			if (answer == 1)
				return 1;
			ppItem = tableSearchItemBySingle(pTable, key1, &key2);
			if (key2 == 0)
				printf("Item(s) is/are not exist!\n");
			else {
				for (answer = 0; answer < key2; answer++) {
					printf("-----\nKey 1: %d\nKey 2: %d; release: %d\nInfo: %d\n",
						ppItem[answer]->key1, ppItem[answer]->key2,
						ppItem[answer]->p2->release, *(ppItem[answer]->pInfo));
				}
				free(ppItem);
			}
			break;
		case 5:
			printf("Enter the key\n");
			char** ppSubList[2] = {"Keyspace #1", "Keyspace #2"};
			answer = getInt(&key1);
			if (answer == 1)
				return 1;
			answer = console("What keyspace do You want to delet in?", ppSubList, 2);
			if (answer == 0)
				return 1;
			answer = tableDeleteItemBySingle(pTable, key1, answer);
			if (answer > 0)
				printf("Item(s) was/were not deleted! ");
			if (answer == 1)
				printf("Wrong keyspace number!\n");
			else if (answer == 2)
				printf("The item is not exist!\n");
			else if (answer == 4)
				printf("Table was not corrupted!\n");
			else if (answer == 3) {
				printf("Table was corrupted!\n");
				return 1;
			}
			else
				printf("Item was deleted!\n");
			break;
		case 6:
			answer = printConsole();
			if (answer == 0)
				return 1;
			tablePrint(pTable, answer);
			break;
		case 7:
			printf("Enter min key\n");
			answer = getInt(&key1);
			if (answer == 1)
				return 1;
			printf("Enter max key\n");
			answer = getInt(&key2);
			if (answer == 1)
				return 1;
			pNewTable = searchRangeKS1(pTable, key1, key2);
			//printf("%p %d\n", pNewTable, pNewTable->pKS1[0].key);
			answer = tablesListAddItem(pTL, pNewTable);
			//printf("%p %d\n", pNewTable, pNewTable->pKS1[0].key);
			if (answer == 1)
				printf("Table was not created!\n");
			else if (answer == 2)
				printf("Table is already exist!\n");
			else if (answer == 3)
				printf("|-> Memory request was declined!\n");
			else
				printf("Table was added! You can see it in the common list!\n");
			break;
		case 8:
			printf("Enter the second key\n");
			answer = getInt(&key2);
			if (answer == 1)
				return 1;
			printf("Enter number of release (-1 all releases, -2 the last release)\n");
			answer = getInt(&key1);
			if (answer == 1)
				return 1;
			if (key1 < -2)
				printf("Wrong nubmer of release!\n");
			else {
				pNewTable = searchByKeyOrRelease(pTable, key2, key1);
				answer = tablesListAddItem(pTL, pNewTable);
				if (answer == 1)
					printf("Table was not created!\n");
				else if (answer == 2)
					printf("Table is already exist!\n");
				else if (answer == 3)
					printf("|-> Memory request was declined!\n");
				else
					printf("Table was added! You can see it in the common list!\n");
			}
			break;
		case 9:
			printf("How many releases should be left (-1 default value)\n");
			answer = getInt(&key2);
			if (answer == 1)
				return 1;
			if (key2 < -1)
				printf("Wrong value!\n");
			else
				answer = tableClean(pTable, key2);
			break;
		case 10:
			answer = tablesListDeleteItem(pTL, pTable, -1);
			if (answer == 1)
				return 1;
			printf("Table was deleted!\n");
			status = 1;
			break;
		case 11:
			status = 1;
			break;
		default:
			return 1;
		}
		printf("\n");
	}
	return 0;
}

int addTableConsole(TablesList* pTL) {
	int status;
	printf("\n---New table menu---\n");
	status = tablesListAddItem(pTL, createTable(0, 0));
	return status;
}
