#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/file_io/tasks/file_io.h"
#include "file_io_test.h"
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/string/tests/string_test.h"
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/string/tasks/string_.h"

char testBuff[MAX_LINE_SIZE];

void testAll_rowsToColumnsInMatrix() {
    FILE *fp = fopen ("file_test1.txt", "w+");

    fprintf(fp, "%d\n", 5);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            fprintf(fp, "%d%d ", i, j);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    rowsToColumnsInMatrix("file_test1.txt");
    size_t fileSize = readFileToBuff("file_test1.txt", testBuff, sizeof(testBuff));
    assert(fileSize == 82);

    ASSERT_STRING("5\n"
                  "11 21 31 41 51 \n"
                  "12 22 32 42 52 \n"
                  "13 23 33 43 53 \n"
                  "14 24 34 44 54 \n"
                  "15 25 35 45 55 \n", testBuff);
}

void testAll_exponentialNumToNum() {
    FILE *fp = fopen ("file_test1.txt", "w+");
    for (int i = 0; i < 10; i++) {
        fprintf(fp, "0.%d7686878468e+%d\n", i, i);
    }
    fclose(fp);
    size_t res = exponentialNumToNum("file_test1.txt", "file_test2.txt");
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 0);
    assert(fileSize == 86);
    ASSERT_STRING("0.08\n"
                  "1.77\n"
                  "27.69\n"
                  "376.87\n"
                  "4768.69\n"
                  "57686.88\n"
                  "676868.81\n"
                  "7768688.00\n"
                  "87686880.00\n"
                  "976868800.00\n", testBuff);
}

void testFileAll() {
    testAll_rowsToColumnsInMatrix();
    testAll_exponentialNumToNum();

}