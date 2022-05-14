#ifndef APP_H
#include "app.h"
#endif

/*
* выводит список деймтвий и запрашивает действие
* Параметры:
* (char*) pQuestion - вопрос к пользователю;
* (char**) ppArray - массив вариантов действий;
* (int) len - длина массива.
* Вернет:
* -1 - конец файла;
* 0 - выход;
* >0 - действие.
*/
int console(char* pQuestion, char** ppArray, int len) {
	int i, answer = len + 1;
	char* msg = "";
	while (answer > len || answer < 0) {
		puts(msg);
		printf("\n%s\nChoose point:\n0) Exit\n", pQuestion);
		for (i = 0; i < len; i++)
			printf("%d) %s\n", i + 1, ppArray[i]);
		i = getInt(&answer);
		if (i == 1)
			return -1;
		msg = "Wrong value, please retry!";
		printf("\n");
	}
	return answer;
}

int dInsertItem(Container* pContainer) {
	int status, key, info;
	printf("\nEnter new key\n");
	status = getInt(&key);
	if (status == 1)
		return 1;
	printf("\nEnter info\n");
	status = getInt(&info);
	if (status == 1)
		return 1;
	status = insertItem(pContainer, key, info);
	switch (status) {
	case 0:
		printf("Successfuly!\n");
		return 0;
		break;
	case 1:
		printf("Wrong structure!\n");
		break;
	case 2:
		printf("Key is alreasy exist!\n");
		break;
	case 3:
		printf("Oversize!\n");
		break;
	case 4:
		printf("The file was not opened!\n");
		break;
	case 5:
		printf("Critical error! Table was corrupted!\n");
		break;
	}
	printf("\n");
	return status + 1;
}

int dDeleteItem(Container* pContainer) {
	int status, key;
	printf("\nEnter key\n");
	status = getInt(&key);
	if (status == 1)
		return 1;
	status = deleteItem(pContainer, key);
	switch (status) {
	case 0:
		printf("Successfuly!\n");
		return 0;
		break;
	case 1:
		printf("Wrong structure!\n");
		break;
	case 2:
		printf("Key is not exist!\n");
		break;
	case 3:
		printf("Critical error! Table was corrupted!\n");
		break;
	}
	printf("\n");
	return status + 1;
}

int dPrintItem(Container* pContainer) {
	int key, status;
	printf("Enter key\n");
	status = getInt(&key);
	if (status == 1)
		return 1;
	status = printItem(pContainer, key);
	if (status == 1) {
		printf("Wrong structure!\n");
		return 2;
	}
	if (status == 3) {
		printf("The file was not opened!\n");
		return 3;
	}
	if (status == 2)
		printf("Key is not exist!\n\n");
	return 0;
}

int dDelete(Container* pContainer) {
	int status;
	char* ppList[2] = { "Yes", "No" };
	status = console("Are You sure?", ppList, 2);
	if (status != 1) {
		if (status == -1)
			return 1;
		return 2;
	}
	status = delete(pContainer);
	if (status == 1) {
		printf("Wrong structure!\n");
		return 3;
	}
	return 0;
}

int dClose(Container* pContainer) {
	int status, *pInfo;
	char* ppList[2] = { "Yes", "No" };
	printf("\n");
	status = console("Are You sure?", ppList, 2);
	if (status != 1) {
		if (status == -1)
			return 1;
		printf("\n");
		return 2;
	}
	status = fGetAllInfo(pContainer->pTable, &pInfo);
	if (status == 1) {
		printf("The file was not opened!\n");
		return 3;
	}
	if (status == 2) {
		printf("Memory request was declined!\n\n");
		return 2;
	}
	status = upload(pContainer, pInfo);
	free(pInfo);
	if (status != 0) {
		if (status == 1)
			printf("Wrong structure!\n");
		else
			printf("The file was not opened!\n");
		return 3;
	}
	status = tDelete(pContainer);
	if (status == 1) {
		printf("Wrong structure!\n");
		return 3;
	}
	printf("Successfully!\n\n");
	return 0;
}

int dGetName(char** ppName) {
	int status = 2, i, j, len = 0;
	char pDict[25] = {'"', '~', '`', '@', '#',
		'№', '$', '%', '^', '&', '?',
		'*', '+', '=', '{', '}', '[',
		']', '|', '<', '>', ' ', '\0'};
	while (status == 2) {
		status = getStr(ppName);
		if (status == 1)
			return 1;
		for (i = 0; i < 16; i++) {
			if ((*ppName)[i] == '\0' && len > 0)
				return 0;
			for (j = 0; pDict[j] != '\0'; j++) {
				if (pDict[j] == (*ppName)[i]) {
					status = 2;
					break;
				}
			}
			len++;
			if (status == 2)
				break;
		}
	}
	return 0;
}

