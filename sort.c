#include "sort.h"

// Returns 1 when a should come after b
int shouldSwap(Point a, Point b, Point anchor) {
    double ax = a.x - anchor.x;
    double ay = a.y - anchor.y;
    double bx = b.x - anchor.x;
    double by = b.y - anchor.y;

    double cross = ax * by - ay * bx;

    if (cross < 0)
        return 1;

    if (cross > 0)
        return 0;

    // Same angle: nearer point comes first
    double distA = ax * ax + ay * ay;
    double distB = bx * bx + by * by;

    return distA > distB;
}

void bubbleSort(Point points[], int n, Point anchor) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (shouldSwap(points[j], points[j + 1], anchor)) {
                Point temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}
