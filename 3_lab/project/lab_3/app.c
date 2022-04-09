#ifndef APP_H
#include "app.h"
#endif // !APP_H



int main() {
	int status;
	Table Table;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");

	status = tableInit(&Table);
	printf("%d %d\n", sizeof(struct KeySpace1), sizeof(struct KeySpace2));
	printf("%d\n", status);

	return 0;
}