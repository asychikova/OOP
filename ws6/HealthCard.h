/*
*****************************************************************************
                          OOP244 Workshop - #5 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.01
*****************************************************************************
*/

#ifndef SDDS_HEALTHCARD_H
#define SDDS_HEALTHCARD_H

#include <iostream>

namespace sdds {

    const int MaxNameLength = 55;

    class HealthCard {
        char* m_name{};
        long long m_number;
        char m_vCode[3];
        char m_sNumber[10];

        bool validID(const char* name, long long number, const char vCode[], const char sNumber[] ) const ;
        void setEmpty() ;
        void allocateAndCopy( const char* name) ;
        std::istream& extractChar(std::istream& istr, char ch ) const;

    public:
        HealthCard();
        HealthCard(const char* name, long long number, const char vCode[], const char sNumber[] );
        HealthCard(const HealthCard& hc) ;
        HealthCard& operator=(const HealthCard& hc );
        ~HealthCard() ;

        operator bool() const ;
        std::ostream& printIDInfo( std::ostream& ostr) const ;
        std::ostream& printIDInfoFile( std::ostream& ostr) const;
        std::ostream& print(std::ostream& ostr, bool toFile = true ) const;
        std::istream& read(std::istream& istr) ;
    };

    std::ostream& operator<<( std::ostream& ostr, const HealthCard& hc);
    std::istream& operator>>( std::istream& istr, HealthCard& hc);

}

#endif 
