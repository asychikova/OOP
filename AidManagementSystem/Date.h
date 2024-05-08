/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Date
Filename: Date.h
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/10/23  Preliminary release
2023/11/02  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Status.h"

namespace sdds {

    class Date {
        int m_year;
        int m_month;
        int m_day ;
        Status m_state ;
        bool m_formatted;
        int uniqueDateValue() const ;

    public:
       void setYear(int year) {
    if (year >= 0 && year <= 99) {
        m_year = year + 2000;
    } else {
        m_year = year;
    }
}


    void setMonth(int month) {
        m_month = month;
    }

    void setDay(int day) {
        
        m_day = day;
    }

     int getYear() const {
        return m_year;
    }
     int getMonth() const {
        return m_month;
    }

     int getDay() const {
        return m_day;
    }

    
        Date() ;
        Date( int year, int month, int day);
        const Status& state() const ;
        bool validate() ; 
        void formatted(bool value);
        bool operator== ( const Date& D ) const;
        bool operator!=( const Date& D ) const ;
        bool operator< ( const Date& D ) const;
        bool operator> ( const Date& D ) const;
        bool operator<=( const Date& D ) const;
        bool operator>=( const Date& D ) const ;
        Date& operator=( const Date& D );
        std::istream& read(std::istream& is) ;
        std::ostream& write(std::ostream& os) const;
    };

    std::ostream& operator<<( std::ostream& os, const Date& D) ;
    std::istream& operator>>(std::istream& is, Date& D );

}

#endif 
