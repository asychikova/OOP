/***********************************************************************
// OOP244 Workshop #5 DIY (part 2): tester program
//
// File  Portfolio.h
// Version 1.0
// Author   Asam Gulaid, revised by Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
/*
*****************************************************************************
                          OOP244 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.10.15
*****************************************************************************
*/

#ifndef SDDS_Portfolio_H_
#define SDDS_Portfolio_H_

#include <iostream>

namespace sdds {

    class Portfolio {
        double m_value = 0;
        char m_stock[16] ;
        char m_type;
        void emptyPortfolio();

    public:
        Portfolio();
        Portfolio(double value, const char* stock, char type);
        std::ostream& display() const;
        void dispPortfolio() const;

        operator double() const ;
        operator const char*() const ;
        operator char() const;
        operator bool() const ;
        bool operator~() const;

        Portfolio& operator+=(double value);
        Portfolio& operator-=(double value);

        friend double operator+(const Portfolio& left, const Portfolio& right);
        friend double& operator+=(double& value, const Portfolio& portfolio);

        Portfolio& operator>>(Portfolio& otherportf);
        Portfolio& operator<<(Portfolio& otherportf);
 
    };
}

#endif // SDDS_Portfolio_H_
