#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

BankAccount* make_account();

void statusMessage(std::string msg);
void errorMessage(std::string msg);
std::string getOption();
double getDouble(std::string msg);
std::string getString(std::string msg);