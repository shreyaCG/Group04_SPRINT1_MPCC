#nclude <cppunit/config/SourcePrefix.h>
#include <string>
#include<algorithm>
#include "Client.h"

CPPUNIT_TEST_SUITE_REGISTRATION(details);
void details::setUp()
{
	uid="123";
	password="nikhitha";
}
void details::getPassword_UT_sunny()
{
	string password="nikhitha";
	string password1=getPassword();
	CPPUNIT_ASSERT_EQUAL(password,password1);
}
void details::getPassword_UT_rainy()
{
	string password="@nikhitha";
	string password1=getPassword();
	CPPUNIT_ASSERT_EQUAL(password,password1);
}
void details::getUID_UT_sunny()
{
	string userid="123";
	string userid1=getUID();
	CPPUNIT_ASSERT_EQUAL(userid,userid1);
}
void details::getUID_UT_rainy()
{

	string userid="456";
	string userid1=getUID();
	CPPUNIT_ASSERT_EQUAL(userid,userid1);
}



