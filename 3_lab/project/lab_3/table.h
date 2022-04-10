#pragma once
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

int tableInit(Table*);
void tableDelete(Table*);

int tableAdd(Table*, int, int, char*);
Item* tableSearchItemByComposite(Table*, int, int);
void tableDeleteItemByComposite(Table*, int, int);
Item* tableSearchItemBySingle(Table*, int);
void tableDeleteItemBySingle(Table*, int);
int tablePrint(Table*);

int setMaxSizeKS(int*, int);
int searchKS1(Table*, int);
int deleteKS1(Table*, int);
int insertKS1(Table*, int, Item*);