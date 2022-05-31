#ifndef APP_H
#include "app.h"
#include "tree.h"
#endif // !APP_H

Tree* treeInit() {
	Tree* pTree = (Tree*)malloc(sizeof(Tree));
	if (pTree == NULL) return NULL;
	pTree->pRoot = NULL;
	return pTree;
}

Node* nodeInit(int key, char* pInfo, Node* pNext) {
	Node* pNode = (Node*)malloc(sizeof(Node));
	if (pNode == NULL) {
#ifdef DEBUG
		printf("<nodeInit> malloc == NULL\n");
#endif
		return NULL;
	}
	pNode->key = key;
	pNode->pInfo = pInfo;
	pNode->pLeft = NULL;
	pNode->pRight = NULL;
	pNode->pParent = NULL;
	pNode->pNext = NULL;

	return pNode;
}

int treeDelete(Tree* pTree) {
	if (pTree == NULL)
		return 1;
	nodesDelete(pTree->pRoot);
	free(pTree);
	return 0;
}

void nodesDelete(Node* pNode) {
	if (pNode != NULL) {
		free(pNode->pInfo);
		nodesDelete(pNode->pLeft);
		nodesDelete(pNode->pRight);
		free(pNode);
	}
}

void detour(Node* pNode, int keyStart, int isKeyStartCorrect) {
	if (pNode != NULL) {
		if (isKeyStartCorrect != 0 || keyStart < pNode->key) {
			printf("Key: %d, Info: %s\n", pNode->key, pNode->pInfo);
			detour(pNode->pLeft, keyStart, isKeyStartCorrect);
		}
		detour(pNode->pRight, keyStart, isKeyStartCorrect);
	}
}

void walk(Node* pNode, int keyStart, int isKeyStartCorrect) {
	if (pNode != NULL) pNode->pNext = NULL;
	while (pNode != NULL) {
		if (isKeyStartCorrect != 0 || keyStart < pNode->key)
			printf("Key: %d, Info: %s\n", pNode->key, pNode->pInfo);

		if (pNode->pLeft != NULL && (isKeyStartCorrect != 0 || keyStart < pNode->key)) {
			pNode = pNode->pLeft;

			if (pNode->pParent->pRight != NULL) pNode->pNext = pNode->pParent->pRight;
			else pNode->pNext = pNode->pParent->pNext;
		}
		else if (pNode->pRight != NULL) {
			pNode = pNode->pRight;

			pNode->pNext = pNode->pParent->pNext;
		}
		else pNode = pNode->pNext;
	}
}

Node* search(Node* pNode, int key, int version) {
	if (pNode == NULL) return NULL;
	if (key == pNode->key) {
		if (version == 1) return pNode;
		version--;
	}
	if (key <= pNode->key) return search(pNode->pLeft, key, version);
	if (key > pNode->key) return search(pNode->pRight, key, version);
}

//void goDetour(Node* pNode, int keyStart, int isKeyStartCorrect) {
//	if (isKeyStartCorrect == 0) callDetour(pNode, keyStart);
//	else detour(pNode);
//}

Node* insertNotFirst(Node* pNode, int key, char* pInfo) {
	int lr = 0;
	Node* pFunnyFather = searchFunnyFather(pNode, key, &lr);
	Node* pChild = nodeInit(key, pInfo, NULL);
	if (pChild == NULL) return NULL;
	if (lr == 0) pFunnyFather->pLeft = pChild;
	else pFunnyFather->pRight = pChild;
	pChild->pParent = pFunnyFather;
	return pChild;
}

Node* searchFunnyFather(Node* pNode, int key, int* pLR) {
	if (key <= pNode->key) {
		if (pNode->pLeft != NULL) return searchFunnyFather(pNode->pLeft, key, pLR);
		*pLR = 0;
		return pNode;
	}
	if (pNode->pRight != NULL) return searchFunnyFather(pNode->pRight, key, pLR);
	*pLR = 1;
	return pNode;
}

Node* insertFirst(Tree* pTree, int key, char* pInfo) {
	pTree->pRoot = nodeInit(key, pInfo, NULL);
	return pTree->pRoot;
}

Node* insert(Tree* pTree, int key, char* pInfo) {
	if (pTree->pRoot == NULL) return insertFirst(pTree, key, pInfo);
	return insertNotFirst(pTree->pRoot, key, pInfo);
}

//void callDetour(Node* pNode, int key) {
//	if (pNode != NULL) {
//		if (key < pNode->key) {
//			printf("Key: %d, Info: %s\n", pNode->key, pNode->pInfo);
//			callDetour(pNode->pLeft, key);
//			detour(pNode->pRight);
//		} else callDetour(pNode->pRight, key);
//	}
//}

