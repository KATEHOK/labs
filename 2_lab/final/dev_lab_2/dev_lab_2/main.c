#ifndef A_H
#include "a.h"
#endif

int main() {
	Stack stackMain, stackSupport, stackBracket, stackFragment;
	int status, len;
	// ��� ��������� ������ ������
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// �������������� ����������� �����
	status = stacksInit(&stackMain, &stackSupport, &stackBracket, &stackFragment, &len);
	if (status == 1)
		return 0;


	// ����������� ������
	stacksFree(&stackMain, &stackSupport, &stackBracket, &stackFragment);
	// ���������, �����
	printf("Successfully!\n");
	return 0;
}