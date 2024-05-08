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
#ifndef SDDS_LABELMAKER_H
#define SDDS_LABELMAKER_H

#include "Label.h"

namespace sdds {
    class LabelMaker {
        Label* m_labels;
        int m_noOfLabels;

    public:
        LabelMaker(int noOfLabels);
        ~LabelMaker();

        void readLabels();
        void printLabels() const;
    };
}

#endif // SDDS_LABELMAKER_H
