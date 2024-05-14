#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "/Users/denzl/CLionProjects/2sem/19.18/lab_18/libs/string/tasks/string_.h"
#include "string_test.h"


// -----------------------------   lab_17   -----------------------------


size_t test_strlen_() {
    char *s = "HelloSV";

    size_t res = strlen_(s);
    assert(res == 7);
}

char* test_find() {
    char *s = "HelloSV";

    char *res = find(&s[0], &s[3], 'e');
    assert(*res == 'e');
}

char* test_findNonSpace() {
    char *s = "   SV  ";

    char *res = findNonSpace(s);
    assert(*res == 'S');
}

char* test_findSpace() {
    char *s = "Hello SV";

    char *res = findSpace(s);
    assert(*res == ' ');
}

char* test_findNonSpaceReverse() {
    char *s = "Hello Hello ";

    char *res = findNonSpaceReverse(s + sizeof(char) * 11, s);
    assert(*res == 'H');
}

char* test_findSpaceReverse() {
    char *s = "CH SV";

    char *res = findSpaceReverse(s + sizeof(char) * 5, s);
    assert(*res == ' ');
}

int test_strcmp_() {
    char *lhs1 = "ABCD";
    char *rhs1 = "EFGH";

    int res1 = strcmp_(lhs1, rhs1);
    assert(res1 < 0);


    char *lhs2 = "HEllO";
    char *rhs2 = "HEllO";

    int res2 = strcmp_(lhs2, rhs2);
    assert(res2 == 0);


    char *lhs3 = "OPRST";
    char *rhs3 = "IKLMN";

    int res3 = strcmp_(lhs3, rhs3);
    assert(res3 > 0);
}

char* test_copy() {
    char *s = "12345333333333333333";
    char sd[20] = {0, 1, 9, 1, 3, 4, 5, 6, 7, 1, 0};

    char *res = copy(s, s + sizeof(char) * 4, sd);
    assert(*res == 4);
}

char* test_copyIf() {
    char *s = "123456";
    char sd[20] = {1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,};

    char *res = copyIf(s, s + sizeof(char) * 5, sd, &checkIfNotNum);
    assert(res[0] == 0 && res[1] == 1);
}

char* test_copyIfReverse() {
    char *s = "123456";
    char sd[20] = {1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,};

    char *res = copyIfReverse(s + sizeof(char) * 5, s, sd, &checkIfNotNum);
    assert(res[0] == 0 && res[1] == 1);
}


void test() {
    test_strlen_();
    test_find();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp_();
    test_copy();
    test_copyIf();
    test_copyIfReverse();
}


// -----------------------------   lab_18   -----------------------------


void testAll_removeNonLetters() {
    char s1[] = "abc dtr yu\0";
    removeNonLetters(s1);
    ASSERT_STRING("abcdtryu", s1);
}

void testAll_removeAdjacentEqualLetters() {
    char s1[] = "abcc aaabbbtr yuu\0";
    removeAdjacentEqualLetters(s1);
    ASSERT_STRING("abc abtr yu", s1);
}

void testAll_convertNumToSpace() {
    char s1[] = "a1rt3b\0";
    convertNumToSpace(s1);
    ASSERT_STRING("a rt   b", s1);
}

void testAll_replace() {
    char s[MAX_STRING_SIZE] = "butterfly three butterfly\0";
    char s1[] = "butterfly\0";
    char s2[] = "dog\0";
    replace(s, s1, s2);
    ASSERT_STRING("dog three dog", s);
}

void testAll_isOrdered() {
    char s1[] = "abc defg hx\0";
    int res = isOrdered(s1);
    assert(res == 1);
}

void testAll_getCountPalindroms() {
    char s1[] = "aba,asdf,zxxz,huji,abcdcba\0";
    int res = getCountPalindroms(s1);
    assert(res == 3);
}

void testAll_getInterleavedString() {
    char s[MAX_STRING_SIZE] = "";
    char s1[] = "aga1 buga3 duga5 kol6 ola7\0";
    char s2[] = "rug2 tot4\0";
    getInterleavedString(s, s1, s2);
    ASSERT_STRING("aga1 rug2 buga3 tot4 duga5 kol6 ola7", s);
}

void testAll_getReversedString() {
    char s1[] = "dog tot three\0";
    getReversedString(s1);
    ASSERT_STRING("three tot dog", s1);
}

void testAll_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(
            getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING
    );
    char s2[] = "ABC";
    assert(
            getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A
    );
    char s3[] = "BC A";
    assert(
            getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND
    );
    char got[MAX_STRING_SIZE];
    copy(word.begin, word.end, got);
    got[word.end - word.begin] = '\0';
    ASSERT_STRING("BC", got);
    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void testAll_getCountEqualWordsInString() {
    char s1[] = "ada tot three ada hox\0";
    int res = getCountEqualWordsInString(s1);
    assert(res == 1);
}

void testAll_hasWordsWithEqualLettersInString() {
    char s1[] = "anton bot bkf len anton\0";
    int res = hasWordsWithEqualLettersInString(s1);
    assert(res == 1);
}

void testAll_getStringWithoutEndWord() {
    char s1[] = "anton bot bkf len anton\0";
    getStringWithoutEndWord(s1);
    ASSERT_STRING("bot bkf len", s1);
}

void testAll_getWordBeforeEqualWords() {
    char s1[MAX_STRING_SIZE] = "bot anton len size\0";
    char s2[MAX_STRING_SIZE] = "word get anton dot\0";
    char res[MAX_STRING_SIZE];
    int found = getWordBeforeEqualWords(s1, s2, res);
    assert(found == 1);
}

void testAll_deletePalindromesInString() {
    char s1[] = "ava bot bkf len acdca\0";
    deletePalindromesInString(s1);
    ASSERT_STRING("bot bkf len", s1);
}

void testAll_appendMissingWords() {
    char s1[MAX_STRING_SIZE] = "anton bot\0";
    char s2[MAX_STRING_SIZE] = "get size let dot got\0";
    appendMissingWords(s1, s2);
    ASSERT_STRING("anton bot let dot got", s1);
}

void testAll_isStringIncludeLettersOfWord() {
    char s1[MAX_STRING_SIZE] = "anton bot z\0";
    char s2[MAX_STRING_SIZE] = "otaz\0";
    int found = isStringIncludeLettersOfWord(s1, s2);
    assert(found == 1);
}

void testAll() {
    testAll_removeNonLetters();
    testAll_removeAdjacentEqualLetters();
    testAll_convertNumToSpace();
    testAll_replace();
    testAll_isOrdered();
    testAll_getCountPalindroms();
    testAll_getInterleavedString();
    testAll_getReversedString();
    testAll_getWordBeforeFirstWordWithA();
    testAll_getCountEqualWordsInString();
    testAll_hasWordsWithEqualLettersInString();
    testAll_getStringWithoutEndWord();
    testAll_getWordBeforeEqualWords();
    testAll_deletePalindromesInString();
    testAll_appendMissingWords();
    testAll_isStringIncludeLettersOfWord();
}