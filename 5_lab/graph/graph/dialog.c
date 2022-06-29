#ifndef APP_H
#include "app.h"
#endif

int console(char* pQuestion, char** ppArray, int len) {
	int i, answer = len + 1;
	char* msg = "";
	while (answer > len || answer < 0) {
		puts(msg);
		printf("\n%s\nChoose point:\n0) Cancel\n", pQuestion);
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

Graph* dInit() {
	Graph* pGraph = initGraph();

	if (pGraph == NULL) printf("Memory request was declined!\n");
	else printf("New graph was created!\n");

	return pGraph;
}

int dDelete(Graph* pGraph) {
	int status;
	char* ppList[2] = { "Yes" };

	status = console("Do you want to delete graph?", ppList, 1);

	if (status == -1) return 1;
	if (status == 0) {
		printf("Canceled!\n");
		return 2;
	}
	else {
		deleteGraph(pGraph);
		printf("Graph was deleted.\n");
	}

	return 0;
}

int dAddPoint(Graph* pGraph) {
	int status;
	char* pName;

	printf("Enter name of new point\n");
	pName = getStr();
	if (pName == NULL) {
		deleteGraph(pGraph);
		return 1;
	}

	status = addPoint(pGraph, pName);

	if (status == 0) printf("Point '%s' was added!\n", pName);
	if (status == 2) printf("Canceled! Point '%s' is already exist!\n", pName);
	free(pName);

	if (status == 0 || status == 2) return 0;
	deleteGraph(pGraph);
	return 1;
}

int dDeletePoint(Graph* pGraph) {
	int status;
	char* pName;

	printf("\nEnter name of point\n");
	pName = getStr();
	if (pName == NULL) {
		deleteGraph(pGraph);
		return 1;
	}

	status = deletePoint(pGraph, pName);
	if (status == 0) printf("Deleted: %s\n", pName);
	else if (status == 1) printf("Canceled! Point '%s' is not exist\n", pName);
	free(pName);

	if (status > 1) {
		deleteGraph(pGraph);
		return 1;
	}

	return 0;
}

int dAddArrow(Graph* pGraph) {
	int status, weight;
	char *pSrc, *pDest;

	printf("Enter name of outgoing point\n");
	pSrc = getStr();

	printf("Enter name of incomming point\n");
	pDest = getStr();

	printf("Enter weight of arrow\n");
	status = getInt(&weight);

	if (status == 1 || pSrc == NULL || pDest == NULL) {
		deleteGraph(pGraph);
		free(pSrc);
		free(pDest);
		return 1;
	}

	status = addArrow(pGraph, pSrc, pDest, weight);

	free(pSrc);
	free(pDest);

	if (status == 0) printf("Arrow was added!\n");
	if (status == 1) printf("Canceled! Point(s) wasn't searched!\n");
	if (status == 0 || status == 1) return 0;

	deleteGraph(pGraph);
	return 1;
}

int dDeleteArrow(Graph* pGraph) {
	char *pSrc, *pDest;

	printf("Enter name of incomming point\n");
	pSrc = getStr();

	printf("Enter name of outcomming point\n");
	pDest = getStr();

	if (pSrc == NULL || pDest == NULL) {
		deleteGraph(pGraph);
		free(pSrc);
		free(pDest);
		return 1;
	}

	deleteArrow(pGraph, pSrc, pDest);

	free(pSrc);
	free(pDest);

	printf("Arrow was deleted!\n");
	return 0;
}

int dPrint(Graph* pGraph) {
	int status;
	status = printGraph(pGraph);

	if (status == 1) {
		deleteGraph(pGraph);
		return 1;
	}
	if (status == 2) printf("Graph is free!\n");

	return 0;
}

int dProcess(Graph* pGraph) {
	int status;
	char* ppList[9] = {
		"Delete graph",//1
		"Add point",//2
		"Delete point",//3
		"Add arrow",//4
		"Delete arrow",//5
		"Print graph",//6
		"Search way",//7
		"Find shortest way",//8
		"Sort graph",//9
	};
	while (1 == 1) {
		printf("\n");
		status = console("What do You want to do with graph?", ppList, 9);

		switch (status) {
		case 0:
		case 1:
			status = dDelete(pGraph);
			if (status != 2) return status;
			break;
		case 2:
			if (dAddPoint(pGraph) == 1) return 1;
			break;
		case 3:
			if (dDeletePoint(pGraph) == 1) return 1;
			break;
		case 4:
			if (dAddArrow(pGraph) == 1) return 1;
			break;
		case 5:
			if (dDeleteArrow(pGraph) == 1) return 1;
			break;
		case 6:
			if (dPrint(pGraph) == 1) return 1;
			break;
		case 7:
			if (dSearchWay(pGraph) == 1) return 1;
			break;
		case 8:
			if (dShortestWay(pGraph) == 1) return 1;
			break;
		case 9:
			if (dSortGraph(pGraph) == 1) return 1;
			break;
		}
	}
	return 0;
}

int dSearchWay(Graph* pGraph) {
	int status;
	char *pSrc, *pDest;

	printf("Enter name of outgoing point\n");
	pSrc = getStr();

	printf("Enter name of incomming point\n");
	pDest = getStr();

	if (pSrc == NULL || pDest == NULL) {
		deleteGraph(pGraph);
		free(pSrc);
		free(pDest);
		return 1;
	}

	status = searchWay(pGraph, pSrc, pDest);

	free(pSrc);
	free(pDest);

	if (status == 0) return 0;
	if (status == 1) printf("Memory error! Please cancel!\n");
	if (status == 2) printf("Point wasn't found or the way isn't exist!\n");

	return 0;
}

int dShortestWay(Graph* pGraph) {
	int status;
	char *pSrc, *pDest;

	printf("Enter name of outgoing point\n");
	pSrc = getStr();

	printf("Enter name of incomming point\n");
	pDest = getStr();

	if (pSrc == NULL || pDest == NULL) {
		deleteGraph(pGraph);
		free(pSrc);
		free(pDest);
		return 1;
	}

	status = findShortestWay(pGraph, pSrc, pDest);

	int destId = searchLine(pGraph->pMatrix, pDest);
	if (status == 0) {
		printf("\nShortest way:\n");
		printShortestWay(pGraph, searchLine(pGraph->pMatrix, pSrc), destId, destId);
		printf("\n");
	}

	free(pSrc);
	free(pDest);

	if (status == 1) {
		deleteGraph(pGraph);
		return 1;
	}

	if (status == 2) printf("Point(s) was (were) not found!\n");
	if (status == 3) printf("Graph includes negative cycle!\n");

	if (status == 4) printf("Points are isolated!\n");
	return 0;
}

int dSortGraph(Graph* pGraph) {
	int status = sortGraph(pGraph);
	if (status == 1) {
		deleteGraph(pGraph);
		return 1;
	}

	if (status == 3) printf("Graph includes cycle!\n");
	else if (status == 0) printf("Graph was sorted!");
	else printf("Graph is correct, but it was not sorted!\n");

	return 0;
}