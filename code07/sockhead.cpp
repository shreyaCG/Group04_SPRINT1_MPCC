#include "sockhead.h"

void TCP_Server::servConn()
{
	int opt = true;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
	{
		perror("setsockopt() error");
		exit(EXIT_FAILURE);
	}
	
	cout<<"TCP_Server:[+]Server Socket Created"<<endl;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(protno);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
	int retVal = bind(sockfd,(struct  sockaddr*)&server_addr,sizeof(server_addr));
	if(retVal<0)
	{
		perror("bind() error");
		exit(EXIT_FAILURE);
	}
	cout<<"TCP_Server:[+]Server bind to port no:"<<protno<<endl;
	if(listen(sockfd, 5)<0)
	{
		cout<<"TCP_Server:[+]Server listening to the clients"<<endl;
	}
}

int TCP_Server::servAccept(int sfd)
{
	len = sizeof(client_addr);
	newsockfd = accept(sfd, (struct sockaddr *)&client_addr, &len);
	if(newsockfd<0)
	{
		perror("accept() failed");
		exit(EXIT_FAILURE);
	}
	cout<<"TCP_Server:[+]Server accept the client"<<endl;
	return newsockfd;
}

void TCP_Server::servClose(int sfd)
{
	close(sfd);
}



void TCP_Client::cliConn()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}
	cout<<"TCP_Client:[+]Client Socket Created"<<endl;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(protno);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
	
	cout<<"TCP_Client:[+]Client bind to port no:"<<protno<<" and ip_address: "<<ipaddr<<endl;
	
	int ret = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret < 0)
	{
		perror("connect() error: ");
		exit(EXIT_FAILURE);
	}

	cout<<"TCP_Client:[+]Client connected to the server"<<endl;
}



void TCP_Client::cliClose(int sfd)
{
	close(sfd);
}
