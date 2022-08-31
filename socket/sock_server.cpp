#include "sock_server.h"

myServer::myServer()
{
}
void myServer::create_socket(string ip_addr, int port_no)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		perror("[-] SOCKET ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER SOCKET IS CREATED"<<endl;
	
	server_length = sizeof(server_addr);
	memset(&server_addr, '\0', server_length);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_no);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ip_addr.c_str());
}
void myServer::bind_server()
{
	server_length = sizeof(server_addr);
	server_bind = bind(sockfd, (struct sockaddr*)&server_addr, server_length);
	if(server_bind<0){
		perror("[-] BIND ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER IS BINDED TO PORT"<<endl;

	server_listen = listen(sockfd, MAXCONN);
	if(server_listen<0){
		perror("[-] LISTEN ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER IS LISTENING TO THE CLIENTS..."<<endl;
}
void myServer::receive_message()
{
}
void myServer::send_message()
{
}
void myServer::accept_client()
{
	client_length = sizeof(client_addr);

	fd_set master;
	FD_ZERO(&master);
	FD_SET(server_listen, &master);
        int MAX = sockfd + 1;
	for(;;)
	{
		FD_SET(sockfd , &master);
		int ready_fd = select(MAX, &master, nullptr, nullptr, nullptr);
		if(FD_ISSET(sockfd, &master)){
			while(1){
				new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length);
				bzero(client_buf, sizeof(client_buf));
				cout<<"Message from client";
				read(new_sockfd, client_buf, sizeof(client_buf));
				cout<<client_buf<<endl;
				char* message = "Hello";
				write(new_sockfd, (const char* )message, sizeof(client_buf));
			}
			close(new_sockfd);
		}
	}

}		

myServer::~myServer()
{
}
