/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Perishable
Filename: Perishable.h
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/~5  Preliminary release
2023/11/15  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/


#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"
#include <iostream>

namespace sdds {

    class Perishable : public Item {
        Date m_expiry ;
        char* m_handlingInstructions;

    public:
   
        Perishable();
        ~Perishable();
        Perishable(const Perishable& other);
        Perishable& operator=(const Perishable& other) ;
        bool isClear() const ;
        operator bool() const override;
        void setExpiry(const Date& date);
        const Date& expiry() const;
        int readSku(std::istream& istr) override;
        std::ofstream& save(std::ofstream& ofstr ) const override;
        std::ifstream& load(std::ifstream& ifstr) override ;
        std::ostream& display(std::ostream& os ) const override;
        std::istream& read(std::istream& is) override;
        const char* getDescription() const override;
        int getQuantity() const override;
        int getNeeded() const override;
        void addQuantity(int quantityToAdd) override ;
        void reduceQuantity(int quantityToReduce) override;
    };
}
#endif 
