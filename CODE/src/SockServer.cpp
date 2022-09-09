#include <SockServer.h>
#include <details.h>
//Creation of Server Socket
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
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
}

//Bind the server to a port and listen to the clients
void Server::bind_listen()
{
	int retbind = bind(sockfd,(struct  sockaddr*)&server_addr,sizeof(server_addr));
	if(retbind<0)
	{
		perror("bind() error");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] Server bind to port no:"<<portno<<endl;
	if(listen(sockfd, 5)<0)
	{
		perror("listen() error");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] Server listening to the clients"<<endl;
}

//Server accepts the client
int Server::acceptclient(int sfd)
{
	len = sizeof(client_addr);
	newsockfd = accept(sfd, (struct sockaddr *)&client_addr, &len);
	if(newsockfd<0)
	{
		perror("accept() failed");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] Server accepts the client"<<endl;
	return newsockfd;
}

//close the server socket
void Server::servClose(int sfd)
{
	close(sfd);
}
//create fd sets
/*void Server::createfds()
{
	readfds = master;
	//max_sd = serverfd;
	//clear the sock set fds
	FD_ZERO(&readfds);
	FD_SET(serverfd,&readfds);
	max_sd = serverfd;
}

//check the number of clients connected and the maximum sockets created
*void Server::countclient()
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
}*/

//check if the fd is set
void Server::registeruser_login()
{
	details *d1=new details;
	details d2;
	int flag=0;
	//if(FD_ISSET(serverfd, &readfds))
	//{		
		int newSockfd = acceptclient(sockfd);	
		int recvopt=recv(newSockfd,buf,MAX_BUF,0);
		//check whether client wants to login or register
		switch(atoi(buf))
		{
			//register and login
			case 1:
				if(send(newSockfd,"register",9,0)<0)
				{
					perror("send() error");
					exit(EXIT_FAILURE);
				}
				bzero(d1,sizeof(details));
				recv(newSockfd,d1,sizeof(details),0);
				d1->database(d1);
				send(newSockfd,"success",8,0);			
				if((recv(newSockfd,buf,MAX_BUF,0))==atoi("2"))
				{
					send(newSockfd,"login",6,0);

					bzero(d1,sizeof(details));
					recv(newSockfd,d1,sizeof(details),0);
					fstream fs;
					string line;
					fs.open("registered.txt");
					if(fs.is_open())
					{
						while(!fs.eof())
						{
							size_t size=sizeof(details);	
							fs.read(reinterpret_cast<char*>(&d2),size);
							if((strcmp(d2.getUID(),d1->getUID()))==0)
							{
								if((strcmp(d2.getPassword(),d1->getPassword()))==0)
								{
								flag=1;
								break;
								}
							}
						}
						if(flag==1)
						{
						//	char uid[MAX_BUF];
							strcpy(uid,d1->getUID());
							string str = uid;
							send(newSockfd,"success",8,0);
							recvmessage(i);
						//	broadcast_msg(str);
							
							userids.push_back(str);
							//broadcast_msg();
							clientlist.push_back(newSockfd);
							FD_SET(newSockfd, &currentfd);
							broadcast_msg(userids[getindex(clientlist,i)]);
						/*	if(newSockfd>maxcli)
							       	maxcli = newSockfd;		*/

						}
						else
						{
							send(newSockfd,"failure",8,0);
						}
					}
					fs.close();
				}
				break;
			//login
			case 2:
				send(newSockfd,"login",8,0);
				bzero(d1,sizeof(details));
				recv(newSockfd,d1,sizeof(details),0);
				fstream fs;
				string line;
				fs.open("registered.txt");
				if(fs.is_open())
				{
					while(!fs.eof())
					{
						size_t size=sizeof(details);	
						fs.read(reinterpret_cast<char*>(&d2),size);
						if((strcmp(d2.getUID(),d1->getUID()))==0)
						{
							if((strcmp(d2.getPassword(),d1->getPassword()))==0)
							{
								flag=1;
								break;
							}
						}
					}
					if(flag==1)
					{

						send(newSockfd,"success",8,0);
						strcpy(uid,d1->getUID());
						string str = "userid ";
						//userid 12 sent : message
						userids.push_back(str);

						recvmessage(i);
						/*str.insert(7,uid);
						str.insert(str.length()," sent: ");
						str.insert(str.length(),buf);*/
						clientlist.push_back(newSockfd);
						FD_SET(newSockfd, &currentfd);
						broadcast_msg(userids[getindex(clientlist,i)]);
						
					}
					else
					{
						cout<<"[-] The User is not registered"<<endl;
						send(newSockfd,"failure",8,0);
					}
				}
				fs.close();
				
				break;
		}
}
int Server::getindex(vector<int> v, int K)
{
	   auto it = std::find(v.begin(), v.end(), K);
	   // calculating the index of K
	   int index = it - v.begin();
	   return index;
}
int Server:: recvmessage(int clientFd)
{
	   int flags = 0;
	   memset(&buf, 0, MAX_BUF);
	   int recvdata = recv(clientFd, &buf, MAX_BUF, flags);
	   //cout<<"received from client"<<buf<<endl;
	   return recvdata;
}
void Server::senddata(string str,int clientFd)
{
	char tbuff[MAX_BUF]={'\0',};
	strcpy(tbuff,str.c_str());
	strcpy(tbuff," sent");
	strcat(tbuff,": ");
	strcat(tbuff,buf);		
	write(clientFd,str.c_str(), str.length());
}
	
//handle the clients that are disconnected
void Server::handledisconnect()
{
	socklen_t len = sizeof(getClientAddr());
	uint16_t port;
	struct sockaddr_in address = getClientAddr();
	getpeername(sd,(struct sockaddr*)&address, &len);						
	cout<<"[+] Client disconnected with IP: "<<inet_ntoa(address.sin_addr);
	cout<<" and with port number: "<<ntohs(address.sin_port)<<endl;
	cout<<"[+] Closing Socket with port  "<<ntohs(address.sin_port)<<endl;
	close(sd);
	client_sock[i] = 0;
}
//broadcast the message sent by one client to all the active clients
void Server::broadcast_msg(string ids)
{
	for(int i=0;i<clientlist.size();i++)
	{
		if(i!=sockfd && (userids[i]!=ids))
		{
			senddata(ids,clientlist[i]);
		}
	}
}	
//checks if the socket is ready for reading or writing
void Server :: serv_select()
{
	fd_set currentfd,readfd;
	FD_ZERO(&currentfd);
	FD_SET(sockfd,&currentfd);
	while(true)
	{
		readfd=currentfd;
		if(select(FD_SETSIZE,&readfd,NULL,NULL,NULL)<0)
		{
			perror("select() error");
			exit(EXIT_FAILURE);
		}
		for(int i=0;i<max_clients;++i)
		{
			if(FD_ISSET(i,&readfd))
			{
					registeruser_login();

			}
		}

	}
	servClose(getServSockfd());

}













	
