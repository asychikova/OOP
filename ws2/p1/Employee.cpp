/***********************************************************************
// OOP244 Workshop #2 lab (part 1)
//
// File  Employee.cpp
// Version 1.0
// Author   Fardad Soleimanloo
// Description
//    To be completed by students
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
***********************************************************************/
#include <iostream>
#include <cstring>
#include "Employee.h"
#include "File.h"


using namespace std;

namespace sdds {

// Holds the number of records (employees) in the file.
   int noOfEmployees;


// Holds the address of the dynamically-allocated array of employees.
// The size of the array is "noOfEmployees".   
   Employee* employees;

   void sort() {
      int i, j;
      Employee temp;
      for (i = noOfEmployees - 1; i > 0; i--) {
         for (j = 0; j < i; j++) {
            if (employees[j].m_empNo > employees[j + 1].m_empNo) {
               temp = employees[j];
               employees[j] = employees[j + 1];
               employees[j + 1] = temp;
            }
         }
      }
   }

// TODO: Finish the implementation of the 1 arg load function which
// reads one employee record from the file and loads it into the employee reference
// argument
// Return the combined success result of the three read functions. These read 
// functions should set the properties of the reference argument of the load function
   /*bool load(Employee& emp ) {
      emp.m_name = nullptr;
      bool ok = read(emp.m_empNo ) && read(emp.m_salary) && read( emp.m_name);
      if (ok) {
         cout << "Read Data: EmpNo="<< emp.m_empNo <<" Salary=" << emp.m_salary << " Name="<< emp.m_name<< endl;
      }
      else {
         cout << "Error reading data!"<< endl;
      }
      return ok;
   }*/

bool load(Employee& emp) {
   emp.m_name = nullptr;
   bool ok = read(emp.m_empNo) && read(emp.m_salary) && read(emp.m_name);
   return ok;
}





// TODO: Finish the implementation of the 0 arg load function 
   bool load() {
      if (noOfEmployees > 0) {
         deallocateMemory();
      }
      if (openFile(DATAFILE)) {

         noOfEmployees = noOfRecords();
         employees = new Employee[noOfEmployees];

         for (int i = 0; i < noOfEmployees;i++) {
            if ( !load(employees[i]) ) {
               cout <<"Error: incorrect number of records read; the data is possibly corrupted." << endl;
               deallocateMemory();
         
               return false;

            }
         }
         closeFile();
     
         return true;
      }
      cout << "Could not open data file: " << DATAFILE << endl;
      return false;
   } 



//precision?? insted of static cast to int
// TODO: Implementation for the display functions 
   void display(const Employee& emp) {
      cout << emp.m_empNo<< ": "<< emp.m_name <<", $" <<static_cast<int>(emp.m_salary)<< endl;
   }

   void display() {
      sort();
      cout<< "Employee Salary report, sorted by employee number" << endl;
      cout <<"no- Empno, Name, Salary"<< endl;
      cout <<"------------------------------------------------"<< endl;
      for (int i = 0; i < noOfEmployees; i++) {
         cout<< i + 1 << "- ";
         display(employees[i] );
      }
   }

// TODO: Implementation for the deallocateMemory function goes here
   void deallocateMemory() {
      for ( int i = 0; i < noOfEmployees;i++) {
         delete[] employees[i].m_name;
      }
      delete[] employees;
      employees = nullptr ;
      noOfEmployees = 0;
   }
}
