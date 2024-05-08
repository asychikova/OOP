/*
*****************************************************************************
                          OOP244 Workshop - #8 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.14
*****************************************************************************
*/


#include <cstring>
#include "LblShape.h"

namespace sdds {
    LblShape::LblShape() : m_label(nullptr) {
    }

    LblShape::LblShape(const char* label) : m_label(nullptr) {
        m_label =new char[ strlen(label) + 1 ] ;
        strcpy(m_label, label );
    }

    LblShape::~LblShape() {
        delete[] m_label;
    }

    const char* LblShape::label() const {
        return m_label;
    }

    void LblShape::getSpecs(std::istream& in) {
        char temp[1000];
        in.getline(temp, 1000, ',') ;
        delete[] m_label ;
        m_label= new char[strlen(temp) + 1];
        strcpy(m_label,temp);
    }
} 
