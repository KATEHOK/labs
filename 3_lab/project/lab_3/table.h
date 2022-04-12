﻿#pragma once
#ifndef APP_H
#include "app.h"
#endif // !APP_H

#define TABLE_H

typedef struct {
	// указатель на информацию
	char* pInfo;
	// опциональные поля, для оптимизации выполнения операций,
	// состав и наличие которых должны быть обоснованы:
	// ключ элемента из 1­го пространства ключей
	int key1;
	// ключ элемента из 2­го пространства ключей
	int key2;
	// связь с элементом 1­го пространства ключей по индексу
	int id1;
	// связь с элементом 2­го пространства ключей по индексу (на первый элемент соответствующего списка)
	int id2;
	// связь с элементом 1­го пространства ключей по указателю
	struct KeySpace1* p1;
	// связь с элементом 2­го пространства ключей по указателю
	struct KeySpace2* p2;
} Item;

struct KeySpace1 {
	// ключ
	int key;
	// указатель на элемент
	Item* pData;
};

struct KeySpace2 {
	// ключ
	int key;
	// номер релиза
	int release;
	// указатель на данные
	Item* pData;
	// указатель на следующий элемент списка
	struct KeySpace2* pNext;
	// указатель на предыдущий элемент списка
	struct KeySpace2* pPrev;
};

typedef struct {
	// указатели на пространства ключей
	struct KeySpace1* pKS1;
	struct KeySpace2* pKS2;
	// максимальные размеры пространств ключей
	int maxSize1;
	int maxSize2;
	// количества ключей
	int countKeys1;
	int countKeys2;
} Table;

/*
* Инициализирует таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу.
* Вернет:
* 0 - успешно;
* 1 - не успешно.
*/
int tableInit(Table*);

/*
* Удаляет таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу.
*/
void tableDelete(Table*);

int tableAdd(Table*, int, int, char*);
Item* tableSearchItemByComposite(Table*, int, int);
void tableDeleteItemByComposite(Table*, int, int);
Item* tableSearchItemBySingle(Table*, int);
void tableDeleteItemBySingle(Table*, int);
int tablePrint(Table*);

/*
* Устанавливает максимальную длину таблицы (пространства ключей)
* Параметры:
* (int*) pData - указатель куда записать значение;
* (int) KSNumber - номер пространства ключей.
* Вернет:
* 0 - успешно;
* 1 - не успешно.
*/
int setMaxSizeKS(int*, int);

/*
* Ищет элемент таблицы по ключу
* Параметры:
* (Table*) pTable - указатель на таблицу,
* (int) key - ключ.
* Вернет:
* > -1 - идентификатор элемента;
* -1 - не успешно.
*/
int searchKS1(Table*, int);

/*
* Удаляет элемент таблицы по ключу
* Параметры:
* (Table*) pTable - указатель на таблицу,
* (int) key - ключ.
* Вернет:
* 0 - успешно;
* 1 - не успешно.
*/
int deleteKS1(Table*, int);

/*
* Вставляет элемент в таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу,
* (int) key - ключ
* (Item*) pData - указатель на новые данные.
* Вернет:
* 0 - успешно;
* 1 - не успешно (переполнение);
* 1 - не успешно (дублирование ключей).
*/
int insertKS1(Table*, int, Item*);

/*
* Хэш-функция
* Параметры:
* (int) key - ключ;
* (int) size - верхняя граница хэша.
* Вернет:
* >= 0 - хэш;
* -1 - не успешно.
*/
int getHash(int, int);

/*
* Ищет элемент(ы) в хэш-таблице
* Параметры:
* (Table*) pTable - указатель на матрицу;
* (int) key - ключ элемента;
* (int) release - версия элемента (-1 - ищет все версии).
* Вернет:
* NULL - не нашел;
* > NULL - нашел (была выделена и не очищена память под возвращаемое значение).
*/
struct KeySpace2** searchKS2(Table*, int, int);

/*
* Вставляет элемент в хэш-таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу,
* (int) key - ключ
* (Item*) pData - указатель на новые данные.
* Вернет:
* 0 - успешно;
* 1 - не успешно (отказ в запросе выделения памяти).
*/
int insertKS2(Table*, int, Item*);