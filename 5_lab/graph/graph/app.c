#ifndef APP_H
#include "app.h"
#endif // !APP_H

// 1 2 a 2 b 2 c 4 a b 1 4 b c 1 4 a c 1 - есть цикл
// 1 2 a 2 b 2 c 4 c b 1 4 c a 1 4 a b 1 - ациклический
// 1 2 a 2 b 2 c 4 b c 1 4 c a 1 - ациклический

int main() {
	int status = 0;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n");

	Graph* pGraph;
	char* ppList[1] = {
		"Make free graph"//1
	};

	while (status == 0) {
		printf("\n");
		status = console("What do You want to do?", ppList, 1);

		switch (status) {
		case 0:
			status = 1;
			break;

		case 1:
			pGraph = dInit();
			if (pGraph == NULL) status = 1;
			else status = dProcess(pGraph);
			break;
		}
	}

	//void* a = malloc(1);

	printf("See You later!\n");
	system("pause");
	return 0;
}