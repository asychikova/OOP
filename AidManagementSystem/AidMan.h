/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: AidMan
Filename: AidMan.h
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/18  Preliminary release
2023/11/23  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
https://stackoverflow.com/questions/5887615/creating-an-array-of-object-pointers-c
-----------------------------------------------------------
*/

#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include <cstring>
#include "Menu.h"
#include "iProduct.h"

namespace sdds {

    class AidMan {
    private:
        char* filename;
        Menu* mainMenu;
        iProduct** itemList; //array of pointers to objects of type iProduct 
        //Each element in the array is a pointer to instance of class derived from iProduct class.
        int numItems;
        unsigned int menu();
        void save();
        void deallocate();
        bool load();

    public:
        AidMan(const char* filename = nullptr) ;
        ~AidMan();
        void run() ;
        int list(const char* sub_desc = nullptr,bool displayPrompt = true);

        int search(int sku) const;
        void addItem();
        
        void remove(int index);
        void removeItem() ;

        void updateQuantity();

        void sort();

        void shipItems();
    
    };

} 
#endif
