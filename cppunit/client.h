#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;




class details : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( details );
	CPPUNIT_TEST( getUserid_UT_sunny);
	CPPUNIT_TEST( getPassword_UT_rainy );
	CPPUNIT_TEST(getUserid_UT_rainy);
	CPPUNIT_TEST(getPassword_UT_sunny);
	CPPUNIT_TEST_SUITE_END();
protected:
	string userid;
	string password;
public:
	void setUp();
	

	void setValues(string uid,string pwd) { string userid=uid;string password=pwd; }
	
	string getPassword(){return password;}
	string getUserid(){ return userid;}
	

	protected:
	//void getEmail_UT();
	void getPassword_UT_sunny();
	void getPassword_UT_rainy();
	void getUserid_UT_sunny();
	void getUserid_UT_rainy();
	

};
