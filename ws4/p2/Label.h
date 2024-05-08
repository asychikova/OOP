/*
*****************************************************************************
                          OOP244 Workshop - #4 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.10.05
*****************************************************************************
*/
#ifndef SDDS_LABEL_H
#define SDDS_LABEL_H

#include <iostream>

namespace sdds {
    class Label {
        char* m_content ;
        char m_frame[9];
    public:
        Label();
        Label( const char* frameArg);
        Label(const char* frameArg, const char* content ) ;
        ~Label();

        std::istream& readLabel();
        std::ostream& printLabel() const;
        Label& text(const char* content );
    };
}

#endif // SDDS_LABEL_H
