/* Citation and Sources...
Final project Milstone 5 Part 6  
Module: Item
Filename: Item.cpp
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/15  Preliminary release
2023/11/  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "iProduct.h"
#include "Status.h"
#include "Item.h"


namespace sdds {

	Item::Item() : m_sku(0), m_price(0.0), m_quantityOnHand(0), m_neededQuantity(0), m_description(nullptr), m_linearFlag(false), m_defaultLinearFlag(false), m_status() {
	}

	Item::Item(int sku, const char* desc, double price, int qtyNeeded, int qtyOnHand)
		: m_sku(sku), m_price(price), m_quantityOnHand(qtyOnHand), m_neededQuantity(qtyNeeded), m_description(nullptr), m_linearFlag(false), m_defaultLinearFlag(false), m_status(desc) {
	}

	Item::~Item() {
		delete[] m_description ;
		m_description = nullptr;
	}

	Item::Item(const Item& other) : Item() {
		*this = other ;
	}

	Item& Item::operator=(const Item& other) {
		if (this != &other) {
			clear();
			m_sku =other.m_sku;
			m_price= other.m_price;
			m_quantityOnHand =other.m_quantityOnHand;
			m_neededQuantity = other.m_neededQuantity;
			m_linearFlag =other.m_linearFlag;
			m_status = other.m_status ;

			if (other.m_description) {
				m_description = new char[strlen( other.m_description ) + 1];
				strcpy(m_description, other.m_description ) ;
			}
			else {
				m_description = nullptr;
			}
		}
		return *this;
	}

	int Item::operator-=(int qty) {
		if (qty > 0) {
			m_quantityOnHand -= qty;
			if (m_quantityOnHand <0) {
				m_quantityOnHand = 0;
			}
		}
		return m_quantityOnHand;
	}

	int Item::operator+=(int qty){
		if (qty > 0) {
			m_quantityOnHand +=qty ;
		}
		return m_quantityOnHand;
	}

	Item::operator double() const {
		return m_price;
	}

	Item::operator bool() const {
		return m_status ;
	}

	int Item::qtyNeeded() const {
		return m_neededQuantity ;
	}

	int Item::qty() const {
		return m_quantityOnHand;
	}

	void Item::linear(bool isLinear) {
		m_linearFlag = isLinear ;
	}

	std::ofstream& Item::save(std::ofstream& ofstr) const {
	//new save
		if (ofstr.tellp() == std::streampos(0)) {
			ofstr << m_sku << "\t" <<m_description<< "\t" <<m_quantityOnHand<< "\t" <<m_neededQuantity<< "\t";
			ofstr.setf(std::ios::fixed) ;
			ofstr.precision(2);
			ofstr << m_price ;
		} else if (m_status) {
			ofstr <<"\n"<< std::setw(5)<< m_sku << "\t" <<m_description<< "\t" <<m_quantityOnHand<< "\t" <<m_neededQuantity<< "\t";
			ofstr.setf(std::ios::fixed) ;
			ofstr.precision(2);
			ofstr << m_price ;
		}
		return ofstr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {
		delete[] m_description;
		m_description =nullptr;
		char tempDesc[2000];
		ifstr  >> m_sku;
		ifstr.ignore();
		ifstr.getline(tempDesc, 2000, '\t') ;
		ifstr >> m_quantityOnHand>> m_neededQuantity >> m_price;

		if (ifstr.fail()) {
			m_status = "Input file stream read failed!";
		} else {
			m_description= new char[strlen(tempDesc) + 1];
			strcpy(m_description, tempDesc);
			if (ifstr.peek() == '\n') {
				ifstr.ignore();
			}
		}
		return ifstr;
	}



	std::ostream& Item::display(std::ostream& ostr) const {
		if (m_status) {
			if (m_linearFlag) {
				std::string truncatedDescription = m_description ? m_description : "";
				if (truncatedDescription.length() > 35 ) {
					truncatedDescription =truncatedDescription.substr(0, 35);
				}

				ostr << std::setw(5)<<m_sku << " | "<< std::setw(35)<< std::setfill(' ')<< std::left <<truncatedDescription
					<< " | " <<std::setw(4) <<std::right <<m_quantityOnHand<< " | " <<std::setw(4) << std::right <<m_neededQuantity
					<<" | " <<std::setw(7)<< std::fixed <<std::setprecision(2) <<std::right << m_price<<" |";
			}
			else {
				ostr << "AMA Item:" <<std::endl;
				ostr <<m_sku << ": "<< m_description << std::endl;
				ostr <<"Quantity Needed: " <<m_neededQuantity << std::endl;
				ostr<< "Quantity Available: "<<m_quantityOnHand << std::endl;
				ostr << "Unit Price: $" << std::fixed <<std::setprecision(2) << m_price << std::endl;
				ostr << "Needed Purchase Fund: $"<<std::fixed <<std::setprecision(2)<< m_price * (m_neededQuantity - m_quantityOnHand)<<std::endl;
			}
		}
		else {
			ostr << m_status;
		}
		return ostr;
	}

	int Item::readSku(std::istream& istr) {
		bool firstAttempt = true;
		int skuValue;
		while (true) {
			if (firstAttempt) {
				std::cout <<"SKU: ";
			}
			if (!(istr>> skuValue)) {
				istr.clear();
				std::string temp;
				std::getline(istr, temp);
				std::cout << "Invalid Integer, retry: ";
				firstAttempt =false;
			}
			else if (skuValue< 10000 || skuValue > 99999) {
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Value out of range [40000<=val<=99999]: ";
				firstAttempt = false;

			}
			else {
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				m_sku =skuValue;
				break;
			}
		}
		return m_sku;
	}


	std::istream& Item::read(std::istream& istr) {
		delete[] m_description;
		m_description= nullptr;
		std::cout<< "AMA Item:" <<std::endl;
		std::cout<< "SKU: " << m_sku<< std::endl;
		std::cout <<"Description: ";

		char tempDesc[2000];
		int tempQtyNeeded, tempQtyOnHand;
		double tempPrice;

		istr.getline(tempDesc, 2000, '\n');
		bool firstAttempt = true;
		while (true) {
			if (firstAttempt) {
				std::cout<< "Quantity Needed: ";
			}
			if (!(istr >> tempQtyNeeded)) {
				istr.clear();
				std::string tempQN;
				std::getline(istr, tempQN);
				std::cout <<"Invalid Integer, retry: ";
				firstAttempt = false;
			}
			else if (istr.fail() || tempQtyNeeded < 1 || tempQtyNeeded > 9999) {
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Value out of range [1<=val<=9999]: ";
				firstAttempt = false;
			}
			else {
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
		}

		firstAttempt = true;
		while (true) {
			if (firstAttempt) {
				std::cout << "Quantity On Hand: ";
			}
			if (!(istr >>tempQtyOnHand)) {
				istr.clear();
				std::string tempQOH;
				std::getline(istr, tempQOH);
				std::cout << "Invalid Integer, retry: ";
				firstAttempt = false;
			}
			else if ( istr.fail() || tempQtyOnHand <0 ||tempQtyOnHand >tempQtyNeeded) {
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Value out of range [0<=val<=" <<tempQtyNeeded << "]: ";
				firstAttempt = false ;
			} else {
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
		}

		firstAttempt = true;
		while (true) {
			if (firstAttempt) {
				std::cout << "Unit Price: $";
			}
			if (!(istr >>tempPrice)) {
				istr.clear();
				std::string tempPriceStr ;
				std::getline(istr, tempPriceStr);
				std::cout <<"Invalid number, retry: ";
				firstAttempt = false ;
			}
			else if (istr.fail() || tempPrice < 0.0 || tempPrice > 9999.0 ) {
				istr.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				std::cout << "Value out of range [0.00<=val<=9999.00]: ";
				firstAttempt = false ;
			}
			else {
				istr.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				break;
			}
		}

		m_description = new char[strlen(tempDesc) + 1];
		strcpy(m_description, tempDesc);
		m_neededQuantity = tempQtyNeeded ;
		m_quantityOnHand =tempQtyOnHand;
		m_price = tempPrice ;
		m_status.clear();

		return istr;
	}

	bool Item::operator==(int sku) const {
		return m_sku == sku;
	}

	bool Item::operator==(const char* description) const {
		return(m_description && description && strstr(m_description, description) != nullptr );
	}

	void Item::clear() {
		delete[] m_description;
		m_description = nullptr;
		m_status = 0;
		m_sku = 0;
		m_price = 0.0;
		m_quantityOnHand = 0 ;
		m_neededQuantity = 0 ;
		m_linearFlag = m_defaultLinearFlag;
	}

	int Item::getSku() const {
		return m_sku;
	}

	void Item::setSku(int sku) {
		m_sku = sku;
	}

		bool Item::isLinear() const {
		return m_linearFlag;
	}

	bool Item::isEmpty() const {
		return m_sku == 0 ;
	}

	bool Item::isClear() const {
		return m_sku;
	}

    const char* Item::getDescription() const {
        return m_description; 
    }

	int Item::getQuantity() const {
		return m_quantityOnHand;
	}

	int Item::getNeeded() const {
		return m_neededQuantity;
	}


    void Item::addQuantity(int quantityToAdd) {
        
        m_quantityOnHand += quantityToAdd;
    }

    void Item::reduceQuantity(int quantityToReduce) {
        
        m_quantityOnHand -= quantityToReduce;
    }
}

