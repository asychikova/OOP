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


#ifndef SDDS_LBLSHAPE_H
#define SDDS_LBLSHAPE_H

#include "Shape.h"

namespace sdds {
    class LblShape : public Shape {
        char* m_label;
    protected:
        const char* label() const ;
    public:
        LblShape() ;
      LblShape(const char* label);
        ~LblShape() ;
        virtual void getSpecs( std::istream& in );
    };
} 

#endif 
