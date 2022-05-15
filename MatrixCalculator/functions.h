#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float** arrayAlloc(int n, int m);
void arrayFree(float** arr, int n);

float** arraySquareEnter(int* n);
float** arrayOblongEnter(int* n, int* m);
void arrayPrint(float** arr, int n, int m);

float determinant(float** arr, int n);
float** algebraAdd(float** arr, int n);
float** transposition(float** arr, int* n, int* m);