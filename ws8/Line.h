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


#ifndef SDDS_LINE_H
#define SDDS_LINE_H

#include "LblShape.h"

namespace sdds {
    class Line : public LblShape {
        int m_length ;
    public:
       Line() ;
        Line(const char* label, int length);
       virtual ~Line() ;
        virtual void getSpecs( std::istream& in );
        virtual void draw(std::ostream& out ) const;
    };
} 

#endif 
