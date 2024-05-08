/*
*****************************************************************************
                          OOP244 Workshop - #9 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.21
*****************************************************************************
*/

#ifndef SDDS_GRADUATE_H
#define SDDS_GRADUATE_H

#include "Student.h"
namespace sdds {
class Graduate : public Student {
    private:
        char* m_title;
        char* supervisor;

    public:
        Graduate();
        Graduate( const char* n,int a, const char* title, const char* sup );
        Graduate(const Graduate& other) ;
        Graduate& operator=(const Graduate& other);
        ~Graduate();
        void display() const;
};


}

#endif 