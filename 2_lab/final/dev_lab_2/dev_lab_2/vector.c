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

int stackPush(Stack* pStack, char* pData) {
	if (pStack->pRelease->top == pStack->pRelease->len)
		return 1;
	pStack->pRelease->ppData[pStack->pRelease->top] = pData;
	pStack->pRelease->top++;
	return 0;
}

int stackCopy(Stack* pStack, char** ppData) {
	if (pStack->pRelease->top == 0)
		return 1;
	*ppData = pStack->pRelease->ppData[pStack->pRelease->top - 1];
	return 0;
}

int stackPop(Stack* pStack, char** ppData) {
	int status;
	status = stackCopy(pStack, ppData);
	if (status == 1)
		return 1;
	pStack->pRelease->top--;
	return 0;
}


#endif