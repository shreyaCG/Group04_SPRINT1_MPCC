#include <cppunit/config/SourcePrefix.h>
#include <string>
#include<algorithm>
#include "client.h"

CPPUNIT_TEST_SUITE_REGISTRATION( details );

void details::setUp()
{
	uid="123";
	password="nikhitha";
	
	
    
}
 void details::getPassword_UT_sunny() {
		string password = "nikhitha";
		string password2 = getPassword();
		
		CPPUNIT_ASSERT_EQUAL(password, password2);
 }
 

void details::getPassword_UT_rainy() {
		string password = "rajesh";
		string password2 = getPassword();
		
		CPPUNIT_ASSERT_EQUAL(password, password2);
 }



void details::getUID_UT_sunny() {
		std::string userID= "123";
		std::string userID1 = getUID();
		
		CPPUNIT_ASSERT_EQUAL(userID, userID1);
 }
 

void details::getUID_UT_rainy() {
		std::string userID= "456";
		std::string userID1= getUID();
		
		CPPUNIT_ASSERT_EQUAL(userID, userID1);
 }




