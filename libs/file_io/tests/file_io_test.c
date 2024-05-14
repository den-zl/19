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


void testAll_saveFileWithMathematicalExpression() {
    FILE *fp = fopen ("file_test1.txt", "w+");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fprintf(fp, "2 + %d\n", i, i);
        } else if (i % 3 == 0) {
            fprintf(fp, "9 - %d * %d\n", i, i);
        } else {
            fprintf(fp, "%d + %d / 5\n", i, i);
        }
    }
    fclose(fp);
    size_t res = saveFileWithMathematicalExpression("file_test1.txt", "file_test1.txt");
    size_t fileSize = readFileToBuff("file_test1.txt", testBuff, sizeof(testBuff));
    assert(res == 10);
    assert(fileSize == 103);
    ASSERT_STRING("2 + 0\n"
                  "1 + 1 / 5\n"
                  "2 + 2\n"
                  "9 - 3 * 3\n"
                  "2 + 4\n"
                  "5 + 5 / 5\n"
                  "2 + 6\n"
                  "7 + 7 / 5\n"
                  "2 + 8\n"
                  "9 - 9 * 9\n"
                  "2\n"
                  "1\n"
                  "4\n"
                  "0\n"
                  "6\n"
                  "6\n"
                  "8\n"
                  "8\n"
                  "10\n"
                  "-72\n", testBuff);
}


void testAll_saveFileWithRequiredLen() {
    FILE *fp = fopen ("file_test1.txt", "w+");
    char word[4] = "bot";
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fputs("bot vdg uy\n", fp);
        } else if (i % 3 == 0) {
            fputs("rama ho isz\n", fp);
        } else {
            fputs("1z i7 bj\n", fp);
        }
    }
    fclose(fp);
    size_t res = saveFileWithRequiredLen("file_test1.txt", "file_test2.txt", word);
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 5);
    assert(fileSize == 19);
    ASSERT_STRING("bot bot bot bot bot", testBuff);
}

void testAll_saveFileWithLongestWord() {
    FILE *fp = fopen ("file_test1.txt", "w+");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            fputs("hasfa hg jui\n", fp);
        } else if (i % 3 == 0) {
            fputs("bhy gamma po\n", fp);
        } else {
            fputs("dd ll rock\n", fp);
        }
    }
    fclose(fp);
    size_t res = saveFileWithLongestWord("file_test1.txt", "file_test2.txt");
    size_t fileSize = readFileToBuff("file_test2.txt", testBuff, sizeof(testBuff));
    assert(res == 10);
    assert(fileSize == 56);
    ASSERT_STRING("hasfa rock hasfa gamma hasfa rock hasfa rock hasfa gamma", testBuff);
}


void testAll_removeZeroPolynomial() {
    FILE *fp = fopen("binary_file_test1.bin", "wb");

    int x = 4;
    Polynomial poly[] = {{3,  1},
                         {2,  1},
                         {1,  1},
                         {0,  1},
                         {5,  1},
                         {4,  2},
                         {1,  1},
                         {0,  2},
                         {7,  1},
                         {5,  1},
                         {3,  1},
                         {0,  1},
                         {19, 1},
                         {5,  1},
                         {8,  1},
                         {0,  1}};

    fwrite(poly, sizeof(Polynomial), sizeof(poly) / sizeof(Polynomial), fp);
    fclose(fp);

    removeZeroPolynomial("binary_file_test1.bin", -2);

    FILE *fd = fopen("binary_file_test1.bin", "rb");

    Polynomial res[100];

    int countRead = fread(res, sizeof(Polynomial), sizeof(res) / sizeof(Polynomial), fd);

    Polynomial expected[] = { {3, 1},{2, 1},{1, 1},{0, 1},
                              {7, 1},{5, 1},{3, 1},{0, 1},
                              {19, 1},{5, 1},{8, 1},{0, 1}};

    assert((sizeof(expected) / sizeof(Polynomial)) == countRead);
    for (int i = 0; i < countRead; i++) {
        assert(expected[i].k == res[i].k);
        assert(expected[i].pow == res[i].pow);
    }
    fclose(fd);
}


void testFileAll() {
    testAll_rowsToColumnsInMatrix();
    testAll_exponentialNumToNum();
    testAll_saveFileWithMathematicalExpression();
    testAll_saveFileWithRequiredLen();
    testAll_saveFileWithLongestWord();
    testAll_removeZeroPolynomial();

}