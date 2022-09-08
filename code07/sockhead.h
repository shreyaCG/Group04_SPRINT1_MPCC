#pragma once

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
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <cstring>
#include <iostream>
#define PERMS 0666
#define MAX_BUF 4096
using namespace std;

class Test_Class 
{
	private:
		int id;
		char name[20];
	public:
		Test_Class(){}
		Test_Class(int i, char *n) { id = i; strcpy(name,n); }
		void setID(int i){ id = i; }
		void setName(char*n){strcpy(name,n);}
		char *getName(){ return name; }
		int getID(){ return id; }
		string toString() {
			ostringstream ss;
			ss << this->getID()<<"|"<< this->getName();
			return ss.str();
		}
};


class TCP_Client
{
	private:
		int sockfd, newsockfd, protno;
		string ipaddr;
		struct sockaddr_in server_addr, client_addr;
		socklen_t len;
	public:
		//TCP_Client() { protno = 8080; ipaddr = "0.0.0.0"; }
		TCP_Client(int _pno, string _ip) { protno = _pno; ipaddr = _ip; }
		void cliConn();
		void cliClose(int);
		int getCliSockfd() { return sockfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
};

class TCP_Server
{
	private:
		int sockfd, newsockfd, protno;
		string ipaddr;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		socklen_t len;
	public:
		//TCP_Server() { protno = 8080; ipaddr = "0.0.0.0"; }
		TCP_Server(int _pno, string _ip) { protno = _pno; ipaddr = _ip; }
		void servConn();
		int servAccept(int);
		void servClose(int);
		int getServSockfd() { return sockfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
};
