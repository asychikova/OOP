/*
*****************************************************************************
                          OOP244 Workshop - #4 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.10.02
*****************************************************************************
*/

#include <cstring>
#include <iostream>
#include "CarInventory.h"
#include <iomanip>

namespace sdds {

    CarInventory::CarInventory() : 
        m_type(nullptr) , 
        m_brand(nullptr ), 
        m_model(nullptr) , 
        m_year(2022), 
        m_code(100) , 
        m_price(1.0) {
    }

    CarInventory::CarInventory(const char* type , const char* brand, const char* model , int year, int code, double price):
        m_type(nullptr) , 
        m_brand(nullptr ), 
        m_model(nullptr) {
            if (year >= 1990) {
                m_year = year;
            } else {
                m_year = 2022;
            }

            if (code >= 100 && code <= 999) {
                m_code = code;
            } else {
                m_code = 100;
            }

            if (price > 0) {
                m_price = price;
            } else {
                m_price = 1.0;
            }

        setType(type);
        setBrand(brand);
        setModel(model);
        }
      

    CarInventory::~CarInventory() {
        delete[] m_type ;
        delete[] m_brand;
        delete[] m_model;
    }

    CarInventory& CarInventory::setInfo(const char* type , const char* brand, const char* model , int year, int code, double price) {
        resetInfo();
        if (year>= 1990 && code >=100 && code<= 999 && price >0) {
            setType( type);
            setBrand(brand );
            setModel(model );
            setYear(year);
            setCode( code);
            setPrice(price);
        }
        return *this;
    }

    void CarInventory::resetInfo() {
        delete[] m_type ;
        delete[] m_brand;
        delete[] m_model ;
        m_type = nullptr;
        m_brand =nullptr;
        m_model = nullptr;
        m_year= 0;
        m_code = 0;
        m_price= 0.0;
    }

    void CarInventory::setType(const char* type) {
       // if ( m_type) {
            delete[] m_type ;
            m_type = nullptr;
      //  }
      //  if (type ) {
            m_type = new char[ strlen(type) + 1] ;
            strcpy( m_type, type);
      //  }
    }

    void CarInventory::setBrand( const char* brand) {
       // if ( m_brand ) {
            delete[] m_brand;
            m_brand = nullptr;
      //  }
      //  if (brand ) {
            m_brand = new char[strlen (brand) + 1 ];
            strcpy(m_brand, brand );
      //  }
    }

    void CarInventory::setModel(const char* model) {
       // if (m_model ) {
            delete[] m_model;
            m_model= nullptr ;
       // }

       // if (model) {        
            m_model = new char[strlen(model) + 1] ;
            strcpy(m_model, model);
       // }
    }

    void CarInventory::setYear(int year) {
        if (year >= 1990) {
            m_year= year;
        } else {
            m_year = 2022;
        }
    }

    void CarInventory::setCode(int code) {
        if (code >= 100 && code <= 999) {
            m_code =code;
        } else {
            m_code = 100;
        }
    }

    void CarInventory::setPrice(double price) {
        if (price > 0) {
            m_price= price ;
        } else {
            m_price = 1.0;
        }
    }

    void CarInventory::printInfo() const {
        std::cout<< "| " << std::left << std::setw(11) <<m_type
                  <<"| " <<std::left << std::setw(17)<< m_brand
                  << "| "<<std::left <<std::setw(17) <<m_model
                  << "| "<< std::setw(4) <<m_year
                  << " | "<< std::right<< std::setw(4) << m_code
                  <<" | " <<std::fixed << std::setprecision(2)<< std::setw(9)<< m_price
                  << " |" <<std::endl;
    }

    bool CarInventory::isValid() const {
        return ( m_type && m_brand && m_model && m_year>= 1990 && m_code >=100 && m_code <=999 && m_price > 0 );
    }

    bool CarInventory::isSimilarTo( const CarInventory& car) const {
        return (m_type && m_brand && m_model &&
                car.m_type && car.m_brand && car.m_model &&
                strcmp( m_type, car.m_type) == 0 &&
                strcmp(m_brand, car.m_brand )== 0 &&
                strcmp(m_model, car.m_model ) ==0 &&
                m_year== car.m_year);
    }

    int find_similar(CarInventory car[], const int num_cars ) {
        for (int i = 0; i < num_cars; i++) {
            for (int j = i + 1; j < num_cars; j++) {
                if (car[i].isSimilarTo(car[j])) {
                    return i; 
                }
            }
        }
         return -1; 
    }

}
