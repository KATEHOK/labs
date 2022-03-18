#include <stdio.h>
#include "compile.h"

int main() {
    int feedback;
    // автограф
    printf("\nDeveloped by KATEHOK (https://github.com/KATEHOK)\nHello, World!\n\n");
    // программа-компилятор
    feedback = compile();
    if (feedback == 1) {
        printf("|-> Compiling Error!\n");
    }
    // "отчет"
    printf("Successfully! Closing...\n");
    return 0;
}
