#ifndef APP_H
#include "app.h"
#endif // !APP_H



int main() {
	int status;
	Table table;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");

	printf("%d %d\n", (int)sizeof(struct KeySpace1), (int)sizeof(struct KeySpace2));
	status = tableInit(&table);
	printf("Init: %d\n\n", status);

	/*
	Item test;
	printf("1 - oversize; 2 - key is already exist\n");
	status = insertKS1(&table, 34, &test);
	printf("Insert 34: %d\n", status);
	for (int i = 0; i < table.countKeys1; i++)
		printf("(%d) %d\n", i, table.pKS1[i].key);
	status = insertKS1(&table, 23, &test);
	printf("\nInsert 23: %d\n", status);
	for (int i = 0; i < table.countKeys1; i++)
		printf("(%d) %d\n", i, table.pKS1[i].key);
	status = insertKS1(&table, 23, &test);
	printf("\nInsert 23: %d\n", status);
	for (int i = 0; i < table.countKeys1; i++)
		printf("(%d) %d\n", i, table.pKS1[i].key);
	status = insertKS1(&table, 54, &test);
	printf("\nInsert 54: %d\n", status);
	for (int i = 0; i < table.countKeys1; i++)
		printf("(%d) %d\n", i, table.pKS1[i].key);
	status = insertKS1(&table, 60, &test);
	printf("\nInsert 60: %d\n", status);
	for (int i = 0; i < table.countKeys1; i++)
		printf("(%d) %d\n", i, table.pKS1[i].key);

	printf("\n1 - key is not exist\n");
	status = deleteKS1(&table, 34);
	printf("Delete 34: %d\n", status);
	status = deleteKS1(&table, 23);
	printf("Delete 23: %d\n", status);
	status = deleteKS1(&table, 23);
	printf("Delete 23: %d\n", status);
	status = deleteKS1(&table, 54);
	printf("Delete 54: %d\n", status);
	status = deleteKS1(&table, 60);
	printf("Delete 60: %d\n", status);
	*/


	return 0;
}