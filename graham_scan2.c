#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "stack.h"
#include "graham_scan.h"

double ccw(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

void run_graham_scan_fast(Point points[], int n) {
    clock_t start_time = clock();

    // Find anchor point
    int min_y = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < points[min_y].y) || 
            (points[i].y == points[min_y].y && points[i].x < points[min_y].x)) {
            min_y = i;
        }
    }

    // Swap anchor to index 0
    Point temp = points[0];
    points[0] = points[min_y];
    points[min_y] = temp;
    Point anchor = points[0];

    // Sort using fast sort
    mergeSort(points, 1, n - 1, anchor);

    // Initialize Stack
    Stack s;
    CREATE(&s);
    PUSH(&s, points[0]);
    PUSH(&s, points[1]);
    PUSH(&s, points[2]);

    // Scan
    for (int i = 3; i < n; i++) {
        while (s.top >= 1 && ccw(NEXT_TO_TOP(&s), TOP(&s), points[i]) <= 0) {
            POP(&s);
        }
        PUSH(&s, points[i]);
    }

    clock_t end_time = clock();
    double elapsed_ms = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;
    
    printf("Fast Graham Scan Convex Hull points:\n");
    for (int i = 0; i <= s.top; i++) {
        printf("(%.6f, %.6f)\n", s.elements[i].x, s.elements[i].y);
    }
    printf("Execution Time: %.2f ms\n", elapsed_ms);
}