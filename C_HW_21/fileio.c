#include <stdio.h>
#include <string.h>
#include "fileio.h"

int save_to_file(const char* filename, Album arr[], int n) {
    FILE* f = fopen(filename, "w");
    if (!f) return -1;

    fprintf(f, "%d\n", n);

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n", arr[i].title);
        fprintf(f, "%d\n", arr[i].year);
        fprintf(f, "%s\n", arr[i].style);
        fprintf(f, "%d\n", arr[i].tracks);
        fprintf(f, "%.2f\n", arr[i].duration);
    }

    fclose(f);
    return 0;
}

int load_from_file(const char* filename, Album arr[], int* n) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    fscanf(f, "%d\n", n);

    for (int i = 0; i < *n; i++) {
        fgets(arr[i].title, 100, f);
        arr[i].title[strcspn(arr[i].title, "\n")] = '\0';

        fscanf(f, "%d\n", &arr[i].year);

        fgets(arr[i].style, 50, f);
        arr[i].style[strcspn(arr[i].style, "\n")] = '\0';

        fscanf(f, "%d\n", &arr[i].tracks);
        fscanf(f, "%lf\n", &arr[i].duration);
    }

    fclose(f);
    return 0;
}