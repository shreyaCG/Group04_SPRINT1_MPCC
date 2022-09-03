#pragma once

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <string>
#include <future>

#define MAX_BUF 4096

using namespace std;


class Client{
	private:
		int sockfd;
		int newsockfd;
		int protno;
		string ipaddr;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		socklen_t len;
	public:
		Client() { protno = 8080; ipaddr = "0.0.0.0"; }
		Client(int _pno, string _ip) { protno = _pno; ipaddr = _ip; }
		void create_socket();
		void clientconnect();
		void Closesoc(int);
		int getCliSockfd() { return sockfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
		void sendobj();	
};
//function to  receive data from the server 
void recv_data(int clientSocketFd, int flags);
//function to  send data
void send_data(int clientSocketFd, int flags);
