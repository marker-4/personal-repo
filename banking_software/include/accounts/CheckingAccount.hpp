#ifndef CHECKINGACCOUNT_HPP
#define CHECKINGACCOUNT_HPP

#include "BankAccount.hpp"
#include <list>

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(std::string first, std::string last, double initBalance) : BankAccount(first, last, initBalance) {};
    CheckingAccount(std::string first, std::string last) : BankAccount(first, last) {};

    bool writeCheck(BankAccount &a, double amount);

    std::list<double> getCheckLog();

    ~CheckingAccount() {}

    std::string toString() {
        return "Checking Account Balance: $" + std::to_string(getBalance());
    }

private:
    std::list<double> checkLog;
};

#endif