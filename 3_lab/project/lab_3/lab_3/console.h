#pragma once
#ifndef APP_H
#include "app.h"
#endif // !APP_H

#define CONSOLE_H

/*
* Печатает построчно список строк
* Параметры:
* (char**) ppList - массив строк;
* (int) lenList - длина массива.
*/
void printList(char**, int);

/*
* Меню-шаблон
* (char*) pQuestion - вопрос к пользователю;
* (char**) ppList - массив строк-вариантов действий;
* (int) lenList - длина массива.
* Вернет:
* > 0 - номер (индекс + 1) выбранного ответа;
* 0 - конец файла.
*/
int console(char*, char**, int);

/*
* Функция предлагает создать список таблиц или же выйти из программы
* Вернет:
* 1 - создать список таблиц;
* 2 - выйти из программы.
*/
int startConsole();

/*
* Меню-запрос подтверждения
* Параметры:
* (char*) pQuestion - вопрос к пользователю.
* Вернет:
* 1 - согласен;
* 2 - не согласен;
* 0 - конец файла.
*/
int confirmConsole(char*);

/*
* Меню выхода из программы
* Параметры:
* (TablesList*) pTL - список таблиц.
* Вернет:
* 0 - готов к выходу;
* 1 - не готов к выходу.
*/
int exitConsole(TablesList*);

/*
* Предлагает пользователю выбрать таблицу для работы
* Параметры:
* (TablesList*) pTL - указатель на список таблиц.
* Вернет:
* > NULL - указатель на выбранную таблицу;
* NULL - не удалось выбрать таблицу (ошибка или пользователь передумал).
*/
Table* selectTableConsole(TablesList*);

int processSelectedTable(Table*);

int addTableConsole(TablesList*);