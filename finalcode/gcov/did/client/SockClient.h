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
#include<signal.h>
#define MAX_BUF 4096

using namespace std;


class Client{
	private:
		int sockfd;
		int newsockfd;
		int Port;
		string ipaddr;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		socklen_t len;
	public:
	//	Client() { Port = 8080; ipaddr = "0.0.0.0"; }
		Client(int _pno, string _ip) { Port = _pno; ipaddr = _ip; }
		void Create_Socket();
		void ConnectClient();
		void cliClose(int);
		int getCliSockfd() { return sockfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
		void choose(int);	
};

void ReadData(int&, char*);
void WriteData(int&, char*);
//function to recieve the data from server
void RecvData(int clientSocketFd, int flags);
//function to send data to the server
void SendData(int clientSocketFd, int flags);
