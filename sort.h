#ifndef SORT_H
#define SORT_H

#include "stack.h"

void bubbleSort(Point points[], int n, Point anchor);
void merge(Point arr[], int l, int m, int r, Point anchor);
void mergeSort(Point arr[], int l, int r, Point anchor);

#endif
