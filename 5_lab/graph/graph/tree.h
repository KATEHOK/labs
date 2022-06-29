#pragma once

typedef struct Tree {
	struct Tree** ppChildren;
	char pName[8];
	int childrenCount;
} Tree;


/*
* »нициализирует пустую вершину с именем:
* (char*) pName - им€ вершины (статический массив символов).
* ¬ернет:
* NULL - отказ в выделении пам€ти, передано NULL или ошибка копировани€;
* (Tree*) - указатель на новую вершину.
*/
Tree* initTree(char pName[8]);

/*
* ”дал€ет поддерево:
* (Tree*) pTree - указатель на дерево;
* (char*) pName - им€ вершины (статический массив символов).
*/
void deleteSubTree(Tree* pTree, char pName[8]);

/*
* –екурсивно удал€ет все дерево:
* (Tree*) pTree - указатель на дерево.
*/
void deleteTree(Tree* pTree);

/*
* –екурсивно ищет узел по имени:
* (Tree*) pTree - указатель на поддерево, в котором осуществл€етс€ поиск;
* (char*) pName - им€ узла (ствтический массив символов).
* ¬ернет:
* NULL - узел не найден;
* (Tree*) - указатель на найденный узел.
*/
Tree* searchTree(Tree* pTree, char pName[8]);

/*
* ¬ставл€ет новый узел в непустое дерево, узел конкретно наследуетс€:
* (Tree*) pTree - указатель на дерево;
* (char*) pParent - им€ родител€ (статический массив символов);
* (char*) pNew - им€ вставл€емого узла (статический массив символов).
* ¬ернет:
* NULL - что-то пошло не так;
* (Tree*) - указатель на вставленный узел.
*/
Tree* insertTree(Tree* pTree, char pParent[8], char pNew[8]);

/*
* ѕечатает дерево в виде дерева:
* (Tree*) pTree - указатель на поддерево;
* (int) offset - отступ дл€ текущего узла.
*/
void printAsTree(Tree* pTree, int offset);