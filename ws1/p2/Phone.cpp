/*
*****************************************************************************
                          OOP244 Workshop - #1 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NCC
Date       : 2023.09.12
*****************************************************************************
*/

#include <iostream>
#include <cstdio>
#include <cstring>

#include "Phone.h"
#include "cStrTools.h"

using namespace std;

namespace sdds {

    void phoneDir(const char* programTitle, const char* fileName) {
        //cout <<"-------------------------------------------------------"<< endl;
        cout <<programTitle << " phone direcotry search"<< endl;
        cout <<"-------------------------------------------------------"<< endl;

        FILE* file = fopen(fileName, "r");
        if (!file) {
            cout <<fileName << " file not found!" << endl;
            cout << "Thank you for using " << programTitle << " directory."<< endl;
            return;
        }

        PhoneRecord records[maxRecords];
        int recordCount = 0;
        while (recordCount < maxRecords){
            int result=fscanf(file, "%[^\t]\t%s\t%s\t%s\n",
                records[recordCount].name, records[recordCount].areaCode, records[recordCount].prefix, records[recordCount].number);
            if (result != 4) {
                break;
            }
            recordCount++;
        }

        char partialName[51];
        cout << "Enter a partial name to search (no spaces) or enter '!' to exit" << endl;
        cout << "> ";

        while (cin >> partialName) {
            if (partialName[0] == '!'){
                break;
            }

           

            for (int i = 0; i < recordCount; i++){
            char lowercaseName[51];
            strCpy(lowercaseName, records[i].name);

            toLowerCaseAndCopy(lowercaseName, lowercaseName);
            toLowerCaseAndCopy(partialName, partialName);
         
                if (strStr(lowercaseName, partialName) != nullptr) {
                    cout << records[i].name << ": (" << records[i].areaCode << ") " << records[i].prefix << "-" << records[i].number << endl;
                }
            }
            cout << "Enter a partial name to search (no spaces) or enter '!' to exit" << endl;
            cout << "> ";  
        }

        fclose(file);
        cout << "Thank you for using " << programTitle << " directory." << endl;
    }

}

