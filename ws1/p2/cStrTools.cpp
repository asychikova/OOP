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


#include <cstdio>
#include "cStrTools.h"


namespace sdds {

// returns the lower case value of a character
char toLower(char ch) {
   if (ch >= 'A' && ch <= 'Z') ch += ('a' - 'A');
   return ch;
}

// compares s1 and s2 cStrings upto len characters and returns:
// > 0 if s1 > s2
// < 0 if s1 < s3
// == 0 if s1 == s2
int strnCmp(const char* s1, const char* s2, int len) {
   int i = 0;
   while (i < len - 1 && s1[i] && s2[i] && s1[i] == s2[i]) {
      i++;
   }
   return s1[i] - s2[i];
}

// copies src to des
void strCpy(char* des, const char* src) {
   int i;
   for (i = 0; src[i]; i++) des[i] = src[i];
   des[i] = 0;
}

// returns the length of str
int strLen(const char* str) {
   int len;
   for (len = 0; str[len]; len++);
   return len;
}

// copies the  lower case version of the source into des
void toLowerCaseAndCopy(char des[], const char source[]) {
   int i = 0, j = 0;
   for (; source[i] != 0; i++) {
      des[j++] = toLower(source[i]);
   }
   des[j] = 0;
}

// if "find" is found in "str" it will return the addres of the match
// if not found it will returns nullptr (zero)
const char* strStr(const char* str, const char* find) {
   const char* faddress = NULL;
   int i, flen = strLen(find), slen = strLen(str);
   for (i = 0; i <= slen - flen && strnCmp(&str[i], find, flen); i++);
   if (i <= slen - flen) faddress = &str[i];
   return faddress;
}

}
