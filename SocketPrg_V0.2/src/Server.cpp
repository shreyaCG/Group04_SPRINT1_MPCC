#include <ServerSocket.h>

void ServerSocket::servConn()
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
	
	cout<<"[+] Server Socket Created"<<endl;
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
	cout<<"[+]Server bind to port no:"<<protno<<endl;
	if(listen(sockfd, 5)<0)
	{
		cout<<"[+]Server listening to the clients"<<endl;
	}
}

int ServerSocket::servAccept(int sfd)
{
	len = sizeof(client_addr);
	newsockfd = accept(sfd, (struct sockaddr *)&client_addr, &len);
	if(newsockfd<0)
	{
		perror("accept() failed");
		exit(EXIT_FAILURE);
	}
	cout<<"[+]Server accept the client"<<endl;
	return newsockfd;
}

void ServerSocket::servClose(int sfd)
{
	close(sfd);
}

int readData1(int &sfd, char*buff)
{
	
	memset(buff, 0, MAX_BUF);
	int ret = read(sfd,buff,MAX_BUF);
	
	return ret;
}


int writeData1(int &sfd, char*buff)
{
	memset(buff, 0, MAX_BUF);
	
	strcpy(buff,"\n\t=====Welcome to the awesome Server-Client Application=====\n");
	int ret = write(sfd,buff,strlen(buff));
	memset(buff, 0, MAX_BUF);
	return ret;
}

