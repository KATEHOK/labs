#include "a.h"

int main() {
	Stack stack;
	int status;
	// дл€ вы€влени€ утечек пам€ти
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	status = stackInit(&stack);
	return 0;
}