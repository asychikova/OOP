/*
*****************************************************************************
                          OOP244 Workshop - #1 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.09.12
*****************************************************************************
*/

#ifndef CSTRTOOLS_H
#define CSTRTOOLS_H

namespace sdds {

char toLower(char ch);
int strnCmp(const char* s1, const char* s2, int len);
void strCpy(char* des, const char* src);
int strLen(const char* str) ;
void toLowerCaseAndCopy(char des[], const char source[]);
const char* strStr(const char* str, const char* find);

} 
#endif 

