#pragma once

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class details : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(details);
	CPPUNIT_TEST(getUID_UT_sunny);
	CPPUNIT_TEST(getPassword_UT_rainy);
	CPPUNIT_TEST(getUID_UT_rainy);
	CPPUNIT_TEST(getPassword_UT_sunny);
	CPPUNIT_TEST_SUITE_END();
	
	private:
		string uid;
		string password;
	
	public:
		void setup();
		void setdetails(string user_id,string passwrd){ 
			string uid=user_id;string password=passwrd; }
		string getPassword(){ return password; }
		string getUID(){ return uid; }

	private:
		void getPassword_UT_sunny();
		void getPassword_UT_rainy();
		void getUID_UT_sunny();
		void getUID_UT_rainy();
};
