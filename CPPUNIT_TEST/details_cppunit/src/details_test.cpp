#include"details_test.h"
#include<cstring>
#include<algorithm>
#include<cppunit/config/SourcePrefix.h>

CPPUNIT_TEST_SUITE_REGISTRATION(details);

void details::setUp()
{
	userid = "nikhitha";
	password = "1212";
}
void details::getUserID_UT_sunny()
{
	string userid = "nikhitha";
        string user_id = getUserID();
        CPPUNIT_ASSERT_EQUAL(userid, user_id);
}
void details::getUserID_UT_rainy()
{
	string userid = "rajesh";
	string user_id = getUserID();
	CPPUNIT_ASSERT_EQUAL(userid, user_id);
}
void details::getPassword_UT_sunny()
{
	string password = "1212";
        string pass_word = getPassword();
        CPPUNIT_ASSERT_EQUAL(password, pass_word);
}
void details::getPassword_UT_rainy()
{
	string password = "1313";
        string pass_word = getPassword();
        CPPUNIT_ASSERT_EQUAL(password, pass_word);
}
