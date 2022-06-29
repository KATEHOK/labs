#ifndef APP_H
#include "app.h"
#endif

Tree* initTree(char pName[8]) {
	Tree* pTree = (Tree*)malloc(sizeof(Tree));
	if (pTree == NULL || pName == NULL) return NULL;

	int status = strcpy_s(pTree->pName, 8 * sizeof(char), pName);
	if (status != 0) return NULL;

	pTree->childrenCount = 0;
	pTree->ppChildren = NULL;
	return pTree;
}

void deleteSubTree(Tree* pTree, char pName[8]) {
	deleteTree(searchTree(pTree, pName));
}

void deleteTree(Tree* pTree) {
	if (pTree == NULL || pTree->ppChildren == NULL) return;
	for (int i = 0; i < pTree->childrenCount; i++) deleteTree(pTree->ppChildren[i]);
	free(pTree->ppChildren);
	free(pTree);
}

Tree* searchTree(Tree* pTree, char pName[8]) {

	Tree* pTarget;
	if (pTree == NULL || pName == NULL) return NULL;
	if (strcmp(pTree->pName, pName) == 0) return pTree;

	for (int i = 0; i < pTree->childrenCount; i++) {
		pTarget = searchTree(pTree->ppChildren[i], pName);
		if (pTarget != NULL) return pTarget;
	}

	return NULL;
}

Tree* insertTree(Tree* pTree, char pParent[8], char pNew[8]) {
	Tree* pFather = searchTree(pTree, pParent);
	if (pFather == NULL) return NULL;

	Tree* pChild = initTree(pNew);
	if (pChild == NULL) return NULL;

	pFather->childrenCount++;
	pFather->ppChildren = (Tree**)realloc(pFather->ppChildren,
											pFather->childrenCount * sizeof(Tree*));
	if (pFather->ppChildren == NULL) {
		free(pChild);
		return NULL;
	}

	pFather->ppChildren[pFather->childrenCount - 1] = pChild;

	return pChild;
}

void printAsTree(Tree* pTree, int offset) {
	if (pTree == NULL) return;

	for (int i = 0; i < offset; i++) printf(" ");

	printf("[%s]\n", pTree->pName);
	offset += (2 + strlen(pTree->pName));

	for (int i = 0; i < pTree->childrenCount; i++)
		printAsTree(pTree->ppChildren[i], offset);
}
