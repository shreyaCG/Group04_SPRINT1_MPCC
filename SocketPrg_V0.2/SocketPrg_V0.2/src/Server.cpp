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
void ServerSocket :: serv_accept()
{	
	ServerSocket *S = new ServerSocket(atoi(argv[2]), argv[1]);
	
	S->servConn();
	serverfd = S->getServSockfd();
	FD_ZERO(&master);
	

	while(true)
	{
		
		readfds = master;
		max_sd = serverfd;
		//clear the sock set fds
		FD_ZERO(&readfds);

		//add master_sock to be monitored
		FD_SET(serverfd,&readfds);

		max_sd = serverfd;

		// for adding childs socket to set
		for(int i=0;i<max_clients;i++)
		{
			sd = client_sock[i];

			//if valid socket desc... then add to readfds lists
			if(sd > 0)
				FD_SET(sd,&readfds);
			//highest fds number, need it for the select fucntion
			if(sd > max_sd)
				max_sd = sd;

		}




		int socketCount = select(max_sd+1,&readfds,NULL,NULL,NULL);
		
		if((socketCount <0) && (errno != EINTR))
		{
			cout<<"select error"<<endl;
		}
		if(FD_ISSET(serverfd, &readfds)){
			
			int newSockfd = S->servAccept(serverfd);
			

			writeData1(newSockfd, buff);

			cout<<"Sent the Welcome Message to the client"<<endl;
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

		for(int i=0;i<max_clients;i++)
		{
			sd  = client_sock[i];
			if(FD_ISSET (sd, &readfds))
			{
				memset(buff,0,MAX_BUF);
				if((readVal = read(sd, buff,MAX_BUF)) == 0)
				{
					socklen_t len = sizeof(S->getClientAddr());
			        uint16_t port;
			        struct sockaddr_in* addressInternet;
			        struct sockaddr_in address = S->getClientAddr();
					getpeername(sd,(struct sockaddr*)&address, &len);
						

					cout<<"Host disconnected with IP: "<<inet_ntoa(address.sin_addr);
					cout<<" and with PortNO: "<<ntohs(address.sin_port)<<endl;
					cout<<"Closing Socket: "<<sd<<endl;
					close(sd);
					client_sock[i] = 0;
					
					if(vs_csock.size()==1)
					{
							vs_csock.erase(vs_csock.begin());
					}
					else
						vs_csock.erase(vs_csock.begin()+i);
					//cout<<"Size: "<<vs_csock.size()<<endl;
					
				}
				else
				{
					
					for(int i=0;(i<vs_csock.size())&&(client_sock[i] !=0 );i++)
					{
						int outSock = client_sock[i];
						//cout<<"Client: "<<outSock<<endl;
						if(outSock != sd && outSock != serverfd && outSock !=0)
						{
							//ostringstream ss;
							//ss << "Socket # "<<sd<<": "<<buff<<"\r\n";
							char tbuff[MAX_BUF] = {'\0',};
							strcpy(tbuff, "Socket # ");
							string temp_str=to_string(sd); 
							strcat(tbuff,temp_str.c_str());
							strcat(tbuff,": ");
							strcat(tbuff,buff);
							strcat(tbuff,"\r\n");
							
							//string sbuff = ss.str();
							//strcpy(sbuff.c_str(),tbuff);
							write(outSock, tbuff, strlen(tbuff));

						}
					}
					memset(buff,0,MAX_BUF);
					// buff[readVal] = '\0';
					// send(sd, buff, strlen(buff),0);
				}
			}
		}

		

		
		
	}// end of while loop

	
	S->servClose(S->getServSockfd());
}
