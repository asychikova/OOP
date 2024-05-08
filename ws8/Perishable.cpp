
#include "Perishable.h"
#include "Item.h"
#include <iomanip>
#include <cstring>
#include <sstream>
#include <limits>


namespace sdds {

 Perishable::Perishable() : Item(), m_handlingInstructions(nullptr) {
   // m_expiry = Date(); // 
}

    Perishable::~Perishable() {
        delete[] m_handlingInstructions;
    }

    const Date& Perishable::expiry() const {
        return m_expiry;
    }

std::ofstream& Perishable::save(std::ofstream& ofstr) const {
    if (isClear()) {
        Item::save(ofstr); 
        ofstr << '\t'; 
        
        if (m_handlingInstructions != nullptr) {
            ofstr << m_handlingInstructions; 
        }
        ofstr << '\t'; 
        
        
        ofstr << std::setw(2) << std::setfill('0') << expiry().getYear() % 100; 
        ofstr << std::setw(2) << std::setfill('0') << expiry().getMonth();
        ofstr << std::setw(2) << std::setfill('0') << expiry().getDay();
        
    }
    return ofstr;
}



//good
/*
std::ifstream& Perishable::load(std::ifstream& ifstr) {
    Item::load(ifstr); 
    
    delete[] m_handlingInstructions;
    m_handlingInstructions = nullptr;

    if (ifstr.fail()) {
        m_status = "Input file stream read (perishable) failed!";
        return ifstr;
    }

    char tempHandlingInstructions[1000];
    ifstr.ignore(); 
    //ifstr.ignore(std::numeric_limits<std::streamsize>::max(), '\t'); // Skip until the next tab
    ifstr.getline(tempHandlingInstructions, 1000, '\t');

    m_handlingInstructions = new char[strlen(tempHandlingInstructions) + 1];
    strcpy(m_handlingInstructions, tempHandlingInstructions);
    //ifstr.ignore(); // Ignore the tab
//ifstr.ignore(std::numeric_limits<std::streamsize>::max(), '\t'); 
    // Read expiry date as a string in YYMMDD format
   
    std::string expiryDateStr;
    ifstr >> std::ws >> expiryDateStr;

    if (expiryDateStr.length() >= 6) { //!=0
    expiryDateStr = expiryDateStr.substr(0, 6);
        int year = std::stoi(expiryDateStr.substr(0, 2));
        int month = std::stoi(expiryDateStr.substr(2, 2));
        int day = std::stoi(expiryDateStr.substr(4, 2));
        m_expiry.setYear(year);
        m_expiry.setMonth(month);
        m_expiry.setDay(day);
    } else {
        m_status = "Invalid date entry";
        return ifstr;
    } 


    return ifstr;

}
*/

std::ifstream& Perishable::load(std::ifstream& ifstr) {
    Item::load(ifstr);

    delete[] m_handlingInstructions;
    m_handlingInstructions = nullptr;

    if (ifstr.fail()) {
        m_status = "Input file stream read (perishable) failed!";
        return ifstr;
    }

    // Read handling instructions
    char tempHandlingInstructions[1000];
    ifstr.ignore(); 
    ifstr.getline(tempHandlingInstructions, 1000, '\t');

    m_handlingInstructions = new char[strlen(tempHandlingInstructions) + 1];
    strcpy(m_handlingInstructions, tempHandlingInstructions);

    // Read expiry date as a string in YYMMDD format
    std::string expiryDateStr;
    ifstr >> std::ws >> expiryDateStr;

    if (expiryDateStr.length() == 6) {
        try {
            int year = std::stoi(expiryDateStr.substr(0, 2));
            int month = std::stoi(expiryDateStr.substr(2, 2));
            int day = std::stoi(expiryDateStr.substr(4, 2));
            m_expiry.setYear(year);
            m_expiry.setMonth(month);
            m_expiry.setDay(day);
        } catch (const std::invalid_argument& e) {
            delete[] m_handlingInstructions;  // Clean up in case of an exception
            m_handlingInstructions = nullptr;
            m_status = "Invalid date entry";
            return ifstr;
        }
    } else {
        delete[] m_handlingInstructions;  // Clean up in case of an invalid date entry
        m_handlingInstructions = nullptr;
        m_status = "Invalid date entry";
        return ifstr;
    }

    return ifstr;
}



 
   
