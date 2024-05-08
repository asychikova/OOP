/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Menu
Filename: Menu.h
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/10/~28  Preliminary release
2023/11/03  Debugged DMA
-----------------------------------------------------------
In function "run" in order to effectively convert the string representing input string into integer value, 
I used stoi function provided by the C++ Standard Library ( choice = std::stoi(input); ) lines 75, 81, 89.
This method of converting I found at https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/
-----------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include "Menu.h"

namespace sdds {

    Menu::Menu(const char* options) : numOptions(0 ) {
        if (options != nullptr) {
            
        int length = strlen(options );
            menuContent = new char[ length + 1];
            strcpy( menuContent, options);

            for ( int i = 0; i < length; ++i) {
            if (menuContent[i] == '\t' ||menuContent[i] == '\n' ) {
                    ++numOptions;
                }
            }
            ++numOptions ;

        } else {
            menuContent =nullptr;
        }
        if (numOptions >15 || menuContent ==nullptr) {
            std::cout << "Invalid Menu!"<<std::endl;
            numOptions = 0 ;
        }
    }

    Menu::~Menu() {
        delete[] menuContent;
    }

    unsigned int Menu::run() const {
        if (numOptions == 0) {
            return 0;
        }

        std::string input;
        int choice;

        while (true) {
            std::cout<< menuContent<< std::endl;
            std::cout<< "---------------------------------"<<std::endl;
            std::cout <<"0- Exit" <<std::endl;
            std::cout<< "> " ;

            std::getline( std::cin, input );

            bool isValidInput = true ;
            
            for (size_t i =0; i <input.length(); ++i ) {
                if (!isdigit( input[i] ) ) { 
                std::cout << "Invalid Integer, retry: ";
                std::getline(std::cin, input ) ;
                choice = std::stoi(input);
                    return static_cast<unsigned int>(choice) ;
                }
            }

            if (isValidInput) {
                choice = std::stoi(input);
                if (choice >=1 && choice<= numOptions ) {
                    return static_cast<unsigned int>(choice) ;
                } else if ( choice == 0) {
                    return static_cast<unsigned int>(choice) ;
                } else {
                    std::cout<<"Value out of range [0<=val<=" <<numOptions << "]: " ;
                    std::getline( std::cin, input);
                    choice =std::stoi(input);
                    return static_cast<unsigned int>(choice) ;
                }
            }


        }
    }

}