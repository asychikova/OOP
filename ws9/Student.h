/*
*****************************************************************************
                          OOP244 Workshop - #9 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.21
*****************************************************************************
*/

#ifndef SDDS_STUDENT_H
#define SDDS_STUDENT_H
namespace sdds {
class Student{
    private:
        char* name;
        int age;

    public:
        Student();
        Student(const char* n,int a) ;
        Student(const Student& other);
        Student& operator=(const Student& other) ;
        virtual ~Student(); //this was hard...
        void display() const;
};


}
#endif