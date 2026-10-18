#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include "stack.h"

// Math helper for turns
double ccw(Point p1, Point p2, Point p3);


void run_graham_scan_slow(Point points[], int n);
void run_graham_scan_fast(Point points[], int n);

#endif