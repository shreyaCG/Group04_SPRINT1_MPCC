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
#define MAXCLIENT 30
#define SIZE 30
using namespace std;

class Server{
	private:
		int server_socketfd,Client_Socketfd;
		int portno;
		string ipaddr;
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		socklen_t len;
	public:
		Server(int _pno, string _ip) { portno = _pno; ipaddr = _ip; }
		void create_socket();
		void bind_listen();
		int acceptclient(int);
		void Server_Close(int);
		int getServSockfd() { return server_socketfd; }
		struct sockaddr_in getClientAddr(){ return client_addr; }
		socklen_t getCAddrlen() { return len; }
		void serv_select();
		void log(string);
		void broadcast_msg(char*,vector<int>&,int,int,int *,char [SIZE][SIZE]);
		void registeruser_login(int,vector<int>&,int *,char [SIZE][SIZE]);
};

