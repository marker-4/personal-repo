#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "AccountManager.hpp"
#include "Utils.hpp"


#include <iostream>

int main() {

    statusMessage("Welcome to the banking software!");

    bool finished = false;

    AccountManager accts;

    while(!finished){
        std::string input_string = getOption();

        if (input_string == "0") {
            statusMessage("Thank you for using the software");
            finished = true;
        
        } else if(input_string == "1") {
            std::string user = getString("Enter the username: ");
            accts.addAccount(user);
          
        } else if (input_string == "2") {
            std::string user = getString("Enter the username: ");
            
            try {
                double deposit_amount = getDouble("Enter Amount: ");
                accts.makeDeposit(user, deposit_amount);
            } catch(std::invalid_argument e) {
                errorMessage("Cannot deposit a non-number quantity.");
            }

        } else if (input_string == "3") {
            std::string user = getString("Enter the username: ");
            
            try {
                double withdrawal_amount = getDouble("Enter amount: ");
                accts.makeWithdrawal(user, withdrawal_amount);
            } catch(std::invalid_argument e) {
                errorMessage("Invalid input. Cannot withdraw a non-number quantity.");
            }
            
        } else if (input_string == "4") {
            std::string user = getString("Enter the username: ");
            accts.displayAccount(user); 
        
        } else if (input_string == "5") { 
            accts.addInterest();
        
        } else if (input_string == "6") {
            std::string user = getString("Enter the username of the account writing the check: ");
            std::string target_account = getString("Enter the username of the account cashing the check: ");
            
            try {
                double check_amount = getDouble("Enter amount: ");
                accts.writeCheck(user, target_account, check_amount);
            } catch(std::invalid_argument e) {
                errorMessage("Cannot write check of non-number quantity.");
            }
                                        
        }
    }

    return 0;
}