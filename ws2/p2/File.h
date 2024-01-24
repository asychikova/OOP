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


#ifndef SDDS_FILE_H_
#define SDDS_FILE_H_

#include <cstdio>

namespace sdds {

    bool read(FILE* fptr, char* postalCode);
    bool read(FILE* fptr, int& population);

} 

#endif 
