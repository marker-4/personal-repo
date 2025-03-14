#include <boost/test/unit_test.hpp>
#include "SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(saving_account_suite)

BOOST_AUTO_TEST_CASE(get_interest_rate_test) {
    SavingsAccount s("firstName", "lastName", 0.01);

    BOOST_CHECK_EQUAL(0.01, s.getInterestRate());
}

BOOST_AUTO_TEST_CASE(set_interest_rate_test) {
    SavingsAccount s("firstName", "lastName", 0.01);
    s.setInterestRate(0.02);

    BOOST_CHECK_EQUAL(0.02, s.getInterestRate());
}


BOOST_AUTO_TEST_CASE(accrue_interest_test) {
    SavingsAccount s("firstName", "lastName", 0.01);

    s.accrueInterest(); //this test showed me a bug where accruing interest to a savings w/ no balance gives a deposit error instead of a specific one to the function

    BOOST_CHECK_EQUAL(0, s.getBalance());
    s.deposit(100);
    s.accrueInterest();
    BOOST_CHECK_EQUAL(101, s.getBalance());
}

BOOST_AUTO_TEST_CASE(to_string_test) {
    SavingsAccount s("firstName", "lastName", 0.05);

    BOOST_CHECK_EQUAL(
        "Savings Account Balance: $0.000000, Interest Rate: 0.050000",
        s.toString()
    );
}

BOOST_AUTO_TEST_SUITE_END()