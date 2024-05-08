/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Status
Filename: Status.cpp
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
#include <iostream>
#include <cstring>
#include "Status.h"

namespace sdds {

    void Status::set(const char* description ) {
        if (description ) {
            m_description= new char[strlen(description) + 1] ;
            strcpy(m_description, description) ;
        } else {
            m_description = nullptr;
        }
    }

    Status::Status() : m_description(nullptr ), m_code(0) {}

    Status::Status( const char* description) : m_code(0) {
        set(description);
    }

    Status::Status(int code, const char* description ) : m_code(code) {
        set(description) ;
    }

    Status::Status( const Status& other) : m_code(other.m_code) {
        set(other.m_description );
    }

    Status& Status::operator=( const Status& other) {
        if (this != &other ) {
            clear() ;
            m_code = other.m_code;
            set( other.m_description) ;
        }
        return *this;
    }

    Status& Status::operator=(int code ) {
        clear();
        m_code = code ;
            if ( m_code == 0 ) {
            set( "Invalid Integer");
        } else if ( m_code == 1 ) {
            set("value too high" );
        } else if ( m_code == -1 ) {
            set("value too low" );
        }
        return *this;
    } 

    Status& Status::operator=( const char* description) {
        clear();
        set(description );
        return *this;
    }

    Status::~Status() {
        clear();
    }

    Status::operator int() const {
        return m_code ;
    }

    Status::operator const char*() const {
        return m_description ? m_description : "" ;
    }

    Status::operator bool() const {
        return ( m_code == 0 && m_description == nullptr);
    }

    Status& Status::clear() {
        delete[] m_description ;
        m_description = nullptr;
        m_code = 0 ;
        return *this;
    }

    std::ostream& operator<<( std::ostream& os, const Status& status) {
        if (status.m_code == 0 && status.m_description ) {
            os << status.m_description ;
        } else if ( status.m_code && status.m_description) {
        os <<"ERR#" <<status.m_code << ": "<< status.m_description;
        } else if (status.m_code ) {
            os <<"ERR#" <<status.m_code;
        }
        return os;
    }

}