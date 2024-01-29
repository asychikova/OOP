/*
*****************************************************************************
                          OOP244 Workshop - #3 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.09.26
*****************************************************************************
*/


#include <iostream>
#include <cstring>
#include "Train.h"

using namespace std;

namespace sdds {

//Declare three C++ constants, for the lowest acceptable time value, the highest acceptable time value and the maximum number of passengers allowed on a train.
    const int MIN_TIME = 700;
    const int MAX_TIME =2300 ;
    const int MAX_NO_OF_PASSENGERS =1000;

   /* //constr
    Train::Train() {
        name = nullptr;
        passengers = -1 ;
        departureTime = -1;
    }

    //destr
    Train::~Train() {
        delete[] name ;
    }*/
    
//Initializes the Train object to an invalid state by setting the name pointer to nullptr and other attributes to -1.
    void Train::initialize(){ 
        //delete[] name;
        name = nullptr;
        passengers= -1;
        departureTime = -1 ;
    }
//Returns true if the value is between the minimum and maximum acceptable values and if the two right digits are less than or equal to 59.
    bool Train::validTime(int value) const {
    if (value >= MIN_TIME && value <= MAX_TIME) {
        int minutes = value % 100; //last 2 dig of numb
        if (minutes <= 59) {
            return true;
        }
    }
    return false;
}
//Returns true if the number of passengers is positive and less than the maximum number of passengers allowed on a train.
    bool Train::validNoOfPassengers(int value) const {
    if (value > 0 && value <= MAX_NO_OF_PASSENGERS) {
        return true;
    } else {
        return false;
    }
}

//Sets the name of the Train dynamically.
    void Train::set(const char* newName){
        delete[] name;
        name =nullptr;

        if ( newName != nullptr && *newName !='\0' ) {
            name =new char[ strlen(newName ) + 1];
            strcpy(name, newName ) ;
        }
    }

//sets the two attributes for the number of passengers and departure time to the incomming values if the are valid. If not both will be set to -1 to mark them as invalid.
    void Train::set ( int noOfPassengers, int departure) {
        if (validNoOfPassengers (noOfPassengers ) && validTime( departure)) {
            passengers =noOfPassengers;
            departureTime = departure ;
        } 
        else  {
            passengers = -1;
            departureTime= -1;
        }
    }

//sets the name, the number of passengers and the departure time to incomming arguments using the same logic of the other two set functions.
    void Train::set( const char* newName,int noOfPassengers,int departure) {
        set( newName);
        set(noOfPassengers, departure );
    }

//Finlizes the use of the Train object by deleting the memory pointed by the name attribute pointer.
    void Train::finalize() {
        delete[] name;
        name = nullptr ;
        passengers = -1;
        departureTime = -1;
    }

//returns true if any of the attributes are set to their invalid state.
    bool Train::isInvalid() const {
    if ( name == nullptr || passengers == -1 || departureTime == -1) {
        return true;
    } else {
        return false;
    }
}

//This query returns the number of people on a train.
    int Train::noOfPassengers() const{
        return passengers ;
    }

//This query returns the name of a train.
    const char* Train::getName() const {
        return name;
    }

//This query returns the time of departure.
    int Train::getDepartureTime() const{
        return departureTime;
    }

//This member function sends the information about a Train to the standard output in the specified format if the object holds valid data values.
    void Train::display()const {
        if (isInvalid()) {
            cout << "Train in an invalid State!"<< endl;
        } 
        else {
            cout <<"NAME OF THE TRAIN:    "<< name << endl;
            cout << "NUMBER OF PASSENGERS: " <<passengers << endl;
            cout << "DEPARTURE TIME:       " << departureTime<< endl;
        }
    }
}


