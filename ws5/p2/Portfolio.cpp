/***********************************************************************
// OOP244 Workshop #5 DIY (part 2): tester program
//
// File  Portfolio.cpp
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


#include "Portfolio.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace sdds {

    Portfolio::Portfolio() {
        emptyPortfolio();
    }

    void Portfolio::emptyPortfolio() {
        m_value = 0;
        m_stock[0] = '\0';
        m_type = 'E';
    }

    Portfolio::Portfolio(double value, const char* stock, char type) {
        emptyPortfolio();
        if (value >= 0 && (type == 'V' || type == 'G' || type == 'I')) {
            m_value = value;
            m_type = type;
            strncpy(m_stock, stock, sizeof( m_stock) - 1) ;
           
        }
    }

    Portfolio::operator double() const{
        return m_value ;
    }

    Portfolio::operator const char*() const {
        return m_stock;
    }

    Portfolio::operator char() const{
        return m_type ;
    }

       Portfolio:: operator bool() const {
            return (m_value >= 0 && (m_type =='G' || m_type == 'V' || m_type== 'I'));
        }

    bool Portfolio::operator~() const {
        return (m_value < 0 );
    }

    Portfolio& Portfolio::operator+=(double value) {
        if ( *this && value >= 0 ) {
            m_value += value ;
        }
        return *this;
    }

    Portfolio& Portfolio::operator-=(double value) {
        if ( *this && value >= 0) {
            m_value -= value ;
        }
        return *this;
    }

    double operator+(const Portfolio& left, const Portfolio& right) {
        return static_cast<double>( left) + static_cast<double>( right ) ;
    }

    double& operator+=(double& value, const Portfolio& portfolio) {
        value += static_cast<double>( portfolio);
        return value ;
    }


Portfolio& Portfolio::operator>>(Portfolio& otherportf) {
    if (this != &otherportf ) {
        otherportf += static_cast<double>( *this);
        this->emptyPortfolio();
    }
    return otherportf;
}

Portfolio& Portfolio::operator<<( Portfolio& otherportf) {
    if (this != &otherportf ) {
        *this += static_cast<double>( otherportf);
        otherportf.emptyPortfolio();
    }
    return *this;
}

    void Portfolio::dispPortfolio() const {
        cout << " ";
        cout.width(10);
        cout << (const char*)(*this);
        cout << " | ";
        cout << "Value: ";
        cout.width(10);
        cout << double(*this);
        cout << " | ";
        cout << " Type: ";
        cout << char(*this);
    }

    ostream& Portfolio::display() const {
        if (~*this) {
            cout << " Portfolio  |  Bad-NG |";
            dispPortfolio();
        }
        else if (*this) {
            cout << " Portfolio  |  Active |";
            dispPortfolio();
        }
        else {
            cout << " Portfolio  |  EMPTY  |";
            dispPortfolio();
        }
        return cout;
    }
} 