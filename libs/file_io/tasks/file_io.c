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


size_t exponentialNumToNum(char *file_path_in, char *file_path_out) {
    FILE *fp = fopen(file_path_in, "r");
    FILE *fd = fopen(file_path_out, "w+");
    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }
    if (fd == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }
    size_t counter = 0;
    float val;
    while (fscanf(fp, "%e", &val) > 0) {
        fprintf(fd, "%.2f\n", val);
    }
    fclose(fp);
    fclose(fd);
    return counter;
}


int processOperation(int d1, int d2, char op) {
    switch (op) {
        case '+' :
            return d1 + d2;
            break;
        case '-' :
            return d1 - d2;
            break;
        case '/' :
            return d1 / d2;
            break;
        case '*' :
            return d1 * d2;
            break;
    }
    return 0;
}

size_t saveFileWithMathematicalExpression(char *file_path_in, char *file_path_out) {
    FILE *fp = fopen(file_path_in, "r");
    FILE *fd = fopen(file_path_out, "a+");

    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    if (fd == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    int countRes = 0;
    int d1, d2, d3;
    char op1, op2;
    int res;
    BagOfWords words;

    while (fgets(_fileReadBuffer, sizeof(_fileReadBuffer), fp) != NULL) {
        clearBagOfWords(&words);
        getBagOfWords(&words, _fileReadBuffer);

        if (words.size == 3) {
            d1 = *words.words[0].begin - '0';
            d2 = *words.words[2].begin - '0';
            op1 = *words.words[1].begin;
            res = processOperation(d1, d2, op1);

        } else if (words.size == 5) {
            d1 = *words.words[0].begin - '0';
            d2 = *words.words[2].begin - '0';
            d3 = *words.words[4].begin - '0';
            op1 = *words.words[1].begin;
            op2 = *words.words[3].begin;

            if (op1 == '*' || op1 == '/') {
                res = processOperation(d1, d2, op1);
                res = processOperation(res, d3, op2);

            } else {
                res = processOperation(d2, d3, op2);
                res = processOperation(d1, res, op1);
            }
        }

        countRes++;
        fprintf(fd,"%d\n", res);

    }

    fclose(fp);
    fclose(fd);

    return countRes;
}
