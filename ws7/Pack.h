/*
*****************************************************************************
                          OOP244 Workshop - #7 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.07
*****************************************************************************
*/

#ifndef SDDS_PACK_H
#define SDDS_PACK_H
#include "Container.h"

namespace sdds {

    class Pack : public Container {
        int m_unitSize;

    public:
        Pack(const char* content, int size, int unitSize = 330, int numberOfUnits =0 ) ;
        int operator+=(int units);
        int operator-=(int units);
        int unit() const;
        int noOfUnits() const ;
        int size() const ;
        void clear(int size, int unitSize, const char* content);
        std::ostream& print(std::ostream& os) const;
        std::istream& read(std::istream& is) ;
    };

    std::ostream& operator<<( std::ostream& os, const Pack& pack);
    std::istream& operator>>( std::istream& is, Pack& pack);
}

#endif 
