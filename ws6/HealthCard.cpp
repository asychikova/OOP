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

#include <iostream>
#include <cstring>
#include <iomanip>
#include "HealthCard.h"

namespace sdds {

    HealthCard::HealthCard() : m_name( nullptr), m_number(0) {
        m_vCode[0] = '\0' ;
        m_sNumber[0] = '\0' ;
    }

    HealthCard::HealthCard( const char* name, long long number, const char vCode[], const char sNumber[]) : m_name(nullptr), m_number(0) {
        if (validID(name, number, vCode, sNumber )) {
            allocateAndCopy(name );
            m_number =number;
            strncpy( m_vCode, vCode, 3);
            m_vCode[2] = '\0';
            strncpy( m_sNumber, sNumber, 10);
            m_sNumber[9] = '\0' ;
        } else {
            setEmpty() ;
        }
    }

    HealthCard::HealthCard( const HealthCard& hc) : m_name(nullptr), m_number(0) {
        *this = hc ; 
    }

    HealthCard& HealthCard::operator=( const HealthCard& hc) {
        if (this != &hc ) {
            setEmpty();
            if (hc.m_name != nullptr ) {
                allocateAndCopy(hc.m_name );
                m_number= hc.m_number;
                strncpy( m_vCode, hc.m_vCode, 3);
                m_vCode[2] = '\0' ;
                strncpy( m_sNumber, hc.m_sNumber, 10);
                m_sNumber[9] = '\0' ;
            }
        }
        return *this;
    }

    HealthCard::~HealthCard() {
        delete[] m_name;
    }

    bool HealthCard::validID( const char* name, long long number, const char vCode[], const char sNumber[]) const {
        if (name == nullptr || strlen(name)> MaxNameLength) {
            return false ;
        }

        if (number < 1000000000 || number > 9999999999 ) {
            return false;
        }

        if (strlen( vCode) != 2) {
            return false ;
        }

        if ( strlen(sNumber ) != 9 ) {
            return false;
        }

        return true ; 
    }

    HealthCard::operator bool() const{
        return ( m_name != nullptr);
    }

/*
    std::ostream& HealthCard::printIDInfo(std::ostream& ostr) const { 
        ostr << std::setw(MaxNameLength) << std::left << m_name << std::setw(0) << std::right << std::setfill('.') << m_number << "-" << m_vCode << ", " << m_sNumber;
        return ostr;
    }
*/

    std::ostream& HealthCard::printIDInfo(std::ostream& ostr ) const {
        if (m_name ) {
            int nameLength = strlen( m_name);
            int dotsCount = MaxNameLength - nameLength ;
            ostr <<std::setw( nameLength) << std::left<< m_name;
            for (int i = 0; i < dotsCount -5; ++i ) {
                ostr << '.' ;
            }
        } 
        ostr << std::setw(0)<<std::right << m_number<< "-" <<m_vCode<< ", " <<m_sNumber;
        return ostr;
    }

    std::ostream& HealthCard::printIDInfoFile( std::ostream& ostr) const {
        ostr << m_name<< ","<< m_number << "-"<<m_vCode << ", "<< m_sNumber;
        return ostr;
    }

    void HealthCard::setEmpty() {
        delete[] m_name ;
        m_name = nullptr ;
        m_number= 0 ;
        m_vCode[0] = '\0';
        m_sNumber[0] = '\0';
    }

    void HealthCard::allocateAndCopy( const char* name) {
        m_name = new char[ strlen(name) + 1];
        strcpy( m_name, name) ;
    }

    std::istream& HealthCard::extractChar(std::istream& istr, char ch ) const {
        char next;
        istr >> std::ws;
        next = istr.peek() ;
        if ( next == ch) {
            istr.ignore() ;
        } else {
            istr.ignore( 1000, ch);
            istr.setstate(std::ios::failbit);
        }
        return istr ;
    }

    std::ostream& HealthCard::print(std::ostream& ostr, bool toFile) const {
            if ( toFile) {
                if (*this) {
                // ostr << m_name << ",";
                    printIDInfoFile(ostr)<< std::endl;
                } 
            } else {
                if (*this ) {
                    printIDInfo(ostr);
                } else {
                    ostr << "Invalid Health Card Record" ;
                }
            }
        //  ostr << std::endl;
            return ostr;
        }

    std::istream& HealthCard::read(std::istream& istr ) {
        char name[MaxNameLength + 1] ;

        istr.get( name, MaxNameLength, ',') ;
        extractChar(istr, ',');
        istr >> m_number;
        extractChar(istr, '-') ;
        istr.get( m_vCode, 3, ',');
        extractChar( istr, ',');
        istr.get(m_sNumber, 10 );

        if ( !validID(name, m_number, m_vCode, m_sNumber)) {
            setEmpty();
            istr.clear() ;
            istr.ignore(1000, '\n');
        } else {
            delete[] m_name ;
            allocateAndCopy(name);
            istr.ignore(1000, '\n' );
        }

        return istr;
    }

    std::ostream& operator<<( std::ostream& ostr, const HealthCard& hc) {
        return hc.print( ostr, false);
    }

    std::istream& operator>>( std::istream& istr, HealthCard& hc) {
        return hc.read(istr ) ;
    }

}
