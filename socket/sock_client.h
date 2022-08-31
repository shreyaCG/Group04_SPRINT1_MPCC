#pragma once

#include<iostream>
#include<cstring>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<sys/socket.h>

#define BSIZE 1024

using namespace std;

class myClient
{
	public:
		myClient();
		void create_socket(string, int);
		void connect_client();
		//void receive_message();
		//void send_message();
		~myClient();
	private:
		int sockfd, client_connect;
		struct sockaddr_in server_addr, client_addr;
		socklen_t server_length, client_length;
};
