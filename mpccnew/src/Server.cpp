#include <ServerSocket.h>

void Server::create_socket()
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
}
void Server::bind_listen()
{
	int retbind = bind(sockfd,(struct  sockaddr*)&server_addr,sizeof(server_addr));
	if(retbind<0)
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

int Server::acceptclient(int sfd)
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

void Server::servClose(int sfd)
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
	
	strcpy(buff,"Welcome!!!");
	int ret = write(sfd,buff,strlen(buff));
	memset(buff, 0, MAX_BUF);
	return ret;
}
void Server::handleusers(char* buff,char* user)
{
	fstream fs;
	if(buff != NULL)
	{
		fs.open("registered.txt", ios::in | ios::app);
		fs<<buff<<endl;
		fs.close();
	}
	int lines=0;
	string line;
	string usr(user);
	fs.open("registered.txt",ios::in);
	if(fs.is_open())
	{
		while(getline(fs,line))
		{
			lines++;		
			if(line.find(usr,0)!=string::npos)
			{
				cout<<usr<<" exists "<<endl;
		
			}
		}
	}
	fs.close();
}
void Server::createfds()
{
	readfds = master;
	max_sd = serverfd;
	//clear the sock set fds
	FD_ZERO(&readfds);
	FD_SET(serverfd,&readfds);
	max_sd = serverfd;
}
void Server::countclient()
{
	for(int i=0;i<max_clients;i++)
	{
		sd = client_sock[i];
		///if valid socket desc... then add to readfds lists
		if(sd > 0)
			FD_SET(sd,&readfds);
		//highest fds number, need it for the select fucntion
		if(sd > max_sd)
			max_sd = sd;
	}
}
void Server::checkfdset()
{
	if(FD_ISSET(serverfd, &readfds))
	{		
		int newSockfd = acceptclient(serverfd);		
		char user[MAX_BUF];
		writeData1(newSockfd,buff );
		readData1(newSockfd, user);
		readData1(newSockfd, buff);
		cout<<user<<" is Registered"<<endl;
		cout<<"Checking if it is existing user"<<endl;
		//filehandling
		handleusers(user,buff);
			
		memset(buff,0,MAX_BUF);
		for(int i=0;i<max_clients;i++)
		{
			if(client_sock[i] == 0)
			{
				client_sock[i] = newSockfd;
				cout<<"Adding the client sockfds to the list"<<endl;
				vs_csock.push_back(newSockfd);
				break;
			}
		}
	}//end if fd_ISSET
}
void Server::handledisconnect()
{
	socklen_t len = sizeof(getClientAddr());
	uint16_t port;
	struct sockaddr_in* addressInternet;
	struct sockaddr_in address = getClientAddr();
	getpeername(sd,(struct sockaddr*)&address, &len);						
	cout<<"Client disconnected with IP: "<<inet_ntoa(address.sin_addr);
	cout<<" and with PortNO: "<<ntohs(address.sin_port)<<endl;
	cout<<"Closing Socket with port  "<<ntohs(address.sin_port)<<endl;
	close(sd);
	client_sock[i] = 0;
}
void Server::broadcast_msg()
{
	for(int i=0;(i<vs_csock.size())&&(client_sock[i] !=0 );i++)
	{
		int sock = client_sock[i];
		if(sock != sd && sock != serverfd && sock !=0)
		{
			char tbuff[MAX_BUF] = {'\0',};
			strcpy(tbuff, "Socket # ");
			string temp_str=to_string(sd); 
			strcat(tbuff,temp_str.c_str());
			strcat(tbuff,": ");
			strcat(tbuff,buff);
			strcat(tbuff,"\r\n");							
			write(sock, tbuff, strlen(tbuff));

		}
	}
}		

void Server :: serv_select(int port,string ip)
{
	for(int i=0;i<max_clients;i++)
	{
		client_sock[i] = 0;	
	}
	serverfd =getServSockfd();
	FD_ZERO(&master);
	while(true)
	{	
		//createfds	
		createfds();
		// for adding new client scket to set
		countclient();
		int socketCount = select(max_sd+1,&readfds,NULL,NULL,NULL);
		
		if((socketCount <0) && (errno != EINTR))
		{
			cout<<"select error"<<endl;
		}
		//check if fds are set
		checkfdset();	
		for(int i=0;i<max_clients;i++)
		{
			sd  = client_sock[i];
			if(FD_ISSET (sd, &readfds))
			{
				memset(buff,0,MAX_BUF);
				if((readVal = read(sd, buff,MAX_BUF)) == 0)
				{
					handledisconnect();	
			
					if(vs_csock.size()==1)
					{
						vs_csock.erase(vs_csock.begin());
					}
					else
					{
						vs_csock.erase(vs_csock.begin()+i);
					
					}
				}
				else
				{
				//broadcast message	
					broadcast_msg();
					memset(buff,0,MAX_BUF);
				}

			}
		}

		
	}// end of while loop
	
	servClose(getServSockfd());
}
