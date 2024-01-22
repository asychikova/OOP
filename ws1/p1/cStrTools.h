/*
*****************************************************************************
                          OOP244 Workshop - #1 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.09.10
*****************************************************************************
*/


#ifndef NAMESPACE_CSTRTOOLS_H
#define NAMESPACE_CSTRTOOLS_H

namespace sdds {

char toLower(char ch);
int strCmp(const char* s1, const char* s2);
int strnCmp(const char* s1, const char* s2, int len);
void strCpy(char* des, const char* src);
int strLen(const char* str);
const char* strStr(const char* str, const char* find);
int isAlpha(char ch);
int isSpace(char ch);
void trim(char word[]);
void toLowerCaseAndCopy(char des[], const char source[]);

}

#endif