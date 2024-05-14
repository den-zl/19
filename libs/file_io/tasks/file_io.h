#ifndef LAB_FILE_IO_H
#define LAB_FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024
extern char _fileReadBuffer[MAX_LINE_SIZE];


size_t readFileToBuff(char *filePath, char *buff, size_t buffSize);

void rowsToColumnsInMatrix(char *filePath);


#endif