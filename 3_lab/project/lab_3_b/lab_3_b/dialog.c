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

int dInsertItem(Table* pTable) {
	//pTable --> oTable (offset), pKey --> oKey (offset)
	int status, key, info;
	Key* pKey;
	printf("\nEnter new key\n");
	status = getInt(&key);
	if (status == 1)
		return 1;
	while (searchKey(pTable, &pKey, key) == 0) {
		printf("Key must be unique!\n\nEnter new key\n");
		status = getInt(&key);
		if (status == 1)
			return 1;
	}
	printf("\nEnter info\n");
	status = getInt(&info);
	if (status == 1)
		return 1;
	status = insertItem(pTable, &pKey, key, info, 0);
	if (status == 1)
		printf("Oversize!\n\n");
	else
		printf("Successfully!\nId: %d; Key: %d; Info: %d.\n\n",
			pKey->pItem->keyId, pKey->value, pKey->pItem->info);
	return 0;
}

int dDeleteItem(Table* pTable) {
	//pTable --> oTable (offset), pKey --> oKey (offset)
	int status, key;
	Key* pKey;
	printf("\nEnter key\n");
	status = getInt(&key);
	if (status == 1)
		return 1;
	if (searchKey(pTable, &pKey, key) == 1)
		printf("Key was not found!\n\n");
	else {
		status = deleteItem(pTable, pKey, key, 0);
		printf("Successfully deleted!\n\n");
	}
	return 0;
}
