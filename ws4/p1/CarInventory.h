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


#ifndef SDDS_CARINVENTORY_H
#define SDDS_CARINVENTORY_H

namespace sdds {
    class CarInventory {
        char* m_type;
        char* m_brand;
        char* m_model;
        int m_year;
        int m_code;
        double m_price;
        void resetInfo();

    public:
        CarInventory();
        CarInventory( const char* type, const char* brand, const char* model, int year= 2022, int code =100, double price =1.0);
        ~CarInventory();
        void setType(const char* type);
        void setBrand( const char* brand) ;
        void setModel(const char* model);
        void setYear( int year) ;
        void setCode(int code);
        void setPrice(double price);
        CarInventory& setInfo(const char* type, const char* brand, const char* model, int year, int code, double price);

        void printInfo() const ;
        bool isValid() const;
        bool isSimilarTo(const CarInventory& car) const ;
    };

    int find_similar( CarInventory car[], const int num_cars);
}

#endif // !SDDS_CARINVENTORY_H
