/***********************************************************************
// Final project Milstone 5 Part 6 
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
/*
-----------------------------------------------------------
This part was provided 
-----------------------------------------------------------
*/

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

namespace sdds {
   const int sdds_testYear = 2023;
   const int sdds_testMon = 12;
   const int sdds_testDay = 9;
   class Utils {
      bool m_testMode = false;
   public:
    void getSystemDate(int* year, int* mon, int* day);
    int daysOfMon(int mon, int year) ;
    void testMode(bool testmode = true);


   };
        extern Utils ut;

}

#endif 