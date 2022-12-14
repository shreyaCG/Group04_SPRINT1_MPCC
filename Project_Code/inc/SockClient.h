#pragma once

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <string>
#include<signal.h>
#define MAX_BUF 4096
using namespace std;


class Client{
	private:
		int Client_Socketfd;
		int Port;
		string ipaddr;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		socklen_t len;
	public:
		Client(int _pno, string _ip) { Port = _pno; ipaddr = _ip; }
		void Create_Socket();
		void ConnectClient();
		void ClientClose(int);
		int getCliSockfd() { return Client_Socketfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
		void log(string);	
};
//function to recieve the data from server
void RecvData(int clientSocketFd, int flags);
//function to send data to the server
void SendData(int clientSocketFd, int flags);
