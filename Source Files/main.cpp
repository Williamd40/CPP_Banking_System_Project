#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "../Header Files/fileReadManip.h"
#include <algorithm>
#include <unistd.h>

class customers{
protected:
    std::string foreName;
    std::string Surname;
    std::string Email;
    std::string SecretQuestion;
    std::string SecretQuestionAnswer;
    float AmountInAccount;
    float AmountInDebt;
    int Overdraft;
    bool Premium;
    int ID;
    std::string Password;

public:
    // constructor for the customer class
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
    ~customers() 
    {  // destructor
    }

    // destructor for the customer class
    // ~customers(delete[]); 
    int getId()
    {
        return ID;
    }

    std::string getName() 
    {
        return foreName + " " + Surname;
    }

    std::string getPW()
    {
        return Password;
    }

    float getBall()
    {
        return AmountInAccount;
    }

    float getDebt()
    {
        return AmountInDebt;
    }

    void makeDeposit(float* amountIn)
    {
        AmountInAccount+=*amountIn;
        printf("Your new balance is: %f", AmountInAccount);
    }
    bool isPremium()
    {
        if (Premium == true) {
            std::cout << "You are premium!" << std::endl;
            return true;
        }
        else
            std::cout << "You are not premium!" << std::endl;
            return false;
    }

    void becomePremium()
    {
        if (AmountInAccount>200) 
        {
            AmountInAccount-=200;
            Premium = true;
            std::cout << "Congratulations " << getName() << ". You are now a premium member!\n" << std::endl;
        }
        else
        {
            printf("Error: not enough money in account.");
        }
    }
    
};

int main() {
    std::ios::sync_with_stdio(false);
    std::string fileName = "../Data Files/bankDetails.csv";
    std::vector<std::vector<std::string>> fileContent =  readFile(fileName);

    fileContent.erase(fileContent.begin()); // removing the headers from the file

    std::vector<customers> customerClasses;
    std::vector<int> allUsers;

    for ( int i = 0; i < fileContent.size(); i++) {
        customers currentCustomerClass = customers(fileContent[i]);
        customerClasses.push_back(currentCustomerClass);
        allUsers.push_back(std::stoi(fileContent[i][9]));
    }

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
            while(std::cin.fail()) { // while loop in case user input != int type
                i++;
                if (i == 5) 
                { // ending the main script if the user inputs incorrect IDs 3 times
                    std::cout << "\nError: all attempts used" << std::endl;
                    return 0;
                }
                std::cout << "Error: invalid input" << std::endl;
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> userID;
            }
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
    const std::string userName = userClassPtr->getName();
    std::cout << "Welcome " << userName << "\nPlease enter your password: " <<std::endl; // asking for the user to enter a password
    std::cin >> passwordEnt; // saving the users input

    if(passwordEnt!=password) 
    {             // checking if the users password is correct
        int i = 1;
        std::cout << "Error: incorrect password" << std::endl;
        while(passwordEnt != password)
            {
                if(i == 3){
                    std::cout <<"\nError: too many password attempts. Please wait." << std::endl;
                    sleep(5);
                    i=0;
                }
                std::cout <<"\nPlease enter your password: " << std::endl;
                std::cin >> passwordEnt; // saving the users input
                i++;
            }
    }

    std::cout << "Thank you " << userName << ".\nWhat are you doing today?" << std::endl;
    printf ("1)Check Balance\n2)Check Debt\n3)Make a deposit \n4)Check Overdraft\n5)Check if Premium\n6)Change Password\n7)Change Secret Question and Answer\n8)Logout\n");
    int userChoice;
    bool userDone = false;
    // scanf ("%i", &userChoice);
    std::cin >> userChoice;

    while(userDone == false) {

        while(std::cin.fail()) {
            std::cout << "Error: please input valid data type" << std::endl; // checking that user input is a valid int
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cin >> userChoice;
        }
    
        if (userChoice==1) { // printing user balance  DONE
            userDone = true;
            std::cout << "You have: " << userClassPtr->getBall() << " in your account." << std::endl;
        }

        else if (userChoice==2) { // printing user debt WIP
            std::cout << "Your current outstanding debt is: " << userClassPtr->getDebt() << std::endl;
            std::string payDebt;
            std::cout << "Would you like to pay off debt? Please enter yes or no: " << std::endl;
            std::cin >> payDebt;
            while(std::cin.fail() && payDebt != "no" && payDebt != "yes") 
                    {
                        std::cout << "Error: please input valid data type or correct word" << std::endl; // checking that user input is a valid string
                        std::cin.clear();
                        std::cin.ignore(256,'\n');
                        std::cin >> payDebt;
                    }
            if (payDebt=="yes"){
                std::cout << "How much of your available balance would you like to pay?\n";
                int toPay;
                std::cout << "Available balance: " << userClassPtr->getBall() << std::endl;
                std::cin >> toPay;
            }
        }

        else if (userChoice==3) { // taking user deposit DONE
            float payIn;
            std::cout << "Please enter amount to be paid in: "<< std::endl;
            scanf ("%f", &payIn);
            userClassPtr->makeDeposit(&payIn);
        }

        else if (userChoice==4) { // Checking Overdraft WIP
        }
        
        else if (userChoice==5) { // Check if user is Premium, maybe add an option to become premium for 200? DONE
            bool isPremium = userClassPtr->isPremium(); 

            if (isPremium==false){ // checks if user is not premium, if not then we ask if they want to become premium
                std::string premiumChoice;
                std::cout << "Would like to become premium for 200? Please enter yes or no" << std::endl;
                std::cin >> premiumChoice;
                std::cout << premiumChoice << std::endl;
                while(std::cin.fail() && premiumChoice != "no" && premiumChoice != "yes") 
                    {
                        std::cout << "Error: please input valid data type or correct word" << std::endl; // checking that user input is a valid string
                        std::cin.clear();
                        std::cin.ignore(256,'\n');
                        std::cin >> premiumChoice;
                    }
                if (premiumChoice == "yes")
                {
                    userClassPtr->becomePremium();
                }
                }
        } 
        
        else if (userChoice==6) { // Password change WIP
        }
        
        else if (userChoice==7) { // change secret question and answer WIP
        }

        else if (userChoice==8) { // user asks to quit session, need to add the saving of new numbers to excel sheet and encryption DONE encryption is WIP
            userDone = true;
            std::cout << "\n\nThank you for using our service - " << userName << std::endl;
            return 0;
        }
        else if (userChoice > 8 || userChoice < 1)
        {
            printf("\nError, number %i is not in range 1-8.\n", userChoice);
        }
        i = 0;
        printf("\nWhat would you like to do next?\n");
        std::cin >> userChoice;
        userDone = false;
    }

    
    return 0;
}
