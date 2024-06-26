﻿#pragma once
#ifndef APP_H
#include "app.h"
#endif // !APP_H

#define TABLE_H

struct Item {
	// указатель на информацию
	int* pInfo;
	// опциональные поля, для оптимизации выполнения операций,
	// состав и наличие которых должны быть обоснованы:
	// ключи элемента из соответствующих пространств ключей
	int key1;
	int key2;
	// связь с элементом 1­го пространства ключей по индексу
	int id1;
	// связь с элементом 2­го пространства ключей по индексу (на первый элемент соответствующего списка)
	int id2;
	// связь с элементоми соответствующих пространств ключей по указателю
	struct KeySpace1* p1;
	struct KeySpace2* p2;
	// для каскадности родительских и дочерних таблиц
	struct Item* pPrev;
	struct Item* pNext;
};

struct KeySpace1 {
	// ключ
	int key;
	// указатель на элемент
	struct Item* pData;
};

struct KeySpace2 {
	// ключ
	int key;
	// номер релиза
	int release;
	// указатель на данные
	struct Item* pData;
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
	// максимальные вставленные ключи
	int maxKey1;
	int maxKey2;
} Table;

/*
* Инициализирует таблицу
* Параметры:
* (Table**) ppTable - указатель на указатель на таблицу;
* (int) maxSize1 - размер 1-го пространства ключей (0 - пользовательский выбор);
* (int) maxSize2 - размер 2-го пространства ключей (0 - пользовательский выбор).
* Вернет:
* 0 - успешно;
* 1 - не успешно (конец файла);
* 2 - не успешно (отказ в выделении памяти).
*/
int tableInit(Table**, int, int);

/*
* Удаляет таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу.
*/
void tableDelete(Table*);

/*
* Вставляет элемент в таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу;
* (int) key1 - ключ для 1-го пространства ключей;
* (int) key2 - ключ для 2-го пространства ключей;
* (int) isKey1True - передача 1-го ключа (0 - ключ верный, 1 - нужно подобрать новый ключ);
* (int) isKey2True - передача 2-го ключа (0 - ключ верный, 1 - нужно подобрать новый ключ);
* (struct Item*) pData - указатель на новые данные.
* Вернет:
* 0 - успешно;
* 1 - не успешно (переполнение);
* 2 - не успешно (дублирование ключей);
* 3 - не успешно (отказ в запросе выделения памяти).
*/
int tableAdd(Table*, int, int, int, int, struct Item*);

/*
* Ищет ячейку по составному ключу
* Параметры:
* (Table*) pTable - указатель на таблицу;
* (int) key1 - ключ 1-го пространства ключей;
* (int) key2 - ключ 2-го пространства ключей.
* Вернет:
* > NULL - указатель на ячейку;
* NULL - не успешно.
*/
struct Item* tableSearchItemByComposite(Table*, int, int);

/*
* Удаляет ячейку таблицы по составному ключу
* Параметры:
* (Table*) pTable - указатель на таблицу;
* (int) key1 - ключ из 1-го пространства ключей;
* (int) key2 - ключ из 2-го пространства ключей.
* Вернет:
* 0 - успешно;
* 1 - не успешно (ошибка поиска);
* 2 - не успешно (ошибка удаления 1-го ключа);
* 3 - не успешно (ошибка удаления 2-го ключа, ошибка возврата 1-го ключа)
* 4 - не успешно (ошибка удаления 2-го ключа, таблица не изменена).
*/
int tableDeleteItemByComposite(Table*, int, int);

/*
* Ищет элементы по одному из ключей
* Параметры:
* (Table*) pTable - указатель на таблицу;
* (int) key - ключ;
* (int*) pCount - указатель, куда записать длину массива.
* Вернет:
* > NULL - указатель на массив элементов;
* NUll - не успешно.
*/
struct Item** tableSearchItemBySingle(Table*, int, int*);

/*
* Удаляет ячейку по одиному из ключей
* Параметры:
* (Table*) pTable - указатель на таблицу;
* (int) key - ключ;
* (int) ks - номер пространства ключей (1 или 2).
* Вернет:
* 0 - успено;
* 1 - не успешно (неправильное значение ks);
* 2 - не успешно (ячейка не найдена);
* 3 - не успешно (ячейка существует, таблица сломана);
* 4 - не успешно (ячейка существует, таблица исправна).
*/
int tableDeleteItemBySingle(Table*, int, int);

