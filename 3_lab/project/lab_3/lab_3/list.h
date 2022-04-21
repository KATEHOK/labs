#pragma once
#ifndef APP_H
#include "app.h"
#endif // !APP_H

#define LIST_H

struct TablesItem {
	struct TablesItem* pPrev;
	struct TablesItem* pNext;
	Table* pTable;
};

typedef struct {
	struct TablesItem* pTop;
} TablesList;

/*
* Инициализирует список таблиц
* Вернет (TablesList*):
* > NULL - успешно;
* NULL - не успешно.
*/
TablesList* tablesListInit();

/*
* Вызывает инициализацию таблицы
* Параметры:
* (int) ms1 - размер 1-го пространства ключей;
* (int) ms2 - размер 1-го пространства ключей.
* Вернет (Table*):
* > NULL - успешно;
* NULL - не успешно.
*/
Table* createTable(int, int);

/*
* Ищет элемент списка таблиц
* Параметры:
* (TablesList*) pTablesList - указатель на список;
* (Table*) pTable - указатель на искомую таблицу.
* Вернет (struct TablesItem*):
* > NULL - успешно;
* NULL - не успешно.
*
*/
struct TablesItem* tablesListSearchItem(TablesList*, Table*);

/*
* Добавляет новый элемент в список таблиц
* Параметры:
* (TablesList*) pTablesList - указатель на список таблиц;
* (Table*) pTable - указатель на добавляемую таблицу.
* Вернет (int):
* 0 - успешно;
* 1 - не успешно (pTable == NULL);
* 2 - не успешно (таблица уже в списке);
* 3 - не успешно (отказ в выделении памяти).
*/
int tablesListAddItem(TablesList*, Table*);

/*
* Удаляет элемент из списка таблиц
* Параметры:
* (TablesList*) pTablesList - указатель на список таблиц;
* (Table*) pTable - указатель на удаляемую таблицу.
* Вернет (int):
* 0 - успешно;
* 1 - не успешно (таблица не найдена).
*/
int tablesListDeleteItem(TablesList*, Table*);

/*
* Удаляет список таблиц
* Параметры:
* (TablesList*) pTablesList - указатель на список таблиц.
* Вернет (int):
* 0 - успешно;
* 1 - не успешно (неудача частного удаления; нарушение структуры списка).
*/
int tablesListDelete(TablesList*);