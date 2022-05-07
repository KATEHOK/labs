#pragma once

/*
* Выводит список действий и запрашивает действие
* Параметры:
* (char*) pQuestion - вопрос к пользователю;
* (char**) ppArray - массив вариантов действий;
* (int) len - длина массива.
* Вернет:
* -1 - конец файла;
* 0 - выход;
* >0 - действие.
*/
int console(char*, char**, int);

/*
* Запрашивает ввод ключа и данных, добавляет новый элемент в таблицу
* Параметры:
* (Table*) pTable - указатель на таблицу.
* Вернет:
* 0 - успешно (не произошло програмных сбоев);
* 1 - конец файла.
*/
//pTable --> oTable (offset), pKey --> oKey (offset)
int dInsertItem(Table*);

/*
* 
*/
//pTable --> oTable (offset), pKey --> oKey (offset)
int dDeleteItem(Table*);
