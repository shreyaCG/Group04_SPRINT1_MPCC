//#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h> /* for definition of errno */
#include <stdarg.h> /* ISO C variable aruments */
#include <cstring>
#include <string>         // std::string
#include <cstddef>        // std::size_t
#define PORT 8080
#define MAXBUFF 1024
using namespace std;
/*const std::string WHITESPACE = " \r\n\t\f\v";

std::string ltrim(const std::string &s)
{
	    size_t start = s.find_first_not_of(WHITESPACE);
	        return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
	    size_t end = s.find_last_not_of(WHITESPACE);
	        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
	    return rtrim(ltrim(s));
}*/
class mysoc
{
	private:
		int sockfd;
		int newSockfd;
		int rbind;
		int ret;
		struct sockaddr_in server_addr, client_addr;
		socklen_t len;
	public:
		mysoc();
		void createsocket(int,string);
		void server();
		void serverconnect();
		void serveraccept();
		void clientconnect();
		void clientreadwrite(string);
		~mysoc();

};

