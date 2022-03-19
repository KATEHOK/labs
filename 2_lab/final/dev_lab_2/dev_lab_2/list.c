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
	int status = 0;
	char trash, *pTrash = &trash;
	while (status == 0)
		status = stackPop(pStack, &pTrash);
	free(pStack->pRelease);
	printf("Stack was cleaned!\n");
}

int stackPush(Stack* pStack, char* pData) {
	Item* pNewItem;
	pNewItem = (Item*)malloc(sizeof(Item));
	if (pNewItem == NULL)
		return 2;
	pNewItem->pData = pData;
	pNewItem->pPrevious = (void*)(pStack->pRelease->top);
	pStack->pRelease->top = pNewItem;
	return 0;
}

int stackCopy(Stack* pStack, char** ppData) {
	if (pStack->pRelease->top == NULL)
		return 1;
	*ppData = pStack->pRelease->top->pData;
	return 0;
}

int stackPop(Stack* pStack, char** ppData) {
	Item* pDeleting;
	int status;
	status = stackCopy(pStack, ppData);
	if (status == 1)
		return 1;
	pDeleting = pStack->pRelease->top;
	pStack->pRelease->top = (Item*)(pDeleting->pPrevious);
	free(pDeleting);
	return 0;
}


#endif