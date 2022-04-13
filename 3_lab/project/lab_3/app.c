#ifndef APP_H
#include "app.h"
#endif // !APP_H



int main() {
	int status;
	Table table;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");

	while (1 == 1) {
		status = tableInit(&table);
		printf("Init: %d\n\n", status);

		printf("CK2: %d\n", table.countKeys2);

		tableDelete(&table);
		system("pause");
		printf("\n");
	}
	return 0;
}