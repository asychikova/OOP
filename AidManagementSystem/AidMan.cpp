/* Citation and Sources...
Final project Milstone 5 Part 6 
Module: AidMan
Filename: AidMan.cpp
Version 1.0
Author	Anna Sychikova
Revision History
-----------------------------------------------------------
Date      Reason
2023/11/18  Preliminary release
2023/11/23  Debugged DMA
-----------------------------------------------------------
In order to clear the input buffer, I used std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') 
in my load function. I found that solution at https://stackoverflow.com/questions/63953373/how-to-ignore-the-rest-of-the-line,
this ensures that all newline characters that remain in input buffer after input are cleared, and problems with subsequent 
input operations are minimized.

std::stoi function in my list funcution (rowNumber = std::stoi(input)) is used to convert "input" string to integer "rowNumber".
This solution I found at https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/.

std::stoi(input): the function tries to convert string input to an integer. But for example, if a string contains non-numeric 
characters, it throws an exception std::invalid_argument. catch (const std::invalid_argument& e): executed if exception 
is thrown std::invalid_argument and an error message is displayed.
This solution I found at https://en.cppreference.com/w/cpp/error/invalid_argument

In load function, in order to correctly identify type of products, I used peek() and unget() functions.
If recordType is 4 or 5 and next character is digit, it unget character and create instance of Item.
If the record type is digit, it unget character and create instance of Perishable.
file.unget() is used to unread character that was read during peek operation and 
it ensures that characters that are part of SKU are correctly associated with next product.
Here is how it works in details: 
Reading SKU 12113:
    Reads '1' (recordType) from the first line.
    Peek next character and find '2' (part of SKU).
    Use file.unget() to put back '2', indicating that it should be read as part of next record.
    Create Perishable instance and load data.
Reading SKU 45678:
    Read '4' (recordType) from the second line.
    Peek next character and find '5' (part of the SKU).
    Uses file.unget() to put back '5', indicating that it should be read as part of next record.
    Create Item instance and load data...
unget() function I found at https://www.geeksforgeeks.org/basic_istreamunget-in-c-with-examples/
-----------------------------------------------------------
*/

#include <iostream>
#include <iomanip> 
#include <limits>
#include <stdexcept> 
#include "AidMan.h"
#include "Perishable.h"
#include "Item.h"
#include "Utils.h"

namespace sdds {
    const int sdds_max_num_items = 100;

    AidMan::AidMan(const char* filename) : filename(nullptr), mainMenu(nullptr), itemList(nullptr), numItems(0) {
        if (filename != nullptr) {
            this->filename = new char[strlen(filename) + 1] ;
            strcpy(this->filename, filename);
        }
        const char* menuOptions = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database";
        mainMenu = new Menu(menuOptions);
        itemList = new iProduct*[sdds_max_num_items]{} ;
    }

    AidMan::~AidMan() {
        delete mainMenu ;
        deallocate();
    }

    int AidMan::search(int sku) const {
        for (int i = 0; i < numItems; ++i) {
            if (itemList[i]->getSku() == sku) {
                return i;  
            }
        }
        return -1;  
    }

    unsigned int AidMan::menu() {
        int year, month, day ;
        sdds::ut.getSystemDate(&year, &month, &day);
        std::cout <<"Aid Management System" << std::endl;
        std::cout<< "Date: " <<year << "/" <<month << "/" << (day < 10 ? "0" : "") <<day <<std::endl;
     
        if (filename != nullptr) {
            std::cout<< "Data file: "<<filename <<std::endl;
            std::cout<< "---------------------------------"<<std::endl;
        } else {
            std::cout << "Data file: No file\n";
            std::cout<<"---------------------------------"<<std::endl ;
        }

        unsigned int choice = mainMenu->run();
        if (choice != 0 && filename == nullptr && choice != 7) {
            choice = 7;
        }
        switch (choice) {
        case 1:
            std::cout << "\n****List Items****\n" ;
            list();
            break;
        case 2:
            std::cout << "\n****Add Item****\n";
            addItem();
            break;
        case 3:
            std::cout << "\n****Remove Item****\n" ;
            removeItem();
            break;
        case 4:
            std::cout << "\n****Update Quantity****\n" ;
            updateQuantity();
            break;
        case 5:
            std::cout << "\n****Sort****\n";
            sort();
            break;
        case 6:
            std::cout << "\n****Ship Items****\n";
            shipItems();
            break;
        case 7:
            std::cout << "\n****New/Open Aid Database****\n" ;
            load();
            break;
        default:
            break;
        }
        return choice;
    }

