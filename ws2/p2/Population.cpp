/*
*****************************************************************************
                          OOP244 Workshop - #2 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.09.22
*****************************************************************************
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include "Population.h"
#include "File.h"

using namespace std;

namespace sdds {

    Population* populations;
    int numPopulations = 0 ;

    void sort() {
        for ( int i = 0;i < numPopulations - 1; i++ ) {
            for (int j = 0; j < numPopulations - i - 1; j++ ) {
                if (populations[j].population > populations[j + 1].population) {
                    
                    Population temp = populations[j];
                    populations[j] = populations[ j + 1];
                    populations[j + 1 ] = temp ;
                }
            }
        }
    }

    bool getPostalCode(char* partial_postal_code_prefix ) {
        cout<< "Population Report"<< endl;
        cout<< "-----------------"<< endl ;
        cout <<"Enter postal code:" << endl;
        cout<< "> ";
        cin.getline( partial_postal_code_prefix, 4);

        return strcmp(partial_postal_code_prefix, "!" ) != 0;
    }

   /* bool load(const char* filename ) {
        return load( filename, "");
    } */

bool load( const char* filename, const char* partial_postal_code_prefix) {
    FILE* fptr = fopen(filename, "r" );
    if (!fptr ) {
        cout<< "Error: Cannot open file " <<filename << endl ;
        return false;
    }

    numPopulations = 0;
    char postalCode[4];
    int population;

    while ( read(fptr, postalCode ) && read( fptr, population) ) {
        if (strcmp( partial_postal_code_prefix, "all" ) == 0 || strncmp( postalCode, partial_postal_code_prefix, strlen( partial_postal_code_prefix) ) == 0 ) {
            Population* newPopulations = new Population[ numPopulations + 1] ;
            for (int i = 0; i < numPopulations; i++ ) {
                newPopulations[i] = populations[i];
            }

            newPopulations[numPopulations].m_code = new char[strlen(postalCode) + 1 ];
            strcpy( newPopulations[numPopulations].m_code, postalCode);
            newPopulations[numPopulations].population =  population;

            delete[] populations;
            populations = newPopulations;
            numPopulations++;
        }
    }

    fclose(fptr);
    return true;
}

    void display() {

        sort();
        cout <<"Postal Code: population" << endl ;
        cout << "-------------------------"<< endl;
        for ( int i = 0;i < numPopulations; i++) {
            cout<< i + 1 << "- " << populations[i].m_code << ":  " <<populations[i].population<< endl;
        }
        cout<< "-------------------------"<< endl ;

        int totalPopulation = 0;
        for ( int i = 0; i < numPopulations;i++) {
            totalPopulation += populations[i].population;
        }
        cout<< "Population of the listed areas: " << totalPopulation<< endl;
        cout<< endl;
    }

    void deallocateMemory() {
        for ( int i = 0;i < numPopulations; i++) {
            delete[] populations[i].m_code;
        }
        delete[] populations ;
        populations = nullptr;
        numPopulations = 0;
    }

}
