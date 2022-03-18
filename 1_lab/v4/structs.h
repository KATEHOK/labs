// Created by DigitalWorm on 22.02.2022.
// Changed by DigitalWorm on 23.02.2022.

#ifndef V3_STRUCTS_H
#define V3_STRUCTS_H

 typedef struct {
    int len;
    int* lin;
} Line;

typedef struct {
    int len;
    Line* matrix;
} Matrix;
#endif //V3_STRUCTS_H
