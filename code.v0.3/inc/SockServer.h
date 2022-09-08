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
#include <bits/stdc++.h>
#define MAX_BUF 4096
#include <details.h>
using namespace std;

class Server{
	private:
		int Server_socket;
		int Client_socket;
		int portno,i;
		string ipaddr, data;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		socklen_t len;
		int client_socket[30];
		char uids[30][30];	
		int max_clients = 30;
		int serverfd, socketfd, max_socket;
		int readVal;
		vector <int> vs_csock;
		char buff[MAX_BUF];
		fd_set master;
		fd_set readfds;
	public:
		Server(int _pno, string _ip) { portno = _pno; ipaddr = _ip; }
		void create_socket();
		void bind_listen();
		int acceptclient(int);
		void servClose(int);
		int log(string);
		int getServSockfd() { return Server_socket; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
		void serv_select();
		void create_fdset();
		void Add_Client_sockets();
		void handledisconnect();
		void broadcast_msg(string);
		void registeruser_login(string &,int &);
		~Server();
};

