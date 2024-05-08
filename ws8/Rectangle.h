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


#ifndef SDDS_RECTANGLE_H
#define SDDS_RECTANGLE_H

#include "LblShape.h"

namespace sdds {
    class Rectangle : public LblShape {
        int m_width;
        int m_height ;
    public:
       Rectangle();
        Rectangle( const char* label, int width, int height );
        virtual ~Rectangle() ;
       virtual void getSpecs(std::istream& in );
        virtual void draw(std::ostream& out) const ;
    };
} 

#endif 
