#ifndef APP_H
#include "app.h"
#include "tree.h"
#endif // !APP_H


// проблемы с fixHigher после удаления!

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
	pTree->pEList->infoCount = 0;
	pTree->pEList->pInfo = NULL;
	pTree->pEList->color = BLACK;

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
	if (pNode == pEList) return;
	infoListDelete(pNode->pInfo);
	nodesDelete(pNode->pLeft, pEList);
	nodesDelete(pNode->pRight, pEList);
	free(pNode);
}

void infoListPrint(Info* pInfo) {
	while (pInfo != NULL) {
		printf(" %s\n", pInfo->pTxt);
		pInfo = pInfo->pNext;
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

void detour(Node* pNode, Node* pEList, int keyEnd, int isKeyEndCorrect) {//l-r-c
	if (pNode == pEList) return;
	detour(pNode->pLeft, pEList, keyEnd, isKeyEndCorrect);

	if (isKeyEndCorrect != 0 || pNode->key <= keyEnd) {
		Info* pInfo = pNode->pInfo;

		detour(pNode->pRight, pEList, keyEnd, isKeyEndCorrect);

		printf("[%d]", pNode->key);
		while (pInfo != NULL) {
			printf(" '%s',", pInfo->pTxt);
			pInfo = pInfo->pNext;
		}
		printf("\n");
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
	return search(pNode->pRight, pEList, key, version, ppInfo);
}

Node* insertNotFirst(Tree* pTree, int key, char* pTxt) {
	// -1 ключ уже есть, встраиваем инфу в список
	//  0 ключ будет левым потомком
	//  1 ключ будет правым потомком
	int lr = 0;
	Node* pFunnyFather = searchFunnyFather(pTree->pRoot, pTree->pEList, key, &lr);
	
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

Node* searchFunnyFather(Node* pNode, Node* pEList, int key, int* pLR) {
	if (key == pNode->key) {
		*pLR = -1;
		return pNode;
	}

	if (key < pNode->key) {
		if (pNode->pLeft != pEList) return searchFunnyFather(pNode->pLeft, pEList, key, pLR);
		*pLR = 0;
		return pNode;
	}

	if (pNode->pRight != pEList) return searchFunnyFather(pNode->pRight, pEList, key, pLR);
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

void rotateRightRight(Tree* pTree, Node* pFirst, Node* pSecond) {
	rotateRight(pTree, pFirst);
	rotateRight(pTree, pSecond);
}

void rotateLeftLeft(Tree* pTree, Node* pFirst, Node* pSecond) {
	rotateLeft(pTree, pFirst);
	rotateLeft(pTree, pSecond);
}

void rotateLeftRight(Tree* pTree, Node* pLeft, Node* pRight) {
	rotateLeft(pTree, pLeft);
	rotateRight(pTree, pRight);
}

void rotateRightLeft(Tree* pTree, Node* pRight, Node* pLeft) {
	rotateRight(pTree, pRight);
	rotateLeft(pTree, pLeft);
}

void insertFix(Tree* pTree, Node* pNode) {
	Node *pGranny, *pUncle;
	Node* pParent = pNode->pParent;

	// снизу все ок, но могли изменить цвет корня
	if (pNode == pTree->pRoot) {
		pNode->color = BLACK;
		return;
	}

	if (pParent->color == BLACK) return; // первая римская

	pGranny = pParent->pParent;

	// текущий - в левой ветви бабки
	if (pParent == pGranny->pLeft) {
		pUncle = pGranny->pRight;

		// текущий - с внешней стороны
		if (pNode == pParent->pLeft) {
			pNode->color = BLACK;
			rotateRight(pTree, pGranny);
			insertFix(pTree, pParent);
		}

		// текущий - с внутреней стороны
		else {
			pParent->color = BLACK;
			rotateLeftRight(pTree, pParent, pGranny);
			insertFix(pTree, pNode);
		}
	}

	// текущий - в правой ветви бабки
	else {
		// отзеркалить предыдущую ветвь

		pUncle = pGranny->pLeft;

		// текущий - с внешней стороны
		if (pNode == pParent->pRight) {
			pNode->color = BLACK;
			rotateLeft(pTree, pGranny);
			insertFix(pTree, pParent);
		}

		// текущий - с внутреней стороны
		else {
			pParent->color = BLACK;
			rotateRightLeft(pTree, pParent, pGranny);
			insertFix(pTree, pNode);
		}
	}
}

int nodeDelete(Tree* pTree, int key) {
	Info* pInfo;
	Node *pParent, *pVictim, *pLeft, *pRight, *pChild;
	Node* pTarget = search(pTree->pRoot, pTree->pEList, key, 1, &pInfo);
	if (pTarget == NULL) return 1;

	if (pTarget->infoCount > 1) {
		// при удалении дублирующихся ключей балансировка не требуется
		Info* pCounter = pTarget->pInfo;

		for (int i = pTarget->infoCount; i > 2; i--) pCounter = pCounter->pNext;
		pInfo = pCounter->pNext;
		pCounter->pNext = NULL;
		pTarget->infoCount--;

		free(pInfo->pTxt);
		free(pInfo);
		return 0;
	}

	pParent = pTarget->pParent;
	pLeft = pTarget->pLeft;
	pRight = pTarget->pRight;

	free(pTarget->pInfo->pTxt);
	free(pTarget->pInfo);

	// хотя бы один из потомков - лист
	if (pLeft == pTree->pEList || pRight == pTree->pEList) {

		// у красной цели оба потомка - листья
		if (pTarget->color == RED) {
			if (pParent->pLeft == pTarget) pParent->pLeft = pTree->pEList;
			else pParent->pRight = pTree->pEList;

			free(pTarget);
			return 0;
		}

		// у цели-корня потомок - лист или красный узел
		if (pTarget == pTree->pRoot) {
			if (pLeft == pTree->pEList)	pTree->pRoot = pRight;
			else pTree->pRoot = pLeft;

			pTree->pRoot->color = BLACK;
			pTree->pRoot->pParent = pTree->pEList;

			free(pTarget);
			return 0;
		}

		// у черной цели потомок - лист или красный узел
		if (pLeft == pTree->pEList) pChild = pRight;
		else pChild = pLeft;

		pChild->color = BLACK;
		if (pChild != pTree->pEList) pChild->pParent = pParent;

		if (pTarget == pParent->pLeft) pParent->pLeft = pChild;
		else pParent->pRight = pChild;
		free(pTarget);

		// если у черной цели потомки - листы, то необходима корректировка высших уровней
		if (pChild == pTree->pEList) {
			// черная высота для pP: справа - 1 или 2 (зависит от pP->c), слева - 2 или 3 (ан-но).
			// или зеркально
			fixHigher(pTree, pChild, pParent);
		}

		// если pC != pEL, балансировка не требуется
		return 0;
	}

	pVictim = searchMax(pTarget->pLeft, pTree->pEList);

	// общие операции с жертвой
	pTarget->infoCount = pVictim->infoCount;
	pTarget->key = pVictim->key;
	pTarget->pInfo = pVictim->pInfo;

	// красная жертва не требует сложной корректировки
	if (pVictim->color == RED) {
		if (pVictim == pLeft) pTarget->pLeft = pTree->pEList;
		else pVictim->pParent->pRight = pTree->pEList;

		free(pVictim);
		return 0;
	}

	if (pVictim == pLeft) {
		// fix-pv-in-left.png
		pChild = pVictim->pLeft;
		free(pVictim);
		pTarget->pLeft = pChild;
		if (pChild != pTree->pEList) {
			pChild->pParent = pTarget;
			pChild->color = BLACK;
		}

		// pC == pEL
		// черная высота для pT:
		// слева - 1 или 2 (зависит от pT->c)
		// справа - 2 или 3 (ан-но)
		else deleteFixLeft(pTree, pTarget);

		return 0;
	}

	pParent = pVictim->pParent;
	pChild = pVictim->pLeft;
	pParent->pRight = pChild;
	free(pVictim);

	if (pChild != pTree->pEList) pChild->pParent = pParent;

	// корректировка с учетом, что жертва была черной
	// fix-pv-in-right.png
	deleteFixRight(pTree, pParent);

	return 0;
}

void deleteFixRight(Tree* pTree, Node* pParent) {
	Node* pChild = pParent->pRight;

	// вторая строчка
	if (pChild->color == RED) pChild->color = BLACK;

	// первая строчка 
	else fixHigher(pTree, pParent->pRight, pParent);
}

void deleteFixLeft(Tree* pTree, Node* pParent) {
	Node* pChild = pParent->pLeft;

	// вторая строчка
	if (pChild->color == RED) pChild->color = BLACK;

	// первая строчка 
	else fixHigher(pTree, pParent->pLeft, pParent);
}

// TO DO TESTS!
void fixHigher(Tree* pTree, Node* pCurrent, Node* pParent) {
	Node* pP;
	Node *pB, *pNL, *pNR;
	Node *pAlpha, *pBetta, *pGamma, *pDelta;

	if (pParent == NULL) pP = pCurrent->pParent;
	else {
		pP = pParent;
		pCurrent = pTree->pEList;
	}

	// текущий - черный, снизу - баланс
	if (pCurrent == pTree->pRoot) return;

	// текущий - справа
	if (pCurrent == pP->pRight) {

		pB = pP->pLeft;
		pNL = pB->pLeft;
		pNR = pB->pRight;

		// черный брат
		if (pB->color == BLACK) {

			// красный родитель
			if (pP->color == RED) {

				// черные племянники (второе)
				if (pNL->color == BLACK && pNR->color == BLACK) {
					pP->color = BLACK;
					pB->color = RED;
				}

				// третье
				else {
					if (pNL->color == BLACK) {
						rotateLeft(pTree, pB);
						// восстановим алиасы
						pB = pP->pLeft;
						pNL = pB->pLeft;
						pNR = pB->pRight;
					}

					rotateRight(pTree, pP);
					pP->color = BLACK;
					pB->color = RED;
					pNL->color = BLACK;
				}
			}

			// черный родитель
			else {

				// черные племянники (первое)
				if (pNL->color == BLACK && pNR->color == BLACK) {
					pB->color = RED;
					fixHigher(pTree, pP, NULL);
				}

				// четвертое
				else if (pNR->color == BLACK) {
					pNL->color = BLACK;
					rotateRight(pTree, pP);
				}

				// пятое
				else {
					pNR->color = BLACK;
					rotateLeftRight(pTree, pB, pP);
				}
			}
		}

		// красный брат
		else {
			pAlpha = pNL->pLeft, pBetta = pNL->pRight;
			pGamma = pNR->pLeft, pDelta = pNR->pRight;

			// пятое
			if (pAlpha->color == BLACK && pBetta->color == BLACK) {
				pNL->color = RED;
				pB->color = BLACK;
				rotateLeftRight(pTree, pB, pP);
			}

			// шестое
			else if (pBetta->color == RED) {
				pB->color = BLACK;
				rotateLeftRight(pTree, pB, pP);
				rotateLeftRight(pTree, pNL, pB);
			}

			// седьмое
			else {
				pAlpha->color = BLACK;
				pB->color = BLACK;
				pNL->color = RED;

				rotateLeftRight(pTree, pB, pP);
				rotateRight(pTree, pB);
			}
		}
	}

	// текущий - слева // отзеркаленное
	else {
		pB = pP->pRight;
		pNL = pB->pLeft;
		pNR = pB->pRight;

		// черный брат
		if (pB->color == BLACK) {

			// красный родитель
			if (pP->color == RED) {

				// черные племянники (второе)
				if (pNL->color == BLACK && pNR->color == BLACK) {
					pP->color = BLACK;
					pB->color = RED;
				}

				// третье
				else {
					if (pNR->color == BLACK) {
						rotateRight(pTree, pB);
						// восстановим алиасы
						pB = pP->pRight;
						pNL = pB->pLeft;
						pNR = pB->pRight;
					}

					rotateLeft(pTree, pP);
					pP->color = BLACK;
					pB->color = RED;
					pNR->color = BLACK;
				}
			}

			// черный родитель
			else {

				// черные племянники (первое)
				if (pNL->color == BLACK && pNR->color == BLACK) {
					pB->color = RED;
					fixHigher(pTree, pP, NULL);
				}

				// четвертое
				else if (pNL->color == BLACK) {
					pNR->color = BLACK;
					rotateLeft(pTree, pP);
				}

				// пятое
				else {
					pNL->color = BLACK;
					rotateRightLeft(pTree, pB, pP);
				}
			}
		}

		// красный брат
		else {
			pDelta = pNL->pLeft, pGamma = pNL->pRight;
			pBetta = pNR->pLeft, pAlpha = pNR->pRight;

			// пятое
			if (pAlpha->color == BLACK && pBetta->color == BLACK) {
				pNR->color = RED;
				pB->color = BLACK;
				rotateRightLeft(pTree, pB, pP);
			}

			// шестое
			else if (pBetta->color == RED) {
				pB->color = BLACK;
				rotateRightLeft(pTree, pB, pP);
				rotateRightLeft(pTree, pNR, pB);
			}

			// седьмое
			else {
				pAlpha->color = BLACK;
				pB->color = BLACK;
				pNR->color = RED;

				rotateRightLeft(pTree, pB, pP);
				rotateLeft(pTree, pB);
			}
		}
	}
}

Node* searchMax(Node* pNode, Node* pEList) {
	if (pNode == pEList) return pEList;
	if (pNode->pRight == pEList) return pNode;
	return searchMax(pNode->pRight, pEList);
}

Node* searchMin(Node* pNode, Node* pEList) {
	if (pNode == pEList) return NULL;
	if (pNode->pLeft == pEList) return pNode;
	return searchMin(pNode->pLeft, pEList);
}

Node* searchSpecial(Node* pNode, Node* pEList, int key, Node* pMemory) {
	if (pNode == NULL || pNode == pEList) return pMemory;
	if (pNode->key < key) return searchSpecial(pNode->pRight, pEList, key, pMemory);
	if (pNode->key == key) return searchMin(pNode->pRight, pEList);
	return searchSpecial(pNode->pLeft, pEList, key, pNode);
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

	int status = 1;
	unsigned int key;
	char pTxt[256] = "\0";
	while (status != 0) {
		Node* pNode = NULL;
		char pKey[15] = "\0";

		if (fgets(pKey, 15, pFile) == NULL || fgets(pTxt, 256, pFile) == NULL) status = 0;
		else {
			if (pTxt[strlen(pTxt) - 1] == '\n') pTxt[strlen(pTxt) - 1] = '\0';
			key = abs(atoi(pKey));
			pNode = insert(pTree, key, pTxt);
		} if (pNode == NULL) status = 0;
	}
	fclose(pFile);
	return pTree;
}

void printAsTree(Node* pNode, Node* pEList, int offset) {
	int i, numLen = 4;
	if (pNode == pEList) return;

	numLen += (floor(log10(abs(pNode->key))) + 1);
	if (pNode->key < 0) numLen++;
	if (pNode->key == 0) numLen = 3;
	printAsTree(pNode->pRight, pEList, offset + numLen);

	for (i = 0; i < offset; i++) printf(" ");
	printf("[%d-%d]\n", pNode->color, pNode->key);

	printAsTree(pNode->pLeft, pEList, offset + numLen);
}