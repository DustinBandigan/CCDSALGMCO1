#include <stdio.h>
#include "sort.h"

int main(void) {
    Point anchor = {0.0, 0.0};

    Point points[] = {
        {0.0, 3.0},
        {2.0, 2.0},
        {3.0, 0.0},
        {1.0, 2.0}
    };

    int n = sizeof(points) / sizeof(points[0]);

    bubbleSort(points, n, anchor);

    printf("Sorted points:\n");

    for (int i = 0; i < n; i++) {
        printf("(%.6f, %.6f)\n",
               points[i].x, points[i].y);
    }

    return 0;
}
