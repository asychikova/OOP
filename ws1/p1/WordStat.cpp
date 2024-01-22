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


#include <iostream>
#include "Word.h"
using namespace sdds;
using namespace std;

int main() {
   char filename[256];
   programTitle();
   cout << "Enter filename: ";
   cin >> filename;
   wordStats(filename);
   return 0;
}