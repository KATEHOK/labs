#ifndef A_H
#include "a.h"
#endif

int main() {
	Stack stackMain, stackSupport, stackBracket, stackFragment;
	int status, len, open = 0, close = 0, previous = 0;
	char* pFormula, *pProcessing;
	// �������� �������
	printf("\nSTACK FORMULA COMPILER\n");
	// ��������
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");
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
	// ������� �������, ����� ������������ ��������
	pProcessing = pFormula;
	do {
		if (*pProcessing == '(') {
			open++;
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
			status = processCloseBracket(&stackBracket, &stackFragment);
			if (status == 1) {
				open = 0;
				close = 1;
			}
			previous = 1;
		}
		else if (*pProcessing == '+' || *pProcessing == '-') {
			status = processPlusMinus(&stackMain, &stackSupport, &stackBracket, pProcessing);
			if (status == 1) {
				open = 0;
				close = 1;
			}
			previous = 2;
		}
		else if (*pProcessing == '*' || *pProcessing == '/') {
			status = processMulDiv(&stackMain, &stackSupport, &stackFragment, pProcessing);
			if (status == 1) {
				open = 0;
				close = 1;
			}
			previous = 3;
		}
		else {
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
	// �������� ���������������� �������
	status = printCompiled(&stackMain, &stackSupport, len);
	if (status == 1)
		printf("|-> Error with printing compiled formula!\n");
	else
		printf("Successfully!\n");
	// ����������� ������
	stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
	free(pFormula);
	return 0;
}