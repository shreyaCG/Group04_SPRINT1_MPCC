#pragma once

#include<iostream>
#include<cstring>
#include<fstream>
#include<sys/types.h>
#include<sys/select.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<sys/socket.h>

#define BSIZE 1024
#define MAXCONNECT 10
#define MAXCLIENT 10 
using namespace std;

class myServer
{
	public:
		myServer();
		void create_socket(string, int);
		void bind_server();
		void login_server();
		void accept_client(); 
		void receive_message();
		void send_message();
		~myServer();
	private:
		int sockfd, new_sockfd, server_bind, server_listen;
		char server_buf[BSIZE], client_buf[BSIZE];
		int user_login;
		struct sockaddr_in server_addr, client_addr;
		socklen_t server_length, client_length;
};
