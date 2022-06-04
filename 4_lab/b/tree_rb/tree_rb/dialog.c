#ifndef APP_H
#include "app.h"
#endif

int console(char* pQuestion, char** ppArray, int len) {
	int i, answer = len + 1;
	char* msg = "";
	while (answer > len || answer < 0) {
		puts(msg);
		printf("\n%s\nChoose point:\n0) Exit\n", pQuestion);
		for (i = 0; i < len; i++)
			printf("%d) %s\n", i + 1, ppArray[i]);
		i = getInt(&answer);
		if (i == 1)
			return -1;
		msg = "Wrong value, please retry!";
		printf("\n");
	}
	return answer;
}

int dInsert(Tree* pTree) {
	int key, status;
	char* pInfo;
	Node* pNode;

	printf("\nEnter key\n");
	status = getInt(&key);
	if (status == 1) {
		treeDelete(pTree);
		return 1;
	}

	printf("Enter info\n");
	pInfo = getStr();
	if (pInfo == NULL) {
		treeDelete(pTree);
		return 1;
	}

	pNode = insert(pTree, key, pInfo);
	if (pNode == NULL) {
		free(pInfo);
		return 2;
	}
	
	printf("Added: (%d, %s)\n", pNode->key, pNode->pInfo);
	return 0;
}

int dDeleteNode(Tree* pTree) {
	int status, key;

	printf("\nEnter key\n");
	status = getInt(&key);
	if (status == 1) {
		treeDelete(pTree);
		return 1;
	}

	status = nodeDelete(pTree->pRoot, key);
	if (status == 0) printf("Deleted: %d\n", key);
	else printf("Key '%d' is not exist\n", key);

	return 0;
}

int dPrintNode(Tree* pTree) {
	int key, version, status;
	Node* pNode;

	printf("\nEnter key\n");
	status = getInt(&key);
	if (status == 1) {
		treeDelete(pTree);
		return 1;
	}

	printf("Enter version\n");
	status = getNat(&version);
	if (status == 1) {
		treeDelete(pTree);
		return 1;
	}

	pNode = search(pTree->pRoot, key, version);
	if (pNode != NULL) printf("Searched!\nKey: %d\nInfo: %s", pNode->key, pNode->pInfo);
	else printf("The %d node with key '%d' is not exist.\n", version, key);

	return 0;
}

int dDelete(Tree* pTree) {
	int status;
	char* ppList[2] = { "Yes", "No" };

	status = console("Do you want to delete the tree?", ppList, 2);
	if (status != 1) {
		if (status == -1) {
			treeDelete(pTree);
			return 1;
		}
		return 2;
	}

	status = treeDelete(pTree);
	if (status == 1) printf("Wrong structure!\n");
	else printf("The tree was deleted.\n");

	return 0;
}

Tree* dDownload() {
	char* pName;
	Tree* pTree;

	printf("\nEnter name of file\n");
	pName = getStr();
	if (pName == NULL) {
		printf("Memory request was declined!\n");
		return NULL;
	}

	pTree = download(pName);
	if (pTree == NULL)
		printf("The file '%s' is not exist or memory request was declined!\n", pName);
	else printf("The file '%s' was opened successfuly!\n", pName);

	free(pName);
	return pTree;
}

Tree* dInit() {
	Tree* pTree = treeInit();

	if (pTree == NULL) printf("Memory request was declined!\n");
	else printf("New tree was created successfuly!\n");

	return pTree;
}

int dWalk(Tree* pTree) {
	int key = 0, isKeyCorrect = 0, status;

	printf("\nEnter 0, if you want to enter max 'not walking' key\n");
	status = getInt(&isKeyCorrect);
	if (status == 1) {
		treeDelete(pTree);
		return 1;
	}
	if (isKeyCorrect != 0) isKeyCorrect = 1;

	if (isKeyCorrect == 0) {
		printf("Enter max 'not walking' key\n");
		status = getInt(&key);
		if (status == 1) {
			treeDelete(pTree);
			return 1;
		}
	}

	walk(pTree->pRoot, key, isKeyCorrect);
	return 0;
}

int dSearchSpecial(Tree* pTree) {
	int key, version, status;
	Node* pNode;

	printf("\nEnter key\n");
	status = getInt(&key);
	if (status == 1) {
		treeDelete(pTree);
		return 1;
	}

	printf("Enter version\n");
	status = getNat(&version);
	if (status == 1) {
		treeDelete(pTree);
		return 1;
	}

	pNode = searchSpecial(pTree->pRoot, key, version);
	printf("Done\n");
	if (pNode == NULL) printf("Wrong structure or this version of node is not exist!\n");
	else printf("Searched!\nKey: %d\nInfo: %s", pNode->key, pNode->pInfo);

	return 0;
}

int dProcess(Tree* pTree) {
	int status;
	char* ppList[7] = {
		"Delete tree",//1
		"Insert node",//2
		"Delete node",//3
		"Search node by key",//4
		"Special search node",//5
		"Print tree 'as tree'",//6
		"Walk",//7
	};
	while (1 == 1) {
		printf("\n");
		status = console("What do You want to do with the tree?", ppList, 7);

		switch (status) {
		case 0:
		case 1:
			if (dDelete(pTree) != 2) return status;
			break;
		case 2:
			if (dInsert(pTree) == 1) return 1;
			break;
		case 3:
			if (dDeleteNode(pTree) == 1) return 1;
			break;
		case 4:
			if (dPrintNode(pTree) == 1) return 1;
			break;
		case 5:
			if (dSearchSpecial(pTree) == 1) return 1;
			break;
		case 6:
			printAsTree(pTree->pRoot, 0);
			break;
		case 7:
			if (dWalk(pTree) == 1) return 1;
			break;
		}
	}
	return 0;
}