      int Perishable::readSku(std::istream& istr) {
        bool firstAttempt = true;
        int skuValue;
        while (true) {
            if (firstAttempt) {
                std::cout << "SKU: ";
            }
            if (!(istr >> skuValue)) {
                istr.clear();
                std::string temp;
                getline(istr, temp); 
                std::cout << "Invalid Integer, retry: ";
                firstAttempt = false;
            } else if (skuValue < 10000 || skuValue > 39999) {
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Value out of range [10000<=val<=39999]: ";
                firstAttempt = false;
            } else {
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                setSku(skuValue); 
                break;
            }
        }
        return getSku(); 
    }



std::ostream& Perishable::display(std::ostream& os) const {
    if (isClear()) {
       if (Item::isLinear()) {
            Item::display(os);
            os << (m_handlingInstructions && m_handlingInstructions[0] != '\0' ? '*' : ' ') << m_expiry;
        } else { 
            os << "Perishable ";
            Item::display(os); 
            os << "Expiry date: " << m_expiry << std::endl;
            if (m_handlingInstructions && m_handlingInstructions[0] != '\0') {
                os << "Handling Instructions: " << m_handlingInstructions;
            }
         
      
        }
      
    } else {
        os << m_status;
    }
    return os;
}








bool Perishable::isClear() const {
    return !(std::cin.fail() || std::cin.bad());
}




std::istream& Perishable::read(std::istream& is) {
    Item::read(is);

    if (isClear()) {
       std::cout << "Expiry date (YYMMDD): ";
       Date expiryDate;
        is >> expiryDate; 

        
       /* if (!m_expiry.validate()) {
            is.setstate(std::ios::failbit);
            m_status = "Invalid date entry";
            return is;
        } */
        m_expiry = expiryDate; //
        is.ignore(); // Consume '\n'
        
        std::cout << "Handling Instructions, ENTER to skip: ";
        delete[] m_handlingInstructions;
        char temp[1000];
        is.getline(temp, 1000, '\n');
        if (temp[0] != '\0') {
            m_handlingInstructions = new char[strlen(temp) + 1];
            strcpy(m_handlingInstructions, temp);
        } else {
            m_handlingInstructions = nullptr;
        }
    }
    
    return is;
}



}
























  // nonConstThis.linear(originalLinear);
             //nonConstThis.linear(false); //
  // nonConstThis.linear(true); //
 //  bool originalLinear = Item::isLinear(); // Store the original value of linear //

     //   Perishable& nonConstThis = const_cast<Perishable&>(*this);//
      //  nonConstThis.linear(false); //

//const int NO_ERROR = 0;

/*
   std::istream& Perishable::read(std::istream& is) {
        // std::cout << "Perishable AMA Item:" << std::endl;
        Item::read(is);
        
        if (isClear()) {
            std::cout << "Expiry date (YYYY/MM/DD): ";
            is >> m_expiry;
            if (!m_expiry.validate()) {
                is.setstate(std::ios::failbit);
            } else {
                is.ignore(); // Consume '\n'
                std::cout << "Handling Instructions, ENTER to skip: ";
                delete[] m_handlingInstructions;
                char temp[1000];
                is.getline(temp, 1000, '\n');
                if (temp[0] != '\0') {
                    m_handlingInstructions = new char[strlen(temp) + 1];
                    strcpy(m_handlingInstructions, temp);
                } else {
                    m_handlingInstructions = nullptr;
                }
            }
        }
        return is;
    } 
*/


