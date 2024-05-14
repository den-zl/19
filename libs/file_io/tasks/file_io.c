#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/data_structures/matrix/matrix.h"
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/string/tasks/string_.h"


char _fileReadBuffer[MAX_LINE_SIZE];
size_t readFileToBuff(char *filePath, char *buff, size_t buffSize) {
    FILE *f = fopen(filePath, "r");
    size_t size = fread(buff, sizeof(char), buffSize, f);
    fclose(f);
    buff[size] = '\0';
    return size;
}

void rowsToColumnsInMatrix(char *filePath) {
    FILE *fp = fopen(filePath, "r");

    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    int n;
    int x;
    fscanf(fp, "%d", &n);

    matrix matrix = getMemMatrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &x);
            matrix.values[i][j] = x;
        }
    }

    fclose(fp);

    FILE *fw = fopen(filePath, "w+");

    if (fw == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    fprintf(fp, "%d\n", n);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            fprintf(fw, "%d ", matrix.values[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fw);
    freeMemMatrix(&matrix);
}
