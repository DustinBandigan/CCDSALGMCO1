#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graham_scan.h"

#define MAX_FILENAME 256

/* static: ~512 KB each, too big for the call stack on some systems */
static Point points[MAX_SIZE];
static Point hull[MAX_SIZE];

int main(void) {
    char inName[MAX_FILENAME];
    char outName[MAX_FILENAME];
    int n, m, i;

    /* 1 & 2: ask for the input and output filenames (with extension) */
    printf("Enter input filename (with extension): ");
    if (scanf("%255s", inName) != 1) {
        fprintf(stderr, "Error: invalid input filename.\n");
        return 1;
    }
    printf("Enter output filename (with extension): ");
    if (scanf("%255s", outName) != 1) {
        fprintf(stderr, "Error: invalid output filename.\n");
        return 1;
    }

    /* 3: open the input file */
    FILE *fin = fopen(inName, "r");
    if (fin == NULL) {
        fprintf(stderr, "Error: cannot open input file '%s'.\n", inName);
        return 1;
    }

    /* 4: read n, then n (x, y) pairs */
    if (fscanf(fin, "%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Error: first line must be a positive number of points.\n");
        fclose(fin);
        return 1;
    }
    if (n > MAX_SIZE) {
        fprintf(stderr, "Error: n = %d exceeds the maximum of %d points.\n", n, MAX_SIZE);
        fclose(fin);
        return 1;
    }
    for (i = 0; i < n; i++) {
        if (fscanf(fin, "%lf %lf", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Error: expected %d points but could only read %d.\n", n, i);
            fclose(fin);
            return 1;
        }
    }

    /* 5: run the Graham's scan (slow version); it prints the elapsed time */
    m = grahamScan1(points, n, hull);

    /* 6: write the hull (anchor first, counterclockwise) */
    FILE *fout = fopen(outName, "w");
    if (fout == NULL) {
        fprintf(stderr, "Error: cannot create output file '%s'.\n", outName);
        fclose(fin);
        return 1;
    }
    fprintf(fout, "%d\n", m);
    for (i = 0; i < m; i++)
        fprintf(fout, "%.6f %.6f\n", hull[i].x, hull[i].y);

    /* 7: close both files */
    fclose(fin);
    fclose(fout);

    printf("Convex hull has %d point(s). Written to %s\n", m, outName);
    return 0;
}
