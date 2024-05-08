/* Citation and Sources...
Final project Milstone 5 Part 6
Module: iProduct
Filename: iProduct.h
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/04  Preliminary release
2023/11/05  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H

#include <iostream>
#include <fstream>

namespace sdds {

    class iProduct {
    public:
        virtual ~iProduct() {}
        virtual int getSku() const = 0;

        virtual const char* getDescription() const = 0;
        virtual int getQuantity() const = 0;
        virtual int getNeeded() const = 0;
        virtual void addQuantity(int quantityToAdd) = 0;
        virtual void reduceQuantity(int quantityToReduce) = 0;

        virtual int readSku(std::istream& istr) = 0 ;
        virtual int operator-=(int qty) =0 ;
        virtual int operator+=(int qty)= 0 ;
        virtual operator double() const= 0;
        virtual operator bool() const =0;
        virtual int qtyNeeded() const =0;
        virtual int qty() const = 0;
        virtual void linear(bool isLinear) = 0 ;
        virtual std::ofstream& save(std::ofstream& ofstr) const = 0;
        virtual std::ifstream& load(std::ifstream& ifstr) = 0;
        virtual std::ostream& display(std::ostream& ostr) const= 0;
        virtual std::istream& read(std::istream& istr) = 0;
        virtual bool operator==(int sku) const = 0;
        virtual bool operator==(const char* description) const = 0;
    };

    std::ostream& operator<<( std::ostream& ostr, const iProduct& product);
    std::istream& operator>>(std::istream& istr, iProduct& product);

}

#endif 
