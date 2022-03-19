#ifndef A_H
#include "a.h"
#endif

int main() {
	Stack stackMain, stackSupport, stackBracket, stackFragment;
	int status, len, open = 0, close = 0, previous = 0;
	char* pFormula, *pProcessing;
	// ��� ��������� ������ ������
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// ����������� �������, ���������� ����� ������� (��� �����-�������)
	status = setFormula(&pFormula, &len);
	// �������������� ����������� �����
	status = stacksInit(&stackMain, &stackSupport, &stackBracket, &stackFragment, &len);
	if (status == 1) {
		free(pFormula);
		return 0;
	}

	/*
	char s = 'S', c = 'C', p = 'P';
	char t = 'T', d = 'D', r = 'R';

	char *ps = &s, *pc = &c, *pp = &p;
	char *pt = &t, *pd = &d, *pr = &r;

	status = stackPush(&stackMain, ps);
	status = stackCopy(&stackMain, &pc);

	status = stackPush(&stackMain, pt);
	status = stackCopy(&stackMain, &pd);

	status = stackPop(&stackMain, &pr);
	status = stackPop(&stackMain, &pp);
	

	printf("%c %c %c\n", *ps, *pc, *pp);
	printf("%c %c %c\n", *pt, *pd, *pr);
	*/

	pProcessing = pFormula;
	do {
		if (*pProcessing == '(') {
			open++;
			printf("Process %c\n", *pProcessing);
			status = processOpenBracket(&stackMain, &stackBracket, &stackFragment, pProcessing, previous);
			// ������� ������� ������ �� ����� � �������
			if (status == 1) {
				open = 0;
				close = 1;
			}
			previous = 0;
		}
		else if (*pProcessing == ')') {
			close++;
			printf("Process %c\n", *pProcessing);
			status = processCloseBracket(&stackBracket, &stackFragment);
			if (status == 1) {
				open = 0;
				close = 1;
			}
			previous = 1;
		}
		else if (*pProcessing == '+' || *pProcessing == '-') {
			printf("Process %c\n", *pProcessing);
			status = processPlusMinus(&stackMain, &stackSupport, &stackBracket, pProcessing);
			if (status == 1) {
				open = 0;
				close = 1;
			}
			previous = 2;
		}
		else if (*pProcessing == '*' || *pProcessing == '/') {
			printf("Process %c\n", *pProcessing);
			status = processMulDiv(&stackMain, &stackSupport, &stackFragment, pProcessing);
			if (status == 1) {
				open = 0;
				close = 1;
			}
			previous = 3;
		}
		else {
			printf("Process %c\n", *pProcessing);
			status = processParam(&stackMain, &stackFragment, pProcessing, previous);
			if (status == 1) {
				open = 0;
				close = 1;
			}
		}
		pProcessing++;
		// ���������� �������� ������ �� ����� ���� ������ ���������� ��������
		if (close > open)
			break;
	} while (*pProcessing != '\0');
	// ���������� �������� ������ �� ������������� ���������� ��������
	if (open != close) {
		printf("|-> Formula invalid!\n");
		stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
		free(pFormula);
		return 0;
	}

	// ����������� ������
	stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
	free(pFormula);
	// ���������, �����
	printf("Successfully!\n");
	return 0;
}