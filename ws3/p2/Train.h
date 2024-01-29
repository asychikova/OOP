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

#ifndef SDDS_TRAIN_H
#define SDDS_TRAIN_H

namespace sdds {

    const int MIN_TIME = 700;
    const int MAX_TIME = 2300;
    const int MAX_NO_OF_PASSENGERS = 1000;


    class Train {
       // a character pointer to hold the dynamic name for the Train.
        char* name;
        //an integer variable for the number of people on a train.
        int passengers;
        //an integer variable for the departure time.
        int departureTime;

    public:
        void initialize();
        bool validTime(int value ) const;
        bool validNoOfPassengers( int value) const;
        void set(const char* name);
        void set( int noOfPassengers, int departure);
        void set(const char* name, int noOfPassengers, int departure);
        void finalize();
        bool isInvalid() const;
        int noOfPassengers() const;
        const char* getName() const;
        int getDepartureTime() const;
        void display() const;

        bool load(int& notBoarded);
        bool updateDepartureTime();
        bool transfer( const Train& from);
    };
}

#endif
