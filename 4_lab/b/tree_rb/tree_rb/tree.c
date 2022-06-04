#ifndef APP_H
#include "app.h"
#include "tree.h"
#endif // !APP_H

Tree* treeInit() {
	Tree* pTree = (Tree*)malloc(sizeof(Tree));
	if (pTree == NULL) {
		printf("\n<treeInit/malloc>\n");
		return NULL;
	}

	pTree->pEList = (Node*)malloc(sizeof(Node));
	if (pTree->pEList == NULL) {
		free(pTree);
		printf("\n<treeInit/malloc>\n");
		return NULL;
	}

	pTree->pEList->key = 0;
	pTree->pEList->color = BLACK;
	pTree->pEList->pInfo = NULL;

	pTree->pEList->pLeft = NULL;
	pTree->pEList->pRight = NULL;
	pTree->pEList->pParent = NULL;

	pTree->pRoot = pTree->pEList;
	return pTree;
}

Node* nodeInit(Tree* pTree, int key, Info* pInfo) {
	Node* pNode = (Node*)malloc(sizeof(Node));
	if (pNode == NULL) {
		printf("\n<nodeInit/malloc>\n"); 
		return NULL; 
	}

	pNode->key = key;
	pNode->infoCount = 0;
	pNode->pInfo = pInfo;
	pNode->color = RED;

	pNode->pLeft = pTree->pEList;
	pNode->pRight = pTree->pEList;
	pNode->pParent = pTree->pEList;

	while (pInfo != NULL) {
		pNode->infoCount++;
		pInfo = pInfo->pNext;
	}

	return pNode;
}

void treeDelete(Tree* pTree) {
	if (pTree != NULL) {
		nodesDelete(pTree->pRoot, pTree->pEList);
		free(pTree->pEList);
		free(pTree);
	}
}

void nodesDelete(Node* pNode, Node* pEList) {
	if (pNode != pEList) {
		infoListDelete(pNode->pInfo);
		free(pNode->pInfo);
		nodesDelete(pNode->pLeft, pEList);
		nodesDelete(pNode->pRight, pEList);
		free(pNode);
	}
}

void infoListDelete(Info* pInfo) {
	Info* pCopy;

	while (pInfo != NULL) {
		pCopy = pInfo;
		pInfo = pInfo->pNext;

		free(pCopy->pTxt);
		free(pCopy);
	}
}

void detour(Node* pNode, Node* pEList, int keyEnd, int isKeyStartCorrect) {//l-r-c
	if (pNode != pEList) {
		detour(pNode->pLeft, pEList, keyEnd, isKeyStartCorrect);

		if (isKeyStartCorrect != 0 || pNode->key <= keyEnd) {
			Info* pInfo = pNode->pInfo;

			printf("[%d]", pNode->key);
			while (pInfo != NULL) {
				printf(" '%s',", pInfo->pTxt);
				pInfo = pInfo->pNext;
			}
			printf("\n");

			detour(pNode->pRight, pEList, keyEnd, isKeyStartCorrect);
		}
	}
}

Node* search(Node* pNode, Node* pEList, int key, int version, Info** ppInfo) {
	if (pNode == pEList) return NULL;
	Info* pInfo = pNode->pInfo;

	if (key == pNode->key) {
		if (pNode->infoCount < version) return NULL;

		for (int curVersion = pNode->infoCount; curVersion > 0; curVersion--) {
			if (curVersion == version) {
				if (ppInfo != NULL) *ppInfo = pNode->pInfo;
				return pNode;
			}

			pInfo = pInfo->pNext; //DANGER! требует точности в pNode->infoCount
		}

		return NULL;
	}

	if (key <= pNode->key) return search(pNode->pLeft, pEList, key, version, ppInfo);
	if (key > pNode->key) return search(pNode->pRight, pEList, key, version, ppInfo);
}

Node* insertNotFirst(Tree* pTree, int key, char* pTxt) {
	// -1 ключ уже есть, встраиваем инфу в список
	//  0 ключ будет левым потомком
	//  1 ключ будет правым потомком
	int lr = 0;
	Node* pFunnyFather = searchFunnyFather(pTree->pRoot, key, &lr);
	
	if (lr == -1) {
		Info* pInfo = infoInit(pTxt, pFunnyFather->pInfo);
		if (pInfo == NULL) {
			printf("\n<insertNotFirst/infoInit>\n");
			return NULL;
		}

		pFunnyFather->pInfo = pInfo;
		pFunnyFather->infoCount++;
		return pFunnyFather;
	}
	else {
		Info* pInfo = infoInit(pTxt, NULL);
		if (pInfo == NULL) {
			printf("\n<insertNotFirst/infoInit>\n");
			return NULL;
		}

		Node* pChild = nodeInit(pTree, key, pInfo);
		if (pChild == NULL) {
			infoListDelete(pInfo);
			printf("\n<insertNotFirst/nodeInit>\n");
			return NULL;
		}

		if (lr == 0) pFunnyFather->pLeft = pChild;
		else pFunnyFather->pRight = pChild;

		pChild->pParent = pFunnyFather;
		insertFix(pTree, pChild);

		return pChild;
	}
}

