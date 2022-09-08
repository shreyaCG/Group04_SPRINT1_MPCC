#pragma once

#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<cppunit/extensions/HelperMacros.h>

using namespace std;

class Server : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Server);
	CPPUNIT_TEST(getIPaddress_UT_sunny);
	CPPUNIT_TEST(getIPaddress_UT_rainy);
	CPPUNIT_TEST(getPortNumber_UT_sunny);
	CPPUNIT_TEST(getPortNumber_UT_rainy);
	CPPUNIT_TEST_SUITE_END();
	
	private:
		string ip_addr;
		int port_num;
	
	public:
		void setUp();
		void setdetails(string ip_address,int port_no) {
			ip_addr = ip_address; port_num = port_no;}
		string getIPaddress(){ return ip_addr; }
		int getPortNumber(){ return port_num; }
	
	private:
		void getIPaddress_UT_sunny();
		void getIPaddress_UT_rainy();
		void getPortNumber_UT_sunny();
		void getPortNumber_UT_rainy();
};
