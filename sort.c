#include "sort.h"
#include <stdlib.h>

// Returns 1 when a should come after b
int shouldSwap(Point a, Point b, Point anchor) {
    double ax = a.x - anchor.x;
    double ay = a.y - anchor.y;
    double bx = b.x - anchor.x;
    double by = b.y - anchor.y;

    int aIsLeft = (ay == 0.0 && ax < 0.0);
    int bIsLeft = (by == 0.0 && bx < 0.0);

    if (aIsLeft != bIsLeft) {
        return aIsLeft;
    }

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


void merge(Point arr[], int l, int m, int r, Point anchor) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Point *L = (Point *)malloc(n1 * sizeof(Point));
    Point *R = (Point *)malloc(n2 * sizeof(Point));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l;
    
    while (i < n1 && j < n2) {
        // Using Dustin's existing helper to determine order
        if (!shouldSwap(L[i], R[j], anchor)) { 
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSort(Point arr[], int l, int r, Point anchor) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, anchor);
        mergeSort(arr, m + 1, r, anchor);
        merge(arr, l, m, r, anchor);
    }
}
