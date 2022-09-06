#include "client.h"

#include <string>
#include<algorithm>
#include <cppunit/config/SourcePrefix.h>

CPPUNIT_TEST_SUITE_REGISTRATION(details);

void details::setup()
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
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




=======
>>>>>>> 7f85fadcc51a8ce184d60bb8b055a751428ef329
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
<<<<<<< HEAD
=======
>>>>>>> 115a509bf037d1a29b409ef4211a2b14fad19078
>>>>>>> 7f85fadcc51a8ce184d60bb8b055a751428ef329
