/*
*****************************************************************************
                          OOP244 Workshop - #8 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.14
*****************************************************************************
*/


#include <cstring>
#include "Rectangle.h"

namespace sdds {
    Rectangle::Rectangle() : m_width(0), m_height(0) {
    }

    Rectangle::Rectangle( const char* label, int width, int height) : LblShape(label ),m_width(width), m_height(height) {
        if (m_height < 3|| m_width < (int)strlen(label) +2) {
            m_width = 0 ;
            m_height = 0;
        }
    }

    Rectangle::~Rectangle() {
    }

    void Rectangle::getSpecs(std::istream& in) {
        LblShape::getSpecs(in) ;
        in >>m_width ;
        in.ignore();
        in>> m_height;
        in.ignore(1000, '\n') ;
    }

    void Rectangle::draw(std::ostream& out) const {
        if (m_width >0 && m_height> 0 && label()!= nullptr) {
            out << "+" ;
            for (int i = 0;i < m_width - 2;++i) {
                out << "-";
            }
            out << "+"<<std::endl ;

            out<< "|" ;
            out<< label();

            for (int i = 0; i < m_width - (int)strlen(label()) - 2; ++i) {
                out<<" ";
            }
            out <<"|"<< std::endl ;

            for (int i = 0; i <m_height - 3; ++i) {
                out <<"|";
                for (int j = 0;j < m_width - 2;++j) {
                    out << " ";
                }
                out<< "|" <<std::endl ;
            }
            out <<"+"  ;
            for(int i = 0; i < m_width - 2; ++i) {
                out<< "-";
            }
            out <<"+" ;
        }
    }
} 
