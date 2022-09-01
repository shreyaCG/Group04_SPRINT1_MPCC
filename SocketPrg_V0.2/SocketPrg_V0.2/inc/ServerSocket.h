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
#include <future>
#include <string>
#include <sstream>
#include <vector>

#define MAX_BUF 4096

using namespace std;


class ServerSocket{
private:
	int sockfd;
	int newsockfd;
	int protno;
	string ipaddr;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t len;
	int csockfd, client_sock[30];
	
	int max_clients = 30;

	int serverfd, sd, max_sd;
	
	int readVal;

	vector <int> vs_csock;
	char buff[MAX_BUF];
	//create master socket
	fd_set master;
	// set of sock_desc...
	fd_set readfds;
	int socketCount=0;
public:
	ServerSocket() { protno = 8080; ipaddr = "0.0.0.0"; }
	ServerSocket(int _pno, string _ip) { protno = _pno; ipaddr = _ip; }
	void servConn();
	int servAccept(int);
	void servClose(int);
	int getServSockfd() { return sockfd; }
	struct sockaddr_in getClientAddr(){ return client_addr; }
	socklen_t getCAddrlen() { return len; }
	void serv_accept();


};

int readData1(int&, char*);
int writeData1(int&, char*);
