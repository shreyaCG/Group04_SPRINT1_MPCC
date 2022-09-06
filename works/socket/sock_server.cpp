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
	server_bind = bind(sockfd, (struct sockaddr*)&server_addr, server_length);
	if(server_bind<0){
		perror("[-] BIND ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER IS BINDED TO PORT"<<endl;

	server_listen = listen(sockfd, MAXCONNECT);
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
void myServer::login_server()
{
	char recv_username[BSIZE];
	memset(recv_username,'\0',sizeof(recv_username));
	recv(new_sockfd, recv_username, BSIZE, 0);
	cout<<"[+] USERNAME RECEIVED"<<endl;	
	
	
	
	
	
	
	
	
	//cout<<recv_username<<endl;	
	//char buffer[BSIZE] = "[+] YOU ARE ADDED TO THE SESSION";
	//write(new_sockfd,buffer,strlen(buffer));
}
void myServer::accept_client()
{
	client_length = sizeof(client_addr);
	new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length);
	if(new_sockfd<0){
		perror("[-] ACCEPT ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER ACCEPTED THE CLIENT"<<endl;
	while(1){
		login_server();
	}
}
	/*while(1){
		fd_set master;
		FD_ZERO(&master);
		FD_SET(sockfd, &master);
		int max = sockfd + 1;
		int new_socket;
		char client_socket[BSIZE];
		int max_client = MAXCLIENT;
		for(int i=0; i<MAXCLIENT;i++){
			int sock_add = client_socket[i];
			if(sock_add > 0){
				FD_SET(sock_add, &master);
			}
			if(sock_add > MAXCLIENT){
			       max_client = sock_add;
			}
		}
		int sock_select = select(max, &master, nullptr, nullptr, nullptr);
		if(sock_select<0){
			perror("[-] SELECT ERROR");
			exit(EXIT_FAILURE);
		}
		if(FD_ISSET(sockfd, &master)){
			new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length);
			if(new_sockfd<0){
				perror("[-] ACCEPT ERROR");
				exit(EXIT_FAILURE);
			}
				}
			}
		}
	}*/
myServer::~myServer()
{
}