/*
* Вызывает печать таблицы
* Параметры:
* (Table*) pTable - указатель на таблицу;
* (int) ks - номер пространства ключей (1, 2 - номера; 3 - оба);
*/
void tablePrint(Table*, int);

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
* (struct Item*) pData - указатель на новые данные;
* (int) isKeyTrue - передача ключа (0 - ключ верный, 1 - нужно подобрать новый ключ).
* Вернет:
* 0 - успешно;
* 1 - не успешно (переполнение);
* 2 - не успешно (дублирование ключей).
*/
int insertKS1(Table*, int, struct Item*, int);

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
* (struct KeySpace2**) ppRes - указатель на массив найденных значений;
* (Table*) pTable - указатель на матрицу;
* (int) key - ключ элемента;
* (int) release - версия элемента (-1 - ищет все версии, -2 - ищет только последнюю версию).
* Вернет:
* >= 0 - количество найденных значений;
* -1 - ppRes равен NULL.
*/
int searchKS2(struct KeySpace2**, Table*, int, int);

/*
* Вставляет элемент в хэш-таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу,
* (int) key - ключ
* (struct Item*) pData - указатель на новые данные;
* (int) isKeyTrue - передача ключа (0 - ключ верный, 1 - нужно подобрать новый ключ).
* Вернет:
* 0 - успешно;
* 1 - не успешно (отказ в запросе выделения памяти).
*/
int insertKS2(Table*, int, struct Item*, int);

/*
* Удаляет элемент из хэш-таблицы
* Параметры:
* (Table*) pTable - указатель на таблицу,
* (int) key - ключ,
* (int) release - релиз:
* >= 0 - конкретрая версия;
* -1 - вся линейка;
* -2 - последняя версия,
* (int) doNotTouch - сколько последних версий оставить.
* Вернет:
* >= 0 - количество удаленных элементов;
* -1 - не успешно (отказ в выделении вспомогательной памяти).
*/
int deleteKS2(Table*, int, int, int, int);

/*
* Ищет элементы таблицы по диапазону ключей
* Параметры:
* (Table*) pTable - указатель на таблицу,
* (int) minKey - ключ-нижняя граница диапазона;
* (int) maxKey - ключ-верхняя граница диапазона.
* Вернет:
* > NULL - указатель на новую таблицу;
* NULL - не успешно.
*/
Table* searchRangeKS1(Table*, int, int);

/*
* Распечатывает таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу.
*/
void printByKS1(Table*);

/*
* Создает дочерний элемент (списковая логика)
* Параметры:
* (struct Item*) pPrev - указатель на родительский элемент.
* Вернет:
* > NULL - указатель на дочерний элемент;
* NULL - не успешно.
*/
struct Item* makeChild(struct Item*);

/*
* Удаляет элемент из списка
* Параметры:
* (struct Item*) pCurrent - удаляемый элемент.
*/
void deleteItemFromList(struct Item*);

/*
* Создает новую ячейку (элемент списка)
* Параметры:
* (char*) pInfo - указатель на информацию.
* Вернет:
* > NULL - указатель на ячейку;
* NULL - не успешно.
*/
struct Item* makeNewItem(int*);

/*
* Ищет ячейки по ключу из 2-го пространства ключей (все версии или указанную)
* (Table*) pTable - указатель на таблицу;
* (int) key - ключ из 2-го пространства ключей;
* (int) release - искомая версия (если -1 - все, -2 - последняя).
* Вернет:
* > NULL - указатель на новую таблицу;
* NULL - не успешно.
*/
Table* searchByKeyOrRelease(Table*, int, int);

/*
* Удаляет ранние релизы
* Параметры:
* (Table*) pTable - указатель на таблицу;
* (int) doNotTouch - сколько редизов оставить (если -2, берется значение по умолчанию).
* Вернет:
* 0 - успешно;
* 1 - не успешно (ошибка выделения вспомогательной памяти);
* 2 - не успешно (критическая поломка таблицы).
*/
int tableClean(Table*, int);

/*
* Распечатывает таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу.
*/
void printByKS2(Table*);