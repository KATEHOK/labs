#pragma once

typedef struct Line {
	char pName[16];
	int* pWeight;
	//
	int prevId;
	int distance;
} Line;

typedef struct Matrix {
	int size;
	Line* pLine;
} Matrix;

/*
* »нициализирует матрицу.
* ¬ернет:
* NULL - отказ в выделении пам€ти;
* (Matrix*) указатель на матрицу.
*/
Matrix* initMatrix();

/*
* ”дал€ет матрицу:
* (Matrix*) pMatrix - указатель на матрицу.
*/
void deleteMatrix(Matrix* pMatrix);

/*
* ƒобавл€ет строку в конец матрицы, преобразует матрицу к квадратному виду:
* (Matrix*) pMatrix - указатель на матрицу;
* (char*) pName - им€ дл€ новой строки (статический массив символов).
* ¬ернет:
* 0 - успешно;
* 1 - отказ в выделении пам€ти (не критично);
* 2 - дублирование имен (не критично);
* 3 - отказ в выделении пам€ти (критично);
* 4 - передан NULL;
*/
int addLine(Matrix* pMatrix, char pName[8]);

/*
* ”дал€ет строку из матрицы, преобразует матрицу к квадратному виду:
* (Matrix*) pMatrix - указатель на матрицу;
* (char*) pName - им€ удал€емой строки (статический массив символов).
* ¬ернет:
* 0 - успешно;
* 1 - вершина не найдена;
* 2 - отказ при работе с пам€тью (критично);
* 3 - передан NULL.
*/
int deleteLine(Matrix* pMatrix, char pName[8]);

/*
* ƒобавл€ет элемент строки (при наличии обновл€ет значение):
* (Matrix*) pMatrix - указатель на матрицу;
* (char*) pSrc - им€ строки (статический массив символов);
* (char*) pDest - им€ столбца (статический массив символов);
* (int) weight - добавл€емое значение.
* ¬ернет:
* 0 - успешно;
* 1 - строка(и) не найдена(ы);
* 2 - передан NULL.
*/
int addWeight(Matrix* pMatrix, char pSrc[8], char pDest[8], int weight);

/*
* «анул€ет элемент строки:
* (Matrix*) pMatrix - указатель на матрицу;
* (char*) pSrc - им€ строки (статический массив символов);
* (char*) pDest - им€ столбца (статический массив символов).
*/
void deleteWeight(Matrix* pMatrix, char pSrc[8], char pDest[8]);

/*
* »щет строку:
* (Matrix*) pMatrix - указатель на матрицу;
* (char*) pTarget - им€ целевой вершины (статический массив символов).
* ¬ернет:
* >= 0 - индекс строки;
* -1 - строка не найдена.
*/
int searchLine(Matrix* pMatrix, char pTarget[8]);

/*
* ѕечатает матрицу:
* (Matrix*) pMatrix - указатель на матрицу.
* ¬ернет:
* 0 - успешно;
* 1 - передано NULL;
* 2 - матрица пуста.
*/
int printMatrix(Matrix* pMatrix);

/*
* —оздает идентичную матрицу
*/
Matrix* copyMatrix(Matrix* pMatrix);