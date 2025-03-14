#include "../../include/accounts/AccountManager.hpp"
#include "../../include/accounts/BankAccount.hpp"
#include "../../include/accounts/SavingsAccount.hpp"
#include "../../include/accounts/CheckingAccount.hpp"
#include "../../include/utils/Utils.hpp"

#include <iostream>

AccountManager::AccountManager() {
    accts = std::map<std::string, BankAccount*>();
    numAccounts = 0;
}

void AccountManager::addAccount(std::string username) {
    if (accts.find(username) != accts.end()) {
        errorMessage("Username already taken.");
    } else {
        BankAccount* acct = make_account();

        if(acct != nullptr){
            accts[username] = acct;
        }
    }
}

void AccountManager::deleteAccount(std::string username) {
    if (accts.find(username) == accts.end()) {
        errorMessage("Username not found.");
    } else {
        delete accts[username];
        accts.erase(username); 
    }
}

void AccountManager::displayAccount(std::string username) {
    if (accts.find(username) != accts.end()) {
        statusMessage(accts[username]->toString());
    } else {
        errorMessage("Account not found.");
    }
}

void AccountManager::makeDeposit(std::string username, double amount) {
    if (accts.find(username) != accts.end()) {
        if (accts[username]->deposit(amount)) {
            statusMessage("Deposit completed successfully!");
        }
    } else {
        errorMessage("Account not found.");
    }
}

void AccountManager::makeWithdrawal(std::string username, double amount) {
    if (accts.find(username) != accts.end()) {
        if (accts[username]->withdrawal(amount)) {
            statusMessage("Withdrawal completed successfully!");
        }
    } else {
        errorMessage("Account not found.");
    }
}

void AccountManager::addInterest() {
    std::map<std::string, BankAccount*>::iterator it;

    for (it = accts.begin(); it != accts.end(); it++) {
        if (dynamic_cast<SavingsAccount*>(it->second)) {
            SavingsAccount *s = dynamic_cast<SavingsAccount*>(it->second);
            s->accrueInterest();
        }
    }
}

void AccountManager::writeCheck(std::string checkWriter, std::string checkReceiver, double amount) {
    if (accts.find(checkWriter) != accts.end()) {
        if (accts.find(checkReceiver) != accts.end()) {
            if (dynamic_cast<CheckingAccount*>(accts[checkWriter])) {
                CheckingAccount* c = dynamic_cast<CheckingAccount*>(accts[checkWriter]);
                c->writeCheck(*(accts[checkReceiver]), amount);
                statusMessage("Check written successfully.");
            } else {
                errorMessage("Cannot write checks from non-checking account.");
            }
        } else {
            errorMessage("Receiving account not found.");
        }
    } else {
        errorMessage("Account writing check not found.");
    }
}

int AccountManager::getNumAccounts() { return numAccounts; }

AccountManager::~AccountManager() {
    for (auto& pair : accts) {
        delete pair.second;
    }
}