int nodeDelete(Node* pNode, int key) {
	Node *pParent, *pVictim;
	Node* pTarget = search(pNode, key, 1);
	if (pTarget == NULL) return 1;

	pParent = pTarget->pParent;
	pVictim = searchMaxOrEqual(pTarget->pLeft, key);
	free(pTarget->pInfo);

	if (pVictim == NULL) {
		if (pParent->pLeft == pTarget) pParent->pLeft = pTarget->pRight;
		else pParent->pRight = pTarget->pRight;

		if (pTarget->pRight != NULL) pTarget->pRight->pParent = pParent;
		free(pTarget);
	}
	else {
		pTarget->pInfo = pVictim->pInfo; //нельзя очищать pVictim->pInfo
		pTarget->key = pVictim->key;

		if (pVictim->pLeft == NULL) {
			if (pVictim->pParent->pLeft == pVictim) pVictim->pParent->pLeft = NULL;
			else pVictim->pParent->pRight = NULL;
			//printf("%d |-> %p -r-> %p\n", pVictim->pParent->key, pVictim->pParent, pVictim->pParent->pRight);
		}
		else {
			if (pVictim->pParent->pLeft == pVictim) {
				pVictim->pParent->pLeft = pVictim->pLeft;
				pVictim->pLeft->pParent = pTarget;//
			}
			else {
				pVictim->pParent->pRight = pVictim->pLeft;
				pVictim->pLeft->pParent = pVictim->pParent;
			}
		}
		//printf("victimparent (%d)-> %p\n", pVictim->pParent->key, pVictim->pParent);
		free(pVictim);
	}
	return 0;
}

Node* searchMaxOrEqual(Node* pNode, int key) {
	if (pNode == NULL) return NULL;
	if (pNode->pRight == NULL || pNode->key == key) return pNode;
	return searchMaxOrEqual(pNode->pRight, key);
}

Node* searchMax(Node* pNode) {
	if (pNode == NULL) return NULL;
	if (pNode->pRight == NULL) return pNode;
	return searchMax(pNode->pRight);
}

Node* searchMin(Node* pNode) {
	if (pNode == NULL) return NULL;
	if (pNode->pLeft == NULL) return pNode;
	return searchMin(pNode->pLeft);
}

Node* searchSpecial(Node* pNode, int key, int version) {
	Node* pTmp;
	Node* pMin = searchMin(pNode);
	Node* pMax = searchMax(pNode);

	if (pMin == pMax) return pNode;

	if (key - pMin->key >= pMax->key - key) {
		while (pMin->pParent->key == pMin->key) pMin = pMin->pParent;
		while (version > 1) {
			pMin = pMin->pLeft;
			if (pMin == NULL) return NULL;
			version--;
		}
		return pMin;
	}
	else {
		while (version > 1) {
			pTmp = searchMax(pMax->pLeft);
			if (pTmp == NULL || pTmp->key != pMax->key) return NULL;
			pMax = pTmp;
			version--;
		}
		return pMax;
	}
}

Tree* download(char* pPath) {
	Tree* pTree = treeInit();
	if (pTree == NULL) return NULL;

	FILE* pFile;
	int err = fopen_s(&pFile, pPath, "r");
	if (err != 0) {
		free(pTree);
		return NULL;
	}

	int status = 1, key;
	char* pInfo;
	while (status != 0) {
		Node* pNode = NULL;
		char pKey[15] = "\0";
		pInfo = (char*)malloc(256 * sizeof(char));
		if (pInfo == NULL) {
			fclose(pFile);
			return pTree;
		}

		if (fgets(pKey, 15, pFile) == NULL || fgets(pInfo, 256, pFile) == NULL) {
			status = 0;
			free(pInfo);
		}
		else {
			key = atoi(pKey);
			pNode = insert(pTree, key, pInfo);
		} if (pNode == NULL) status = 0;
	}
	fclose(pFile);
	return pTree;
}

void printAsTree(Node* pNode, int offset) {
	int i, numLen = 2;
	if (pNode != NULL) {
		numLen += floor(log10(abs(pNode->key))) + 1;
		if (pNode->key < 0) numLen++;
		if (pNode->key == 0) numLen = 3;
		//printf("1-> %d; %p -r-> %p\n", pNode->key, pNode, pNode->pRight);
		printAsTree(pNode->pRight, offset + numLen);

		for (i = 0; i < offset; i++) printf(" ");
		printf("[%d]\n", pNode->key);

		//printf("2-> %d\n", pNode->key);
		printAsTree(pNode->pLeft, offset + numLen);
		//printf("3-> %d\n", pNode->key);
	}
}