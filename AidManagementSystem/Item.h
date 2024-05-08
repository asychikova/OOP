/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Item
Filename: Item.h
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/09  Preliminary release
2023/11/11  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"
#include "Status.h"
namespace sdds {
    class Item : public iProduct {
        int m_sku ;
        double m_price;
        int m_quantityOnHand;
        int m_neededQuantity ;
        char* m_description ;
        bool m_linearFlag;
        bool m_defaultLinearFlag;
            
    protected: 
        Status m_status;
      
    public:
        Item();
        Item( int sku, const char* desc, double price, int qtyNeeded, int qtyOnHand ) ;
        ~Item();
        Item(const Item& other) ;
        Item& operator=(const Item& other);
        int readSku(std::istream& istr);
        int operator-=(int qty) ;
        int operator+=(int qty) ;
        operator double() const;
        operator bool() const ;
        int qtyNeeded() const;
        int qty() const ;
        void linear(bool isLinear);
        std::ofstream& save(std::ofstream& ofstr) const;
        std::ifstream& load(std::ifstream& ifstr ) ;
        std::ostream& display(std::ostream& ostr) const;    
        std::istream& read(std::istream& istr) ;
        bool operator==(int sku) const;
        bool operator==(const char* description ) const;
        void clear();
        bool isLinear() const;
        bool isEmpty() const ;
        bool isClear() const;
        int getSku() const;
        void setSku(int sku);
        const char* getDescription() const;
        int getQuantity() const;
        int getNeeded() const;
         void addQuantity(int quantityToAdd) ;
        void reduceQuantity(int quantityToReduce) ;
    };
}
#endif





