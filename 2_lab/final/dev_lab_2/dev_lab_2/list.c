#ifndef A_H
#include "a.h"
#endif
#ifndef VECTOR


int stackInit(Stack* pStack, int len) {
	printf("I'm using LIST!\n");
	pStack->pRelease = (Release*)malloc(sizeof(Release));
	if (pStack->pRelease == NULL) {
		printf("|-> Memory request was declined!\n");
		return 1;
	}
	pStack->pRelease->top = NULL;
	return 0;
}

void stackFree(Stack* pStack) {
	free(pStack->pRelease);
	printf("Stack was cleaned!\n");
}


#endif