add_library(accounts)

target_sources(
    accounts
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BankAccount.cpp
            ${CMAKE_SOURCE_DIR}/include/accounts/BankAccount.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/SavingsAccount.cpp
            ${CMAKE_SOURCE_DIR}/include/accounts/SavingsAccount.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/CheckingAccount.cpp
            ${CMAKE_SOURCE_DIR}/include/accounts/CheckingAccount.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/AccountManager.cpp

)   

target_include_directories(
    accounts
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/accounts
    ${CMAKE_SOURCE_DIR}/include/utils
)