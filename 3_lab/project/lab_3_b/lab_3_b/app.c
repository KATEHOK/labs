#ifndef APP_H
#include "app.h"
#endif

int main() {
	int status = 0;
	Container* pContainer = NULL;
	char* ppStart[2] = { "Open table", "Make new table" };
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");

	while (status == 0) {
		status = console("What do You want to do?", ppStart, 2);
		if (status == 0)
			break;
		if (status == 1) {
			status = dOpen(&pContainer);
			if (status == 1)
				break;
			if (status == 2) {
				status = 0;
				continue;
			}
			status = dProcessTable(pContainer);
			if (status == 1)
				break;
		} else {
			status = dMakeNew(&pContainer);
			if (status == 1 || status == 2)
				break;
			status = 0;
		}
	}
	printf("See You later!\n");
	system("pause");
	return 0;
}