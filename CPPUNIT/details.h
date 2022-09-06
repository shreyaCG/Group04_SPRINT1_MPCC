
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
	

};
