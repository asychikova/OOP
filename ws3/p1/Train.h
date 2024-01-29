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

#ifndef SDDS_TRAIN_H
#define SDDS_TRAIN_H

namespace sdds {

    class Train {
       // a character pointer to hold the dynamic name for the Train.
        char* name;
        //an integer variable for the number of people on a train.
        int passengers;
        //an integer variable for the departure time.
        int departureTime;

    public:
        /*Train();
        ~Train();*/
        void initialize();
        void finalize();
        bool validTime(int value ) const;
        bool validNoOfPassengers( int value) const;
        void set(const char* name);
        void set( int noOfPassengers, int departure);
        void set(const char* name, int noOfPassengers, int departure);
        bool isInvalid() const;
        int noOfPassengers() const;
        const char* getName() const;
        int getDepartureTime() const;
        void display() const;
    };
}

#endif //SDDS_TRAIN_H
