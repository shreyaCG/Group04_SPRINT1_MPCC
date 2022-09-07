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
<<<<<<< HEAD:cppunit/client.h
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> f06fcb491fcd1729d8c6eb5a0b39b3eb9d03b79e:CPPUNIT_SERVER/client.h
	CPPUNIT_TEST_SUITE( details );
	CPPUNIT_TEST( getUID_UT_sunny);
	CPPUNIT_TEST( getPassword_UT_rainy );
	CPPUNIT_TEST(getUID_UT_rainy);
	CPPUNIT_TEST(getPassword_UT_sunny);
	CPPUNIT_TEST_SUITE_END();
private:
	string uid;
	string password;
public:
	void setUp();
	

	void setdetails(string userid,string pass) { string uid=userid;string password=pass; }
	
	string getPassword(){return password;}
	string getUID(){ return uid;}
	

	private:
	//void getEmail_UT();
	void getPassword_UT_sunny();
	void getPassword_UT_rainy();
	void getUID_UT_sunny();
	void getUID_UT_rainy();
	

<<<<<<< HEAD:cppunit/client.h
=======
>>>>>>> 7f85fadcc51a8ce184d60bb8b055a751428ef329
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
<<<<<<< HEAD
=======
>>>>>>> 115a509bf037d1a29b409ef4211a2b14fad19078
>>>>>>> 7f85fadcc51a8ce184d60bb8b055a751428ef329
=======
>>>>>>> f06fcb491fcd1729d8c6eb5a0b39b3eb9d03b79e:CPPUNIT_SERVER/client.h
};
