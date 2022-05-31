#ifndef APP_H
#include "app.h"
#endif // !APP_H


int main() {
	int status = 0;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n");

	Tree* pTree;
	char* ppList[3] = {
		"Make free tree",//1
		"Download tree from file",//2
		"Check time",//3
	};

	while (status == 0) {
		printf("\n");
		status = console("What do You want to do?", ppList, 3);

		switch (status) {
		case 0:
			status = 1;
			break;

		case 1:
			pTree = dInit();
			if (pTree == NULL) status = 1;
			else status = dProcess(pTree);
			break;

		case 2:
			pTree = dDownload();
			if (pTree == NULL) status = 0;
			else status = dProcess(pTree);
			break;

		case 3:
			checkTime("GFG.txt");
			status = 0;
			break;
		}
	}

	printf("See You later!\n");
	system("pause");
	return 0;
}