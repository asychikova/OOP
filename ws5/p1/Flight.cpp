/***********************************************************************
// OOP244 Workshop #5 lab (part 1): tester program
//
// File  Flight.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "Flight.h"
using namespace std;

namespace sdds {

    void Flight::emptyPlane() {
        m_passengers = 0;
        m_fuel = 0;
        strcpy(m_title, "EmptyPlane");
    }

    Flight::Flight() {
        emptyPlane();
    }

    Flight::Flight(int passengers, double fuel, const char* title) {
        emptyPlane();
        if (passengers > 0 && passengers <= Boeing747Capacity && fuel >= 0 &&
            fuel <= FuelTankCapacity) {
            m_passengers = passengers;
            m_fuel = fuel;
            strcpy(m_title,title);
        }
    }

    std::ostream& Flight::display() const {

            if (*this) {
                cout << " Flight  |  Ready to Depart";
                cout << " ";
                cout.width(10);
                cout << std::string(*this);
                cout << " | ";
                cout << "Pass: ";
                cout.width(10);
                cout << int(*this);
                cout << " | ";
                cout.width(12);
                cout.precision(2);
                cout.setf(ios::right);
                cout.setf(ios::fixed);
                cout << double(*this);
                cout.unsetf(ios::right);
                cout << " Liters";
            }
            else if (~*this) {
                cout << " Flight  |  Empty Plane    ";
            }
            else {
                cout << " Flight  |  Low Fuel       ";
                cout << " ";
                cout.width(10);
                cout << (const char *)(*this);
                cout << " | ";
                cout << "Pass: ";
                cout.width(10);
                cout << int(*this);
                cout << " | ";
                cout.width(12);
                cout.precision(2);
                cout.setf(ios::right);
                cout.setf(ios::fixed);
                cout << double(*this);
                cout.unsetf(ios::right);
                cout << " Liters";
            }
            return cout;
        }


    Flight::operator bool() const {
        //// Calculate the minimum required fuel for the current number of passengers
        return m_passengers>0 && m_fuel >= m_passengers * 600;
    }

    //Returns the Flight number of passengers. This operator can not modify the Flight object.
    Flight::operator int() const {
        return m_passengers ;
    }

    //Returns the Flight Fuel. This operator can not modify the Flight object.
    Flight::operator double() const {
        return m_fuel;
    }

    //Returns the Flight Title. This operator can not modify the Flight object.
    Flight::operator const char*() const {
        return m_title ;
    }

    //This operator returns true if the Flight number of passengers is equal to 0, otherwise, it will return false. This operator can not modify the Flight object.
    bool Flight::operator~() const {
        return m_passengers == 0;
    }

    //Copy the Flight passengers and the Flight fuel, Flight title from one Flight to another
    Flight& Flight::operator=(Flight& flight) {
        if (this != &flight) {
            m_passengers= flight.m_passengers;
            m_fuel = flight.m_fuel ;
            strcpy(m_title, flight.m_title );
            flight.emptyPlane();
        }
        return *this;
    }

    //Overload the assignment operator so a Flight can be set to an integer. Doing so should set the Flight number of passengers of the Flight to the integer value, only if the integer value is positive and less than or equal to the Boeing 747 Passenger Max Capacity. 
    Flight& Flight::operator=(int passengers) {
        if (passengers >0 && passengers<= Boeing747Capacity) {
            m_passengers = passengers;
        }
        else {
            emptyPlane();
        }
        return *this ;
    }

    //Overload the assignment operator so a Flight can be set to a double. Doing so should set the Flight fuel of the Flight to the double value, only if the double value is positive and less than the Boeng747 Fuel Tank Max Capacity. 
    Flight& Flight::operator=(double fuel) {
        if (fuel >= 0 && fuel <= FuelTankCapacity ) {
            m_fuel = fuel;
        }
        else {
            emptyPlane();
        }
        return *this;
    }

    //Overload the += operator to add a double value to a Flight. This should act like adding fuel into the Flight Tank. (i.e. the value of the double should be added to the m_fuel)
    //If the double value is negative or Flight Tank is full, no action should be taken. You can fill the Flight Tank with more fuel, the double value, until the Flight Tank is full
    //In any case, a reference of the current object (Flight) should be returned.
    Flight& Flight::operator+=(double fuel ) {
        if ( fuel > 0 && m_fuel + fuel<= FuelTankCapacity) {
            m_fuel += fuel ;
        }
        return *this;
    }

    //Overload the += operator to add an integer value to a Flight. This should act like adding more passengers to the Flight. (i.e. the value of the integer should be added to the m_passengers)
    //If the integer value is negative or Flight full, no action should be taken. You can board more passengers into the Flight, the integer value, until the Flight FULL
    //In any case, a reference of the current object (Flight) should be returned.
    Flight& Flight::operator+=(int passengers ) {
        if (passengers > 0 && m_passengers + passengers <=Boeing747Capacity) {
            m_passengers += passengers;
        }
        return *this ;
    }

    //Overload the -= operator to reduce a Flight fuel by a double value. This should act like pumping out fuel from the Flight Fuel Tank. (i.e. the value of the Flight fuel should be reduced by the double value)
    Flight& Flight::operator-=(double fuel) {
        if (fuel > 0 && m_fuel - fuel >= 0) {
            m_fuel -= fuel;
        }
        return *this ;
    }

    //Overload the -= operator to reduce the number of passengers in a Flight fuel by an integer value.
    Flight& Flight::operator-=(int passengers) {
        if (passengers> 0 && m_passengers - passengers>= 0 ) {
            m_passengers -= passengers;
        }
        return *this;
    }
 
    //Move passengers from the right Flight to the left. After this operation, the total number of passengers in the left Flight will be the sum of both up to the Maximum Capacity of the Boeing 747, and the number of passengers in the right Flight will be zero or the remaining number of passengers after the left plane reached its maximum capacity
    Flight& Flight::operator<<(Flight& flight) {
        if (this != &flight && *this && flight && m_passengers< Boeing747Capacity) {
            int spaceAvailable= Boeing747Capacity- m_passengers ;
            int passengersToMove =flight.m_passengers ;
            if ( passengersToMove > spaceAvailable ) {
                passengersToMove =spaceAvailable ;
            }
            m_passengers += passengersToMove;
            flight.m_passengers-= passengersToMove ;
            double fuelToMove = passengersToMove * 600.0 ;
            if (fuelToMove >0 && m_fuel + fuelToMove <= FuelTankCapacity ) {
                m_fuel += fuelToMove ;
                flight.m_fuel -=fuelToMove;
            }
        }
        return *this;
    }

    //helper += operator that accepts an int reference at left and a constant Flight reference at right and returns an int value
    int& operator+=(int& num, const Flight& flight) {
        num += static_cast<int>( flight); 
        return num;
    }

    //Overload the >> operator (right shift operator) to move passengers from the left Flight to the right. After this operation, the total number of passengers in the right Flight will be the sum of both up to the Maximum Capacity of the Boeing 747, and the number of passengers in the left Flight will be zero or the remaining number of passengers after the right plane reached its maximum capacity
    Flight& Flight::operator>>(Flight& flight) {
        if (this != &flight && *this && flight && flight.m_passengers< Boeing747Capacity) {
            int spaceAvailable= Boeing747Capacity- flight.m_passengers;
            int passengersToMove =m_passengers;
            if (passengersToMove > spaceAvailable) {
                passengersToMove =spaceAvailable;
            }
            flight.m_passengers += passengersToMove;
            m_passengers-= passengersToMove;
            double fuelToMove = passengersToMove * 600.0 ;
            if (fuelToMove >0 && flight.m_fuel + fuelToMove <= FuelTankCapacity ) {
                flight.m_fuel += fuelToMove;
                m_fuel -=fuelToMove;
            }
        }
        return *this;
    }



//Overload the binary member + operator that accepts a constant Flight reference and returns a int value. 
    int Flight::operator+(const Flight& flight) const {
        return m_passengers + flight.m_passengers ;
    }
}
