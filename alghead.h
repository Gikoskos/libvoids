#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARRAY_SIZE 20
#define NO_WALL -1
#define RANDOM_INT(x) rand()%x

int i;
void printArray(int*,int);
void fillArray(int*);
void insertionSort(int[]);
void selectionSort(int[]);