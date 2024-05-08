# OOP
/*
*****************************************************************************
             OOP244 FINAL PROJECT - REFLECTION and NOTES from OOP244
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.11.26
*****************************************************************************
*/


   	    +--------------------------------+
		    |				                         |
		    |	           PROJECT             |
		    |				                         |
	      +--------------------------------+


Entire code is encapsulated within sdds namespace, providing a structured and organized framework. Application have 8 classes, each of them performs the necessary functionality for the program. Status class play a crucial role in maintaining state of an object, holding description of state. Date class encapsulates year, month, and day values, contributing to efficient date-related functionalities.

To create a user-friendly interface for the system, AidMan and Menu modules have been implemented. AidMan class is responsible for managing a list of products, providing various operations such as listing items, adding items, removing items, updating quantities, sorting items, shipping items, and loading/saving data from/to file.

iProduct serves as an interface, defining essential functionalities for an item within application. Item class, a concrete implementation of iProduct. Item class represents an item in application, implementing functionalities related to tracking quantity, pricing, validate SKU, read and validate item details from input stream, loads item details from an input file stream, saves item details to an output file stream.

Extending the capabilities of Item class, Perishable class provides additional features for handling perishable items. It incorporates functionality for managing expiry dates and handling instructions, making it extension for products with limited shelf life.

  		    +--------------------------------+
		      |				                         |
		      |	            AidMan             |
		      |				                         |
	        +--------------------------------+
Class: 

    Private Members:
        char* filename: pointer to a character array representing filename
        Menu* mainMenu: pointer to instance of Menu class
        iProduct** itemList: array of pointers to objects of type iProduct

   		iProduct:  is a class 
  		iProduct*: a pointer to object of type iProduct. It can store memory address of object of type iProduct.
    		iProduct**: is pointer to pointer to an object of type iProduct.  It can store memory address of pointer to an object of type iProduct.
   		itemList: store pointers to instances of classes derived from iProduct
        int numItems: integer represents number of items

Private Methods:

    unsigned int menu(): display main menu, takes user input, and return chosen menu option.
    void save(): save data to the specified file
    void deallocate(): deallocate memory used by class members
    bool load(): load data from a file into program

Public Members:

    AidMan(const char* filename = nullptr): Constructor for AidMan class. It take parameter for filename and initialize other members.
    ~AidMan(): destructor for AidMan class, it deallocates memory used by class members.

Public Methods:

    void run(): execute main program loop, repeatedly display menu and process user input until user chooses to exit
    int list(const char* sub_desc = nullptr, bool displayPrompt = true): lists items based on a description, it returns number of items listed
    int search(int sku) const: search for item in itemList based on SKU and return it index
    void addItem(): add a new item to itemList
    void remove(int index): remove item from itemList at specified index
    void removeItem(): prompt user for item description, list items matching description and remove selected item
    void updateQuantity(): prompt user for item description, lists items matching the description and update quantity of selected item
    void sort(): sorts items in itemList based on difference between needed and available quantity
    void shipItems(): create shipping order file for items with fulfilled quantities

____________________________________________________________________________

Constructor of the AidMan class:

    AidMan::AidMan(const char* filename) : filename(nullptr), mainMenu(nullptr), itemList(nullptr), numItems(0) {
        if (filename != nullptr) {
            this->filename = new char[strlen(filename) + 1] ;
            strcpy(this->filename, filename);
        }
        const char* menuOptions = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database";
        mainMenu = new Menu(menuOptions);
        itemList = new iProduct*[sdds_max_num_items]{} ;
    }

    Constructor initialize member variables such as filename, mainMenu, itemList and numItems, if filename provided, it dynamically allocate memory for filename and copy inputed filename. It create Menu object mainMenu with predefined list of options for different operations.

new iProduct*[sdds_max_num_items]: allocate dynamic memory for array of pointers to iProduct objects. Size of the array is sdds_max_num_items(constant represent maximum number of items which is 100). This array will be used to store pointers to objects of classes derived from iProduct.

{}: this part initialize array elements to default values. Since it's an array of pointers all pointers are initialized to nullptr. itemList array store pointers to objects representing products in the system. Actual objects can be of different types derived from iProduct, such as Item or Perishable.

____________________________________________________________________________

Destructor: 

AidMan::~AidMan() {
//deallocate memory used by Menu object pointed by mainMenu
    delete mainMenu ;
//function deallocate called to perform freeing memory allocated for filename and array of iProduct pointers
    deallocate();
}

____________________________________________________________________________

AidMan::menu() function:
 	 int year, month, day ;
        sdds::ut.getSystemDate(&year, &month, &day);
//takes current system date using utility function getSystemDate. Date year, month, day are stored in variables year, month, and day
//display header for the Aid Management System with current date
  std::cout <<"Aid Management System" << std::endl;
        std::cout<< "Date: " <<year << "/" <<month << "/" << (day < 10 ? "0" : "") <<day <<std::endl;

 if (filename != nullptr) {
            std::cout<< "Data file: "<<filename <<std::endl;
            std::cout<< "---------------------------------"<<std::endl;
        } else {
            std::cout << "Data file: No file\n";
            std::cout<<"---------------------------------"<<std::endl ;
        }
//Next it check if a filename is set and display information about data file. If there is no filename it indicates that there is no file
   unsigned int choice = mainMenu->run();
//call run() method on mainMenu object, which is instance of Menu class. run will call menu in order to display options. Next, using switch construction and based on user input calls appropriate functions for each of cases. 

____________________________________________________________________________

 void AidMan::run() function represents control flow of the system, it runs loop where the user interacts with menu until user choose to exit (choice <= 0). It then display an exit message and saves the data.
    void AidMan::run() {
//declare unsigned integer variable choice to store the user menu choice 
        unsigned int choice;
//perform do-while loop that call menu() function and assign it return value to choice variable, loop continues as long as user choice is > 0
        do {
            choice = menu();
        } while (choice > 0);

        std::cout << "Exiting Program!\n";
//call save() function in order to save data 
        save() ;
    }

____________________________________________________________________________

void AidMan::deallocate() function is responsible for deallocate memory used by AidMan object 
    void AidMan::deallocate() {
//delete dynamically allocated memory for filename characters array using delete[]
        delete[] filename;
//use loop to delete each item in itemList. Each item is object derived from iProduct
        for (int i = 0; i < numItems; ++i) {
            delete itemList[i];
        }
//delete dynamically allocated memory for itemList array
        delete[] itemList;
//set filename and itemList pointers to nullptr in order to ensure that they don't point to invalid memory
        filename = nullptr ;
        itemList = nullptr ;
        numItems = 0;
    }

____________________________________________________________________________

