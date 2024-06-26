#ifndef LAB_STRING__H
#define LAB_STRING__H

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)

#include <stdint.h>


size_t strlen_(char *s);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char* findSpace(char *begin);

char* findNonSpaceReverse(char *rbegin, char *rend);

char* findSpaceReverse(char *rbegin, char *rend);

int strcmp_(const char *lhs, const char *rhs);

char* copy(const char *beginSource, const char *endSource, char *beginDestination);

int checkIfNotNum(int i);
char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));
char* copyIf2(char *beginSource, const char *endSource, char *beginDestination, int appendStringEnd, int (*f)(int));

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));


// -----------------------------   lab_18   -----------------------------


#define MAX_STRING_SIZE 200
#define MAX_N_WORDS_IN_STRING 200

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;


extern char _stringBuffer[MAX_STRING_SIZE + 1];

extern BagOfWords _bag;
extern BagOfWords _bag2;

char* getEndOfString(char *begin);
void removeNonLetters(char *s);

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line);

void removeAdjacentEqualLetters(char *s);

int getWord(char *beginSearch, WordDescriptor *word);
void digitToStart(WordDescriptor word);
void digitInWordShift(WordDescriptor word);
void wordInStringProcessor(char *beginString, void(*f)(WordDescriptor));

void digitInWordShift2(WordDescriptor word);
void digitToEnd(WordDescriptor word);

void convertNumToSpace(char *source);

int findWord(char *beginSearch, WordDescriptor *patternWord, WordDescriptor *resWord);
void replace(char *source, char *w1, char *w2);

int isOrdered(char *source);

void getBagOfWords(BagOfWords *bag, char *s);
void printBagOfWordsReverse(BagOfWords *bag);
void printWord(const WordDescriptor *word);
void clearBagOfWords(BagOfWords *bag);

int getCountPalindroms(char *s);

void getInterleavedString(char *res, char *s1, char *s2);

void getReversedString(char *s);

int hasWordLetter(WordDescriptor *word, char letter);
void printWordBeforeFirstWordWithA (char *s);
WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *source, WordDescriptor *w);

void findLastWord(char *s1, char *s2);

int getCountEqualWordsInString(char *s);

int hasWordsWithEqualLettersInString(char *s);

void getStringWithoutEndWord(char *s);

int getWordBeforeEqualWords(char *s1, char *s2, char *res);

void deletePalindromesInString(char *s);

void appendMissingWords(char *s1, char *s2);

int isStringIncludeLettersOfWord(char *s, char *word);


#endif