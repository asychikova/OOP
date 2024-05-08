/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Status
Filename: Status.h
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

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <cstring>
#include <iostream>

namespace sdds {
    class Status {

        char* m_description;
        int m_code;
        void set(const char* description);

    public:
        Status() ;
        Status(const char* description ) ;
        Status( int code, const char* description);
        Status(const Status& other);
        Status& operator=( const Status& other ) ;
        Status& operator=(int code);
        Status& operator=( const char* description);
        ~Status();

        operator int() const ;
        operator const char*() const;
        operator bool() const ;
        Status& clear();
        friend std::ostream& operator<<( std::ostream& os, const Status& status) ;
    };
}

#endif 