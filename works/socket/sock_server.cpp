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

	while(1){
		fd_set copy = master;
		if((select(FD_SETSIZE, &copy, nullptr, nullptr, nullptr))<0){
			perror("[-] SELECT ERROR");
			exit(EXIT_FAILURE);
		}
		for(int i=0;i<FD_SETSIZE;i++){
			if(FD_ISSET(i, &copy)){
				if(i == server_listen){
					new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length);
					//cout<<"[+] SERVER ACCEPTED THE CLIENT"<<endl;
					if(new_sockfd<0){
						perror("[-] ACCEPT ERROR");
						exit(EXIT_FAILURE);
					}
					
					FD_SET(new_sockfd, &master);
				}
				else{
					FD_CLR(i, &copy);
					close(sockfd);
				}
			}
		}
	}
}
myServer::~myServer()
{
}
