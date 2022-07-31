#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "../Header Files/fileReadManip.h"
#include <algorithm>


class customers{
protected:
    std::string foreName;
    std::string Surname;
    std::string Email;
    std::string SecretQuestion;
    std::string SecretQuestionAnswer;
    float AmountInAccount;
    float AmountInDebt;
    float Overdraft;
    bool Premium;
    int ID;
    std::string Password;

public:
    customers(std::vector<std::string> customerDetails) {   
        foreName = customerDetails[0];
        Surname = customerDetails[1];
        Email = customerDetails[2];
        SecretQuestion = customerDetails[3];
        SecretQuestionAnswer = customerDetails[4];
        AmountInAccount = std::stod(customerDetails[5]);
        AmountInDebt = std::stod(customerDetails[6]);
        Overdraft = std::stod(customerDetails[7]);
        if (customerDetails[8]=="TRUE")
            Premium = true;
        else 
            Premium = false;
        ID = std::stoi(customerDetails[9]);
        Password = customerDetails[10];
        
    }
    int getId(){
        return ID;
    }

    std::string getName(){
        return foreName + " " + Surname;
    }

    std::string getPW(){
        return Password;
    }
    
};


// struct userDeposit  
// {  
//     std::string name;  
//     int depositAmount;
// };

int main() {
    std::string fileName = "../Data Files/bankDetails.csv";
    std::vector<std::vector<std::string>> fileContent =  readFile(fileName);

    fileContent.erase(fileContent.begin()); // removing the headers from the file

    std::vector<customers> customerClasses;
    std::vector<int> allUsers;

    for ( int i = 0; i < fileContent.size(); i++) {

        // std::string customerName = fileContent[i][0];
        customers currentCustomerClass = customers(fileContent[i]);
        customerClasses.push_back(currentCustomerClass);
        allUsers.push_back(std::stoi(fileContent[i][9]));
        // namesPointerMap.insert (std::make_pair(customerName, pObj) );
    }
    // for (int i = 0; i <customerClasses.size();i++) {
    //     std::cout << allUsers[i] << std::endl;
    // }
    int userID;

    bool IDFound = false;
    int i = 1;
    std::cout << "Hello user, please enter your ID: "; // asking for user ID
    std::cin >> userID ; // storing user ID
    if (std::count(allUsers.begin(), allUsers.end(), userID)) {  // checking user ID is in database
            IDFound = true;
        }
    else {
        std::cout << "Error: incorrect user ID" << "\n" << std::endl;
        };

    while (IDFound == false) {
            i++;
            if (i == 4) 
            { // ending the main script if the user inputs incorrect IDs 3 times
                std::cout << "Error: all attempts used" << std::endl;
                return 0;
            }

            std::cout << "Attempt number: " << i << "\n" << std::endl;
            std::cout << "Please enter your ID: "; // asking for user ID
            std::cin >> userID ; // storing user ID
            if (std::count(allUsers.begin(), allUsers.end(), userID)) // checking user ID is in database
            {  
                IDFound = true;
            }

        }
    

    customers* userClassPtr = NULL;
    while (userClassPtr == NULL) {
        for(int i = 0; i < customerClasses.size(); i++)
        {
            if(customerClasses[i].getId() == userID)
            {
               userClassPtr = &customerClasses[i];
            }
            
        };
    };
    std::string passwordEnt;
    std::string password = userClassPtr->getPW(); // saving the users actual password
    std::cout << "Welcome " << userClassPtr->getName() << "\nPlease enter your password: " <<std::endl; // asking for the user to enter a password
    std::cin >> passwordEnt; // saving the users input

    if(passwordEnt!=password) 
    {             // checking if the users password is correct
        std::cout << "Error: incorrect password" << std::endl;
        while(password != userClassPtr->getPW())
            {
                std::cout << "Welcome " << userClassPtr->getName() << "\nPlease enter your password: " << std::endl;

            }
    }
    

    



    
    return 0;
}