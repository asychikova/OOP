/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Date
Filename: Date.cpp
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/10/23  Preliminary release
2023/11/02  Debugged DMA
-----------------------------------------------------------
In function "read" in order to effectively convert the string representing date into integer value, 
I used "dateValue = dateValue * 10 + (input[i] - '0');" (line 136).
This method of converting without using stoi I found at 
https://stackoverflow.com/questions/19311641/c-string-to-int-without-using-atoi-or-stoi
-----------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include "Utils.h"
#include "Status.h"
#include "Date.h"

namespace sdds {

    Date::Date() : m_year(0), m_month(0), m_day(0), m_formatted(true) {
        sdds::ut.getSystemDate(&m_year, &m_month, &m_day) ;
    }

    Date::Date( int year, int month, int day) : m_year(year), m_month(month), m_day(day), m_formatted(true) {
        if ( !validate() ) {
            m_state= Status(3, "Invalid date value" );
            m_year =0;
            m_month = 0;
            m_day =0 ;
        }
    }

     





    const Status& Date::state() const {
        return m_state ;
    }

    void Date::formatted(bool value) {
        m_formatted = value;
    }

    bool Date::validate() {
        int maxDaysInMonth =sdds::ut.daysOfMon( m_month, m_year);
        if (m_year< 15 || m_year >9999 ) {
        //  m_state = Status(1, "Invalid year in date 4");
            return false;
        }
        if (m_month <1 || m_month> 12 ) {
        //  m_state = Status(2, "Invalid month in date 4");
            return false;
        }
        if (m_month ==2 ) {
            if ((m_year % 4 == 0 && m_year % 100 != 0) ||( m_year % 400 == 0)) {
                if ( m_day < 1 || m_day> 29) {
                //  m_state = Status(3, "Invalid day in date 4");
                    return false;
                }
            } else {
                if ( m_day< 1 || m_day> 28) {
                // m_state = Status(3, "Invalid day in date 4");
                    return false;
                }
            }
        } else {
            if (m_day < 1 || m_day> maxDaysInMonth) {
            // m_state = Status(3, "Invalid day in date 4");
                return false;
            }
        }
        m_state.clear() ;
        return true;
    }

    int Date::uniqueDateValue() const {
        //leap years
        int days= m_year * 372 + ( m_year /4) * 1 - ( m_year/ 100 ) * 1 +(m_year /400) * 1; 
        for (int i = 1; i < m_month; ++i) {
            days += sdds::ut.daysOfMon(i, m_year) ;
        }
        days += m_day ;
        return days;
    }

    bool Date::operator==( const Date& D ) const {
        return uniqueDateValue()== D.uniqueDateValue();
    }

    bool Date::operator!=( const Date& D ) const {
        return !(*this == D) ;
    }

    bool Date::operator<( const Date& D) const {
        return uniqueDateValue()< D.uniqueDateValue();
    }

    bool Date::operator>( const Date& D) const {
        return uniqueDateValue() >D.uniqueDateValue();
    }

    bool Date::operator<=( const Date& D) const {
        return !(*this > D) ;
    }

    bool Date::operator>=( const Date& D) const {
        return !(*this < D);
    }

    Date& Date::operator=( const Date& D ) {
        if (this != &D) {
            m_year = D.m_year ;
            m_month = D.m_month;
            m_day = D.m_day ;
            m_state = D.m_state ;
            m_formatted = D.m_formatted;
        }
        return *this;
    }

    std::istream& Date::read( std::istream& is ) {
        std::string input;
        is >> input ;

        bool isInvalidInput = false ;
        int dateValue = 0;
        for (size_t i = 0;i < input.length(); ++i) {
            if (!isdigit(input[i])) {
                isInvalidInput = true ;
                break;
            }
            dateValue =dateValue * 10 +(input[i] - '0'); //converting 
        }

        if (isInvalidInput || input.empty()) {
            m_state = Status( "Invalid date value" );
            is.setstate(std::ios::failbit );
            return is;
        }

        int year, month, day;

        if (dateValue>= 1000000) {
            year = dateValue / 10000 ;
            month =(dateValue / 100) % 100;
            day= dateValue % 100;
        } else if (dateValue>= 10000) {
            year =dateValue / 10000;
            month= (dateValue / 100) % 100;
            day = dateValue % 100;
            if (year < 15 ) {
                m_state =Status(1, "Invalid year in date");
                is.setstate(std::ios::failbit);
                return is;
            }
            year +=(year < 20 ? 0 : 2000);
        } else if ( dateValue >= 100) {
            year= sdds_testYear;
            month= dateValue / 100;
            day= dateValue % 100;
        } else {
            m_state =Status(2, "Invalid month in date");
            is.setstate(std::ios::failbit);
            return is;
        }

        m_year = year;
        m_month= month;
        m_day = day;

        if (!validate()) {
            if (m_year< 0 || m_year >9999) {
                m_state = Status(1, "Invalid year in date" );
            } else if (m_month < 1 || m_month > 12) {
                m_state = Status(2, "Invalid month in date" );
            } else {
            m_state = Status(3, "Invalid day in date" );
            }
            is.setstate(std::ios::failbit);
        } else {
            m_state.clear();
        }

        return is;
    }


    std::ostream& Date::write( std::ostream& os) const {
        if (m_formatted ) {
            os <<std::setw(4) << std::setfill('0')<<  m_year << '/'
            <<std::setw(2) << std::setfill('0') <<m_month << '/'
            << std::setw(2) << std::setfill('0')<< m_day;
        } else {
            os << std::setw(2) << std::setfill('0')<< (m_year % 100)
            <<std::setw(2) << std::setfill('0') <<m_month
            <<std::setw(2) << std::setfill('0')<< m_day;
        }
        return os;
    }


    std::ostream& operator<<( std::ostream& os, const Date& D) {
        return D.write(os) ;
    }

    std::istream& operator>>( std::istream& is, Date& D ) {
        return D.read(is);
    }
}