    void AidMan::run() {
        unsigned int choice;
        do {
            choice = menu();
        } while (choice > 0);

        std::cout << "Exiting Program!\n";
        save() ;
    }

    void AidMan::deallocate() {
        delete[] filename;

        for (int i = 0; i < numItems; ++i) {
            delete itemList[i];
        }

        delete[] itemList;
        filename = nullptr;
        itemList = nullptr;
        numItems = 0;
    }

    void AidMan::save() {
        if (filename != nullptr) {
            std::ofstream file(filename);
            if (file) {
                for (int i = 0; i < numItems; ++i) {
                    itemList[i]->save(file);
                }
                file << '\n';
            }
        }
    } 

    bool AidMan::load() {
        if (filename ==nullptr) {
            std::string newFileName ;
            std::cout << "Enter file name: ";
            std::cin >> newFileName ;

            if (newFileName.empty()) {
                return false ; 
            }

            filename =new char[newFileName.length() + 1];
            strcpy(filename, newFileName.c_str()) ;
        }

        std::ifstream file(filename);

        if (!file) {
            std::cout<< "Failed to open " << filename << " for reading!"<< std::endl;
            std::cout<< "Would you like to create a new data file?" <<std::endl;
            std::cout <<"1- Yes!" <<std::endl;
            std::cout <<"0- Exit"<< std::endl;

            int choice;
            std::cin >>choice ;

            if (choice == 1) {
                std::ofstream newFile(filename) ;
                return true;
            } else {
                return false;
            }
        }
        
        int recordsLoaded = 0;
        numItems = 0;

        while (file) {
        char recordType ;
        file >>recordType;

        char peekedChar = file.peek();  

            if (file.fail()) {
                if (file.eof()) {
                    break ;
                } else {
                    std::cout << "Error reading record type from the file." << std::endl;
                    break;
                }
            }

        iProduct* product = nullptr;

            if (recordType == '4' || recordType == '5') {
                if (isdigit(peekedChar)) {
                    file.unget();  
                    product = new Item();
                }
            } else if (isdigit(recordType)) {
                file.unget();  
                product = new Perishable();
            } else {
                file.setstate(std::ios::failbit);
                break;
            }

            if (product != nullptr) {
                if (product->load(file)) {
                    itemList[numItems++] = product;
                    ++recordsLoaded;
                } else {
                    delete product;
                    std::cout <<"Error loading product data."<< std::endl ;
                    break;
                }
            }
        }

        std::cout <<recordsLoaded <<" records loaded!" <<std::endl;
        std::cout <<std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        return true;
    }

