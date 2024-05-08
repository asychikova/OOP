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

#include "Container.h"
#include <cstring>
#include <iostream>

namespace sdds {
 
    Container::Container( const char* content, int capacity, int contentVolume ) {
        if ( content && content[0]!= '\0' && capacity >0 && contentVolume >=0 && contentVolume<= capacity) {
            strncpy( m_content, content, 50);
            m_content[50] ='\0';
            m_capacity =capacity ;
            m_contentVolume= contentVolume;
        } else {
            setEmpty();
        }
    }

    Container::~Container() {}

    Container::operator bool() const {
        return isValid() ;
    }

    int Container::getCapacityToAdd(int value) const {
            return m_capacity - m_contentVolume + value;
        }

    int Container::getCapacityToRemove(int value) const {
            return m_contentVolume - value;
    }

    int Container::getContentVolume() const {
            return m_contentVolume;
    }

    void Container::setContentVolume(int value) {
            m_contentVolume = value;
        }

    int Container::contentVolume() const {
        return m_contentVolume;
    }

    int Container::getCapacity() const {
        return m_capacity;
    }

    int Container::operator+=( int value) {
        if (isValid() ) {
            int spaceAvailable= m_capacity - m_contentVolume ;
            int amountToAdd =(spaceAvailable >= value) ? value : spaceAvailable ;
            m_contentVolume +=amountToAdd;
            return amountToAdd ;
        }
        return 0;
    }

    int Container::operator-=(int value ) {
        if ( isValid() ) {
            int amountToRemove= (m_contentVolume >= value) ? value : m_contentVolume;
            m_contentVolume -=amountToRemove ;

            return amountToRemove;
        }
         return 0;
    }

    std::ostream& Container::print( std::ostream& os) const {
        if (isValid()) {
           os << m_content<< ": (" <<m_contentVolume << "cc/"<< m_capacity<< ")" ;
        } else {
            os<<"****: (**cc/***)" ;
        }
        return os;
    }

    bool Container::isValid() const {
        return m_content[0] != '\0' && m_contentVolume>= 0 && m_contentVolume <=m_capacity;
    }

    void Container::setEmpty() {
        m_content[0] = '\0';
        m_capacity =0 ;
        m_contentVolume= 0;
    }

    void Container::clear(int capacity, const char* content) {
        if (content && content[0] !='\0' && capacity> 0) {
            strncpy(m_content, content, 50) ;
            m_content[50]= '\0';
            m_capacity= capacity ;
            m_contentVolume =0 ;
        } else {
            setEmpty();
        }
    }

    std::istream& Container::read(std::istream& is ) {
        if ( !isValid() ) {
            std::cout<< "Broken Container, adding aborted! Press <ENTER> to continue....";
            char ch;
            while(is.get(ch) && ch != '\n' );
            return is ;
        }

        std::cout << "Add to "<< m_content<< ": (" <<m_contentVolume<< "cc/"<< m_capacity<<")" << std::endl <<"> " ;
        int value;

        while (!( is >>value) || is.get() != '\n' || value< 1 ) {
            is.clear(); 
            std::cout<< "Invalid input. Please enter a valid positive integer: " ;
            while (is.get() !='\n') ;
            std::cout <<"> ";
        }
        
        int actualAdded;
        if (value < 1 ) {
            actualAdded = 1;
        } else if (value> m_capacity - m_contentVolume ) {
            actualAdded =m_capacity - m_contentVolume;
        } else {
            actualAdded = value ;
        }

        *this += actualAdded;
        std::cout << "Added "<< actualAdded <<" CCs" <<std::endl;
        return is;
    }


    std::ostream& operator<<( std::ostream& os, const Container& container) {
        return container.print(os);
    }

    std::istream& operator>>( std::istream& is, Container& container) {
        return container.read(is);
    }
}
