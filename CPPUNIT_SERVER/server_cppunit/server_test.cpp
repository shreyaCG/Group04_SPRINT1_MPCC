#include"server_test.h"
#include<cstring>
#include<algorithm>
#include<cppunit/config/SourcePrefix.h>

CPPUNIT_TEST_SUITE_REGISTRATION(Server);

void Server::setUp()
{
	ip_addr = "127.0.0.1";
	port_num = 8080;
}
void Server::getIPaddress_UT_sunny()
{
	string ipaddress = "127.0.0.1";
        string ip_address = getIPaddress();
        CPPUNIT_ASSERT_EQUAL(ipaddress, ip_address);
}
void Server::getIPaddress_UT_rainy()
{
	string ipaddress = "127.6.6.1";
	string ip_address = getIPaddress();
	CPPUNIT_ASSERT_EQUAL(ipaddress, ip_address);
}
void Server::getPortNumber_UT_sunny()
{
	int portnumber = 8080;
        int port_number = getPortNumber();
        CPPUNIT_ASSERT_EQUAL(portnumber, port_number);
}
void Server::getPortNumber_UT_rainy()
{
	int portnumber = 6060;
	int port_number = getPortNumber();
	CPPUNIT_ASSERT_EQUAL(portnumber, port_number);
}
