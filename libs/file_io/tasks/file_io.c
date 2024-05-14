#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"
#include <math.h>
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

size_t readFileBinaryToBuff(char *filePath, char *buff, size_t buffSize) {
    FILE *f = fopen(filePath, "rb");
    size_t size = fread(buff, sizeof(char), buffSize, f);
    fclose(f);

    return size;
}


void rowsToColumnsInMatrix(char *filePath) {
    FILE *fp = fopen(filePath, "r");

    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    int n, res;
    fscanf(fp, "%d", &n);

    matrix matrix = readMatrixFromStream(fp, n, &res);

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

matrix readMatrixFromStream(FILE *fp, int n, int *res) {
    matrix matrix = getMemMatrix(n, n);

    int x, count;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count = fscanf(fp, "%d", &x);

            if (count == 0) {
                *res = 0;
                return matrix;
            }
            matrix.values[i][j] = x;
        }
    }
    *res = 1;
    return matrix;
}

matrix readMatrixFromBinaryStream(FILE *fp, int n, int *res) {
    matrix matrix = getMemMatrix(n, n);

    int x, count;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count = fread(&x, sizeof(int), 1, fp);

            if (count == 0) {
                *res = 0;
                return matrix;
            }
            matrix.values[i][j] = x;
        }
    }
    *res = 1;
    return matrix;
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


int isPatternInWord(WordDescriptor word, const char *pattern) {
    int counter = 0;
    char *curPatternPtr = pattern;
    int len = strlen_(pattern);

    for (char *i = word.begin; i <= word.end; i += sizeof(char)) {
        if (*i == *curPatternPtr) {
            counter++;
            if (counter == len) {
                return 1;
            }
            curPatternPtr += sizeof(char);
        } else if (counter > 0) {
            counter = 0;
            curPatternPtr = pattern;
        }
    }

    return 0;
}

size_t saveFileWithRequiredLen(char *file_path_in, char *file_path_out, char *pattern) {
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
    BagOfWords words;

    while (fgets(_fileReadBuffer, sizeof(_fileReadBuffer), fp) != NULL) {
        clearBagOfWords(&words);

        getBagOfWords(&words, _fileReadBuffer);
        for (int i = 0; i < words.size; i++) {
            WordDescriptor currWord = words.words[i];
            if (isPatternInWord(currWord, pattern)) {
                if (counter > 0) {
                    fputc(' ', fd);
                }
                fwrite(currWord.begin, currWord.end - currWord.begin, 1, fd);
                counter++;
            }
        }
    }

    fclose(fp);
    fclose(fd);

    return counter;
}


int compareWordDescriptorsByLen(const void *wordPtr1, const void *wordPtr2) {
    WordDescriptor *word1 = (WordDescriptor *)wordPtr1;
    WordDescriptor *word2 = (WordDescriptor *)wordPtr2;

    unsigned long len1 = word1->end - word1->begin;
    unsigned long len2 = word2->end - word2->begin;

    return len2 - len1;
}

size_t saveFileWithLongestWord(char *file_path_in, char *file_path_out) {
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
    BagOfWords words;
    while (fgets(_fileReadBuffer, sizeof(_fileReadBuffer), fp) != NULL) {
        clearBagOfWords(&words);
        getBagOfWords(&words, _fileReadBuffer);
        qsort(words.words, words.size, sizeof(WordDescriptor), compareWordDescriptorsByLen);
        WordDescriptor currWord = words.words[0];
        if (counter > 0) {
            fputc(' ', fd);
        }
        fwrite(currWord.begin, currWord.end - currWord.begin, 1, fd);
        counter++;
    }
    fclose(fp);
    fclose(fd);
    return counter;
}


void removeZeroPolynomial(char *filePath, int x) {
    FILE *fp = fopen(filePath, "r+b");
    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    Polynomial pols[1000];

    int count = fread(&pols, sizeof(Polynomial), sizeof(pols) / sizeof(Polynomial), fp);
    int sum = 0;
    int startPolIdx = 0;
    for (int i = 0; i < count; i++) {
        Polynomial pol = pols[i];
        sum += pol.k * pow(x, pol.pow);

        if (pol.pow == 0) {
            if (sum == 0) {
                for (int j = startPolIdx; j <= i; j++) {
                    pols[j].k = 0;
                }
            }
            startPolIdx = i + 1;
            sum = 0;
        }
    }
    fclose(fp);

    FILE *fw = fopen(filePath, "wb");
    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        if (pols[i].k != 0) {
            fwrite(&pols[i], sizeof(Polynomial), 1, fw);
        }
    }
    fclose(fw);
}


int compareInts(const void *intPtr1, const void *intPtr2) {
    int *num1 = (int *)intPtr1;
    int *num2 = (int *)intPtr2;

    return *num2 - *num1;
}

void binFileSort(char *filePath) {
    FILE *fp = fopen(filePath, "r+b");

    if (fp == NULL) {
        fprintf(stderr, "file cannot be opened");
        exit(1);
    }

    int array[1000];
    int *ptr = array;

    int count = 0;
    while (fread(ptr, sizeof(int), 1, fp) > 0) {
        ptr++;
        count++;
    }

    qsort(array, count, sizeof(int), compareInts);

    fseek(fp, 0, SEEK_SET);
    ptr = array;
    for (int i = 0; i < count; i++) {
        fwrite(ptr++, sizeof(int), 1, fp);
    }
    fclose(fp);
}
