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


#include "Shape.h"

namespace sdds {
    Shape::~Shape() {
    }

    std::ostream& operator<<( std::ostream& os, const Shape& shape ) {
        shape.draw(os);
        return os;
    }
    std::istream& operator>>( std::istream& is, Shape& shape) {
        shape.getSpecs(is);
        return is;
    }
} 
