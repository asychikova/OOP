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

#include "Graduate.h"
#include <iostream>
#include <cstring>
namespace sdds {
Graduate::Graduate() : m_title(nullptr ), supervisor(nullptr) {}

Graduate::Graduate( const char* n, int a, const char* title, const char* sup)
    : Student(n,a), m_title(nullptr), supervisor(nullptr){
    m_title = new char[ strlen(title) + 1 ] ;
    strcpy(m_title, title);

    supervisor = new char[ strlen(sup) + 1 ] ;
    strcpy(supervisor,sup);
}

Graduate::Graduate(const Graduate& other): Student(other) {
    m_title = new char[strlen(other.m_title) + 1];
    strcpy(m_title,other.m_title );

    supervisor = new char[ strlen(other.supervisor) + 1];
    strcpy(supervisor, other.supervisor);
}

Graduate& Graduate::operator=(const Graduate& other){
    if (this != &other ) {
        Student::operator=(other);
        delete[] m_title ;
        delete[] supervisor;

        m_title = new char[ strlen(other.m_title) + 1] ;
        strcpy(m_title,other.m_title);

        supervisor = new char[strlen(other.supervisor) + 1 ];
        strcpy(supervisor, other.supervisor) ;
    }
    return *this;
}

Graduate::~Graduate(){
    delete[] m_title ;
    delete[] supervisor;
}

void Graduate::display() const {
    Student::display();
    std::cout <<"Thesis Title: "<<m_title <<"\nSupervisor: "<<supervisor <<std::endl;
    std::cout<<"---------------------------------------------" <<std::endl;
}
}