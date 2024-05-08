/*
*****************************************************************************
                          OOP244 Workshop - #7 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.07
*****************************************************************************
*/

#include "Pack.h"
#include <iostream>

namespace sdds {
    Pack::Pack(const char* content, int size, int unitSize, int numberOfUnits)
        : Container( content, size * unitSize, numberOfUnits * unitSize), m_unitSize( unitSize) {
        if (m_unitSize <=0) {
            setEmpty();
        }
    }

    int Pack::operator+=(int units) {
        int availableUnits =( getCapacity() -getContentVolume()) / m_unitSize ;
        int addedUnits =(units <= availableUnits ) ? units : availableUnits ;
        Container::operator+=( addedUnits * m_unitSize );
        return addedUnits ;
    }

    int Pack::operator-=(int units) {
        int removedUnits = (units <= getContentVolume() / m_unitSize) ? units : getContentVolume() / m_unitSize;
        Container::operator-=(removedUnits * m_unitSize);
        return removedUnits;
    }

    int Pack::unit() const {
        return m_unitSize ;
    }

    int Pack::noOfUnits() const {
        return contentVolume() / m_unitSize;
    }

    int Pack::size() const {
        return getCapacity() / m_unitSize ;
    }

    void Pack::clear(int size, int unitSize, const char* content ) {
        Container::clear(size * unitSize, content );
        if (unitSize > 0 ) {
            m_unitSize = unitSize;
        } else {
            setEmpty() ;
        }
    }

    std::ostream& Pack::print(std::ostream& os) const {
        Container::print(os);
            os <<", "<< noOfUnits()<<" in a pack of " << size();
        return os;
    }

    std::istream& Pack::read(std::istream& is) {
        if (!isValid() ) {
            std::cout <<"Broken Container, adding aborted! Press <ENTER> to continue...." ;
            char ch;
            while ( is.get(ch) && ch !='\n');
        } else if (noOfUnits() < size() ) {
            std::cout <<"Add to " ;
            std::cout<< *this <<std::endl;
            std::cout<<"> " ;
            int units;
            is >>units;

            while (is.fail() || units <1 || units>size() - noOfUnits() ) {
                if ( is.fail()) {
                    is.clear() ;
                    while (is.get() !='\n'); 
                    std::cout<< "Invalid Integer, retry: ";
                } else {
                    std::cout<<"Value out of range [1<=val<="<< size() - noOfUnits()<< "]: " ;
                }
                is >>units ;
            }
            *this += units;

            std::cout <<"Added "<< units<<std::endl;
            while ( is.get() !='\n') ;
        } else {
            std::cout<<"Pack is full!, press <ENTER> to continue..." ;
            char ch;
            while ( is.get(ch) && ch !='\n');
        }

        return is;
    }

    std::ostream& operator<<( std::ostream& os, const Pack& pack) {
        return pack.print(os);
    }

    std::istream& operator>>( std::istream& is, Pack& pack) {
        return pack.read(is);
    }

}
