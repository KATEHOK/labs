#ifndef A_H
#include "a.h"
#endif

int main() {
	Stack stackMain, stackSupport, stackBracket, stackFragment;
	int status, len;
	// для выявления утечек памяти
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// инициализируем необходимые стеки
	status = stacksInit(&stackMain, &stackSupport, &stackBracket, &stackFragment, &len);
	if (status == 1)
		return 0;


	// освобождаем память
	stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
	// сообщение, выход
	printf("Successfully!\n");
	return 0;
}