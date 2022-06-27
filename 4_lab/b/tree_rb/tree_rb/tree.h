#pragma once

/*
* 
*    B
*   / \
*.........
*....R....
*.../ \...
*..B   B..
*./ \.....
*.........
* .../....
* .(B)....
* 
* +5th
*  
*/


typedef struct Info {
	char* pTxt;
	struct Info* pNext;
} Info;

typedef struct Node {
	unsigned int key;
	short color; //0 - black; 1 - red
	int infoCount;
	Info* pInfo;

	struct Node* pLeft;
	struct Node* pRight;
	struct Node* pParent;
} Node;

typedef struct Tree {
	Node* pRoot;
	Node* pEList;
} Tree;

/*
* Инициализирует дерево.
* Вернет:
* NULL - отказ в выделении памяти;
* (Tree*) - указатель на созданное дерево.
*/
Tree* treeInit();

/*
* Инициализирует узел дерева, окраска - RED:
* (Tree*) pTree - указатель на дерево;
* (int) key - ключ;
* (char*) pInfo - информация (строка).
* Вернет:
* NULL - отказ в выделении памяти;
* (Node*) - указатель на созданный узел.
*/
Node* nodeInit(Tree* pTree, int key, Info* pInfo);

/*
* Вызывает рекурсивное удаление всех узлов дерева, удаляет дерево:
* (Tree*) pTree - указатель на дерево.
*/
void treeDelete(Tree* pTree);

/*
* Рекурсивно удаляет все поддеревья текущего узла и сам текущий узел:
* (Node*) pNode - указатель на текущий узел;
* (Node*) pEList - указатель на лист.
*/
void nodesDelete(Node* pNode, Node* pEList);

/*
* Выводит список информаций:
* (Info*) pInfo - указатель на элемент списка, с которого начинается удаление.
*/
void infoListPrint(Info* pInfo);

/*
* Удаляет список информаций:
* (Info*) pInfo - указатель на элемент списка, с которого начинается удаление.
*/
void infoListDelete(Info* pInfo);

/*
* Рекурсивно обходит дерево и печатает ключ и инфу узлов, ключ которых не больше заданного:
* (Node*) pNode - указатель на узел;
* (Node*) pEList - указатель на лист;
* (int) keyEnd - максимальный ключ, который будет распечатан;
* (int) isKeyEndCorrect - если не равен нулю, печатает все дерево.
*/
void detour(Node* pNode, Node* pEList, int keyEnd, int isKeyEndCorrect);

/*
* Рекурсивно ищет узел по ключу и версии:
* (Node*) pNode - указатель на узел;
* (Node*) pEList - указатель на лист;
* (int) key - искомый ключ;
* (int) version - искомая версия (начинается с 1)
* (Info**) ppInfo - указатель на указатель на информацию (если NULL, то инфа не запоминается);
* Вернет:
* NULL - узел не найден;
* (Node*) - указатель на найденный узел.
*/
Node* search(Node* pNode, Node* pEList, int key, int version, Info** ppInfo);

/*
* НЕ ВСТАВЛЯЕТ В ПУСТОЕ ДЕРЕВО
* Всставляет новый узел (дублирующиеся ключи - в список):
* (Tree*) pTree - указатель на дерево;
* (int) key - новый ключ;
* (char*) pTxt - информация (строка), данные из нее КОПИРУЮТСЯ.
* Вернет:
* NULL - отказ в выделении памяти или ошибка копирования;
* (Node*) - указатель на созданный узел.
*/
Node* insertNotFirst(Tree* pTree, int key, char* pTxt);

/*
* Ищет родительский элемент для нового ключа:
* (Node*) pNode - указатель на узел;
* (Node*) pEList указатель на лист;
* (int) key - новый ключ;
* (int*) pLR - указатель, куда записать метку ребенка (-1 - возвращаемый ключ, 0 - left, 1 - right).
* Вернет:
* (Node*) - искомый указатель.
*/
Node* searchFunnyFather(Node* pNode, Node* pEList, int key, int* pLR);

/*
* Вставляет первый узел СТРОГО В ПУСТОЕ дерево:
* (Tree*) pTree - указатель на дерево;
* (int) key - ключ;
* (char*) pTxt - информация (строка), данные из нее КОПИРУЮТСЯ.
* Вернет:
* NULL - отказ в выделении памяти или ошибка копирования функццией strcpy;
* (Node*) - указатель на вставленный узел.
*/
Node* insertFirst(Tree* pTree, int key, char* pTxt);

/*
* Инициализирует новый элемент спмска информации:
* (char*) pTxt - информация (строка), данные из нее КОПИРУЮТСЯ;
* (Info*) pNext - указатель на следующий элемент списка (для создания первого - NULL).
* Вернет:
* NULL - отказ в выделении памяти или ошибка копирования;
* (Info*) - указатель на новый элемент.
*/
Info* infoInit(char* pTxt, Info* pNext);

