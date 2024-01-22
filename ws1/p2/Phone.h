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

#ifndef PHONE_H
#define PHONE_H

namespace sdds {

    const int maxRecords = 50;

    struct PhoneRecord {
        char name[51];
        char areaCode[4];
        char prefix[4];
        char number[5];
    };

void phoneDir(const char* programTitle, const char* fileName);

    
}
#endif 
