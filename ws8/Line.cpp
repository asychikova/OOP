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


#include "Line.h"

namespace sdds {
    Line::Line() : m_length(0) {
    }

    Line::Line( const char* label, int length) : LblShape(label),m_length(length) {
    }

    Line::~Line() {
    }

    void Line::getSpecs(std::istream& in) {
        LblShape::getSpecs(in) ;
        in >>m_length;
        in.ignore(1000, '\n')  ;
    }

    void Line::draw(std::ostream& out) const {
        if (m_length >0 && label() !=nullptr) {
            out<<label() <<std::endl;
            for (int i = 0; i< m_length; ++i) {
                out << "=" ;
            }
          
        }
    }
} 
