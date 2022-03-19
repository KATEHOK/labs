#ifndef A_H
#include "a.h"
#endif

int main() {
	Stack stackMain, stackSupport, stackBracket, stackFragment;
	int status, len, open = 0, close = 0, previous = 0;
	char* pFormula, *pProcessing;
	// название проекта
	printf("\nSTACK FORMULA COMPILER\n");
	// автограф
	printf("Developed by KATEHOK (https://github.com/KATEHOK)\nPlease enjoy!\n\n");
	// для выявления утечек памяти
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// запрашиваем формулу, определяем длину вектора (для стека-вектора)
	status = setFormula(&pFormula, &len);
	// инициализируем необходимые стеки
	status = stacksInit(&stackMain, &stackSupport, &stackBracket, &stackFragment, &len);
	if (status == 1) {
		free(pFormula);
		return 0;
	}
	// перебор массива, вызов обработчиков символов
	pProcessing = pFormula;
	do {
		if (*pProcessing == '(') {
			open++;
			status = processOpenBracket(&stackMain, &stackBracket, &stackFragment, pProcessing, previous);
			// удобный костыль выхода из цикла с ошибкой
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
		// количество закрытых скобок не может быть больше количества открытых
		if (close > open)
			break;
	} while (*pProcessing != '\0');
	// количество закрытых скобок не соответствует количеству открытых
	if (open != close) {
		printf("|-> Formula invalid!\n");
		stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
		free(pFormula);
		return 0;
	}
	// печатает скомпилированную формулу
	status = printCompiled(&stackMain, &stackSupport, len);
	if (status == 1)
		printf("|-> Error with printing compiled formula!\n");
	else
		printf("Successfully!\n");
	// освобождаем память
	stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
	free(pFormula);
	return 0;
}