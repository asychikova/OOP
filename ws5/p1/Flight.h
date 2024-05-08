/***********************************************************************
// OOP244 Workshop #5 lab (part 1): tester program
//
// File  Flight.h
// Version 1.0
// Author   Asam Gulaid, revised by Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
/*
*****************************************************************************
                          OOP244 Workshop - #5 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.10.11
*****************************************************************************
*/

#ifndef SDDS_FLIGHT_H
#define SDDS_FLIGHT_H

#include <iostream>

namespace sdds {

    const int Boeing747Capacity = 388;
    const int FuelTankCapacity = 238840;

    class Flight {
        int m_passengers;
        double m_fuel;
        char m_title[16];
        void emptyPlane();

    public:
    //constr, 3arg constr, display
        Flight(); 
        Flight(int passengers, double fuel, const char* title);
        std::ostream& display() const;
    
    //type conversion orepators
    //bool
        operator bool() const;
    //int
        operator int() const;
    //double
        operator double() const;
    //const char*
        operator const char*() const;

    //unary member operator
        bool operator~() const;

    //assignment
        Flight& operator=(Flight& flight);
        Flight& operator=(int passengers) ;
        Flight& operator=(double fuel);

    //compound assignment
        Flight& operator+=(double fuel) ;
        Flight& operator+=(int passengers) ;
        Flight& operator-=(double fuel);
        Flight& operator-=(int passengers);

    //stream input and output
        Flight& operator<<(Flight& flight) ;
        Flight& operator>>(Flight& flight) ;

    //binary + for class objects
        int operator+(const Flight& flight) const;
    };
    //binary helper
        int& operator+=(int& num, const Flight& flight);
}

#endif // SDDS_FLIGHT_H