void AidMan::save() function is responsible for saving data in the AidMan object to a file
    void AidMan::save() {
        if (filename != nullptr) {
//create an std::ofstream object named file and associates it with specified filename. Now file open for writing. 
            std::ofstream file(filename);
            if (file) {
//next, iterate through each item in itemList and call save function on each item, pass file stream as an argument. Save function of each product is responsible for writing its data to file.
                for (int i = 0; i < numItems; ++i) {
                    itemList[i]->save(file) ;
                
                }
                file << '\n';
            }
        }
    }

____________________________________________________________________________

bool AidMan::load() function initialize filename, open file for reading, reads and creates instances of iProduct derived classes based on content of the file, load data to AidMan object. 
    bool AidMan::load() {
// if filename is not set, prompt user to enter a filename
        if (filename ==nullptr) {
            std::string newFileName ;
            std::cout << "Enter file name: ";
            std::cin >> newFileName ;

//if entered filename is empty, return false
            if (newFileName.empty()) {
                return false ; 
            }
//allocate memory for filename and copy entered filename
            filename =new char[newFileName.length() + 1];
            strcpy(filename, newFileName.c_str()) ;
        }

//open file associated with filename for reading
        std::ifstream file(filename);

        if (!file) {
            std::cout<< "Failed to open " << filename << " for reading!"<< std::endl;
            std::cout<< "Would you like to create a new data file?" <<std::endl;
            std::cout <<"1- Yes!" <<std::endl;
            std::cout <<"0- Exit"<< std::endl;

            int choice;
            std::cin >>choice ;

//if user choose to create a new file, create it and return true
            if (choice == 1) {
                std::ofstream newFile(filename) ;
                return true;
            } else {
//user chooses exit, return false
                return false;
            }
        }
        
        int recordsLoaded = 0;
        numItems = 0;

 //read records from file
        while (file) {
        char recordType ;
        file >>recordType;

        char peekedChar = file.peek(); 

//check for errors in reading recordType
            if (file.fail()) {
                if (file.eof()) {
                    break ;
                } else {
                    std::cout << "Error reading record type from the file." << std::endl;
                    break;
                }
            }

//pointer product is later used to dynamically create instances of classes derived from iProduct (Item or Perishable)
        iProduct* product = nullptr;


//if recordType is 4 or 5 and next character is digit, it unget character and create instance of Item.
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

//if an instance is created, load data of it from file
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
//ignore any remaining characters in the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        return true;
    }

____________________________________________________________________________

int AidMan::list function is responsible for display a list of items ,  function iterate through items in itemList, filters items based on the sub_desc, and prompts for displaying details for a specific item(prompt is invisible for updateQty and removeItem)
    int AidMan::list(const char* sub_desc, bool displayPrompt) {
        int count = 0 ;
//check if there are items in the list
        if (numItems > 0) {
            std::cout<<" ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry"
                      <<"\n-----+-------+-------------------------------------+------+------+---------+-----------\n";
//iterate through each item in itemList
            for (int i = 0; i <numItems; ++i ) {
//check if sub_desc is nullptr or if items description contain specified substring
                if (sub_desc ==nullptr || strstr(itemList[i]->getDescription(), sub_desc) != nullptr )  {
//display information about item
                    std::cout << std::setw(4) << std::setfill(' ') <<std::right << i + 1 << " | ";
                    itemList[i]->linear(true );
                    itemList[i]->display( std::cout) ; 
                    std::cout<<std::endl;
                    ++count;
                }
            }
            std::cout<< "-----+-------+-------------------------------------+------+------+---------+-----------"<< std::endl;
        }

//display message if list empty
        if (count == 0) {
            std::cout <<"The list is empty!" <<std::endl;
        }
        if (displayPrompt) {
                std::string input;
                std::cout<< "Enter row number to display details or <ENTER> to continue:\n";
                std::cout <<"> " ;
                std::getline(std::cin, input);
            //If the user pressed Enter, return the count without further actions
                if (input.empty()) {
                    std::cout << "\n";
                    return count;
                
                }

            try {
//convert input to integer represent selected row number using string to integer function
                int rowNumber = std::stoi(input);

                if (rowNumber >= 1 && rowNumber <= count) {
                    int foundIndex = rowNumber - 1;
//display detailed information about selected item
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

____________________________________________________________________________

void AidMan::addItem() responsible for adding a new item to file.

    void AidMan::addItem() {
        if (numItems >= sdds_max_num_items) {
            std::cout << "Database full!\n" ;
            return;
        }

        int itemType ;
//display menu for item type 
        std::cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ";
//loop to handle user input for item type
        while (true) {
  //check for non-integer input which is invalid
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
//exit function if user chooses to abort
        if (itemType == 0) {
            std::cout<< "Aborted\n";
            return;
        }
//create pointer to iProduct
        iProduct* product = nullptr;

//create instance of Perishable or Item based on user choice
        if (itemType == 1) {
            product = new Perishable();
        } else if (itemType == 2) {
            product = new Item() ;
        }
//check if creation of product was successful
        if (product == nullptr) {
            std::cout << "Error creating product.\n";
            return;
        }

//read SKU from user input
        if(product->readSku(std::cin)) { 
            int sku = product->getSku();
                int index = search(sku) ;
//check if SKU already exist in system

                if (index != -1) {
                    std::cout<< "Sku: "<< sku<<" is already in the system, try updating quantity instead.\n"<<std::endl;
                    delete product;
                    return;
                }
//read information for product
            if (product->read(std::cin)) {
                std::cin.clear() ;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
                std::cout<<std::endl;
//add product to itemList
                itemList[numItems++] = product ;
            
            } else {
//if reading fail, display product information and delete instance
                product->display(std::cout);
                delete product;
            }


        }
    }

____________________________________________________________________________

void AidMan::remove(int index) allow to delete product with specified index and update inventory array.

 void AidMan::remove(int index) {
        if (index >= 0 && index < numItems) {
//retrieve product to be removed
            iProduct* removedProduct = itemList[index] ;
//fill gap left by removed item by shifting all items one position to the left. Loop complete and last element in the array will be duplicated at second one from the end position, remove last duplicated element and now array one element shorter 

            for (int i = index; i < numItems - 1; ++i) {
                itemList[i] = itemList[i + 1 ];
            }
 //delete product at specified index

            delete removedProduct;
 //update number of items in array
            --numItems;

            std::cout<< "Item removed!\n";
            return;
        } else {
            std::cout << "Invalid index. No item removed.\n";
            return;
        }
    }

____________________________________________________________________________

void AidMan::removeItem() ask for item description and lists matching item, when match found it confirm if user want to remove item of not 

	void AidMan::removeItem() {
//prompt for item description
        std::cout <<"Item description: " ;
        char desc[100];  
        std::cin.getline(desc, 100) ;

//lost items with given description without displaying prompt
        int count = list(desc,false);

//if there are items with given description
        if (count > 0) {  
            std::cout<< "Enter SKU: ";
            int skuToRemove;
            std::cin >> skuToRemove;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;

//search for index of item with specified SKU using search function
            int foundIndex = search(skuToRemove);

//item with the SKU is found
            if (foundIndex != -1 ) {
//display item that will be removed
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
//convert input to integer
                    confirmChoice = std::stoi(confirmInput);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//if user confirm removal
                    if (confirmChoice == 1) {
//delete item at found index and leave gap in array at position where was item
                        delete itemList[foundIndex] ;
//shift remaining products in array 
                        for (int i = foundIndex; i < numItems - 1; ++i) {
                            itemList[i] = itemList[ i + 1 ];
                        }
//update number of items
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

____________________________________________________________________________

void AidMan::updateQuantity() allow update quantity of items and provide options to add or reduce quantity based on user input. 

    void AidMan::updateQuantity() {
//prompt user for item description
        std::cout << "Item description: ";
        char sub_desc[100];
        std::cin.getline(sub_desc, 100);

//list items with given description without displaying prompt
        int count = list(sub_desc, false);

 	//if there are no matches with description
        if (count == 0) {
            std::cout <<"No matches found!\n";
            return;
        }

//prompt for SKU for item 
        std::cout<< "Enter SKU: ";
        int skuToUpdate;
        std::cin >>skuToUpdate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

 //search for index of item with entered SKU
        int foundIndex = search(skuToUpdate);

	//if SKU not found
        if (foundIndex == -1) {
            std::cout <<"SKU not found!\n";
            return;
        }

 //prompt user to choose type of update
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
 //add quantity to item
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

       //validate entered quantity
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
 //validate second entered quantity
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
    //reduce quantity from item
    //retrieving current quantity of product at index in the itemList array using getter getQuantity
        int currentQuantity = itemList[foundIndex]->getQuantity();

        while (true) {
            int quantityToReduce;
            std::cout <<"Quantity to reduce: ";
            std::cin >> quantityToReduce;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //validate entered quantity more than 1 and less than current quantity 
            if (quantityToReduce >= 1 && quantityToReduce<= currentQuantity) {
                itemList[foundIndex]->reduceQuantity(quantityToReduce);
                std::cout<<quantityToReduce<< " items removed!"<<std::endl;
                std::cout<<std::endl;
                break; 
            } else {
                std::cout<<"Value out of range [1<=val<=" << currentQuantity <<"]: ";
                int quantityToReduce2;
                std::cin >> quantityToReduce2;
//validate second entered quantity
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
____________________________________________________________________________

 void AidMan::sort() implements bubble sort algorithm in order to sort items in itemList array based on difference between needed and current quantity. It is move items with a greater needed quantity in the front of array.

     void AidMan::sort() {
 //loop for iterate through each item
        for (int i = 0; i < numItems - 1; ++i ) {
 //loop for comparing items and swap
            for (int j = 0; j < numItems - i - 1;++j ) {
 //calculate differences between needed and current quantity for items
                int difference1 = itemList[j]->getNeeded()- itemList[j]->getQuantity();
                int difference2 = itemList[ j + 1]->getNeeded()- itemList[ j + 1]->getQuantity();

//compare differences and swap items using temp if difference 1 is less than difference 2 
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
____________________________________________________________________________

void AidMan::shipItems() responsible for creating shipping file, removing items from inventory that have needed quantity full and update inventory.

    void AidMan::shipItems() {
   //open shippingOrder.txt file for writing
        std::ofstream shippingFile("shippingOrder.txt");
   //get current date
        int year, month, day;
        sdds::ut.getSystemDate(&year, &month, &day);
        shippingFile<< "Shipping Order, Date: "<< year<<'/'<< month << '/' << std::setw(2) << std::setfill('0')<< day <<'\n';

        shippingFile<< " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry"
                    << "\n-----+-------+-------------------------------------+------+------+---------+-----------\n";
//count shipped items
        int shippedItemsCount = 0;
//iterate through each item in itemList
        for (int i = 0; i < numItems; ) {
            int quantityNeeded = itemList[i]->getNeeded() ;
            int quantityOnHand= itemList[i]->getQuantity();

//if quantity needed match quantity on hand
            if (quantityNeeded == quantityOnHand) {
//write item details to shipping file in linear format
                shippingFile << std::setw(4)<< std::setfill(' ') << std::right << shippedItemsCount + 1<< " | ";
                itemList[i]->linear(true);
                itemList[i]->display(shippingFile);
                shippingFile <<std::endl;
//delete shipped item 
                delete itemList[i];

//shift items that in itemList array to fill the gap after removed item
                for (int j = i; j < numItems - 1; ++j) {
                    itemList[j] = itemList[j + 1] ;
                }
//update number of items in the list
                --numItems;
//increment count of shipped items
                ++shippedItemsCount ;
            } else {
  //and if quantity needed doesn't match, move to next item
                ++i ;
            }
        }
        shippingFile<< "-----+-------+-------------------------------------+------+------+---------+-----------\n";

        std::cout <<"Shipping Order for " << shippedItemsCount<<" times saved!\n";
        std::cout<<std::endl;
    }



		    +--------------------------------+
		    |				                         |
		    |	           Date                |
		    |				                         |
	      +--------------------------------+

Class Date contain private data members m_year, m_month, m_day, m_state (of type Status), m_formatted and uniqueDateValue(). Member functions are public. 

Constructors:

    Date::Date() : m_year(0), m_month(0), m_day(0), m_formatted(true) {
        sdds::ut.getSystemDate(&m_year, &m_month, &m_day) ;
    }
        Initialize Date object with current system date, use the Utils class to take current year, month, and day.
        
        Date::Date( int year, int month, int day) : m_year(year), m_month(month), m_day(day), m_formatted(true) {
        if ( !validate() ) {
            m_state= Status(3, "Invalid date value" );
            m_year =0;
            m_month = 0;
            m_day =0 ;
        }
    }
        Initialize Date object with the provided year, month, and day values. Validate input date using validate() function. If input date is invalid, sets m_state member variable with an error message.

Member Functions:

    bool validate():
        Check if current date stored in m_year, m_month, m_day is valid. Validate year, month, and day values based on calendar rules (month range and leap year for 2nd month). If date is valid, clears m_state status object and return true. If date is invalid, returns false.

    int uniqueDateValue() const:

    m_year * 372: add total number of days in all years without leap years.
    (m_year / 4) * 1: add one day for each leap year every 4 years.
    (m_year / 100) * 1: remove one day for each 100th year (unless it's also divisible by 400, making it a leap year).
    (m_year / 400) * 1: add one day every 400 years 

   Loop iterate through months from January (i = 1) to month before the current month (m_month - 1). For each month, add number of days in that month to days variable using ut.daysOfMon(i, m_year) function.

Finally, it add current day of month (m_day) to days variable.

  Calculated days variable now holds unique integer value with date. Function returns this date value.


    std::istream& read(std::istream& is):
	Reading function in date module was difficult to create because it handles various input formats, ensuring correct parsing of input string into components of year, month and day. 
Function should analyze input string, which can be in different formats, such as non-integer, "YYYYMMDD", "YYMMDD" or "MMDD". Function must also handle various types of errors, including invalid 		  characters, invalid values of year, month or day, and empty input. If errors occur, function should set error states and std::ios::failbit of input stream.

	Since function contains nested conditional statements (if and else if blocks) to determine input format, I had a lot of problems with logic in blocks and as a result, several read functions were formed that did not work as required. As a result, I managed to combine parts of these functions and make correct version of read().
Special cases, such as processing leap years and converting 2-digit years to 4-digit years, complicate function. For example, adding 2000 to two-digit years less than 20 ensures correct conversion to 4-digit years in 21st century. Function also interacts with other parts of code, such as validation function, Status class and Utils module. 

	In addition, function should check analyzed values of year, month and day to make sure that they form a valid date. This involves taking into account leap years, acceptable ranges of months (from 1 to 12) and acceptable ranges of days depending on month and year.

How it works: 

        Read date from input stream, parse input string to extract year, month, and day information, validate parsed date using validate() function. If input date is valid, update the m_year, m_month, m_day member variables and clears the m_state. If input date is invalid, sets m_state with an error message and sets std::ios::failbit flag for the input stream which means that most recent operation on stream was failed.

    std::istream& Date::read( std::istream& is ) {
        std::string input;
        is >> input ; //read string input from provided input stream is

//iterates through each character of input string. If a character is not a digit, isInvalidInput is set to true. It constructs an integer dateValue by converting characters to integer
        bool isInvalidInput = false ;
        int dateValue = 0;
        for (size_t i = 0;i < input.length(); ++i) {
            if (!isdigit(input[i])) {
                isInvalidInput = true ;
                break;
            }
            dateValue =dateValue * 10 +(input[i] - '0'); //converting to integer value
        }


//if isInvalidInput is true (indicating non-digit characters) or if input is empty, function sets m_state to indicate invalid date value, sets std::ios::failbit of input stream, and returns modified input stream to signal failure.
        if (isInvalidInput || input.empty()) {
            m_state = Status( "Invalid date value" );
            is.setstate(std::ios::failbit );
            return is;
        }

        int year, month, day;

//if dateValue is greater than or equal to 1000000, it mean the input format is "YYYYMMDD". In this case, code calculates year by dividing dateValue by 10000 removing month and day parts, calculates month by taking  remainder after dividing by 10000 and then dividing by 100 removing year and day parts, and calculates the day by taking the remainder after dividing by 100 keep only day part:
        if (dateValue>= 1000000) {
            year = dateValue / 10000 ;
            month =(dateValue / 100) % 100;
            day= dateValue % 100;
//if dateValue between 10000 and 999999, it means input format is "YYMMDD". Code calculate the year, month, and day in a similar way as previous case but also check if the parsed year is less than 15. If it is, it sets error state indicating invalid year and sets the std::ios::failbit of the input stream. Additionally, if parsed year less than 20, it adds 2000 to the year to convert it into a 4-digit year:
        } else if (dateValue>= 10000) {
            year =dateValue / 10000;
            month= (dateValue / 100) % 100;
            day = dateValue % 100;
            if (year < 15 ) {
                m_state =Status(1, "Invalid year in date");
                is.setstate(std::ios::failbit);
                return is;
            }
            year +=(year < 20 ? 0 : 2000);
//if dateValue between 100 and 9999, it means input format is "MMDD". In this case, code sets year to a test year (sdds_testYear), calculates month and day.
        } else if ( dateValue >= 100) {
            year= sdds_testYear;
            month= dateValue / 100;
            day= dateValue % 100;
        } else {
//check if the parsed year, month, and day form a valid date
            m_state =Status(2, "Invalid month in date");
            is.setstate(std::ios::failbit);
            return is;
        }

        m_year = year;
        m_month= month;
        m_day = day;
//if input date is invalid, sets the m_state status object with an appropriate error message and sets std::ios::failbit flag for input stream which means that most recent operation on the stream has failed
        if (!validate()) {
            if (m_year< 0 || m_year >9999) {
                m_state = Status(1, "Invalid year in date" );
            } else if (m_month < 1 || m_month > 12) {
                m_state = Status(2, "Invalid month in date" );
            } else {
            m_state = Status(3, "Invalid day in date" );
            }
            is.setstate(std::ios::failbit);
        } else {
            m_state.clear();
        }

        return is;
    }


    std::ostream& write(std::ostream& os) const:
        Write formatted or unformatted date to output stream os.
        Format date as either "YYYY/MM/DD" or "YYMMDD" based on m_formatted member variable.
        Returns output stream.

Comparison Operators:

    bool operator==(const Date& D) const:
        compare two Date objects based on their unique integer date values.

    bool operator!=(const Date& D) const:
        compare two Date objects based on their unique integer date values.

    bool operator<(const Date& D) const:
        check if the current Date object is less than provided Date object based on unique integer date values.

    bool operator>(const Date& D) const:
        check if the current Date object is greater than provided Date object based on unique integer date values.

    bool operator<=(const Date& D) const:
        check if current Date object is less than or equal to provided Date object based on unique integer date values.

    bool operator>=(const Date& D) const:
        check if current Date object is greater than or equal to provided Date object based on unique integer date values.

Assignment Operator:

    Date& operator=(const Date& D):
        assign Date object's member variables and m_state status object based on another Date object.
        self-assignment protection, and return modified Date object.

        +--------------------------------+
		    |				                         |
		    |	            Status             |
		    |				                         |
	      +--------------------------------+

Class Status contain private data members m_description, m_code and set(const char* description) function. Other member functions are public. 

Constructors:

    Status():
        Default constructor that initializes m_description pointer to nullptr and m_code to 0.

    Status(const char* description):
        Constructor that takes a C-string description as a parameter.
        Initializes m_code to 0 and sets m_description pointer to a dynamically allocated copy of input description.

    Status(int code, const char* description):
        Constructor that takes an integer code and a C-string description as parameters. Initialize m_code with the provided code and sets the m_description pointer to a dynamically allocated copy of input description.

    Status(const Status& other):
        Copy constructor that creates a new Status object by copying description and code from another Status object.

Assignment Operators:

    Status& operator=(const Status& other):
        Assignment operator that copy the description and code from another Status object to current object. Complete self-assignment protection and return the modified Status object.

    Status& operator=(int code):
        Assign integer code to the Status object, set m_description and m_code based on input code (error messages for specific codes).
        Return the modified Status object.

    Status& operator=(const char* description):
        Assign description to Status object, set m_description and m_code based on input description.
        Return modified Status object.

Conversion Operators:

    operator int() const:
        Convert Status object to an integer, return m_code member variable.

    operator const char*() const:
        Convert Status object to a C-string, return m_description pointer or an empty string if m_description is nullptr.

    operator bool() const:
        Convert Status object to a boolean value.
        Return true if m_code is 0 and m_description is nullptr, indicating no errors, false otherwise.

Destructor:

    ~Status():
       Call clear() that deallocates dynamically allocated memory for m_description.

Friend Function:

    friend std::ostream& operator<<(std::ostream& os, const Status& status):
        Overloaded << operator allow print Status objects to output stream.
        Print status description and code to output stream, handling different cases (no description, no code, both here).

 		    +--------------------------------+
		    |				                         |
		    |	             Utils             |
		    |				                         |
	      +--------------------------------+

Class Utils contain private data member m_testMode. Member functions are public. 


 Member Functions:

    void getSystemDate(int* year, int* mon, int* day):
        Take pointers to integers as parameters (year, mon, and day).
        Retrieve current system date and stores the year, month, and day values.
        if program in test mode, it use predefined test date values.

    int daysOfMon(int mon, int year):
        Take integers mon (month) and year as parameters.
        Calculate and returns the number of days in specified month of the given year, handling leap years.

    void testMode(bool testmode = true):
        Take a boolean parameter testmode (default is true).
        Set test mode of the Utils class to provided value.
        When in test mode, getSystemDate function return predefined test date values
    

		    +--------------------------------+
		    |				                         |
		    |	           Menu                |
		    |				                         |
	      +--------------------------------+
Class Menu have private data members content of the menu and the number of options available. Member functions are public. 

Menu::Menu(const char* options): constructor for Menu class. take string of menu options and initialize menuContent, count number of options based on newlines. Validate menu by check number of options and whether menuContent is nullptr.

Menu::~Menu(): destructor for the Menu class. Delete allocated memory for menuContent.

unsigned int Menu::run() const: display menu options and return user choice. Accept user input, validate it, and return user choice as unsigned integer.

Menu::run() in more details: 

  unsigned int Menu::run() const {
	//if there are no menu options, return 0
        if (numOptions == 0) {
            return 0;
        }

	//store user input and choice for store numeric value of input 
        std::string input;
        int choice;


	//display menu content with "Exit" option and prompt user for input.
        while (true) {
            std::cout<< menuContent<< std::endl;
            std::cout<< "---------------------------------"<<std::endl;
            std::cout <<"0- Exit" <<std::endl;
            std::cout<< "> " ;

	    //read a line of input from user
            std::getline( std::cin, input );

	    //check if input consists only of digits. If not, it prompt user to retry and return choice
            bool isValidInput = true ;
	    //in order to match type returned by input.length() I used size_t i = 0: 
            for (size_t i =0; i <input.length(); ++i ) {
		//checks if character at index i in string input is not digit
                if (!isdigit( input[i] ) ) { 
                std::cout << "Invalid Integer, retry: ";
                std::getline(std::cin, input ) ;
                choice = std::stoi(input);
                    return static_cast<unsigned int>(choice) ;
                }
            }

            if (isValidInput) {
		//convert valid input to integer using "string to integer"
                choice = std::stoi(input);

		//if choice is within valid range, return choice
                if (choice >=1 && choice<= numOptions ) {
                    return static_cast<unsigned int>(choice) ;
		//if choice is 0 return choice
                } else if ( choice == 0) {
                    return static_cast<unsigned int>(choice) ;
                } else {
		//if choice is out of range, it prompts user to retry and return choice
                    std::cout<<"Value out of range [0<=val<=" <<numOptions << "]: " ;
                    std::getline( std::cin, input);
                    choice =std::stoi(input);
                    return static_cast<unsigned int>(choice) ;
                }
            }
        }
    }

		    +--------------------------------+
		    |				                         |
		    |	            iProduct           |
		    |				                         |
	      +--------------------------------+

iProduct is an abstract base class with pure virtual functions, defining an interface for products.
It includes functions for reading and modify product information, perform operations on quantities, and display product details.

	      +--------------------------------+
		    |				                         |
		    |	             Item              |
		    |				                         |
	      +--------------------------------+
Item is a concrete class that contain implementation of iProduct virtual functions.It include functions to read, display and modify information about items. Clear function is used to clean dynamically allocated memory and reset the Item. Item have private data members SKU, price, quantity on hand, needed quantity, description, and flags indicating whether the item is linear. Protected data member m_status of type Status. All member functions are public. 


Default constructor 
Item::Item() : m_status(), m_sku(0), m_price(0.0), m_quantityOnHand(0), m_neededQuantity(0), m_description(nullptr), m_linearFlag(false) , m_defaultLinearFlag(false) {
    } Initialize member variables to default values.


Parameterized constructor 
Item::Item(int sku, const char* desc, double price, int qtyNeeded, int qtyOnHand)
        : m_status(desc) , m_sku(sku), m_price(price), m_quantityOnHand(qtyOnHand), m_neededQuantity(qtyNeeded), m_description(nullptr) , m_linearFlag(false), m_defaultLinearFlag(false) {
    }Initialize member variables with provided values.
  

Destructor  
Item::~Item() {
        clear();
    } Call clear() function to release dynamically allocated memory.


Item::Item(const Item& other) {
        *this = other;
    }create copy of another Item object.


Copy assignment operator 
Item& Item::operator=(const Item& other) {
        if (this != &other) {
            clear();
            m_sku =other.m_sku;
            m_price= other.m_price ;
            m_quantityOnHand =other.m_quantityOnHand;
            m_neededQuantity= other.m_neededQuantity;
            m_linearFlag =other.m_linearFlag ;
            m_status = other.m_status;
            m_description = new char[ strlen(other.m_description) + 1 ];
            strcpy(m_description, other.m_description) ;
        }
        return *this;
    }do deep copy of another Item object.


Quantity subtraction 
int Item::operator-=(int qty) {
        if (qty > 0) {
            m_quantityOnHand -= qty;
            if (m_quantityOnHand < 0 ) {
                m_quantityOnHand = 0;
            }
        }
        return m_quantityOnHand ;
    }subtract specified quantity from on-hand quantity.
     Ensure on-hand quantity do not go below zero.


Quantity addition  
int Item::operator+=(int qty) {
        if (qty > 0) {
            m_quantityOnHand += qty ;
        }
        return m_quantityOnHand;
    }Add specified quantity to on-hand quantity.


Conversion to double 
Item::operator double() const {
        return m_price;
    }Convert object to double (return price).


Conversion to bool 
Item::operator bool() const {
        return m_status ;
    }Convert object to bool (return status).


Quantity needed getter
int Item::qtyNeeded() const {
        return m_neededQuantity;
    }Return quantity needed.


Quantity getter     
int Item::qty() const {
        return m_quantityOnHand;
    }Return on-hand quantity.


Linear setter    
void Item::linear(bool isLinear) {
        m_linearFlag = isLinear ;
    }Set linear flag to control display format.


Save to file operator  
std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (m_status) {
            ofstr <<"\n"<< m_sku<<"\t" <<m_description<< "\t" <<m_quantityOnHand<< "\t" <<m_neededQuantity<<"\t";
            ofstr.setf(std::ios::fixed) ;
            ofstr.precision(2);
            ofstr << m_price ;
        }
        return ofstr;
    }Write item information to output file stream in specific format with tab separators.


Load from file operator  
std::ifstream& Item::load(std::ifstream& ifstr) {
        delete[] m_description;
        m_description = nullptr;
        char tempDesc[2000];
        ifstr >> m_sku;
        ifstr.ignore(); 
        ifstr.getline(tempDesc, 2000, '\t'); 
        ifstr >> m_quantityOnHand >> m_neededQuantity >> m_price;
        
        if (ifstr.fail()) {
            m_status = "Input file stream read failed!";
        } else {
            m_description = new char[strlen(tempDesc) + 1];
            strcpy(m_description, tempDesc);
            if (ifstr.peek() == '\n') {
                ifstr.ignore();
            }
        }
        
        return ifstr;
    }Read item information from input file stream. It is delete any existing m_description data to avoid memory leaks. Declare temporary array tempDesc to store description , Read SKU, description, quantity on hand, needed quantity and price from input file stream. Check if fs is fail state. If yes, it set error message in m_status member. If reading is successful, allocate memory for m_description member, copy description data. Check newline character in file stream and ignore it(for case where next item in file starts on new line). After it return input file stream. Returninf stream allow multiple input operations.


Display operator  
std::ostream& Item::display(std::ostream& ostr) const {
        if (m_status) {
            if (m_linearFlag) {
                std::string truncatedDescription = m_description;
                if (truncatedDescription.length() > 35) {
                    truncatedDescription = truncatedDescription.substr(0, 35);
                }

                ostr << std::setw(5) << m_sku << " | " << std::setw(35) << std::left << truncatedDescription
                    << " | " << std::setw(4) << std::right << m_quantityOnHand << " | " << std::setw(4)  << std::right << m_neededQuantity
                    << " | " << std::setw(7) << std::fixed << std::setprecision(2)<< std::right << m_price << " |";
            } else {
                ostr << "AMA Item:" << std::endl;
                ostr << m_sku << ": " << m_description << std::endl;
                ostr << "Quantity Needed: " << m_neededQuantity << std::endl;
                ostr << "Quantity Available: " << m_quantityOnHand << std::endl;
                ostr << "Unit Price: $" << std::fixed << std::setprecision(2) << m_price << std::endl;
                ostr << "Needed Purchase Fund: $" << std::fixed << std::setprecision(2) << m_price * (m_neededQuantity - m_quantityOnHand) << std::endl;
            }
        } else {
            ostr << m_status;
        }
        return ostr;
    }Output item information to an output stream based on linear flag.


SKU read
int Item::readSku(std::istream& istr) {
        bool firstAttempt = true;
            int skuValue;
        while (true) {
            if (firstAttempt ) {
                std::cout << "SKU: ";
            }
            if (!(istr >> skuValue)) {
                istr.clear();
                std::string temp;
                getline(istr, temp); 
                std::cout << "Invalid Integer, retry: ";
                firstAttempt = false;
            } else if (skuValue < 40000 || skuValue > 99999) {
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Value out of range [40000<=val<=99999]: ";
                firstAttempt = false;
                
            } else {
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    m_sku = skuValue;
                break;
            }
        }
        return m_sku; 
    } It read SKU from input stream and validating input range.To clear input buffer after using getline to read input string, in order to remove remaining characters (including the new line) before further input operations, I used istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n').


Item read 
 std::istream& Item::read(std::istream& istr)  {  
    std::cout << "AMA Item:" << std::endl ;
    std::cout << "SKU: " << m_sku << std::endl;
    std::cout << "Description: ";

    char tempDesc[2000] ;
    int tempQtyNeeded, tempQtyOnHand;
    double tempPrice ;

    //Use getline to read description of item (up to 2000 characters) from input stream. 
    istr.getline(tempDesc, 2000, '\n');
    bool firstAttempt = true;

    //Prompt for quantity needed.
    //Handle cases whereinput is not valid integer or falls outside specified range [1, 9999]. Repeat prompt until valid input.
    while (true) {
        if (firstAttempt) {
            std::cout << "Quantity Needed: " ;
        }
        if (!(istr >> tempQtyNeeded)) {
            // Handle non-integer input
            istr.clear(); // Clear error flag
            std::string tempQN ;
            getline(istr, tempQN); // Consume the invalid input
            std::cout << "Invalid Integer, retry: ";
            firstAttempt = false; // Set to false 
        } else if (istr.fail() || tempQtyNeeded < 1 || tempQtyNeeded > 9999) {
            // Handle out of range input
            istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume invalid input
            std::cout << "Value out of range [1<=val<=9999]: " ;
            firstAttempt = false ;
        } else {
            // Valid input; consume the newline character and exit the loop
            istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    firstAttempt = true;

    //Prompt for quantity on hand.
    //Handle cases where input is not valid int, fall outside specified range [0, Quantity Needed], or is greater than Quantity Needed. Repeat prompt until valid input.

    while (true) {
        if (firstAttempt) {
            std::cout << "Quantity On Hand: ";
        }
        if (!(istr >> tempQtyOnHand)) {
            // Handle non-integer input
            istr.clear(); // Clear error flag
            std::string tempQOH ;
            getline(istr, tempQOH); // Consume invalid input
            std::cout << "Invalid Integer, retry: ";
            firstAttempt = false;
        } else if (istr.fail() || tempQtyOnHand < 0 || tempQtyOnHand > tempQtyNeeded) {
            // Handle out of range input
            istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume invalid input
            std::cout << "Value out of range [0<=val<=" << tempQtyNeeded << "]: ";
            firstAttempt = false; 
        } else {
            // Valid input; consume newline character and exit loop
            istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break ;
        }
    }

    firstAttempt = true;

    //Read and validate Unit Price
    //Prompt for unit price.
    //Handle cases where input is not a valid floating-point number or fall outside specified range [0.00, 9999.00].
    //Repeat prompt until valid input is received.
    while (true) {
        if (firstAttempt) {
            std::cout << "Unit Price: $";
        }
        if (!(istr >> tempPrice)) {
            // Handle non-floating-point input
            istr.clear(); // Clear error flag
            std::string tempPriceStr ;
            getline(istr, tempPriceStr); // Consume invalid input
            std::cout << "Invalid number, retry: " ;
            firstAttempt = false;
        } else if (istr.fail() || tempPrice < 0.0 || tempPrice > 9999.0) {
            // Handle out-of-range input
            istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume invalid input
            std::cout << "Value out of range [0.00<=val<=9999.00]: ";
            firstAttempt = false ;
        } else {
            // Valid input; consume newline character and exit the loop
            istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        } 
    }

    // Set member variables with validated values
    //Allocate memory frog description and copy input.
    //Set other member variables with validated input.

    m_description = new char[strlen(tempDesc) + 1];
    strcpy(m_description, tempDesc);
    m_neededQuantity =tempQtyNeeded;
    m_quantityOnHand = tempQtyOnHand;
    m_price= tempPrice;

    // Clear status state
    m_status.clear();

    //return input stream 
    return istr;
}Read item information from input stream, prompting for input.

 
Equal operator bool 
Item::operator==(int sku) const {
        return m_sku == sku ;
    } Check if SKU of item is equal to provided SKU.


bool Item::operator==(const char* description) const {
        return (m_description && description && strstr( m_description, description) != nullptr ) ;
    }Check if description of item contain provided substring.


Clear function    
void Item::clear() {
        delete[] m_description;
        m_description= nullptr ;
        m_status =0;
        m_sku = 0 ;
        m_price= 0.0 ;
        m_quantityOnHand = 0;
        m_neededQuantity = 0 ;
        m_linearFlag= m_defaultLinearFlag; 
    }Release dynamically allocated memory and reset member variables.




		    +--------------------------------+
		    |				                         |
		    |	          Perishable           |
		    |				                         |
	      +--------------------------------+

In this part of project was created Perishable class which have public member functions(some of them override virtual functions from base class Item). Also it have private data members Date m_expiry, and 
char* m_handlingInstructions. m_expiry is object of Date and m_handlingInstructions is pointer to character array.
This part of the project seemed to me one of the most interesting because Perishable class extends Item class and add additional functionality for handling perishable items with expiry dates and handling instructions. 

This is default constructor for Perishable class. It call Item default constructor to initialize Item details and set m_handlingInstructions to nullptr: 

	Perishable::Perishable() : Item(), m_handlingInstructions(nullptr) {
	}

Copy constructor copy Item information using Item copy constructor, then copy m_expiry and m_handlingInstructions members of Perishable class: 

	Perishable::Perishable(const Perishable& other) : Item(other) {
		m_expiry = other.m_expiry ;
		if (other.m_handlingInstructions) {
			m_handlingInstructions = new char[strlen(other.m_handlingInstructions) + 1];
			strcpy(m_handlingInstructions, other.m_handlingInstructions) ;
		}
		else {
			m_handlingInstructions = nullptr;
		}
	}

Copy assignment operator call Item copy assignment operator, then copy m_expiry and m_handlingInstructions of Perishable class:

	Perishable& Perishable::operator=(const Perishable& other) {
		if (this != &other) {
			Item::operator=(other); 
			m_expiry = other.m_expiry ;
			if (m_handlingInstructions)
				delete[] m_handlingInstructions;
			if (other.m_handlingInstructions) {
				m_handlingInstructions = new char[strlen(other.m_handlingInstructions) + 1];
				strcpy(m_handlingInstructions, other.m_handlingInstructions);
			} else {
				m_handlingInstructions =nullptr;
			}
		}
		return *this;
	}


Destructor delete dynamically allocated memory for m_handlingInstructions if it is not nullptr: 

	Perishable::~Perishable() {
		if (m_handlingInstructions)
		delete[] m_handlingInstructions;
	}

Expiry return reference to m_expiry member:
	const Date& Perishable::expiry() const {
		return m_expiry ;
	}

isClear call Item isClear() function which return bool value based on m_quantityOnHand (if it is non exists, thats mean that object is clear): 

	bool Perishable::isClear() const {
		return Item::isClear();	
	}


readSku read SKU from input stream:
int Perishable::readSku(std::istream& istr) {
		int skuValue;
		std::cout << "SKU: " ;
		while (true) {
			istr >>skuValue;
			if (istr.fail() || skuValue <10000 || skuValue > 39999) {
				istr.clear();
				istr.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				std::cout<< "Value out of range [10000<=val<=39999]: " ;
			} else {
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				setSku(skuValue) ;
				break;
			}
		}
		return getSku();

	}

Save function is responsible for saving data of Perishable objects to output file stream, including data from base class Item and data for perishable items which is handling instructions and expiry date.

std::ofstream& Perishable::save(std::ofstream& ofstr) const {
		Item::save(ofstr); // call save function of base class Item
		ofstr << '\t'; //add tab

		if (m_handlingInstructions) {
			ofstr << m_handlingInstructions ; //save instructions
		}
		ofstr << '\t'; //add tab
		ofstr << std::setw(2) <<std::setfill('0') <<m_expiry.getYear() % 100; //save last two digits of year of expiry
		ofstr <<std::setw(2)<< std::setfill('0') <<m_expiry.getMonth() ;//save month of expiry
		ofstr << std::setw(2)<< std::setfill('0') << m_expiry.getDay();//save day of expiry
	
		return ofstr;
	}




Load function read data for Perishable object from input file stream, including details from base class Item and handling instructions and expiry date for perishable items. 

std::ifstream& Perishable::load(std::ifstream& ifstr) {
		Item::load(ifstr); //call load function of base class Item

		if (m_handlingInstructions) { // check if m_handlingInstructions is not nullptr. If it is not nullptr, that mean there were previous handling instructions that need be cleared before reading new ones.
			delete[] m_handlingInstructions;
			m_handlingInstructions = nullptr ;
		}

		if (ifstr.fail()) { //check if there was a fail in input file stream. If yes, it set error message in m_status and returs ifstream object.
			m_status= "Input file stream read (perishable) failed!";
			return ifstr;
		}

		ifstr.ignore(std::numeric_limits<std::streamsize>::max(), '\t') ; //ignore characters in input file stream until next tab character.

		char tempHandlingInstructions[1000]; 
		ifstr.getline(tempHandlingInstructions, 1000, '\t'); //read handling instructions from input file stream until next tab character, and store instructions in a temporary character array tempHandlingInstructions.

//if temporary handling instructions array is not empty, allocate memory for m_handlingInstructions and copy instructions into it
		if (tempHandlingInstructions[0] !='\0' ) {
			m_handlingInstructions = new char[strlen(tempHandlingInstructions) + 1] ;
			strcpy(m_handlingInstructions, tempHandlingInstructions) ;
		}

		ifstr >>m_expiry; //read expiry date from input file stream
		if (ifstr.fail()) { //if there was a fail in reading expiry date. If yes, it set error message in m_status.
			m_status = "Input file stream read (perishable) failed!";
		}
		return ifstr;
	}


Display function output information about a Perishable item to output stream. Format depend on whether item should be displayed in linear format or with additional details.

std::ostream& Perishable::display(std::ostream& os) const {
		if (isClear() ) { //check if isClear function returns true
			if ( Item::isLinear()) { //check if the item should be displayed in linear format
				Item::display(os); //call display function of base class Item 
				os << (m_handlingInstructions ? '*' : ' ') <<m_expiry ; //after print expiry date.display * if there are handling instructions, or ' ' if there are none 
			} else { //isLinear is false, display additional details
				os <<"Perishable "; //label for perishable item 
				Item::display(os) ; //call display function of base class Item
				os <<"Expiry date: " << m_expiry ; //display expiry date
				if (m_handlingInstructions) { 
					os << std::endl <<"Handling Instructions: "<< m_handlingInstructions;
				} //display handling instructions if they exist
				os <<std::endl;
			}
		} else {
			os<< m_status; 
		}
		return os;
	}



Read function in Perishable class responsible for reading input to Perishable class from input stream. It builds on the read function inherited from class Item	

	std::istream& Perishable::read(std::istream& is) {
		Item::read(is); // call read function of Item

		if (m_handlingInstructions) { // delete any existing handling instructions
			delete[] m_handlingInstructions ;
			m_handlingInstructions =nullptr;
		}

		std::cout << "Expiry date (YYMMDD): ";
		is>> m_expiry;
		is.ignore(); 

		std::cout <<"Handling Instructions, ENTER to skip: " ;
		char temp[1000];
		is.peek();

		if (is && is.peek() !='\n') { //check if next character is newline
			is.getline(temp, 1000, '\n' ); //read handling instructions and allocate memory for it
			m_handlingInstructions = new char[ strlen(temp) + 1 ];
			strcpy(m_handlingInstructions, temp ) ;
		}
		if (is.fail()) { //fail in reading
			m_status = "Perishable console date entry failed!";
		}
		return is;
	}


____________________________________________________________________________

		    +--------------------------------+
		    |				                         |
		    | OOP244 NOTES (2nd part of sem) |
		    |				                         |
	      +--------------------------------+

Classes allows to create custom data types that combine data and functions that work with that data. Data and functions within a class are called members. Class members are accessed through the member selection operator. (or through the -> operator if access the element through a pointer).

-> (Member Access Operator for Pointers) is used to access a member of an object that is referenced by a pointer.
. (Member Access Operator for Objects) is used to access a member of an object directly.
:: (Scope Resolution Operator) is used to access members (variables or functions) of a class or namespace.

Access specifiers allows to specify who will have access to class members. Everyone has access to the public members of the class. Only other members of the class have access to private members of the class.  By default, all members of the class are private, and all members of the structure are public.

Encapsulation is when all member variables of a class are private and cannot be accessed directly. 

A constructor is a special type of class method that allows to initialize class objects. A constructor that does not accept any parameters (or has all the default parameters) is called a default constructor. The default constructor is executed if no initialization values are provided by the user. 

The initialization list of class members allows to initialize member variables from the constructor (instead of assigning values to member variables).

A destructor is a special type of class method that is used to clean up a class. It is in destructors that dynamically allocated memory should be freed.

All methods have a hidden *this pointer that points to the current object of the class (which is currently in use). 

 Class definitions are in the header file with the same name as the class, and class method definitions are in the file.cpp with the same name as the class.

Class methods can be const if they do not modify class data. Constant class objects can only call constant class methods.

Friend functions are external functions that have access to private members of a class.

Friend classes are classes in which all methods are friend functions.

Operator overloading is a specific function overload that allows operators to be used with objects of custom classes. When overloading operators, their functionality and purpose should be kept as close as possible to their original use.

Operators can be overloaded through regular functions, through friendly functions, and through class methods. 

Overloading of assignment operators (=) is performed through class methods in the same way as overloading of unary operators and overloading of binary operators that change their left operand.

Overloading of binary operators that do not change their left operand through regular or friendly functions.

Overloading of data type conversion operations is used to explicitly or implicitly convert objects of a user class to another data type.

A copy constructor is a special type of constructor used to initialize an object with another object of the same class. Copy constructors are used in direct/uniform initialization of objects by objects of the same type, copying initialization and when passing or returning parameters by value.

The assignment operator can be overloaded to perform assignment operations on class objects. Overloaded assignment operators should always have a self-assignment check.

By default, the assignment operator and copy constructor provided by the compiler perform immediate initialization/assignment, which is a shallow copy. If there are dynamically allocated members in the class, then this will lead to problems (since several objects can point to the same allocated memory). In this case, need to explicitly define your copy constructor and overload the assignment operator to perform deep copying.

Inheritance allows you to model the relationship between two objects. The object that inherits is called a child class. The object that is inherited is called the parent class.

When inheriting, the child class inherits all the members of the parent class.

When initializing objects of a child class, the parent part of the object is built first, and then the child part of the object. First, memory is allocated for the object of the child class (a sufficient portion for the two parts that make up the object: the parent and the child). The constructor of the child class is called. The parent part is being built using the constructor of the parent class. If no constructor is specified, the default constructor of the parent class is used.
The initialization list of the child class initializes the members of the child class.
The constructor body of the child class is executed.

Memory release (destruction) occurs in the opposite order of construction: from child classes to parent classes.

The C++ language has 3 access specifiers: public, private and protected. The protected specifier is used to allow access to members of friendly classes/functions and child classes, all other objects are denied access.

There are 3 types of inheritance: public, private and protected. The most common type of inheritance is public.

Child classes can modify the methods of the parent class, add their own functionality, change the access specifier of inherited members, or even hide the methods of the parent class. 

A virtual function is a special type of function that, when accessed, calls the most childlike method (override) that exists between the parent and child classes. To be considered an override, a method of a child class must have the same signature and return type as the virtual function of the parent class. 

The override modifier is used to designate a method as an override.

The final modifier prohibits redefining a virtual function or inheriting a specific class.

Using virtual functions, it is necessary to use a virtual destructor in the parent class so that, if the pointer to the parent class is deleted, the corresponding destructor is called.

A virtual function can be made a pure virtual/abstract function by adding = 0 to the end of its prototype. A class containing a pure virtual function is called an abstract class. Abstract class objects cannot be created. A class that inherits pure virtual functions must provide its own overrides of these functions, or it will also be considered abstract. Pure virtual functions may have a body (a definition written separately), but they are still considered abstract functions.

An interface is a class without member variables, all methods of which are pure virtual functions.

A virtual base class is a parent class whose object is shared by all child classes.

When assigning an object of a child class to an object of a parent class, only the parent part of the copied object is copied to the object of the parent class, the child part of the copied object is cut off. 

Dynamic casting is used to convert the pointer of the parent class to the pointer of the child class. This is called down-casting. If the conversion failed, a null pointer is returned.

Templates allows to write a single version of a function or class that will work with different types of data. 

All function or class templates must start with the template keyword and the declaration of template parameters. The declaration of template parameters specifies type parameters and non-type parameters.

The template type parameter is a parameter that is responsible for the types of data that the template will work with.

The non–type parameter can be a variable, for example, char, bool, int, long, short, pointer/reference to a function or to a method/object of a class.

Separating the definition of class templates and its methods into different files does not work as with regular classes — you cannot put the definition of a class template in a header file, and the definition of method templates of this class in a separate .cpp file.
