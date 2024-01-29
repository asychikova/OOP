/*
*****************************************************************************
                          OOP244 Workshop - #3 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.09.28
*****************************************************************************
*/

#include <iostream>
#include <cstring>
#include "Train.h"

using namespace std;

namespace sdds {
//Initializes the Train object to an invalid state by setting the name pointer to nullptr and other attributes to -1.
    void Train::initialize(){ 
        //delete[] name;
        name = nullptr;
        passengers= -1;
        departureTime = -1 ;
    }

//Finlizes the use of the Train object by deleting the memory pointed by the name attribute pointer.
    void Train::finalize(){
        delete[] name;
        name = nullptr ;
        passengers = -1;
        departureTime = -1;
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

//Load returns a boolean and has at least one integer reference argument. The function returns true if everyone is boarded and false if some are left behind.
    bool Train::load(int& notBoarded) {
        int passengersBoarding;
        cout << "Enter number of passengers boarding:"<< endl;
        cout<< "> " ;
        cin >>passengersBoarding;      
        if (passengersBoarding<= 0) {
            notBoarded =0;
            return false;
         }
        if (passengersBoarding+ passengers <= MAX_NO_OF_PASSENGERS) {
            passengers += passengersBoarding;
            notBoarded =0;
            return true;
        } else 
        {
            notBoarded = passengersBoarding + passengers- MAX_NO_OF_PASSENGERS ;
            passengers = MAX_NO_OF_PASSENGERS;
            return false;
        }
    }

// Updates the departure time of a train.
    bool Train::updateDepartureTime() {
        int newDepartureTime ;
        cout <<"Enter new departure time:" <<endl;
        cout << "> " ;
        cin>> newDepartureTime;
        if ( validTime(newDepartureTime)) 
        {
            departureTime = newDepartureTime;
            return true ;
        } else {
            departureTime = -1;
            return false;
        }
    }

//Transfers the passengers of a Train to the current Train.
bool Train::transfer(const Train& from) {
    if ( isInvalid() || from.isInvalid()) 
    {
        return false ;
    }

    int totalPassengers = passengers + from.noOfPassengers();

    if (totalPassengers<= MAX_NO_OF_PASSENGERS ) {
        char* combinedName = new char[ strlen(name )+ strlen(from.getName() ) + 3];
        strcpy(combinedName, name );
        strcat( combinedName, ", ");
        strcat(combinedName, from.getName() );

        delete[] name;
        name = combinedName;
        passengers = totalPassengers;

        if ( departureTime < from.getDepartureTime() ) 
        {
            departureTime = from.getDepartureTime();
        }

        return true;
    } else {
        int passengersNotBoarded= totalPassengers - MAX_NO_OF_PASSENGERS;
        cout<< "Train is full; " <<passengersNotBoarded <<" passengers of "<<from.getName() << " could not be boarded!" <<endl ;

        passengers = MAX_NO_OF_PASSENGERS;

        char* combinedName = new char[ strlen( name)+ strlen(from.getName() ) + 3];
        strcpy(combinedName, name );
        strcat( combinedName, ", ");
        strcat(combinedName, from.getName() ) ;

        delete[] name;
        name = combinedName;

        cout<< "Transfer Complete:" <<endl;
        display();
        cout << endl ;

        return false;
    }
}



}


