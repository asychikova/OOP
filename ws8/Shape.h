/*
*****************************************************************************
                          OOP244 Workshop - #8 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.14
*****************************************************************************
*/


#ifndef SDDS_SHAPE_H
#define SDDS_SHAPE_H

#include <iostream>

namespace sdds {
    class Shape {
    public:
        virtual ~Shape() ;
       virtual void draw(std::ostream& out) const =0;
        virtual void getSpecs(std::istream& in )= 0 ; 
    };
    std::ostream& operator<<( std::ostream& os, const Shape& shape ) ;
    std::istream& operator>>( std::istream& is, Shape& shape);
} 

#endif 
 /*   bool AidMan::load() {
        if (filename ==nullptr) {
            std::string newFileName ;
            std::cout << "Enter file name: ";
            std::cin >> newFileName ;

            if (newFileName.empty()) {
                return false ; 
            }

            filename =new char[newFileName.length() + 1];
            strcpy(filename, newFileName.c_str()) ;
        }

        std::ifstream file(filename);

        if (!file) {
            std::cout<< "Failed to open " << filename << " for reading!"<< std::endl;
            std::cout<< "Would you like to create a new data file?" <<std::endl;
            std::cout <<"1- Yes!" <<std::endl;
            std::cout <<"0- Exit"<< std::endl;

            int choice;
            std::cin >>choice ;

            if (choice == 1) {
                std::ofstream newFile(filename) ;
                return true;
            } else {
                return false;
            }
        }
        int recordsLoaded = 0;
        numItems = 0;
        while (file) {
            char recordType;
            file >>recordType;

            if (file.fail()) {    
                if (file.eof()) {
                    break;
                } else {
                    std::cout << "Error reading record type from the file." << std::endl;
                    break;
                }
            }

            iProduct* product = nullptr;

            if (recordType== '4' || recordType == '5') {
                file.seekg(-1, std::ios::cur); // Move back to the beginning of the line
                product = new Item();
            } else if (isdigit(recordType)) {
                file.seekg(-1, std::ios::cur); // Move back to the beginning of the line
                //file.unget();
                product = new Perishable();
            } else {
                // Invalid record type, set the ifstream into an invalid state
                file.setstate(std::ios::failbit);
                break;
        }
            if (product != nullptr) {
                if (product->load(file)) {
                    itemList[numItems++] = product;
                    ++recordsLoaded;
                } else {
                    delete product;
                    std::cout <<"Error loading product data."<< std::endl;
                    break;
                }
            }
        }

        std::cout <<recordsLoaded <<" records loaded!" <<std::endl;
        std::cout <<std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        return true;
    }
*/