/*
std::ifstream& Perishable::load(std::ifstream& ifstr) {
    Item::load(ifstr); // Call base class load function
    
    delete[] m_handlingInstructions;
    m_handlingInstructions = nullptr;

    if (ifstr.fail()) {
        m_status = "Input file stream read (perishable) failed!";
        return ifstr;
    }

    // Read handling instructions dynamically
    char tempHandlingInstructions[1000];
    ifstr.ignore(); // Ignore the tab
    ifstr.getline(tempHandlingInstructions, 1000, '\t'); // Read handling instructions until the tab
    m_handlingInstructions = new char[strlen(tempHandlingInstructions) + 1];
    strcpy(m_handlingInstructions, tempHandlingInstructions);

    // Read expiry date
    ifstr >> m_expiry;
    if (ifstr.fail()) {
        m_status = "Invalid date entry";
    }

    ifstr.ignore(); // Ignore the new line
    return ifstr;
}*/


//first 3 but good
/*
std::ifstream& Perishable::load(std::ifstream& ifstr) {
    Item::load(ifstr); // Call base class load function

    delete[] m_handlingInstructions;
    m_handlingInstructions = nullptr;

    if (ifstr.fail()) {
        m_status = "Input file stream read (perishable) failed!";
        return ifstr;
    }

    // Read handling instructions dynamically
    char tempHandlingInstructions[1000];
    ifstr.ignore(); // Ignore the tab
    ifstr.getline(tempHandlingInstructions, 1000, '\t'); // Read handling instructions until the tab
    m_handlingInstructions = new char[strlen(tempHandlingInstructions) + 1];
    strcpy(m_handlingInstructions, tempHandlingInstructions);

    // Read expiry date as a string
    std::string expiryDateStr;
    ifstr >> expiryDateStr;

    // Set expiry date using the Date class's read function
    std::istringstream dateStream(expiryDateStr);
    if (!m_expiry.read(dateStream)) {
        m_status = "Invalid date entry";
        return ifstr;
    }

    if (ifstr.fail()) {
        m_status = "Invalid date entry";
    }

    ifstr.ignore(); // Ignore the new line
    return ifstr;
}
*/



//all but bad
/*
std::ifstream& Perishable::load(std::ifstream& ifstr) {
    Item::load(ifstr); // Call base class load function
//setExpiry(Date());
    delete[] m_handlingInstructions;
    m_handlingInstructions = nullptr;

    if (ifstr.fail()) {
        m_status = "Input file stream read (perishable) failed!";
        return ifstr;
    }

    // Read handling instructions dynamically
    char tempHandlingInstructions[1000];
    ifstr.ignore(); // Ignore the tab
    ifstr.getline(tempHandlingInstructions, 1000, '\t');
     ifstr.ignore(); // Ignore the tab
        std::string expiryDateStr;
    ifstr >> expiryDateStr;

    // Set expiry date using the Date class's read function
    std::istringstream dateStream(expiryDateStr); // Read handling instructions until the new line
    m_handlingInstructions = new char[strlen(tempHandlingInstructions) + 1];
    strcpy(m_handlingInstructions, tempHandlingInstructions);
    //
    //ifstr.ignore(); // Ignore the tab
    

   
    //
    return ifstr;
}
*/

/*
std::ofstream& Perishable::save(std::ofstream& ofstr) const {
  //  if (isClear()) {
      
        Item::save(ofstr); // Call the base class save function
        //ofstr << '\t';
        if (m_handlingInstructions != nullptr) {
            ofstr << '\t' << m_handlingInstructions;
        } else {
             ofstr << '\t';
        }
        ofstr << '\t' << expiry();
   // }
    return ofstr;
}
*/

/*good
std::ofstream& Perishable::save(std::ofstream& ofstr) const {
    if (isClear()) {
        Item::save(ofstr); // Call the base class save function
        ofstr << '\t'; // Write a tab
        
        if (m_handlingInstructions != nullptr) {
            ofstr << m_handlingInstructions; // Write handling instructions
        }
        ofstr << '\t'; // Write a tab
        
        ofstr << expiry().getYear() << expiry().getMonth() << expiry().getDay(); // Write unformatted expiry date
    }
    return ofstr;
}
*/