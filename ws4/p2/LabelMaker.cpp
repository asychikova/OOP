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

#include <iostream>
#include "LabelMaker.h"

using namespace std;

namespace sdds {
    LabelMaker::LabelMaker( int noOfLabels) : m_labels( new Label[noOfLabels ] ), m_noOfLabels(noOfLabels ) {}

    LabelMaker::~LabelMaker() {
        delete[] m_labels;
    }

    void LabelMaker::readLabels() {
        char temp[100];
        cout<< "Enter 6 labels:" <<endl; 
        for ( int i= 0; i < m_noOfLabels; ++i ) {
            cout<< "Enter label number "<< i + 1<< endl;
            cout<< "> ";
            cin.getline( temp, 100);
            m_labels[i].text(temp );
        }
    }

    void LabelMaker::printLabels() const {
        for ( int i =0; i< m_noOfLabels; ++i) {
            m_labels[i].printLabel();
             cout<< endl; 
        }
    }
}
