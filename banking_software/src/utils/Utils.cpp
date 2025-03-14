#include "Utils.hpp"
#include <iostream>
#include <stdexcept>

BankAccount* make_account() {
    BankAccount *acct = nullptr;

    std::string first = getString("Enter the first name:");
    std::string last = getString("Enter the last name:");

    std::string choice = getString("Would you like to make a savings (1) or checking (2) account:");

    if (choice == "1") {
        try {
            double interestRate = getDouble("Enter the interest rate:");
            if (interestRate > 0 && interestRate < 1) {
                acct = new SavingsAccount(first, last, interestRate);
                statusMessage("Savings account created succesfully!");
            } else {
                errorMessage("Interest rate must be between 0 and 1.");
            }
        } catch (std::invalid_argument e) {
            errorMessage("Interest rate must be numeric.");
        }
        
    } else if (choice == "2") {
        acct = new CheckingAccount(first, last);
        statusMessage("Checking account created successfully!");
    } else {
        errorMessage("Invalid choice (Must be \"1\" or \"2\").");
    }


    return acct;
}

void statusMessage(std::string msg) {
    std::cout << msg << std::endl;
}

void errorMessage(std::string errorMsg) {
    std::cout << "[ERROR] " << errorMsg << std::endl;
}

std::string getOption() {
    std::cout<<"Options"<<std::endl;
    std::cout<<"0) Exit"<<std::endl;
    std::cout<<"1) Make account"<<std::endl;
    std::cout<<"2) Deposit to existing account"<<std::endl;
    std::cout<<"3) Withdraw from existing account"<<std::endl;
    std::cout<<"4) Display existing account"<<std::endl;
    std::cout<<"5) Accrue Interest"<<std::endl;
    std::cout<<"6) Write a check"<<std::endl;
    std::cout<<"What would you like to do (Input single number):"<<std::endl;

    std::string input_string;
    std::cin >> input_string;
    
    return input_string;
}

double getDouble(std::string msg) {
    std::cout << msg << std::endl;
    std::string dblStr;
    std::cin >> dblStr;

    char *end;
    double dbl = strtod(dblStr.c_str(), &end);

    if (*end == '\0') {
        std::cout << std::endl;
        return dbl;
    } else {
        throw std::invalid_argument("Invalid input");
    }
}

std::string getString(std::string msg) {
    std::cout << msg << std::endl;
    std::string inputString;
    std::cin >> inputString;

    std::cout << std::endl;

    return inputString;
}

