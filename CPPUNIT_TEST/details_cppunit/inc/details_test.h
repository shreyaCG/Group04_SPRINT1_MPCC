#pragma once

#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<cppunit/extensions/HelperMacros.h>

using namespace std;

class details : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(details);
	CPPUNIT_TEST(getUserID_UT_sunny);
	CPPUNIT_TEST(getUserID_UT_rainy);
	CPPUNIT_TEST(getPassword_UT_sunny);
	CPPUNIT_TEST(getPassword_UT_rainy);
	CPPUNIT_TEST_SUITE_END();
	
	private:
		string userid;
		string password;
	
	public:
		void setUp();
		void setdetails(string user_id,string pass_word) {
			userid = user_id; password = pass_word;}
		string getUserID(){ return userid; }
		string getPassword(){ return password; }
	
	private:
		void getUserID_UT_sunny();
		void getUserID_UT_rainy();
		void getPassword_UT_sunny();
		void getPassword_UT_rainy();
};
