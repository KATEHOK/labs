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

	/*
	char s = 'S', c = 'C', p = 'P';
	char t = 'T', d = 'D', r = 'R';

	char *ps = &s, *pc = &c, *pp = &p;
	char *pt = &t, *pd = &d, *pr = &r;

	status = stackPush(&stackMain, ps);
	status = stackCopy(&stackMain, &pc);

	status = stackPush(&stackMain, pt);
	status = stackCopy(&stackMain, &pd);

	status = stackPop(&stackMain, &pr);
	status = stackPop(&stackMain, &pp);
	

	printf("%c %c %c\n", *ps, *pc, *pp);
	printf("%c %c %c\n", *pt, *pd, *pr);
	*/


	// освобождаем память
	stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
	// сообщение, выход
	printf("Successfully!\n");
	return 0;
}