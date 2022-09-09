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
#include <exception>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>
#define MAX_BUF 4096
#include <details.h>
using namespace std;

class Server{
	private:
		int sockfd;
		int newsockfd;
		int portno,i;
		string ipaddr;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		socklen_t len;
		int client_sock[30];
		char uids[30][30];	
		int max_clients = 30;
		int serverfd, sd, max_sd;
		int readVal;
		vector <int> vs_csock;
		char buff[MAX_BUF];
		char str[MAX_BUF];
		fd_set master;
		fd_set readfds;
		int socketCount=0;
	public:
		Server(int _pno, string _ip) { portno = _pno; ipaddr = _ip; }
		void create_socket();
		void bind_listen();
		int acceptclient(int);
		void servClose(int);
		int getServSockfd() { return sockfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
		void serv_select();
		void createfds();
		void countclient();
		void handledisconnect();
		void broadcast_msg(string);
		void registeruser_login(string &,int &);
};

