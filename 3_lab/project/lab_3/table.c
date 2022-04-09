#ifndef APP_H
#include "app.h"
#endif // !APP_H


int tableInit(Table* pTable) {
	int maxSize1 = 0, maxSize2 = 0, status;
	pTable->countKeys1 = 0;
	pTable->countKeys2 = 0;
	if (maxSize1 == 0) {
		status = setMaxSizeKS(&maxSize1, 1);
		if (status == 1)
			return 1;
	}
	if (maxSize2 == 0) {
		status = setMaxSizeKS(&maxSize1, 2);
		if (status == 1)
			return 1;
	}
	pTable->maxSize1 = maxSize1;
	pTable->maxSize2 = maxSize2;
	pTable->ks1 = (struct KeySpace1*)malloc(maxSize1 * sizeof(struct KeySpace1));
	if (pTable->ks1 == NULL) {
		printf("|-> Memory request Error!\n");
		return 1;
	}
	pTable->ks2 = (struct KeySpace2*)malloc(maxSize2 * sizeof(struct KeySpace2));
	if (pTable->ks2 == NULL) {
		printf("|-> Memory request Error!\n");
		free(pTable->ks1);
		return 1;
	}
	return 0;
}
void tableDelete(Table*);

int tableAdd(Table*, int, int, char*);
Item* tableSearchItemByComposite(Table*, int, int);
void tableDeleteItemByComposite(Table*, int, int);
Item* tableSearchItemBySingle(Table*, int);
void tableDeleteItemBySingle(Table*, int);
int tablePrint(Table*);

int setMaxSizeKS(int* pData, int KSNumber) {
	int status = 0;
	printf("Enter max count of keys in the %d keys-field\n", KSNumber);
	status = getNat(pData);
	if (status == 1)
		printf("|-> setMaxSizeKS(%d) Error!\n", KSNumber);
	return status;
}