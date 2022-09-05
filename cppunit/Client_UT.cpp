#include "client.h"

#include <string>
#include<algorithm>
#include <cppunit/config/SourcePrefix.h>

CPPUNIT_TEST_SUITE_REGISTRATION(details);

void details::setup()
{
	uid = "123";
	password = "nikhitha";
}

//UT-Testcases for password
void details::getPassword_UT_sunny()
{
	string password = "nikhitha";
	string password_2 = getPassword();
	CPPUNIT_ASSERT_EQUAL(password,password_2);
}
void details::getPassword_UT_rainy()
{
	string password = "shreya";
	string password_2 = getPassword();
	CPPUNIT_ASSERT_EQUAL(password,password_2);
}

//UT-Testcases for user-id
void details::getUID_UT_sunny()
{
	string user_id = "123";
	string user_id_2 = getUID();
	CPPUNIT_ASSERT_EQUAL(user_id,user_id_2);
}
void details::getUID_UT_rainy()
{
	string user_id = "456";
	string user_id_2 = getUID();
	CPPUNIT_ASSERT_EQUAL(user_id,user_id_2);
}
