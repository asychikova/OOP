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

#include "Student.h"
#include <iostream>
#include <cstring>

namespace sdds {
Student::Student() : name(nullptr),age(0) {}

Student::Student(const char* n, int a) : age(a){
    name = new char[strlen(n) + 1 ];
    strcpy(name,n) ;
}

Student::Student(const Student& other) : age(other.age) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

Student& Student::operator=(const Student& other){
    if (this!= &other) {
        delete[] name ;
        age = other.age;
        name = new char[strlen( other.name) + 1 ];
        strcpy(name, other.name) ;
    }
    return *this;
}

Student::~Student() {
    delete[] name ;
}

void Student::display() const {
    std::cout<< "Name: "<<name << "\nAge: "<<age <<std::endl;
}
}