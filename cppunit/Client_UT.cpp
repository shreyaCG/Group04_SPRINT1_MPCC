#include <cppunit/config/SourcePrefix.h>
#include <string>
#include<algorithm>

#include "client.h"

CPPUNIT_TEST_SUITE_REGISTRATION( details );

void details::setUp()
{
	userid="123";
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



void details::getUserid_UT_sunny() {
		std::string Name = "123";
		std::string Name2 = getUserid();
		
		CPPUNIT_ASSERT_EQUAL(Name, Name2);
 }
 

void details::getUserid_UT_rainy() {
		std::string Name = "456";
		std::string Name2 = getUserid();
		
		CPPUNIT_ASSERT_EQUAL(Name, Name2);
 }






/*
	void User::getCPhno_UT(){
		long int num=8509374297;
		long int num2 =getCPhno();
		CPPUNIT_ASSERT_EQUAL(num,num2 );
}*/