Node* searchFunnyFather(Node* pNode, int key, int* pLR) {
	if (key == pNode->key) {
		*pLR = -1;
		return pNode;
	}

	if (key < pNode->key) {
		if (pNode->pLeft != NULL) return searchFunnyFather(pNode->pLeft, key, pLR);
		*pLR = 0;
		return pNode;
	}

	if (pNode->pRight != NULL) return searchFunnyFather(pNode->pRight, key, pLR);
	*pLR = 1;
	return pNode;
}

Node* insertFirst(Tree* pTree, int key, char* pTxt) {
	Info* pInfo = infoInit(pTxt, NULL);
	if (pInfo == NULL) {
		printf("\n<insertFirst/infoInit>\n");
		return NULL;
	}

	pTree->pRoot = nodeInit(pTree, key, pInfo);
	pTree->pRoot->color = BLACK;

	return pTree->pRoot;
}

Info* infoInit(char* pTxt, Info* pNext) {
	Info* pInfo = (Info*)malloc(sizeof(Info));
	if (pInfo == NULL) {
		printf("\n<infoInit/malloc>\n");
		return NULL;
	}

	pInfo->pTxt = (char*)malloc(256 * sizeof(char));
	if (pInfo->pTxt == NULL) {
		free(pInfo);
		printf("\n<infoInit/malloc>\n");
		return NULL;
	}

	if (strcpy_s(pInfo->pTxt, 256, pTxt) != 0) {
		free(pInfo->pTxt);
		free(pInfo);
		printf("\n<infoInit/strcpy_s>\n");
		return NULL;
	}

	pInfo->pNext = pNext;
	return pInfo;
}

Node* insert(Tree* pTree, int key, char* pTxt) {
	if (pTree->pRoot == pTree->pEList) return insertFirst(pTree, key, pTxt);
	return insertNotFirst(pTree, key, pTxt);
}

void rotateLeft(Tree* pTree, Node* pA) {
	// url = '5 Красно-черные деревья.pdf' (33)
	Node* pParent = pA->pParent;
	Node* pB = pA->pRight;
	Node* pBetta = pB->pLeft;

	pA->pRight = pBetta;
	if (pBetta != pTree->pEList) pBetta->pParent = pA;

	pB->pLeft = pA;
	pB->pParent = pA->pParent;
	pA->pParent = pB;

	if (pA == pTree->pRoot) pTree->pRoot = pB;
	else if (pA == pParent->pLeft) pParent->pLeft = pB;
	else pParent->pRight = pB;
}

void rotateRight(Tree* pTree, Node* pB) {
	// url = '5 Красно-черные деревья.pdf' (36)
	Node* pParent = pB->pParent;
	Node* pA = pB->pLeft;
	Node* pBetta = pA->pRight;

	pB->pLeft = pBetta;
	if (pBetta != pTree->pEList) pBetta->pParent = pB;

	pA->pRight = pB;
	pA->pParent = pB->pParent;
	pB->pParent = pA;

	if (pB == pTree->pRoot) pTree->pRoot = pA;
	else if (pB == pParent->pLeft) pParent->pLeft = pA;
	else pParent->pRight = pA;
}

void insertFix(Tree* pTree, Node* pNode) {
	// у черного родителя может быть любой потомок, при этом все свойства сохранены
	// root - всегда черный
	// если родитель - root, то выход по первому условию
	// если текущий узел - root, то достаточно покрасить его в BLACK
	Node* pParent = pNode->pParent;
	if (pParent->color == BLACK) {
		if (pNode == pTree->pRoot) pNode->color = BLACK;
		return;
	}

	Node* pGrandParent = pParent->pParent;
	Node* pUncle;
	Node* pTmp;

	if (pParent == pGrandParent->pLeft)	pUncle = pGrandParent->pRight;
	else pUncle = pGrandParent->pRight;

	if (pUncle->color == RED) {
		// 1 случай: url = '5 Красно-черные деревья.pdf' (91):
		pParent->color = BLACK;
		pUncle->color = BLACK;
		pGrandParent->color = RED;

		insertFix(pTree, pGrandParent);
		return;
	}

	if (pParent == pGrandParent->pLeft) { 
		if (pNode == pParent->pRight) {
			// 2 случай: url = '5 Красно-черные деревья.pdf' (104):
			rotateLeft(pTree, pParent);
			pTmp = pNode;
			pNode = pParent;
			pParent = pTmp;
		}
		// 3 случай: url = '5 Красно-черные деревья.pdf' (112):
		pParent->color = BLACK;
		pGrandParent->color = RED;
		rotateRight(pTree, pGrandParent);
	}
	else { 
		if (pNode == pParent->pLeft) {
			// 2 случай: url = '5 Красно-черные деревья.pdf' (108):
			rotateRight(pTree, pParent);
			pTmp = pNode;
			pNode = pParent;
			pParent = pTmp;
		}
		// 3 случай
		pParent->color = BLACK;
		pGrandParent->color = RED;
		rotateLeft(pTree, pGrandParent);
	}
}

// TO DO

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