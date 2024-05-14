#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/file_io/tasks/file_io.h"
#include "file_io_test.h"
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/string/tests/string_test.h"
#include "/Users/denzl/CLionProjects/2sem/19.19/lab_19/libs/string/tasks/string_.h"

char testBuff[MAX_LINE_SIZE];

FILE testAll_rowsToColumnsInMatrix() {
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


void testFileAll() {
    testAll_rowsToColumnsInMatrix();

}