/*
* Вызывает соответствующую функцию вставки:
* (Tree*) pTree - указатель на дерево;
* (int) key - ключ;
* (char*) pInfo - информация (строка), данные из нее КОПИРУЮТСЯ.
* Вернет:
* NULL - отказ в выделении памяти или ошибка копирования;
* (Node*) - указатель на вставленный узел.
*/
Node* insert(Tree* pTree, int key, char* pTxt);

/*
* Левый поворот вокруг узла (против часовой стрелки):
* url = '5 Красно-черные деревья.pdf' (33);
* (Tree*) pTree - указатель на дерево;
* (Node*) pNode - указатель на узел 'А'.
*/
void rotateLeft(Tree* pTree, Node* pA);

/*
* Правый поворот вокруг узла (по часовой стрелке):
* url = '5 Красно-черные деревья.pdf' (36);
* (Tree*) pTree - указатель на дерево;
* (Node*) pNode - указатель на узел 'B'.
*/
void rotateRight(Tree* pTree, Node* pB);

/*
* Поочередно вызывает два левых поворота:
* (Tree*) pTree - указатель на дерево;
* (Node*) pFirst - указатель на первый узел;
* (Node*) pSecond - указатель на второй узел.
*/
void rotateLeftLeft(Tree* pTree, Node* pFirst, Node* pSecond);

/*
* Поочередно вызывает два правых поворота:
* (Tree*) pTree - указатель на дерево;
* (Node*) pFirst - указатель на первый узел;
* (Node*) pSecond - указатель на второй узел.
*/
void rotateRightRight(Tree* pTree, Node* pFirst, Node* pSecond);

/*
* Поочередно вызывает два поворота:
* (Tree*) pTree - указатель на дерево;
* (Node*) pLeft - указатель на узел для левого поворота;
* (Node*) pRight - указатель на узел для правого поворота.
*/
void rotateLeftRight(Tree* pTree, Node* pLeft, Node* pRight);

/*
* Поочередно вызывает два поворота:
* (Tree*) pTree - указатель на дерево;
* (Node*) pRight - указатель на узел для правого поворота;
* (Node*) pLeft - указатель на узел для левого поворота.
*/
void rotateRightLeft(Tree* pTree, Node* pRight, Node* pLeft);

/*
* Балансирует дерево после вставки оригинального ключа (не вызывается после первой вставки):
* (Tree*) pTree - указатель на дерево;
* (Node*) pNode - указатель на вставленный (корректируемый) элемент.
*/
void insertFix(Tree* pTree, Node* pNode);

/*
* Корректно удаляет узел по ключу:
* (Tree*) pTree - указатель на дерево;
* (int) key - целевой ключ.
* Вернет:
* 0 - успешно;
* 1 - ключ не найден.
*/
int nodeDelete(Tree* pTree, int key);

/*
* fix-pv-in-right.png
*/
void deleteFixRight(Tree* pTree, Node* pParent);

/*
* fix-pv-in-right.png // зеркально
*/
void deleteFixLeft(Tree* pTree, Node* pParent);

/*
* Балансировка высших уровней.
* Снизу - баланс. Высота текущего на 1 меньше необходимой.
* Высота текущего не меньше двух.
* Текущий - черный.
*/
void fixHigher(Tree* pTree, Node* pCurrent, Node* pParent);

/*
* Рекурсивно ищет узел с максимальным ключом:
* (Node*) pNode - указатель на поддерево, в котором осуществляется поиск.
* Вернет:
* NULL - если pNode == NULL;
* (Node*) - указатель на искомый узел.
*/
Node* searchMax(Node* pNode, Node* pEList);

/*
* Рекурсивно ищет узел с минимальным ключом:
* (Node*) pNode - указатель на поддерево, в котором осуществляется поиск.
* Вернет:
* NULL - если pNode == NULL;
* (Node*) - указатель на искомый узел.
*/
Node* searchMin(Node* pNode, Node* pEList);

/*
* Ищет узел с первым ключом, превышающим заданный:
* (Node*) pNode - указатель на поддерево, в котором нужно осуществить поиск;
* (Node*) pEList - указатель на лист;
* (int) key - заданный ключ;
* (Node*) pMemory - последний "верный ответ".
* Вернет:
* NULL - передан NULL или pEList вместо pNode;
* (Node*) - указатель на искомый узел.
*/
Node* searchSpecial(Node* pNode, Node* pEList, int key, Node* pMemory);

/*
* Считывает из текстового файла данные об дереве:
* (char*) pPath - путь до файла.
* Вернет:
* NULL - не успешно (не выделена память или не открыт файл);
* (Tree*) -указатель на новое дерево.
*/
Tree* download(char* pPath);

/*
* Рекурсивно печатает дерево "в виде дерева":
* (Node*) pNode - узел, с которого начать печать;
* (int) offset - количество пробелов перед текущим узлом (ставить 0).
*/
void printAsTree(Node* pNode, Node* pEList, int offset);