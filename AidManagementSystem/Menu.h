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
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {

class Menu {
    private:
        char* menuContent ;
        int numOptions;

    public:
        Menu( const char* options) ;
        ~Menu();
        unsigned int run() const;
   
};

}
#endif 