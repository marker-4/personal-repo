find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(bank_account_tests) #creates exec, gives it a name

target_sources(bank_account_tests #gives data to executable
    PRIVATE
    BankAccountTests.cpp
    CheckingAccountTests.cpp
    SavingsAccountTests.cpp 
)

target_include_directories(bank_account_tests #gives libraries to use (include files)
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include/accounts
    ${CMAKE_SOURCE_DIR}/include/utils
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(bank_account_tests #gives libraries to link against
    PRIVATE
    accounts
    utils 
    ${Boost_LIBRARIES} # ${var} is variable format in CMake
)