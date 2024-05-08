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

#include <cstring>
#include <iostream>
#include <iomanip>
#include "Label.h"

using namespace std;

namespace sdds {

    Label::Label() : m_content( nullptr) {
        strcpy( m_frame, "+-+|+-+|" );
    }

    Label::Label( const char* frameArg) : m_content( nullptr) {
        if (frameArg )
            strcpy( m_frame, frameArg );
        else
            strcpy( m_frame, "+-+|+-+|");
    }

    Label::Label( const char* frameArg, const char* content) : m_content( nullptr) {
        if (frameArg )
            strcpy(m_frame, frameArg );
        else
            strcpy( m_frame, "+-+|+-+|" );

        if ( content) {
            int len = strlen( content);
            if (len> 70) len = 70;
            m_content = new char[ len + 1];

        for (int i = 0; i < len; ++i ) {
            m_content[i]= content[i] ;
        }
            m_content[len] ='\0';
        }
    }

    Label::~Label() {
        delete[] m_content;
    }

    istream& Label::readLabel() {
        char input[100];
        cin.getline( input, 100); 
        char* trimmedText= input;
        text(trimmedText );
        return cin;
    }

    ostream& Label::printLabel() const {
        if ( m_content) {
            int len = strlen( m_content);
            int width = len > 23 ? len : 23; 
            int padding= (width- len ) / 2; 

            cout << m_frame[0];
            for ( int i = 0; i < width + 2; ++i)
            cout << m_frame[1];
            cout<< m_frame[2]<< '\n';

        
            cout<< m_frame[7];
            for (int i = 0; i < width + 2; ++i)
            cout << ' ';
            cout <<m_frame[3] <<'\n';

        
            cout<< m_frame[7] <<' '; 
            for ( int i = 0; i < padding; ++i )
            cout << ' '; 
            cout<< right << setw(len ) << m_content;
            for (int i = 0; i < padding + (width - len - 2) % 2; ++i)
            cout << ' ';
            cout << ' ' <<m_frame[3] << '\n'; 

            cout << m_frame[7];
            for ( int i = 0; i < width + 2; ++i)
            cout<< ' ';
            cout <<m_frame[3] <<'\n';

            cout <<m_frame[6];
            for ( int i = 0; i < width + 2; ++i)
            cout<< m_frame[5];
            cout <<m_frame[4] ;
        
        }
        return cout;
    }


    Label& Label::text(const char* content ) {
        delete[] m_content ; 
        int len = strlen(content);
        if (len > 70) len = 70;
        m_content =new char[len + 1]; 
        for (int i= 0; i <len; ++i ) {
            m_content[i] =content[i];
        }
        m_content[len]= '\0' ; 
        return *this; 
    }
}

