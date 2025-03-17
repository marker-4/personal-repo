The Bank Account software project was a solo project (with assistance from my program director who wrote
the outline of the make files, although I was largely on my own to troubleshoot and expand them).

This project is my most involved projet yet, relying heavily on OOP in C++ to create a system that manages
various bank accounts the user can add, modify, or remove.

Key features:

        * Two separate account types made with inheritance: Checking and Savings
        * Basic functions: Account creation, depositing/withdrawing, interest accrual (with credential 
          requirements to access this function which would normally be automized), account access (displays 
          account balances and other relevant info), and check writing
        * Password security to each account
              * Formating requirements from the boost::regex library
              * Serialization that exports each account to a cvv file after each use and imports them from 
                said file upon re-running the program
        * Admin account with special access to accrual
        * Unit testing for all crucial functions
