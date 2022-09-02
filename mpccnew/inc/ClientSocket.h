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


class ClientSocket{
private:
	int sockfd;
	int newsockfd;
	int protno;
	string ipaddr;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t len;
public:
	ClientSocket() { protno = 8080; ipaddr = "0.0.0.0"; }
	ClientSocket(int _pno, string _ip) { protno = _pno; ipaddr = _ip; }
	
	void cliConn();
	void cliClose(int);
	int getCliSockfd() { return sockfd; }
	struct sockaddr_in getClientAddr(){ return client_addr; }
	socklen_t getCAddrlen() { return len; }
	


};

// void readData(promise<int>& dataready, promise<void>& consumed,int&, char*);
// void writeData(promise<int>& dataready, promise<void>& consumed,int&, char*);
void readData1(int&, char*);
void writeData1(int&, char*);
void writeuser(int&,char*);
// this function received data from the server and stores it in rcvDataBuf array
void recv_data(int clientSocketFd, int flags);


// this function sends data taken from the terminal to the server
void send_data(int clientSocketFd, int flags);
