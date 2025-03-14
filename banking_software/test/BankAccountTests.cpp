#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(bank_account_suite) //acct suite is var name

BOOST_AUTO_TEST_CASE(get_balance_test) {
    SavingsAccount s("Bradley", "Sumner", 500, 0.1);

    BOOST_CHECK_EQUAL(500, s.getBalance());

}

BOOST_AUTO_TEST_CASE(get_first_test) {
    SavingsAccount s("Bradley", "Sumner", 0.1);

    BOOST_CHECK_EQUAL("Bradley", s.getFirstName());
}

BOOST_AUTO_TEST_CASE(get_last_test) {
    SavingsAccount s("Bradley", "Sumner", 0.1);

    BOOST_CHECK_EQUAL("Sumner", s.getLastName());
}

BOOST_AUTO_TEST_CASE(set_first_test) {
    SavingsAccount s("Sadley", "Sumner", 0.1);

    BOOST_CHECK_EQUAL("Sadley", s.getFirstName());

    s.setFirstName("Bradley");

    BOOST_CHECK_EQUAL("Bradley", s.getFirstName());
}

BOOST_AUTO_TEST_CASE(set_last_test) {
    SavingsAccount s("Bradley", "wrongName", 0.1);

    BOOST_CHECK_EQUAL("wrongName", s.getLastName());

    s.setLastName("rightName");

    BOOST_CHECK_EQUAL("rightName", s.getLastName());
}

BOOST_AUTO_TEST_CASE(withdrawal_test) {
    SavingsAccount s("firstName", "lastName", 500, 0.1);
    s.withdrawal(200);

    BOOST_CHECK_EQUAL(300, s.getBalance());
}

BOOST_AUTO_TEST_CASE(deposit_test) {
    SavingsAccount s("Frank", "Oz", 0.1);

    BOOST_CHECK_EQUAL(0, s.getBalance());

    s.deposit(100);

    BOOST_CHECK_EQUAL(100, s.getBalance());
}



BOOST_AUTO_TEST_SUITE_END()