// Created by DigitalWorm on 22.02.2022.
// Changed by DigitalWorm on 23.02.2022.

#include "structs.h"
#ifndef V3_FUNCS_H
#define V3_FUNCS_H

int getNum(int*, int);
int setLen(int*, int);
int askMemoryMatrix(Matrix*);
int askMemoryLine(Line*);
int setItem(int*);
void clean(Matrix*, int);
int isPalindrome(int);
int fillFirstMatrix(Matrix*);
int fillSecondMatrix(Matrix*, Matrix*);
int createFirstMatrix(Matrix*);
int createSecondMatrix(Matrix*, Matrix*);
void printMatrix(Matrix*, int);

#endif //V3_FUNCS_H
