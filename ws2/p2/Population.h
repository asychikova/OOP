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

#ifndef SDDS_POPULATION_H_
#define SDDS_POPULATION_H_

namespace sdds {
    struct Population {
        char* m_code;
        int population ;
    };

void sort();
bool getPostalCode( char* partial_postal_code_prefix);
//bool load(const char* filename) ;
bool load(const char* filename, const char* partial_postal_code_prefix);
void display();
//void display(const char* postal_code);
void deallocateMemory();
//ool startsWith(const char* cstring, const char* subString);

}

#endif 