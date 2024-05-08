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

#ifndef SDDS_CONTAINER_H
#define SDDS_CONTAINER_H

#include <iostream>

namespace sdds {
    class Container {

        char m_content[51];
        int m_capacity ;
        int m_contentVolume;

protected: 
        void setEmpty();
        int contentVolume() const;
        int getCapacity() const;

    public:
        Container(const char* content, int capacity, int contentVolume = 0);
        ~Container();
        operator bool() const;

        int getCapacityToAdd(int value) const;
        int getCapacityToRemove(int value) const ;
        int getContentVolume() const ;
        void setContentVolume(int value) ;
        int operator+=( int value);
        int operator-=(int value) ;
        bool isValid() const;
        void clear(int capacity, const char* content);
        std::ostream& print(std::ostream& os) const;
        std::istream& read(std::istream& is );
    };

    std::ostream& operator<<( std::ostream& os, const Container& container);
    std::istream& operator>>( std::istream& is, Container& container);
}

#endif 
