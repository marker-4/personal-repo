#include "CheckingAccount.hpp"
#include <iostream>

bool CheckingAccount::writeCheck(BankAccount &a, double amount){
    bool success = withdrawal(amount);

    if(success){
        a.deposit(amount);
        checkLog.push_back(amount);
    }

    return success;
}

std::list<double> CheckingAccount::getCheckLog(){
    return checkLog;
}