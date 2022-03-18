#ifndef A_H
#include "a.h"
#endif
#ifdef VECTOR


int stackInit(Stack* pStack, int len) {
	int status;
	printf("I'm using VECTOR! Length is %d.\n", len);

	pStack->pRelease = (Release*)malloc(sizeof(Release));
	if (pStack->pRelease == NULL) {
		printf("|-> Memory request was declined!\n");
		return 1;
	}

	pStack->pRelease->top = 0;
	pStack->pRelease->len = len;

	pStack->pRelease->ppData = (char**)malloc(len * sizeof(char*));
	if (pStack->pRelease->ppData == NULL) {
		printf("|-> Memory request was declined!\n");
		free(pStack->pRelease);
		return 1;
	}
	return 0;
}

void stackFree(Stack* pStack) {
	free(pStack->pRelease->ppData);
	free(pStack->pRelease);
	printf("Stack was cleaned!\n");
}


#endif