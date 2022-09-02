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
#include<fstream>
#define MAX_BUF 4096

using namespace std;


class Server{
	private:
		int sockfd;
		int newsockfd;
		int protno,i;
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
		Server() { protno = 8080; ipaddr = "0.0.0.0"; }
		Server(int _pno, string _ip) { protno = _pno; ipaddr = _ip; }
		void create_socket();
		void bind_listen();
		int acceptclient(int);
		void servClose(int);
		int getServSockfd() { return sockfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
		void serv_select(int,string);
		void handleusers(char*,char*);
		void createfds();
		void countclient();
		void checkfdset();
		void handledisconnect();
		void broadcast_msg();
};

int readData1(int&, char*);
int writeData1(int&, char*);
