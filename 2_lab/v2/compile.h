//
// Created by DigitalWorm on 04.03.2022.
//

#ifndef V2_COMPILE_H
#define V2_COMPILE_H

int compile();
int processOpenBracket(char*, int, int, void*, void*, void*);
int processCloseBracket(int, void*, void*);
int processPlusMinus(char*, int, void*, void*, void*);
int processMulDiv(char*, int, void*, void*, void*);
int processLiteral(char*, int, int, void*, void*);
void printCompiled(int, int, void*, void*);

#endif //V2_COMPILE_H
