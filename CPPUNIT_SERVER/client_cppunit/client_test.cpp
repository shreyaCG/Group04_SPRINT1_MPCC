#include"client_test.h"
#include<cstring>
#include<algorithm>
#include<cppunit/config/SourcePrefix.h>

CPPUNIT_TEST_SUITE_REGISTRATION(Client);

void Client::setUp()
{
	ip_addr = "127.0.0.1";
	port_num = 8080;
}
void Client::getIPaddress_UT_sunny()
{
	string ipaddress = "127.0.0.1";
        string ip_address = getIPaddress();
        CPPUNIT_ASSERT_EQUAL(ipaddress, ip_address);
}
void Client::getIPaddress_UT_rainy()
{
	string ipaddress = "127.9.9.1";
	string ip_address = getIPaddress();
	CPPUNIT_ASSERT_EQUAL(ipaddress, ip_address);
}
void Client::getPortNumber_UT_sunny()
{
	int portnumber = 8080;
        int port_number = getPortNumber();
        CPPUNIT_ASSERT_EQUAL(portnumber, port_number);
}
void Client::getPortNumber_UT_rainy()
{
	int portnumber = 9090;
	int port_number = getPortNumber();
	CPPUNIT_ASSERT_EQUAL(portnumber, port_number);
}
