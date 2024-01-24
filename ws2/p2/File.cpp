/*
*****************************************************************************
                          OOP244 Workshop - #2 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.09.22
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS
#include "File.h"

namespace sdds {

    bool read(FILE* fptr, char* postalCode ) {
        if (fscanf( fptr, "%3s,", postalCode) == 1 ) {
            return true;
        }
        return false;
    }

    bool read(FILE* fptr, int& population ) {
        if ( fscanf(fptr, "%d,", &population) == 1) {
            return true;
        }
        return false ;
    }

} 

