/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: Perishable
Filename: Perishable.cpp
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/~5  Preliminary release
2023/11/15  Debugged DMA
-----------------------------------------------------------
To clear the input buffer after using getline to read the input string, 
in order to remove the remaining characters (including the new line) 
before further input operations, I used istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n').
I found that solution on: https://stackoverflow.com/questions/63953373/how-to-ignore-the-rest-of-the-line
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include "Perishable.h"
#include "Item.h"
#include <iomanip>
#include <cstring>
#include <limits>


namespace sdds {

	Perishable::Perishable() : Item(), m_handlingInstructions(nullptr) {
	}

	Perishable::Perishable(const Perishable& other) : Item(other) {
		m_expiry = other.m_expiry ;
		if (other.m_handlingInstructions) {
			m_handlingInstructions =new char[strlen(other.m_handlingInstructions) + 1] ;
			strcpy(m_handlingInstructions, other.m_handlingInstructions) ;
		} else {
			m_handlingInstructions = nullptr;
		}
	}

	Perishable& Perishable::operator=(const Perishable& other) {
		if (this != &other) {
			Item::operator=(other); 
			m_expiry = other.m_expiry ;
			if (m_handlingInstructions)
				delete[] m_handlingInstructions;
			if (other.m_handlingInstructions) {
				m_handlingInstructions = new char[strlen(other.m_handlingInstructions) + 1] ;
				strcpy(m_handlingInstructions, other.m_handlingInstructions) ;
			} else {
				m_handlingInstructions =nullptr;
			}
		}
		return *this;
	}
	Perishable::~Perishable() {
		if (m_handlingInstructions)
		delete[] m_handlingInstructions;
	}

	const Date& Perishable::expiry() const {
		return m_expiry ;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const {
		Item::save(ofstr);
		ofstr << '\t';

		if (m_handlingInstructions) {
			ofstr << m_handlingInstructions;
		} 

		ofstr << '\t';

		ofstr << std::setw(2) <<std::setfill('0') <<m_expiry.getYear() % 100;
		ofstr <<std::setw(2)<< std::setfill('0') <<m_expiry.getMonth() ;
		ofstr << std::setw(2)<< std::setfill('0') << m_expiry.getDay();
			
		return ofstr ;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		Item::load(ifstr) ;

		if (m_handlingInstructions ) {
			delete[] m_handlingInstructions;
			m_handlingInstructions = nullptr ;
			
		}
		if (ifstr.fail()) {
			m_status = "Input file stream read (perishable) failed!";
			return ifstr;
		}

		ifstr.ignore(std::numeric_limits<std::streamsize>::max(),'\t') ;

		char tempHandlingInstructions[1000];
		ifstr.getline(tempHandlingInstructions, 1000, '\t');

		if (tempHandlingInstructions[0] != '\0' ) {
			m_handlingInstructions = new char[strlen(tempHandlingInstructions) + 1] ;
			strcpy(m_handlingInstructions, tempHandlingInstructions) ;
		 } else {
        m_handlingInstructions = nullptr; 
    }

		ifstr >>m_expiry;
		if (ifstr.fail()) {
			m_status ="Input file stream read (perishable) failed!";
		}
		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& os ) const {
		if (isClear()) {
			if ( Item::isLinear()) {
				Item::display(os) ;
				os << (m_handlingInstructions ? '*' : ' ')<<m_expiry ;
			} else {
				std::cout<<std::endl;
				os <<"Perishable ";
				Item::display(os) ;
				os <<"Expiry date: " << m_expiry ;
				if (m_handlingInstructions) {
					os <<std::endl << "Handling Instructions: "<< m_handlingInstructions;
				}
				os <<std::endl;
			}
		} else {
			os<< m_status;
		}
		return os;
	}

	bool Perishable::isClear() const {
		return Item::isClear() ;
	}

	std::istream& Perishable::read(std::istream& is) {
		Item::read(is);

		if (m_handlingInstructions) {
			delete[] m_handlingInstructions ;
			m_handlingInstructions =nullptr ;
		}

		std::cout <<"Expiry date (YYMMDD): ";
		is >> m_expiry;
		is.ignore(); 

		std::cout << "Handling Instructions, ENTER to skip: ";
		char temp[1000];
		is.peek();
		if (is && is.peek() !='\n') {
			is.getline(temp, 1000,'\n');
			m_handlingInstructions = new char[strlen(temp) + 1];
			strcpy(m_handlingInstructions, temp) ;
		}
		if (is.fail()) {
			m_status ="Perishable console date entry failed!";
		}

		return is;
	}

	int Perishable::readSku(std::istream& istr) {
		int skuValue;
		std::cout << "SKU: " ;
		while (true) {
			istr >> skuValue;
			if (istr.fail() || skuValue < 10000 || skuValue > 39999) {
				istr.clear() ;
				istr.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				std::cout << "Value out of range [10000<=val<=39999]: ";
			} else {
				istr.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				setSku(skuValue) ;
				break;
			}
		}
		return getSku();
	}

	Perishable::operator bool() const {
		return isClear() ;
	}

    const char* Perishable::getDescription() const {
        return Item::getDescription(); 
    }	

	int Perishable::getQuantity() const {
		return Item::getQuantity(); 
	}	
		
	int Perishable::getNeeded() const {
		return Item::getNeeded(); 
	}	


    void Perishable::addQuantity(int quantityToAdd) {
        
       return Item::addQuantity(quantityToAdd); 
    }

    void Perishable::reduceQuantity(int quantityToReduce) {
       return Item::reduceQuantity(quantityToReduce); 
    }
} 