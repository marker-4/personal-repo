#include <boost/test/unit_test.hpp>
#include "CheckingAccount.hpp"

BOOST_AUTO_TEST_SUITE(checking_account_suite)


BOOST_AUTO_TEST_CASE(write_check_test) {
    CheckingAccount sender("firstName", "lastName", 500);
    CheckingAccount receiver("otherFirstName", "otherLastName", 200);

    BOOST_CHECK_EQUAL(true, sender.writeCheck(receiver, 200));
    BOOST_CHECK_EQUAL(false, sender.writeCheck(receiver, 10000));

    BOOST_CHECK_EQUAL(500-200, sender.getBalance());
    BOOST_CHECK_EQUAL(200+200, receiver.getBalance());
    
}

BOOST_AUTO_TEST_CASE(get_check_log_test) {
    CheckingAccount sender("firstName", "lastName", 500);
    CheckingAccount receiver("otherFirstName", "otherLastName");

    sender.writeCheck(receiver, 200);
    sender.writeCheck(receiver, 100);
    sender.writeCheck(receiver, 10000);

    std::list<double> checkLog = sender.getCheckLog();

    BOOST_CHECK_EQUAL(200, checkLog.front());
    BOOST_CHECK_EQUAL(100, checkLog.back());
}

BOOST_AUTO_TEST_CASE(to_string_test) {
    CheckingAccount c("Braeden", "Marker", 500000);

    BOOST_CHECK_EQUAL("Checking Account Balance: $500000.000000", c.toString());
}


BOOST_AUTO_TEST_SUITE_END()