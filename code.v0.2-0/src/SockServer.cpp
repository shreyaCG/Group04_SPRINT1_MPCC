#include <SockServer.h>
#include <details.h>

/*Creation of Server Socket using socket() system call and
error handling, if server socket is not created.
setsockopt() is used to connect multiple sockets of client.
Taking IP Address and Port Number through command line arguments.*/
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

/*Bind the server to a port using bind() and error handling if server 
is not binded to the port.
Server is waiting for the client connection
and error handling if server is not waiting for the clients.*/
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
void Server::createfds()
{
	readfds = master;
	//max_sd = serverfd;
	//clear the sock set fds
	FD_ZERO(&readfds);
	FD_SET(serverfd,&readfds);
	max_sd = serverfd;
}

//check the number of clients connected and the maximum sockets created
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

//check if the fd is set
void Server::registeruser_login(string &s,int &f)
{
	//details d1;
	//details d2;
	details *d1 = new details;
	char user_data[MAX_BUF] = {'\0',}; 
	int flag=0;
	char buf[MAX_BUF];
	if(FD_ISSET(serverfd, &readfds))
	{		
		int newSockfd = acceptclient(serverfd);	
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
				recv(newSockfd,&user_data,sizeof(user_data),0);
				cout<<user_data<<endl;
				//data = user_data;
				//d1.tokenid(data);
				d1->database(user_data);
				send(newSockfd,"success",8,0);
				break;
			//login
			case 2:
				send(newSockfd,"login",8,0);
				memset(user_data,0,sizeof(user_data));
				recv(newSockfd,&user_data,sizeof(user_data),0);
				//cout<<user_data<<endl;
				//data = user_data;
				//d1.tokenid(data);

				fstream fs;
				string line;
				fs.open("data/registered.txt");
				if(fs.is_open())
				{
					while(!fs.eof())
					{
						getline(fs,line);
						//size_t size=sizeof(details);	
						//fs.read(reinterpret_cast<*>(&d2),size);
						
						if((strcmp(user_data,line.c_str())==0))
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						//cout<<"[+] The user is registered"<<endl;
						//s=d1->getUID();
						string middle;
						vector<string> vstring;
        					stringstream check(user_data);
        					while(getline(check,middle,'|'))
        					{
                					vstring.push_back(middle);
        					}
						d1->setUID((char*)vstring[0].c_str());
						d1->setPassword((char*)vstring[1].c_str());
						f=1;
						send(newSockfd,"success",8,0);

					}
					else
					{
						//cout<<"[-] The User is not registered"<<endl;
						send(newSockfd,"failure",8,0);
					}
				}
				fs.close();
				
				break;
		}
		//add the clients connecting to the server in a vector
		for(int i=0;i<max_clients;i++)
		{
			if(client_sock[i] == 0)
			{
				client_sock[i] = newSockfd;
				cout<<"[+] Adding the client sockfds to the list"<<endl;
				strcpy(uids[i],d1->getUID());
				vs_csock.push_back(newSockfd);
				break;
			}
		}
	}//end if fd_ISSET
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
void Server::broadcast_msg(string uid)
{
	string UID;
	memset(&UID,0,MAX_BUF);
	
	for(int i=0;(i<vs_csock.size())&&(client_sock[i] !=0 );i++)
	{
		int sock=client_sock[i];
		if(sock==sd && sock!=serverfd && sock!=0)
		{
			UID=uids[i];
			break;
		}
	}


	for(int i=0;(i<vs_csock.size())&&(client_sock[i] !=0 );i++)
	{
		int sock = client_sock[i];
		
		if(sock != sd && sock != serverfd && sock !=0)
		{
			char tbuff[MAX_BUF] = {'\0',};
			strcpy(tbuff, "Message sent by ");
			strcat(tbuff,UID.c_str());
			strcat(tbuff,": ");
			strcat(tbuff,buff);
			strcat(tbuff,"\r\n");							
			write(sock, tbuff, strlen(tbuff));

		}
	}

}	
//checks if the socket is ready for reading or writing
void Server :: serv_select()
{
	string userid="";
	int f=0;
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
		//check if the socket is ready
		int socketCount = select(max_sd+1,&readfds,NULL,NULL,NULL);
		//check if fds are set
		registeruser_login(userid,f);
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
					broadcast_msg(userid);	
					memset(buff,0,MAX_BUF);
				}

			}
		}

	}// end of while loop
	servClose(getServSockfd());
}