    int AidMan::list(const char* sub_desc, bool displayPrompt) {
        int count = 0 ;
        if (numItems > 0) {
            std::cout<<" ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry"
                      <<"\n-----+-------+-------------------------------------+------+------+---------+-----------\n";
            for (int i = 0; i <numItems; ++i ) {
                if (sub_desc ==nullptr || strstr(itemList[i]->getDescription(), sub_desc) != nullptr )  {
                    std::cout << std::setw(4) << std::setfill(' ') <<std::right << i + 1 << " | ";
                    itemList[i]->linear(true );
                    itemList[i]->display( std::cout) ; 
                    std::cout<<std::endl;
                    ++count;
                }
            }
            std::cout<< "-----+-------+-------------------------------------+------+------+---------+-----------"<< std::endl;
        }

        if (count == 0) {
            std::cout <<"The list is empty!" <<std::endl;
        }
        if (displayPrompt) {
                std::string input;
                std::cout<< "Enter row number to display details or <ENTER> to continue:\n";
                std::cout <<"> " ;
                std::getline(std::cin, input);
            
                if (input.empty()) {
                    std::cout << "\n";
                    return count;
                
                }

            try {
                int rowNumber = std::stoi(input);

                if (rowNumber >= 1 && rowNumber <= count) {
                    int foundIndex = rowNumber - 1;
                    itemList[foundIndex]->linear(false);
                    itemList[foundIndex]->display(std::cout);
                    std::cout << std::endl;
                    std::cout << std::endl;
                } else {
                    std::cout << "Invalid input. Details not displayed." << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid input. Details not displayed." << std::endl;
            }
        }
        return count;
        
    }

    void AidMan::addItem() {
        if (numItems >= sdds_max_num_items) {
            std::cout << "Database full!\n" ;
            return;
        }

        int itemType ;
        std::cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ";
        while (true) {
            std::cin >> itemType;

            if (std::cin.fail()) {
                std::cin.clear() ;  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;  
                std::cout << "Invalid input. Please enter a valid option: ";
            } else if (itemType >= 0 && itemType < 3) {
                break; 
            } else {
                std::cout<< "Invalid input. Please enter a valid option: ";
            }
        }

        if (itemType == 0) {
            std::cout<< "Aborted\n";
            return;
        }

        iProduct* product = nullptr;

        if (itemType == 1) {
            product = new Perishable();
        } else if (itemType == 2) {
            product = new Item() ;
        }

        if (product == nullptr) {
            std::cout << "Error creating product.\n";
            return;
        }

    
        if(product->readSku(std::cin)) { 
            int sku = product->getSku();
                int index = search(sku) ;

                if (index != -1) {
                    std::cout<< "Sku: "<< sku<<" is already in the system, try updating quantity instead.\n"<<std::endl;
                    delete product;
                    return;
                }
            
            if (product->read(std::cin)) {
                std::cin.clear() ;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
                std::cout<<std::endl;
                itemList[numItems++] = product ;
            
            } else {
                product->display(std::cout);
                delete product;
            }


        }
    }

    void AidMan::remove(int index) {
        if (index >= 0 && index < numItems) {
            iProduct* removedProduct = itemList[index] ;

            for (int i = index; i < numItems - 1; ++i) {
                itemList[i] = itemList[i + 1 ];
            }

            delete removedProduct;
            --numItems;

            std::cout<< "Item removed!\n";
            return;
        } else {
            std::cout << "Invalid index. No item removed.\n";
            return;
        }
    }

    void AidMan::removeItem() {
        std::cout <<"Item description: " ;
        char desc[100];  
        std::cin.getline(desc, 100) ;

        int count = list(desc,false);

        if (count > 0) {  
            std::cout<< "Enter SKU: ";
            int skuToRemove;
            std::cin >> skuToRemove;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
            int foundIndex = search(skuToRemove);

            if (foundIndex != -1 ) {
                std::cout <<"Following item will be removed: ";
                itemList[foundIndex]->linear(false) ;
                itemList[foundIndex]->display(std::cout);

                std::cout<< "\nAre you sure?\n";
                std::cout << "1- Yes!\n";
                std::cout<< "0- Exit\n> ";

                int confirmChoice;
                std::string confirmInput;
                std::cin >>confirmInput;

                try {
                    confirmChoice = std::stoi(confirmInput);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (confirmChoice == 1) {
                        delete itemList[foundIndex] ;
                        for (int i = foundIndex; i < numItems - 1; ++i) {
                            itemList[i] = itemList[ i + 1 ];
                        }
                        --numItems;
                        std::cout <<"Item removed!\n\n";
                        return;
                    } else {
                        std::cout<< "Aborted!\n";
                        return;
                    }
                } catch (const std::invalid_argument& e) {
                    std::cout<<"Invalid input. Aborted!\n" ;
                    return;
                }
            }
        
        }

    } 


    void AidMan::updateQuantity() {
        std::cout << "Item description: ";
        char sub_desc[100];
        std::cin.getline(sub_desc, 100);

        int count = list(sub_desc, false);

        if (count == 0) {
            std::cout <<"No matches found!\n";
            return;
        }

        std::cout<< "Enter SKU: ";
        int skuToUpdate;
        std::cin >>skuToUpdate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int foundIndex = search(skuToUpdate);

        if (foundIndex == -1) {
            std::cout <<"SKU not found!\n";
            return;
        }

        std::cout<< "1- Add\n2- Reduce\n0- Exit\n> ";
        int updateChoice;
        std::cin >> updateChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (updateChoice) {
        case 0:
            std::cout <<"Aborted!\n";
             std::cout<<std::endl;
            break;
                
        case 1: {
            int currentQuantity = itemList[foundIndex]->getQuantity();
            int neededQuantity = itemList[foundIndex]->getNeeded();

            if (currentQuantity >= neededQuantity) {
                std::cout <<"Quantity Needed already fulfilled!\n";
                std::cout<<std::endl;
                return;
            }

            while (true) {
            int quantityToAdd;
            std::cout<< "Quantity to add: ";
            std::cin >> quantityToAdd;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (quantityToAdd >= 1 && quantityToAdd <= neededQuantity) {
                itemList[foundIndex]->addQuantity(quantityToAdd) ;
                std::cout <<quantityToAdd <<" items added!"<<std::endl;
                std::cout<<std::endl;
                break; 
            } else {
                std::cout <<"Value out of range [1<=val<=" <<neededQuantity<< "]: " ;
                int quantityToAdd2;
                std::cin >> quantityToAdd2;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
                if (quantityToAdd2 >= 1 && quantityToAdd2 <= neededQuantity) {
                itemList[foundIndex]->addQuantity(quantityToAdd2 );
                std::cout << quantityToAdd2<< " items added!"<<std::endl;
                std::cout<<std::endl;
                break; 
                }
            }
        }
        break;
        }
            
        case 2: {
        int currentQuantity = itemList[foundIndex]->getQuantity();

        while (true) {
            int quantityToReduce;
            std::cout <<"Quantity to reduce: ";
            std::cin >> quantityToReduce;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (quantityToReduce >= 1 && quantityToReduce<= currentQuantity) {
                itemList[foundIndex]->reduceQuantity(quantityToReduce);
                std::cout<<quantityToReduce<< " items removed!"<<std::endl;
                std::cout<<std::endl;
                break; 
            } else {
                std::cout<<"Value out of range [1<=val<=" << currentQuantity <<"]: ";
                int quantityToReduce2;
                std::cin >> quantityToReduce2;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
                if (quantityToReduce2 >= 1 && quantityToReduce2 <= currentQuantity){
                itemList[foundIndex]->reduceQuantity(quantityToReduce2);
                std::cout << quantityToReduce2<< " items removed!"<<std::endl;
                std::cout<<std::endl;
                break; 
                }
            }
        }
        break;
        }
        default:
            std::cout<<"Invalid choice. Aborted!\n" ;
        break;
        }
    }

     void AidMan::sort() {
        for (int i = 0; i < numItems - 1; ++i ) {
            for (int j = 0; j < numItems - i - 1;++j ) {
                int difference1 = itemList[j]->getNeeded()- itemList[j]->getQuantity();
                int difference2 = itemList[ j + 1]->getNeeded()- itemList[ j + 1]->getQuantity();

                if (difference1 < difference2) {
                    iProduct* temp = itemList[j];
                    itemList[j] = itemList[ j + 1 ];
                    itemList[ j + 1 ] = temp;
                }
            }
        }

        std::cout <<"Sort completed!\n";
        std::cout<<std::endl ;
    }

    void AidMan::shipItems() {
        std::ofstream shippingFile("shippingOrder.txt");

        int year, month, day;
        sdds::ut.getSystemDate(&year, &month, &day);
        shippingFile<< "Shipping Order, Date: "<< year<<'/'<< month << '/' << std::setw(2) << std::setfill('0')<< day <<'\n';

        shippingFile<< " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry"
                    << "\n-----+-------+-------------------------------------+------+------+---------+-----------\n";
        
        int shippedItemsCount = 0;
        for (int i = 0; i < numItems; ) {
            int quantityNeeded = itemList[i]->getNeeded() ;
            int quantityOnHand= itemList[i]->getQuantity();

            if (quantityNeeded == quantityOnHand) {
                shippingFile << std::setw(4)<< std::setfill(' ') << std::right << shippedItemsCount + 1<< " | ";
                itemList[i]->linear(true);
                itemList[i]->display(shippingFile);
                shippingFile <<std::endl;

                delete itemList[i];

                for (int j = i; j < numItems - 1; ++j) {
                    itemList[j] = itemList[j + 1] ;
                }
                --numItems;
                ++shippedItemsCount ;
            } else {
                ++i ;
            }
        }
        shippingFile<< "-----+-------+-------------------------------------+------+------+---------+-----------\n";

        std::cout <<"Shipping Order for " << shippedItemsCount<<" times saved!\n";
        std::cout<<std::endl;
    }

}