int dCopyRange(Container* pContainer, Container** ppNew) {
	char** ppList[2] = {"Stay with parent table", "Switch on the new table"};
	int status, minKey, maxKey;
	char pName = (char*)malloc(16 * sizeof(char));
	if (pName == NULL)
		return 2;
	printf("\nEnter name of new file\n");
	status = dGetName(&pName);
	if (status == 1) {
		free(pName);
		return 1;
	}
	printf("Enter min key\n");
	status = getInt(&minKey);
	if (status == 1) {
		free(pName);
		return 1;
	}
	printf("Enter max key\n");
	status = getInt(&maxKey);
	if (status == 1) {
		free(pName);
		return 1;
	}
	status = copyRange(pContainer, ppNew, minKey, maxKey, pName);
	free(pName);
	if (status == 1 || status == 3 || status == 6) {
		printf("Critical error!\n");
		return 2;
	}
	if (status != 0) {
		if (status == 2 || status == 5)
			printf("Memory request was declined!\n");
		else
			printf("New file was not created!\n");
		return 3;
	}
	printf("Successfuly!\n\n");
	status = console("What do You want to do?", ppList, 2);
	printf("\n");
	if (status != 2)
		return 3;
	return 0;
}

int dOpen(Container** ppContainer) {
	int status;
	char* pName = (char*)malloc(16 * sizeof(char));
	if (pName == NULL)
		return 1;
	printf("\nEnter name of table\n");
	status = dGetName(&pName);
	if (status == 1) {
		free(pName);
		return 1;
	}
	status = open(ppContainer, pName);
	if (status == 0) {
		printf("Successfuly!\n\n");
		free(pName);
		return 0;
	}
	if (status == 1)
		printf("File '%s' is not exist!\n", pName);
	else if (status == 2)
		printf("Memory request was declined!\n");
	else
		printf("File '%s' is free!\n", pName);
	printf("\n");
	free(pName);
	return 2;
}

int dMakeNew(Container** ppContainer) {
	int status, maxKeyCount;
	char* pName = (char*)malloc(16 * sizeof(char));
	if (pName == NULL)
		return 1;
	printf("\nEnter name of new table\n");
	status = dGetName(&pName);
	if (status == 1) {
		free(pName);
		return 1;
	}
	printf("Enter max count of items\n");
	status = getInt(&maxKeyCount);
	if (status == 1) {
		free(pName);
		return 1;
	}
	status = init(ppContainer, pName, maxKeyCount);
	tDelete(*ppContainer);
	if (status == 3) {
		printf("Critical error!\n\n");
		free(pName);
		return 2;
	}
	if (status == 0) {
		printf("Successfuly!\n\n");
		free(pName);
		return 0;
	}
	printf("Table was not created! ");
	if (status == 1)
		printf("Memory request was declined!\n\n");
	else
		printf("Table was not uploaded into file!\n\n");
	free(pName);
	return 3;
}

int dProcessTable(Container* pContainer) {
	int status = 0;
	Container* pNew;
	char* ppList[6] = { "Delete table", "Insert item", "Delete item",
		"Print item", "Print table", "Make new table by interval", };
	status = console("What do You want to do with the table?", ppList, 6);
	while (status >= 0) {
		switch (status) {
		case 0:
			status = dClose(pContainer);
			if (status == 0)
				return 0;
			if (status == 1 || status == 3)
				return 1;
		case 1:
			status = dDelete(pContainer);
			printf("%d\n", status);
			if (status == 0)
				return 0;
			if (status == 1 || status == 3)
				return 1;
			break;
		case 2:
			status = dInsertItem(pContainer);
			if (status == 1 || status >= 5) {
				status = delete(pContainer);
				return 1;
			}
			break;
		case 3:
			status = dDeleteItem(pContainer);
			if (status == 1 || status == 2 || status == 4) {
				status = delete(pContainer);
				return 1;
			}
			break;
		case 4:
			status = dPrintItem(pContainer);
			if (status > 0) {
				status = delete(pContainer);
				return 1;
			}
			break;
		case 5:
			status = print(pContainer);
			if (status == 1) {
				status = delete(pContainer);
				return 1;
			}
			if (status == 2)
				printf("Memory request was declined!\n");
			break;
		case 6:
			status = dCopyRange(pContainer, &pNew);
			if (status == 0) {
				free(pContainer->pKey);
				free(pContainer->pTable);
				free(pContainer);
				pContainer = pNew;
			}
			if (status <= 2) {
				status = delete(pContainer);
				return 1;
			}
			break;
		}
		status = console("What do You want to do with the table?", ppList, 6);
	}
	return 0;
}