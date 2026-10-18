#include <stdio.h>
#include "stack.h"
#include "graham_scan.h"

#define MAX_FILENAME 256
#define MAX_LINE 256
#define TEMP_FILE "hull_temp.txt"

/* global arrays: 32,768 points (about 512 KB each) are too big for local arrays in main */
Point points[MAX_SIZE];
Point hull[MAX_SIZE];

/* > 0: counterclockwise turn, < 0: clockwise turn, 0: collinear */
double turn(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

/* Remove duplicate points and points lying on a straight edge (they are not corners of the hull) */
int cleanHull(Point h[], int m) {
    int k = 0, i;

    for (i = 0; i < m; i++) {
        if (k >= 1 && h[i].x == h[k - 1].x && h[i].y == h[k - 1].y)
            continue;
        while (k >= 2 && turn(h[k - 2], h[k - 1], h[i]) <= 0)
            k--;
        h[k] = h[i];
        k++;
    }
    return k;
}

int main(void) {
    char inName[MAX_FILENAME];
    char outName[MAX_FILENAME];
    char line[MAX_LINE];
    int n, m, i;
    double ms = 0.0;
    Point tmp;

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
    fclose(fin);

    /* 5: run the Graham's scan (fast version) */
    if (n < 3) {
        /* too few points for a scan: the hull is just the point(s), anchor (lowest y, then lowest x) first */
        if (n == 2 && (points[1].y < points[0].y || (points[1].y == points[0].y && points[1].x < points[0].x))) {
            tmp = points[0];
            points[0] = points[1];
            points[1] = tmp;
        }
        hull[0] = points[0];
        m = 1;
        if (n == 2 && (points[1].x != points[0].x || points[1].y != points[0].y)) {
            hull[1] = points[1];
            m = 2;
        }
        fprintf(stderr, "Execution Time: 0.00 ms (n < 3, no scan needed)\n");
    } else {
        /* the scan function prints the hull and its elapsed time, so its printout is sent to a
           temporary file first, then read back here and rewritten in the required output format */
        fflush(stdout);
        if (freopen(TEMP_FILE, "w", stdout) == NULL) {
            fprintf(stderr, "Error: cannot create temporary file.\n");
            return 1;
        }
        run_graham_scan_fast(points, n);
        fclose(stdout);

        FILE *ftmp = fopen(TEMP_FILE, "r");
        if (ftmp == NULL) {
            fprintf(stderr, "Error: cannot read temporary file.\n");
            return 1;
        }
        m = 0;
        while (fgets(line, MAX_LINE, ftmp) != NULL) {
            if (line[0] == '(' && m < MAX_SIZE) {
                if (sscanf(line, "(%lf, %lf)", &hull[m].x, &hull[m].y) == 2)
                    m++;
            } else {
                sscanf(line, "Execution Time: %lf ms", &ms);
            }
        }
        fclose(ftmp);
        remove(TEMP_FILE);

        m = cleanHull(hull, m);
        fprintf(stderr, "Elapsed time (fast Graham's scan): %.2f ms\n", ms);
    }

    /* 6: write the hull (anchor first, counterclockwise) */
    FILE *fout = fopen(outName, "w");
    if (fout == NULL) {
        fprintf(stderr, "Error: cannot create output file '%s'.\n", outName);
        return 1;
    }
    fprintf(fout, "%d\n", m);
    for (i = 0; i < m; i++)
        fprintf(fout, "%.6f %.6f\n", hull[i].x, hull[i].y);

    /* 7: close the output file (the input file was closed after reading) */
    fclose(fout);

    fprintf(stderr, "Convex hull has %d point(s). Written to %s\n", m, outName);
    return 0;
}
